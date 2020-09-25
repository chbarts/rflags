#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int main(void)
{
    printf("%llx\n", (unsigned long long) rflags());
    return 0;
}
