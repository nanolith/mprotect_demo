#include <example.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

extern void* __start_example;
extern void* __stop_example;

int main(int argc, char* argv[])
{
    pid_t child;
    child = fork();
    if (0 != child)
    {
        /* parent. */
        ptrdiff_t example_size =
            (ptrdiff_t)&__stop_example - (ptrdiff_t)&__start_example;
        printf("Address of example section: %lx\n", (ptrdiff_t)&__start_example);
        printf("Address of main           : %lx\n", (ptrdiff_t)&main);
        printf("Size of example section   : %ld\n", example_size);

        /* protect this section. */
        if (mprotect(&__start_example, example_size, PROT_NONE) < 0)
        {
            perror("mprotect");
        }

        /* wait on child to complete. */
        int status;
        if (waitpid(child, &status, 0) < 0)
        {
            perror("waitpid");
        }

        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
        {
            printf("child crashed.\n");
        }
        else if (WIFSIGNALED(status))
        {
            printf("child exited abnormally.\n");
        }
        else
        {
            printf("child exited normally.\n");
        }
    }
    else
    {
        /* child. */

        /* child has not been restricted. */
        for (long i = 0; i < 90; ++i)
        {
            printf("%ld: %ld\n", i, example1_fib(i));
        }
    }

    return 0;
}
