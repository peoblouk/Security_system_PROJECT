/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 31-05-2022 - 17:27:27
 * @modify date 31-05-2022 - 17:27:27
 * @desc [TM1637 Library]
 */
#include "stm8s_tm1637.h"

/* Private macro -------------------------------------------------------------*/
#define CLOCK_DELAY 0

#define LOW 0
#define HIGH 1

/* Private variables ---------------------------------------------------------*/
// Table which translates a digit into the segments
const uint8_t cDigit2Seg[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

// 0x80 - pomlčka

GPIO_Pin_TypeDef bClockPin, bDataPin;
GPIO_TypeDef *bClockPort, *bDataPort;

/* Private typedef -----------------------------------------------------------*/
/// Initialize tm1637 with the clock and data pins
int tm1637Init(GPIO_TypeDef *bClock, GPIO_Pin_TypeDef bClockP, GPIO_TypeDef *bData, GPIO_Pin_TypeDef bDataP)
{
    bClockPort = bClock;
    bDataPort = bData;
    bClockPin = bClockP;
    bDataPin = bDataP;
    GPIO_Init(bClockPort, bClockPin, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(bDataPort, bDataPin, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_WriteLow(bClockPort, bClockPin);
    GPIO_WriteLow(bDataPort, bDataPin);

    return 0;
}
/* Private functions ---------------------------------------------------------*/
/// Start wire transaction
void tm1637Start(void)
{
    GPIO_WriteHigh(bDataPort, bDataPin);
    GPIO_WriteHigh(bClockPort, bClockPin);
    delay.us(CLOCK_DELAY);
    GPIO_WriteLow(bDataPort, bDataPin);
}

/// Stop wire transaction
void tm1637Stop(void)
{
    // clock low
    GPIO_WriteLow(bClockPort, bClockPin);
    delay.us(CLOCK_DELAY);
    // data low
    GPIO_WriteLow(bDataPort, bDataPin);
    delay.us(CLOCK_DELAY);
    // clock high
    GPIO_WriteHigh(bClockPort, bClockPin);
    delay.us(CLOCK_DELAY);
    // data high
    GPIO_WriteHigh(bDataPort, bDataPin);
}

/// Get data ack
uint8_t tm1637GetAck(void)
{
    uint8_t bAck = 1;

    // read ack
    // clock to low
    GPIO_WriteLow(bClockPort, bClockPin);
    // data as input

    delay.us(CLOCK_DELAY);

    // clock high
    GPIO_WriteHigh(bClockPort, bClockPin);
    delay.us(CLOCK_DELAY);
    // clock to low
    GPIO_WriteLow(bClockPort, bClockPin);
    return bAck;
}

/// Write a unsigned char to the controller
void tm1637WriteByte(uint8_t b)
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        // clock low
        GPIO_WriteLow(bClockPort, bClockPin);
        // LSB to MSB
        if (b & 1)
            GPIO_WriteHigh(bDataPort, bDataPin);
        else
            GPIO_WriteLow(bDataPort, bDataPin);
        delay.us(CLOCK_DELAY);
        // clock high
        GPIO_WriteHigh(bClockPort, bClockPin);
        delay.us(CLOCK_DELAY);
        b >>= 1;
    }
}

/// Write a sequence of unsigned chars to the controller
void tm1637Write(uint8_t *pData, uint8_t bLen)
{
    uint8_t b, bAck;
    bAck = 1;
    tm1637Start();
    for (b = 0; b < bLen; b++)
    {
        tm1637WriteByte(pData[b]);
        bAck &= tm1637GetAck();
    }
    tm1637Stop();
}

/* Public functions ----------------------------------------------------------*/
/// Set brightness (0-8)
void tm1637SetBrightness(uint8_t b)
{
    uint8_t bControl;
    if (b == 0)
        // display off
        bControl = 0x80;
    else
    {
        if (b > 8)
            b = 8;
        bControl = 0x88 | (b - 1);
    }
    tm1637Write(&bControl, 1);
}

/// Display a string of 4 digits and optional colon
/// by passing a string such as "12:34" or "45 67" or "-- --"
void tm1637ShowDigits(char *pString)
{
    // commands and data to transmit
    uint8_t b, bTemp[16];
    uint8_t i, j;

    j = 0;
    // memory write command (auto increment mode)
    bTemp[0] = 0x40;
    tm1637Write(bTemp, 1);

    // set display address to first digit command
    bTemp[j++] = 0xc0;
    for (i = 0; i < 5; i++)
    {
        // position of the colon
        if (i == 2)
        {
            // turn on correct bit
            if (pString[i] == ':')
            {
                // second digit high bit controls colon LEDs
                bTemp[2] |= 0x80;
            }
        }
        else if (pString[i] == '-')
        {
            b = 0;
            b = cDigit2Seg[pString[i] & 0xf];
            bTemp[j++] = b;
        }
        else
        {
            b = 0;
            if (pString[i] >= '0' && pString[i] <= '9')
            {
                // segment data
                b = cDigit2Seg[pString[i] & 0xf];
            }
            bTemp[j++] = b;
        }
    }
    // send to the display
    tm1637Write(bTemp, j);
}

const TM1637_module tm1637 = {
    .init = tm1637Init,
    .brightness = tm1637SetBrightness,
    .show = tm1637ShowDigits,
};
/* -------------------------------------------------------------------------------------------*/

/**
 * @}
 */

/*****************************END OF FILE****/