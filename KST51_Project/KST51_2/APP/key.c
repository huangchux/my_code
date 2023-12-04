//#include "AllHead.h"

//u8 code KeyCodeMap[4][4] = { //矩阵按键编号到标准键盘键码的映射表
// { '1', '2', '3', 0x26 }, //数字键 1、数字键 2、数字键 3、向上键
// { '4', '5', '6', 0x25 }, //数字键 4、数字键 5、数字键 6、向左键
// { '7', '8', '9', 0x28 }, //数字键 7、数字键 8、数字键 9、向下键
// { '0', 0x1B, 0x0D, 0x27 } //数字键 0、ESC 键、 回车键、 向右键
//};
//u8 pdata Key_State[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};//按键当前状态
//	
///* 按键驱动函数，检测按键动作，调度相应动作函数，需在主循环中调用 */
//void Key_Driver()
//{
//	u8 i,j;
//	static u8 backup[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}}; //按键值备份，保存前一次的值
//	for(i = 0; i < 4; i++) //循环扫描 4*4 的矩阵按键
//	{
//		for(j = 0; j < 4; j++)
//		{
//			if(backup[i][j] != Key_State[i][j]) //当前值与前次值不相等说明此时按键有动作
//	    {
//		    if(backup[i][j] != 0)  //前次值不等于0，则当前值等于0，按键按下
//		    {
//			    Key_Action(KeyCodeMap[i][j]); //调用按键动作函数
//		    }
//		    backup[i][j] = Key_State[i][j]; //更新前一次的备份值
//	    } 
//		}
//	}
//}

///* 按键扫描函数，需在定时中断中调用 */
//void Key_Scan()
//{
//    u8 i = 0;
//    static u8 KeyOut = 0; //矩阵按键扫描输出索引
//    static u8 keybuf[4][4] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF},
//                              {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}
//    }; //矩阵按键扫描缓冲区
//    //将一行的 4 个按键值移入缓冲区
//    keybuf[KeyOut][0] = (keybuf[KeyOut][0] << 1) | KeyIn1;
//    keybuf[KeyOut][1] = (keybuf[KeyOut][1] << 1) | KeyIn2;
//    keybuf[KeyOut][2] = (keybuf[KeyOut][2] << 1) | KeyIn3;
//    keybuf[KeyOut][3] = (keybuf[KeyOut][3] << 1) | KeyIn4;
//    //消抖后更新按键状态
//    for (i = 0; i < 4; i++) //每行 4 个按键，所以循环 4 次
//    {
//        if (0x00 == (keybuf[KeyOut][i] & 0x0F))
//        {
//            //连续 4 次扫描值为 0，即 4*4ms 内都是按下状态时，可认为按键已稳定的按下
//            Key_State[KeyOut][i] = 0;
//        }
//        else if (0x0F == (keybuf[KeyOut][i] & 0x0F))
//        {
//            //连续 4 次扫描值为 1，即 4*4ms 内都是弹起状态时，可认为按键已稳定的弹起
//            Key_State[KeyOut][i] = 1;
//        }
//    }
//    //执行下一次的扫描输出
//    KeyOut++; //输出索引递增
//    if (KeyOut >= 4)
//    {
//        KeyOut = 0;
//    }
//    //	KeyOut = KeyOut & 0x03; //索引值加到 4 即归零
//    switch(KeyOut) //根据索引，释放当前输出引脚，拉低下次的输出引脚
//    {
//    case 0:
//        KeyOut4 = 1;
//        KeyOut1 = 0;
//        break;
//    case 1:
//        KeyOut1 = 1;
//        KeyOut2 = 0;
//        break;
//    case 2:
//        KeyOut2 = 1;
//        KeyOut3 = 0;
//        break;
//    case 3:
//        KeyOut3 = 1;
//        KeyOut4 = 0;
//        break;
//    default:
//        break;
//    }
//}