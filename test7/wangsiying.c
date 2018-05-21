#include "LPC11xx.h"                           
#define LED         (1ul << 0)
#define LEDOFF()    LPC_GPIO2->DATA |=  LED  
#define LEDON()     LPC_GPIO2->DATA &= ~LED  
//LED³õÊ¼»¯
void LedInit()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);      
    LPC_IOCON->PIO2_0 &= ~0x07;    
    LPC_IOCON->PIO2_0 |= 0x00;                           
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);     
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);          
    LPC_GPIO2->DIR |= LED;                                      
    LPC_GPIO2->DATA |= LED;                                   
}

void TIMER32_0_IRQHandler (void)
{
    LPC_TMR32B0->IR = 0x01;                               
    if (LPC_GPIO2->DATA & LED) 
    {
            LEDON();                                               
    } 
    else 
    {
            LEDOFF();                                                 
    }
}
void Timer0Init (void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 9); 
    LPC_TMR32B0->IR      = 0x01;
    LPC_TMR32B0->PR      = 0;                           
    LPC_TMR32B0->MCR     = 0x03;                   
    LPC_TMR32B0->MR0     = SystemCoreClock/2; 
    LPC_TMR32B0->TCR     = 0x01;                   
    NVIC_EnableIRQ(TIMER_32_0_IRQn);           
}
int main(void)
{
    LedInit();
    Timer0Init();
    while (1) ;
}