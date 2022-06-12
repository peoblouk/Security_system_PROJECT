/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 24-05-2022 - 21:06:06
 * @modify date 24-05-2022 - 21:06:06
 * @desc [Simple keypad library]
 */

#include "keypad.h"

void init_keypad(void)
{
    // Řádky
    GPIO_Init(R1_PORT, R1_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_Init(R2_PORT, R2_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_Init(R3_PORT, R3_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
    GPIO_Init(R4_PORT, R4_PIN, GPIO_MODE_OUT_OD_HIZ_SLOW);
    // Sloupce
    GPIO_Init(C1_PORT, C1_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(C2_PORT, C2_PIN, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(C3_PORT, C3_PIN, GPIO_MODE_IN_PU_NO_IT);
}

uint8_t check_keypad(void)
{
    int key = 20; // Tato hodnota je naprosto náhodilá

    // první rádek
    ROW_ON(R1);
    if (COLUMN_GET(C1))
    {
        key = 1;
    }
    if (COLUMN_GET(C2))
    {
        key = 2;
    }
    if (COLUMN_GET(C3))
    {
        key = 3;
    }

    ROW_OFF(R1);

    // druhý řádek
    ROW_ON(R2);
    if (COLUMN_GET(C1))
    {
        key = 4;
    }
    if (COLUMN_GET(C2))
    {
        key = 5;
    }
    if (COLUMN_GET(C3))
    {
        key = 6;
    }

    ROW_OFF(R2);

    ROW_ON(R3);
    if (COLUMN_GET(C1))
    {
        key = 7;
    }
    if (COLUMN_GET(C2))
    {
        key = 8;
    }
    if (COLUMN_GET(C3))
    {
        key = 9;
    }
    ROW_OFF(R3);

    ROW_ON(R4);
    if (COLUMN_GET(C1))
    {
        key = 15;
    }
    if (COLUMN_GET(C2))
    {
        key = 0;
    }
    if (COLUMN_GET(C3))
    {
        key = 16;
    }
    ROW_OFF(R4);

    return key;
}

const Keypad_module keypad = {
    .init = init_keypad,
    .check = check_keypad,
};
/*****************************END OF FILE****/
