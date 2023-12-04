#ifndef __RELAY_H
#define __RELAY_H

// 继电器触发电平  1高电平0低电平
// #define USE_Relay_Trigger_Level_Hight // 高电平触发继电器
// #define USE_Relay_Trigger_Level_Low   // 低电平触发继电器

// 如果没有定义 USE_Relay_Trigger_Level_Hight 并且 没有定义 USE_Relay_Trigger_Level_Low 则在里面定义某个宏
#if !defined(USE_Relay_Trigger_Level_Hight) && !defined(USE_Relay_Trigger_Level_Low)

#define USE_Relay_Trigger_Level_Hight  

#endif

// 全部继电器打开
#define __Relay_All_Open() do {	\
	Relay.Relay_Control(Relay_Left, RELAY_ON);	\
	Relay.Relay_Control(Relay_Right, RELAY_ON);	\
	Relay.Relay_Control(Relay_Body_White, RELAY_ON); \
	Relay.Relay_Control(Relay_Body_Yellow, RELAY_ON); \
} while (0)

// 全部继电器关闭
#define __Relay_All_Close() do {	\
	Relay.Relay_Control(Relay_Left, RELAY_OFF);	\
	Relay.Relay_Control(Relay_Right, RELAY_OFF);	\
	Relay.Relay_Control(Relay_Body_White, RELAY_OFF); \
	Relay.Relay_Control(Relay_Body_Yellow, RELAY_OFF); \
} while (0)


// 继电器状态枚举
typedef enum
{
    RELAY_ON = 0,   // 打开继电器
    RELAY_OFF = 1,  // 关闭继电器
} Relay_State_et; 

// 选择哪个继电器
typedef enum
{
    Relay_Left = 0x00,        // 左耳朵继电器
    Relay_Right = 0x01,       // 右耳朵继电器
    Relay_Body_White = 0x02,  // 白色灯继电器
    Relay_Body_Yellow = 0x03, // 黄色灯继电器
} Relay_Number_et;

typedef struct
{
    Relay_State_et Relay_Status[4]; // 继电器状态
    uint8_t Relay_Flip_Count;       // 继电器翻转计数
    uint8_t Relay_Left_Count;       // 左耳朵继电器计数
    uint8_t Relay_Right_Count;      // 右耳朵继电器计数
    uint8_t Relay_Flip_Flag;        // 继电器翻转标志位
    uint8_t Relay_Left_Flip_Flag;   // 左继电器翻转标志位
    uint8_t Relay_Right_Flip_Flag;  // 右继电器翻转标志位

    void (*Relay_Init)(void);                               // 继电器初始化
    void (*Relay_Control)(Relay_Number_et, Relay_State_et); // 继电器控制
    void (*Relay_Flip)(Relay_Number_et);                    // 继电器翻转
} Relay_st;

extern Relay_st Relay;

#endif
