#define  MMIO(addr) (*(volatile int*)addr)

//  SYSCON Registers
#define SYSAHBCLKCTRL  MMIO(0x40048080)

//  GPIO Registers
#define GPIO0DIR       MMIO(0x50008000)
#define GPIO0DATA      MMIO(0x50003FFC)

//  IOCON
#define IOCON_PIO0_2   MMIO(0x4004401C)

int main()
{
  int i;

  //  Enable clocks on advanced high-performance bus
  //  SYSCLK on IRC - for simplicity
  SYSAHBCLKCTRL = 0x3FFFF;

  //  Configure PIO0_2 as General Purpose IO
  IOCON_PIO0_2 = 0x00;

  //  Configure PIO0_2 as output
  GPIO0DIR= 0x04;

  while(1) {
    GPIO0DATA = GPIO0DATA | 0x04;       // Turn on
    for(i=0;i<1000000;i++) asm("NOP");  // Pause
    GPIO0DATA = GPIO0DATA & ~(0x04);    // Turn on
    for(i=0;i<1000000;i++) asm("NOP");  // Pause
  }  
}
