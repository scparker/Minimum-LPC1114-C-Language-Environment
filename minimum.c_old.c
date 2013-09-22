#include "LPC11xx.h"

void SystemInit() 
{
  uint32_t i;

  LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
  LPC_SYSCON->SYSOSCCTRL    = 0x00000000;
  for (i = 0; i < 200; i++) __NOP();
  LPC_SYSCON->SYSPLLCLKSEL  = 0x00000000;         /* Select PLL Input         */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
  LPC_SYSCON->SYSPLLCTRL    = 0x00000023;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));       /* Wait Until PLL Locked    */
  LPC_SYSCON->MAINCLKSEL    = 0x00000003;         /* Select PLL Clock Output  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
}

void main()
{
  int i;

  //  Enable clocks on advanced high-performance bus
  LPC_SYSCON->SYSAHBCLKCTRL = 0x3FFFF;

  LPC_IOCON->PIO0_2 = 0x00;
  LPC_GPIO0->DIR= 0x04;

  while(1) {
    LPC_GPIO0->DATA = LPC_GPIO0->DATA | 0x04;
    for(i=0;i<4800000;i++) __NOP();
    LPC_GPIO0->DATA = LPC_GPIO0->DATA & ~(0x04);
    for(i=0;i<4800000;i++) __NOP();
  }  
}
