/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 17-04-2022 - 11:43:25
 * @modify date 21-04-2022 - 07:31:15
 * @desc [4 digit segment display library]
 */

/* Includes ------------------------------------------------------------------*/
#include "stm8s_4segment.h"

/** @addtogroup STM8S_StdPeriph_Driver
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
 * @addtogroup HELPERS_Public_Functions
 * @{
 */

/* -------------------------------------------------------------------------------------------*/
//   0    1    2    3    4    5    6    7    8    9    -
// {192, 249, 164, 176, 153, 146, 130, 248, 128, 144, 255}; // numbers
char numbers[12] =
    {
        0b11000000, // 0
        0b11111001, // 1
        0b10100100, // 2
        0b10110000, // 3
        0b10011001, // 4
        0b10010010, // 5
        0b10000010, // 6
        0b11111000, // 7
        0b10000000, // 8
        0b10010000, // 9
        0b10111111, // -
        0b11111111  // NOTHING
};
// letters
char letters[12] = {
    163, // a (0)
    131, // b (1)
    167, // c (2)
    161, // d (3)
    6,   // E (4)
    14,  // F (5)
    11,  // h (6)
    27,  // n (7)
    243, // o (8)
    12,  // P (9)
    175, // r (10)
    255, // - (11)
};
/* -------------------------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------------------------*/
// display digits init
void display_init_dgt(GPIO_TypeDef *dgt_port, GPIO_Pin_TypeDef dgt_pins)
{
  GPIO_Init(dgt_port, dgt_pins, GPIO_MODE_OUT_PP_LOW_FAST);
}

// display segment init
void display_init_seg(GPIO_TypeDef *seg_port)
{
  GPIO_Init(seg_port, PIN_ALL, GPIO_MODE_OUT_PP_LOW_FAST);
}

char pin[4] = {PIN_7, PIN_6, PIN_5, PIN_4}; // array of digits
/* -------------------------------------------------------------------------------------------*/
// function to display number on 4 digit 7 segment
// you must enter Number, number lenght and place where you want dot
void display_num(uint32_t display, uint8_t number_lenght, uint8_t segment_dot)
{
  uint32_t temp1 = (display / 1000);       // thousands
  uint32_t temp2 = ((display / 100) % 10); // hundreds
  uint32_t temp3 = ((display / 10) % 10);  // tens
  uint32_t temp4 = (display % 10);         // unit

  char displayed_numbers[4] = {temp1, temp2, temp3, temp4}; // save variables to array

  for (uint8_t i = 0; i < number_lenght; i++)
  {
    GPIO_Write(GPIOB, numbers[displayed_numbers[i]]);
    if (i == segment_dot)
    {
      numbers[displayed_numbers[i]] += 0b01111111;
      GPIO_Write(GPIOB, numbers[displayed_numbers[i]]);
    }
    GPIO_WriteHigh(GPIOG, pin[i]);
    delay.us(10);
    GPIO_WriteLow(GPIOG, pin[i]);
  }
}

/* -------------------------------------------------------------------------------------------*/
// write letters
void display_let(uint32_t letter, uint8_t dgt) // functions for control each digit
{
  GPIO_Write(GPIOG, letters[letter]);
}
/* -------------------------------------------------------------------------------------------*/
// write on one digit
void display_dgt(bool value, uint8_t dgt) // functions for control each digit
{
  if (value == TRUE)
  {
    GPIO_WriteHigh(GPIOG, pin[dgt]); // on digit
  }

  else
  {
    GPIO_WriteLow(GPIOG, pin[dgt]); // off digit
  }
}

const Segment_module display = {
    .init_seg = display_init_seg,
    .init_dgt = display_init_dgt,
    .num = display_num,
    .let = display_let,
    .dgt = display_dgt,
};
/* -------------------------------------------------------------------------------------------*/

/**
 * @}
 */

/*****************************END OF FILE****/
