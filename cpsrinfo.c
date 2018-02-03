/*
 Compile with `cc -O2 cpsrinfo.c -o cpsrinfo`
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpsrinfo.h"

#define status_str(x) ((x) ? "enabled" : "disabled")
#define set_str(x)    ((x) ? "set" : "clear")

const char *pmode_str(uint_least32_t cpsr)
{
    switch(cpsr & PMODE_MASK) {
        case PMODE_USR: return "User";
        case PMODE_FIQ: return "FIQ";
        case PMODE_IRQ: return "IRQ";
        case PMODE_SVC: return "Supervisor";
        case PMODE_ABT: return "Abort";
        case PMODE_UND: return "Undefined";
        case PMODE_SYS: return "System";
        default:        return "Unknown";
    }
}

const char *emode_str(uint_least32_t cpsr)
{
    switch(cpsr & EMODE_MASK) {
        case EMODE_ARM:     return "ARM";
        case EMODE_THUMB:   return "Thumb";
        case EMODE_JAZELLE: return "Jazelle";
        default:            return "Unknown";
    }
}

int main(int argc, char *argv[])
{
    uint_least32_t cpsr;
    if (argc < 2) {
        printf("Usage: %s CPSR\n", argv[0]);
        return EXIT_FAILURE;
    }

    cpsr = strtol(argv[1], NULL, 0L);
    printf("CPSR: 0x%08X\n", cpsr);
    printf("\n");

    printf("In %s mode\n", pmode_str(cpsr));
    printf("Executing %s code\n", emode_str(cpsr));
    printf("\n");

    printf("FIQs %s\n", status_str(!(cpsr & IFLAGS_FIQ)));
    printf("IRQs %s\n", status_str(!(cpsr & IFLAGS_IRQ)));
    printf("IMAs %s\n", status_str(!(cpsr & IFLAGS_IMP)));
    printf("\n");

    printf("oVerflow %s\n", set_str(cpsr & CFLAGS_V));
    printf("Carry    %s\n", set_str(cpsr & CFLAGS_C));
    printf("Zero     %s\n", set_str(cpsr & CFLAGS_Z));
    printf("Negative %s\n", set_str(cpsr & CFLAGS_N));
    printf("\n");

    printf("Endianness: %s\n", cpsr & OFLAGS_END ? "Big" : "Little");
    printf("ARMv5 Underlow/Saturation %s\n", set_str(cpsr & OFLAGS_Q));
    printf("\n");
    return EXIT_SUCCESS;
}
