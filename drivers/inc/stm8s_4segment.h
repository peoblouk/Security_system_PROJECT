/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 24-05-2022 - 21:54:54
 * @modify date 24-05-2022 - 21:54:54
 * @desc [Milis function]
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __4SEGMENT_H
#define __4SEGMENT_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/

/** @addtogroup HELPERS_Exported_Types
 * @{
 */
typedef struct
{
  void (*init_seg)(GPIO_TypeDef *);
  void (*init_dgt)(GPIO_TypeDef *, GPIO_Pin_TypeDef);
  void (*num)(uint32_t, uint8_t, uint8_t);
  void (*let)(uint32_t, uint8_t);
  void (*dgt)(bool, uint8_t);
} Segment_module;
/**
 * @}
 */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup HELPERS_Exported_Constants
 * @{
 */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup HELPERS_Private_Macros
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup HELPERS_Exported_Functions
 * @{
 */
void display_init_seg(GPIO_TypeDef *seg_port);
void display_init_dgt(GPIO_TypeDef *dgt_port, GPIO_Pin_TypeDef dgt_pins);
void display_num(uint32_t display, uint8_t number_lenght, uint8_t segment_dot);
void display_let(uint32_t letter, uint8_t dgt);
void display_dgt(bool value, uint8_t dgt);
extern const Segment_module display;

/**
 * @}
 */

#endif /* __STM8S_4SEGMENT_H */
