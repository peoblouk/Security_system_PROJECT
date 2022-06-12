/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 17-05-2022 - 18:48:22
 * @modify date 17-05-2022 - 18:48:22
 * @desc [Milis function]
 */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef _MILIS_H_
#define _MILIS_H_ 1
/* Exported types ------------------------------------------------------------*/

/** @addtogroup HELPERS_Exported_Types
 * @{
 */
/* Includes ------------------------------------------------------------------*/
#include "stm8s_conf.h"

typedef struct
{
    uint16_t (*get)(void);
    void (*init)(void);
} Milis_module;

// configure PRESCALER and PERIOD according to your clock, to setup 1ms time base
#if F_CPU == 16000000
// varianta pro 16MHz
#define PRESCALER TIM4_PRESCALER_128
#define PERIOD (125 - 1)
#elif F_CPU == 2000000
// varianta pro 2MHz
#define PRESCALER TIM4_PRESCALER_16
#define PERIOD (125 - 1)
#else
#warning "milis timer parameters not defined for this clock !"
#endif
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
uint16_t get_milis(void);
void init_milis(void);
extern const Milis_module milis;

#endif
/*****************************END OF FILE****/