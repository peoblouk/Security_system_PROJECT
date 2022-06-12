/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 17-05-2022 - 18:48:38
 * @modify date 17-05-2022 - 18:48:38
 * @desc [Milis function]
 */
#include "stm8s_milis.h"

// Tato knihovna je pro STM8S103
#if defined(STM8S208) || defined(STM8S103)
volatile uint16_t miliseconds = 0; // global variable storing milis value
/* -------------------------------------------------------------------------------------------*/
// return value of milisecond timestamp ("atomic" read)
uint16_t get_milis(void)
{
    uint16_t tmp;
    TIM3_ITConfig(TIM3_IT_UPDATE, DISABLE);
    tmp = miliseconds;
    TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);
    return tmp;
}
/* -------------------------------------------------------------------------------------------*/
// init TIM3 as source for milis interrupt (low priority)
void init_milis(void)
{
    TIM3_TimeBaseInit(PRESCALER, PERIOD); // (16MHz / 128) / 125 = 1000Hz
    TIM3_ClearFlag(TIM3_FLAG_UPDATE);
    TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);
    ITC_SetSoftwarePriority(ITC_IRQ_TIM3_OVF, ITC_PRIORITYLEVEL_1); // nÍzká priorita přerušení
    TIM3_Cmd(ENABLE);
    enableInterrupts();
}

// milis interrupt routine
INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
{
    TIM3_ClearFlag(TIM3_FLAG_UPDATE);
    miliseconds++;
}

const Milis_module milis = {
    .init = init_milis,
    .get = get_milis,
};
/* -------------------------------------------------------------------------------------------*/

#else
#warning "millis not defined for this platform !"
#endif
/*****************************END OF FILE****/
