
.equ REGSIZEBYTES,      4

.align 2                            // Align to 4(2^2) bytes boundary
.global function_name               // Emit functgion_name to symbol table (scope GLOBAL)
.type function_name, @function
function_name:
    # prologue (save three saved registers and the return address)
    addi sp, sp, -16                # Allocate the routine stack frame
    sw ra, 12(sp)                   # Save the return address
    sw fp, 8(sp)                    # Save the frame pointer
    sw s1, 4(sp)
    sw s2, 0(sp)
    addi fp, sp, 16                 # Set the framepointer


    // Put ypur code here. If you use saved regiasters other than s1, s2,
    // you should save them onto stack first!

    # epilogue (restore three saved registers and the return address):
    lw s2, 0(sp)
    lw s1, 4(sp)
    lw fp, 8(sp)                    # restore the frame pointer
    lw ra, 12(sp)                   # restore the return address from the stack frame
    addi sp, sp, 16                 # de-allocate the routine stack frame
    ret





.balign 4
.global _some_interrupt_handler
.type _some_interrupt_handler, @function     # Mark the symbol as being a function name
_some_interrupt_handler:

    # Prologue : save 16 ABI caller registers (ra, t0-t6, a0-a7)
    addi sp, sp, -16*REGSIZEBYTES   # Allocate the routine stack frame
    sw t0, 0*REGSIZEBYTES(sp)
    sw t1, 1*REGSIZEBYTES(sp)
    sw t2, 2*REGSIZEBYTES(sp)
    sw t3, 3*REGSIZEBYTES(sp)
    sw t4, 4*REGSIZEBYTES(sp)
    sw t5, 5*REGSIZEBYTES(sp)
    sw t6, 6*REGSIZEBYTES(sp)
    sw a0, 7*REGSIZEBYTES(sp)
    sw a1, 8*REGSIZEBYTES(sp)
    sw a2, 9*REGSIZEBYTES(sp)
    sw a3, 10*REGSIZEBYTES(sp)
    sw a4, 11*REGSIZEBYTES(sp)
    sw a5, 12*REGSIZEBYTES(sp)
    sw a6, 13*REGSIZEBYTES(sp)
    sw a7, 14*REGSIZEBYTES(sp)
    sw ra, 15*REGSIZEBYTES(sp)


    # Body:

    # epilogue: restore ABI caller regs
    lw t0, 0*REGSIZEBYTES(sp)
    lw t1, 1*REGSIZEBYTES(sp)
    lw t2, 2*REGSIZEBYTES(sp)
    lw t3, 3*REGSIZEBYTES(sp)
    lw t4, 4*REGSIZEBYTES(sp)
    lw t5, 5*REGSIZEBYTES(sp)
    lw t6, 6*REGSIZEBYTES(sp)
    lw a0, 7*REGSIZEBYTES(sp)
    lw a1, 8*REGSIZEBYTES(sp)
    lw a2, 9*REGSIZEBYTES(sp)
    lw a3, 10*REGSIZEBYTES(sp)
    lw a4, 11*REGSIZEBYTES(sp)
    lw a5, 12*REGSIZEBYTES(sp)
    lw a6, 13*REGSIZEBYTES(sp)
    lw a7, 14*REGSIZEBYTES(sp)
    lw ra, 15*REGSIZEBYTES(sp)
    addi sp, sp, 16*REGSIZEBYTES    # de-allocate the routine stack frame
    mret
