/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 24-05-2022 - 21:10:28
 * @modify date 24-05-2022 - 21:10:28
 * @desc [Simple keypad library]
 */

#include "stm8s.h"
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEYPAD_H__
#define __KEYPAD_H__

typedef struct
{
    void (*init)(void);
    uint8_t (*check)(void);

} Keypad_module;

// sloupce
#define C1_PORT GPIOD
#define C1_PIN PIN_4
#define C2_PORT GPIOB
#define C2_PIN PIN_7
#define C3_PORT GPIOF
#define C3_PIN PIN_6

// if you have 4x4 you can use this
//#define C4_PORT GPIOD
//#define C4_PIN  GPIO_PIN_1

// řádky
#define R1_PORT GPIOB
#define R1_PIN PIN_6
#define R2_PORT GPIOF
#define R2_PIN PIN_4
#define R3_PORT GPIOF
#define R3_PIN PIN_5
#define R4_PORT GPIOF
#define R4_PIN PIN_7

// aktivuje == uzemní řádek
#define ROW_ON(R) GPIO_WriteLow(R##_PORT, R##_PIN);
// deaktivuje řádek == přepne do stavu vysoké impedance
#define ROW_OFF(R) GPIO_WriteHigh(R##_PORT, R##_PIN);
// je tento sloupec přibitý k zemi?
#define COLUMN_GET(C) (GPIO_ReadInputPin(C##_PORT, C##_PIN) == RESET)

void init_keypad(void);
uint8_t check_keypad(void);
extern const Keypad_module keypad;

#endif /* __KEYPAD_H__*/