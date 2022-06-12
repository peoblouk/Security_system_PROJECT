/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 31-05-2022 - 17:05:15
 * @modify date 31-05-2022 - 17:05:15
 * @desc [TM1637 Library]
 */
#ifndef __STM8S_TM1637_H
#define __STM8S_TM1637_H

#include "stm8s.h"
/* Exported functions ------------------------------------------------------- */

/** @addtogroup HELPERS_Exported_Functions
 * @{
 */
typedef struct
{
    int (*init)(GPIO_TypeDef *, GPIO_Pin_TypeDef, GPIO_TypeDef *, GPIO_Pin_TypeDef);
    void (*brightness)(uint8_t);
    void (*show)(char *);
} TM1637_module;
/**
 * @}
 */
int tm1637Init(GPIO_TypeDef *bClock, GPIO_Pin_TypeDef bClockP, GPIO_TypeDef *bData, GPIO_Pin_TypeDef bDataP);

/// <summary>
/// Start wire transaction
/// </summary>
void tm1637Start(void);

/// <summary>
/// Stop wire transaction
/// </summary>
void tm1637Stop(void);

/// <summary>
/// Get data acknowledgement
/// </summary>
uint8_t tm1637GetAck(void);

/// <summary>
/// Write a unsigned char to the controller
/// </summary>
void tm1637WriteByte(uint8_t b);

/// <summary>
/// Write a sequence of unsigned chars to the controller
/// </summary>
void tm1637Write(uint8_t *pData, uint8_t bLen);

/// <summary>
/// Set brightness (0-8)
/// </summary>
void tm1637SetBrightness(uint8_t b);

/// <summary>
/// Display a string of 4 digits and optional colon
/// by passing a string such as "12:34" or "45 67"
/// </summary>
void tm1637ShowDigits(char *pString);

extern const TM1637_module tm1637;

#endif /* __STM8S_TM1637_H */