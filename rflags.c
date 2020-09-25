#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static char names[] = {
    "Carry", // 0
    "Reserved", // 1
    "Parity", // 2
    "Reserved", // 3
    "Adjust", // 4
    "Reserved", // 5
    "Zero", // 6
    "Sign", // 7
    "Trap", // 8
    "Interrupt Enable", // 9
    "Direction", // 10
    "Overflow", // 11
    "I/O Privilege Level", // 12-13
    NULL,
    "Nested Task", // 14
    "Reserved", // 15
    "Resume", // 16
    "V86 Mode", // 17
    "Alignment Check", // 18
    "Virtual Interrupt", // 19
    "Virtual Interrupt Pending", // 20
    "Can Use CPUID" // 21
};

static uint64_t rflags(void)
{
    uint64_t rflags;

    __asm__ (
        "pushfq;"
        "popq %%rax;"
        "movq %%rax, %0;"
        : "=r" (rflags) // Output
        :               // Input
        : "%rax" );     // Clobbered

    return rflags;
}

static void print(uint64_t rflags)
{
    int i;

    for (i = 0; i <= 21;) {
        printf("%s: ", names[i]);
        if (i != 12) {
            if ((rflags >> i) & 1) {
                puts("Set");
            } else {
                puts("Clear");
            }

            i++;
        } else {
            unsigned int val = (((rflags >> (i + 1)) & 1) << 1) | ((rflags >> i) & 1);
            printf("%s: %x\n", names[i], val);
            i += 2;
        }
    }
}

int main(void)
{
    uint64_t rf = rflags();
    printf("0x%llx\n", (unsigned long long) rf);
    print(rf);
    return 0;
}
