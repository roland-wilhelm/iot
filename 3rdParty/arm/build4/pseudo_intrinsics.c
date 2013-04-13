/* Small pieces of assembler that the compiler does not have an intrinsic for.
 * 
 * If kept to a single 32bit instruction or 1 or 2 16bit instructions then
 * the linker will be able to inline the instruction(s) in the space occupied 
 * by the 32bit BL that the compiler uses to call the function.
 * Must turn on inlining with --inline i.e.
 * 
 * armlink --inline ...
 * 
 */
 

__asm void __WFI(void)
{
    WFI
    BX r14
}


__asm void __ISB(void)
{
    ISB
    BX r14
}


__asm void __DSB(void)
{
    DSB
    BX r14
}


__asm void __DMB(void)
{
    DMB
    BX r14
}

__asm int __MRS_control(void)
{
    MRS r0,CONTROL
    BX lr
}

__asm void __MSR_control(int control)
{
    MSR CONTROL,r0
    BX lr
}
