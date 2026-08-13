#include <REGX52.H>
sbit LED = P2^0;
void DEALY(unsigned int x)
{
    while(x--);
}

void main ()
{
    unsigned char TIME,i;
    while(1)
    {
        for(TIME = 0;TIME <= 100;TIME++)
        {
            for(i = 0;i < 20;i++)
            {
                LED = 0;
                DEALY(TIME);
                LED = 1;
                DEALY(100 - TIME);
            }
        }
         for(TIME = 100;TIME > 0;TIME--)
        {
            for(i = 0;i < 20;i++)
            {
                LED = 0;
                DEALY(TIME);
                LED = 1;
                DEALY(100 - TIME);
            }
        }
    }

}