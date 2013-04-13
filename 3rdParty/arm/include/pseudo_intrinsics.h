#ifndef PSEUDO_INTRINSICS_H_
#define PSEUDO_INTRINSICS_H_

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

void __WFI(void);

void __ISB(void);

void __DSB(void);

void __DMB(void);

int __MRS_control(void);

void __MSR_control(int control);

#endif /*PSEUDO_INTRINSICS_H_*/
