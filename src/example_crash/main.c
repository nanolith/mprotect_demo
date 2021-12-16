#include <example.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

extern void* __start_example;
extern void* __stop_example;

int main(int argc, char* argv[])
{
    ptrdiff_t example_size =
        (ptrdiff_t)&__stop_example - (ptrdiff_t)&__start_example;
    printf("Address of example section: %lx\n", (ptrdiff_t)&__start_example);
    printf("Size of example section   : %ld\n", example_size);

    /* protect this section. */
    if (mprotect(&__start_example, example_size, PROT_NONE) < 0)
    {
        perror("mprotect");
    }

    for (long i = 0; i < 90; ++i)
    {
        printf(
            "%ld: %ld\n", i,
            /* this will crash due to mprotect above. */
            example1_fib(i));
    }
}
