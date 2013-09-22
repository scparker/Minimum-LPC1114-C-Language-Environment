//  SYSCON Registers
int volatile *SYSPLLCTRL    = (int*)0x40048008;
int volatile *SYSPLLSTAT    = (int*)0x4004800C;
int volatile *SYSOSCCTRL    = (int*)0x40048020;
int volatile *SYSPLLCLKSEL  = (int*)0x40048040;
int volatile *SYSPLLCLKUEN  = (int*)0x40048044;
int volatile *MAINCLKSEL    = (int*)0x40048070;
int volatile *MAINCLKUEN    = (int*)0x40048074;
int volatile *SYSAHBCLKCTRL = (int*)0x40048080;
int volatile *UARTCLKDIV    = (int*)0x40048098;
int volatile *PDRUNCFG      = (int*)0x40048238;

//  GPIO Registers
int volatile *GPIO0DIR      = (int*)0x50008000;
int volatile *GPIO0DATA     = (int*)0x50003FFC;

//  IOCON
int volatile *IOCON_PIO0_2  = (int*)0x4004401C;

void SystemInit() 
{
  int i;

  *PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
  *SYSOSCCTRL    = 0x00000000;
  for (i = 0; i < 200; i++) asm("NOP");
  *SYSPLLCLKSEL  = 0x00000000;         /* Select PLL Input         */
  *SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  *SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
  *SYSPLLCLKUEN  = 0x01;
  while (!(*SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
  *SYSPLLCTRL    = 0x00000023;
  *PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
  while (!(*SYSPLLSTAT & 0x01));       /* Wait Until PLL Locked    */
  *MAINCLKSEL    = 0x00000003;         /* Select PLL Clock Output  */
  *MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  *MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  *MAINCLKUEN    = 0x01;
  while (!(*MAINCLKUEN & 0x01));       /* Wait Until Updated       */
}

void main()
{
  int i;

  //  Enable clocks on advanced high-performance bus
  *SYSAHBCLKCTRL = 0x3FFFF;

  *IOCON_PIO0_2 = 0x00;
  *GPIO0DIR= 0x04;

  while(1) {
    *GPIO0DATA = *GPIO0DATA | 0x04;
    for(i=0;i<1000000;i++) asm("NOP");
    *GPIO0DATA = *GPIO0DATA & ~(0x04);
    for(i=0;i<1000000;i++) asm("NOP");
    j++;
  }  
}
