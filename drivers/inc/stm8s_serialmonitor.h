/**
 * @author [Matěj Křenek]
 * @github [https://github.com/peoblouk]
 * @create date 24-04-2022 - 22:02:19
 * @modify date 24-04-2022 - 22:02:19
 * @desc [Serial monitor]
 */
#ifndef __Serial_H
#define __Serial_H

typedef struct
{
    void (*begin)(uint32_t);
} Serial_Module;

void Serial_Begin(uint32_t BaudRate);
const extern Serial_Module Serial;

#endif