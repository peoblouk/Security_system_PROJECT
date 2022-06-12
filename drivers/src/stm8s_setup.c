/**
 * @author [Matěj Křenek]
 * @github [https://github.com/peoblouk]
 * @create date 15-04-2022 - 22:56:55
 * @modify date 15-04-2022 - 22:56:55
 * @desc [To seperate void main(void)]
 */

/*------------------------------------*/
#include "stm8s_setup.h"

void main(void)
{
    setup();

    while (1)
    {
        loop();
    }
}
/*------------------------------------*/