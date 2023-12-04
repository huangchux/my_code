#ifndef __TASK_H
#define __TASK_H

typedef struct
{
    uint8_t Task_Status;     // 任务状态(TRUE/FALSE)
    uint16_t Task_cnt;       // 任务定时器计数器(ms)
    uint16_t Task_Timer;     // 重载值计数值(分配的时间)
    void (*Task_Hook)(void); // 任务函数
} Task_st;

extern Task_st Task[];
extern uint8_t ucTask_MAX;


#endif
