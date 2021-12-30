#include<LPC214x.h>

void delay(unsigned int z);

void pll();

int main(void)
{
    IO0DIR=0xFFFFFFFF;
    IO1DIR = 0x0;                         
    pll();
	
    while(1) 
		{
      if((IO1PIN & (1<<16)) ==0)
        {           
					IO0SET=0x000000ff;
					delay(1000);            //1sec delay
					IO0CLR=0x000000ff;
					delay(1000);
        }
				
        if((IO1PIN & (1<<17)) ==0)
        {
					IO0SET=0x0000ff00;
					delay(500); 						//500msec delay
					IO0CLR=0x0000ff00;
					delay(500);
        }           
    }
}

void pll()                  //Foscillator=12Mhz,CpuCLK=60Mhz,PeripheralCLK=60MHz
{
    PLL0CON=0x01;	//PLLCON is one of the SFR's here we are Turning on the PLL(0x01)
    PLL0CFG=0x24;	//PLLCFG is used to set Multiplier and divider values (0to4bits for Multiplier) (5and6 bits for divider)
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;	//we are enabling and tuerning on the pll here
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01; //
}

void delay(unsigned int z)
{
    T0CTCR=0x0;                 //Select Timer Mode
    T0TCR=0x00;                 //Timer off (TCR-timer control register - enable 1 and disable 0)
    T0PR=59999;                 //Prescaler value for 1ms (formula based caluculation)
    T0TCR=0x02;                 //Timer reset
    T0TCR=0x01;                 //Timer ON
    while(T0TC<z);          
    T0TCR=0x00;                 //Timer OFF
    T0TC=0;                     //Clear the TC value.
}