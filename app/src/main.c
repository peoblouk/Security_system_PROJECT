/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 15-04-2022 - 16:46:28
 * @modify date 19-04-2022 - 19:24:41
 * @desc [description]
 */
/* -------------------------------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_milis.h"
#include "keypad.h"
#include "stm8s_tm1637.h"

#define port_led GPIOG
#define pin_green PIN_4
#define pin_red PIN_5

uint8_t key_now = 20;
uint8_t key_last = 20;
uint32_t mtime_key = 0;

uint8_t chyba = 0;
uint8_t spatne = 0;
int pozice = 0;
char initial_password[4] = {1, 2, 3, 4};
char password[4];

char szTemp[8];
char nula[8] = "00 00";

/* -------------------------------------------------------------------------------------------*/
/* void buzzer(uint32_t delka)
{
    for (int i = 500; i < delka; i++)
    {
        GPIO_WriteReverse(GPIOB, PIN_7);
        delay.us(i);
    }
} */
/* -------------------------------------------------------------------------------------------*/
void vymaz() // Vymaž
{
    pozice = -1;
    for (uint8_t i = 0; i < 4; i++)
    {
        password[i] = 0;
    }
    spatne = 0;
    GPIO_WriteLow(port_led, pin_green);
    GPIO_WriteHigh(port_led, pin_red);
    tm1637.show(nula);
}
/* -------------------------------------------------------------------------------------------*/
int main(void)
{
    tm1637.show(nula);
    GPIO_DeInit;
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);             // taktovat MCU na 16MHz
    Serial.begin(9600);                                        // Inicializace Serial monitoru
    milis.init();                                              // Initializace milis
    keypad.init();                                             // Initializace klávesnice
    GPIO_Init(port_led, pin_green, GPIO_MODE_OUT_PP_LOW_FAST); // LED Green
    GPIO_Init(port_led, pin_red, GPIO_MODE_OUT_PP_LOW_FAST);   // LED Red
    tm1637.init(GPIOG, PIN_2, GPIOG, PIN_3);                   // TM1637 inicializace
    tm1637.brightness(7);                                      // TM1637 brightness

    // GPIO_Init(GPIOB, PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);         // PB7 pin buzzer
    // GPIO_Init(GPIOC, PIN_5, GPIO_MODE_OUT_PP_HIGH_SLOW);        // PC5 LED (interní LED)
    printf("Proběhla incializace\n");
    /* ---------------------------------------------------------------------------------------*/
    while (1)
    {
        if (milis.get() - mtime_key > 55)
        {
            mtime_key = milis.get();  // milis now
            key_now = keypad.check(); // check keypad now
            if (key_last == 20 && key_now != 20)
            {
                // Proběhne mazání kódu při stisku *
                if (key_now == 15)
                {
                    vymaz();
                    printf("Deleted\n");
                }

                // Proběhne kontrola kódu při stisku #
                else if (key_now == 16)
                {
                    bool status = FALSE;

                    // Kontrola správného hesla
                    printf("Initial password: ");
                    for (int i = 0; i < 4; i++)
                    {
                        printf("%d", initial_password[i]);
                    }
                    // Vypiš zadané heslo uživateli
                    printf("\nYour password: ");
                    for (int i = 0; i < 4; i++)
                    {
                        printf("%d", password[i]);
                    }
                    /* */
                    // Kontrola shody hesla
                    for (int i = 0; i < 4; i++)
                    {
                        if (initial_password[i] != password[i])
                        {
                            status = FALSE;
                            spatne++;
                        }
                        else
                        {
                            status = TRUE;
                        }
                    }

                    if (status == TRUE && spatne == 0)
                    {
                        printf("\nWelcome in!\n");
                        GPIO_WriteLow(port_led, pin_red);
                        GPIO_WriteHigh(port_led, pin_green);
                        delay.ms(5000);
                    }
                    else
                    {
                        printf("\nIncorrect password!\n");
                        chyba++;
                    }

                    vymaz();
                }
                else
                {
                    // Vytiskni do SerialMonitoru *
                    if (key_now == 15)
                    {
                        printf("\nstisk *\n");
                    }
                    // Vytiskni do SerialMonitoru #
                    else if (key_now == 16)
                    {
                        printf("stisk #\n");
                    }
                    else
                    {
                        // Vytiskni aktuálně zmačknutou klávesu
                        printf("Klavesa: %d\n\r", key_now);
                        password[pozice] = key_now;
                        for (uint8_t i = 0; i < 4; i++)
                        {
                            printf("%d", password[i]);
                        }
                        sprintf(szTemp, "%d%d %d%d", password[0], password[1], password[2], password[3]);
                        tm1637.show(szTemp);
                        printf("\n");
                    }
                }
                pozice++;
                if (pozice == 5)
                {
                    pozice = 0;
                    vymaz();
                }
            }
            key_last = key_now; // Čas se stal minulostí
            GPIO_WriteLow(port_led, pin_green);
            GPIO_WriteHigh(port_led, pin_red);
        }
        if (chyba == 3)
        {
            // GPIO_WriteHigh(GPIO)
            chyba = 0;
        }
    }
    /* ---------------------------------------------------------------------------------------*/
}
/* -------------------------------------------------------------------------------------------*/