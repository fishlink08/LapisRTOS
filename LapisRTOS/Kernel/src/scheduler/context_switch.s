.syntax unified
.cpu cortex-m3
.thumb

.section .text


.global get_ptr
.type get_ptr, %function

get_ptr:
    mrs r0, psp // get current pointer at register 0
    bx lr // return to saved function address


.global set_ptr 
.type set_ptr, %function

set_ptr:
    msr psp, r0 // set ptr to register 0
    bx lr // return to saved function address (back to where the program counter was at)



.global SVCall_Handler
.type SVCall_Handler, %function

SVCall_Handler: // last step, returns control back to task using the program counter
    bl get_stack_first

    ldmia r0!, {r4-r11}

    msr psp, r0

    ldr lr, =0xFFFFFFFD 
    bx lr

.size SVCall_Handler, . - SVCall_Handler // pseudo-op code telling linker size of function


.global PendSV_Handler
.type PendSV_Handler, %function

PendSV_Handler:
    mrs r0, psp

    stmdb r0!, {r4-r11}
    msr psp, r0 
    push {lr}

    bl scheduler_pendsv

    pop {lr}
    mrs r0, psp

    ldmia r0!, {r4-r11}
    msr psp, r0

    bx lr

.size PendSV_Handler, . - PendSV_Handler