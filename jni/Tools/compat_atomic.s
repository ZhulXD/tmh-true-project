    .syntax unified
    .arch armv7-a
    .text
    .align 2
    .global __sync_add_and_fetch_4
    .type __sync_add_and_fetch_4, %function
__sync_add_and_fetch_4:
.Ladd_loop:
    ldrex r2, [r0]
    add r2, r2, r1
    strex r3, r2, [r0]
    cmp r3, #0
    bne .Ladd_loop
    mov r0, r2
    bx lr

    .global __sync_sub_and_fetch_4
    .type __sync_sub_and_fetch_4, %function
__sync_sub_and_fetch_4:
.Lsub_loop:
    ldrex r2, [r0]
    sub r2, r2, r1
    strex r3, r2, [r0]
    cmp r3, #0
    bne .Lsub_loop
    mov r0, r2
    bx lr
