Cortex-M3 Application Note - Example Project Readme
---------------------------------------------------

This example project contains four builds showing the typical stages needed when 
developing an embedded Cortex-M3 application. These builds show how to migrate a
build from a simple application which sends output to the debugger console via
semihosting, to a fully retargeted build that uses a UART for output and
demonstrates the use of the SysTick interrupt and SVC calls.

Build 1 - Simple semihosted main() function, with a vector table that points to
          some dummy exception handlers.
Build 2 - Output is retargeted to use the UART.
Build 3 - This build demonstrates how to configure the NVIC, MPU and SysTick
          interrupt.
Build 4 - This build adds an SVC handler and modifies the main() function to use
          it. This allows the main application to use an SVC to generate non-
          interruptible output.
