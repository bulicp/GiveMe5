# ----------------------------------------------------------------------------
#
# CRS manipulation
#
# (c) Pa3cio, UL FRI
# 2023
# ----------------------------------------------------------------------------

.section .text

.option norvc       # disables the generation of compressed instructions.


.equ MSTATUS_MIE_BIT_MASK,  0x00000008  # bit 3
.equ MIE_MTIE_BIT_MASK,     0x00000080  # bit 7
.equ MIE_MEIE_BIT_MASK,     0x00000800  # bit 11



/*---------------------------------------
    Register the base address for vector table in mtvec

    # a0 - interrupt vector table base address
    # a1 - interrupt processing mode (0x0 - direct, 0x1 - vectored)
---------------------------------------*/
.balign 4
.global register_handler
.type register_handler, @function
register_handler:
    # prologue (save three saved registers and the return address)
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

    or a0, a0, a1                   # OR base address with mode
    csrw mtvec, a0                  # and save into mtvec

    # epilogue (restore three saved registers and the return address):
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret





/*---------------------------------------
    Enable global interrupts in mstatus

---------------------------------------*/
.balign 4
.global enable_global_interrupts
.type enable_global_interrupts, @function
enable_global_interrupts:
    # prologue (save three saved registers and the return address)
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

    li t0, MSTATUS_MIE_BIT_MASK     # load the mask for MIE
    csrs mstatus, t0                #  set the MIE bit in mstatus

    # epilogue (restore three saved registers and the return address):
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret



/*---------------------------------------
    Enable machine timer interrupt in mie

---------------------------------------*/

.balign 4
.global enable_mtimer_interrupt
.type enable_mtimer_interrupt, @function
enable_mtimer_interrupt:
    # prologue (save three saved registers and the return address)
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

    li t0, MIE_MTIE_BIT_MASK
    csrs mie, t0

    # epilogue (restore three saved registers and the return address):
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret



/*---------------------------------------
    Enable machine external interrupt in mie

---------------------------------------*/

.balign 4
.global enable_mexternal_interrupt
.type enable_mexternal_interrupt, @function
enable_mexternal_interrupt:
    # prologue (save three saved registers and the return address)
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer

    li t0, MIE_MEIE_BIT_MASK
    csrs mie, t0

    # epilogue (restore three saved registers and the return address):
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret
