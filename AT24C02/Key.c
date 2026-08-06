#include <REGX52.H>
#include "Delay.h"
unsigned char KEYNUM = 0;
unsigned char Key_GetState(void)
{
    unsigned char KeyNum = 0;
    if(P3_1==0)
    {
        KeyNum = 1;
    }
     if(P3_0==0)
    {
        KeyNum = 2;
    }
     if(P3_2==0)
    {
        KeyNum = 3;
    }
     if(P3_3==0)
    {
        KeyNum = 4;
    }
    return KeyNum;
}

void Key_Loop(void)
{
    unsigned char KeyNum_Last = 0;
    static unsigned char KeyNum_Now = 0;
    KeyNum_Last = KeyNum_Now;

    KeyNum_Now = Key_GetState();
    if(KeyNum_Last == 1 && KeyNum_Now == 0)
    {
        KEYNUM = 1;
    }
    if(KeyNum_Last == 2 && KeyNum_Now == 0)
    {
        KEYNUM = 2;
    }
    if(KeyNum_Last == 3 && KeyNum_Now == 0)
    {
        KEYNUM = 3;
    }
    if(KeyNum_Last == 4 && KeyNum_Now == 0)
    {
        KEYNUM = 4;
    }
}
unsigned char KEY(void)
{
    unsigned char Temp = 0;
    Temp = KEYNUM;
    KEYNUM = 0;
    return Temp;
}