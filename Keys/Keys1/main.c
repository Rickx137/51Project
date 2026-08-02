#include <REGX52.H>
#include <Delay.h>
#include <Leds.h>
#include <Keys.h>
void main()
{
	unsigned char i = 0;
	unsigned char Location = 1;
	unsigned char Num = 0;
	unsigned char Data[9] = {255,255,255,255,255,255,255,255,255};
	while(1)
	{
		Num = Keys();
		if(Num >= 0 && Num <= 9)
		{
			Data[Location] = Num;
			Location++;
			if(Location > 8)
				Location = 1;
			
		}	
		
		else if(Num == 16)
		{
			for (i = 1;i <= 8;i++)
			{
				Data[i] = 255;
			}
				Location = 1;
		}
		for (i = 1;i <= 8;i++)
			{
				Leds(i,Data[i]);
			}
	}
}