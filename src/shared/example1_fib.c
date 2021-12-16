#include <example.h>

long example1_fib(long x)
{
    long t1 = 0;
    long t2 = 1;
    long t3 = 0;

    switch (x)
    {
        case 0:
            return t1;

        case 1:
            return t2;

        default:
            for (long i = 1; i < x; ++i)
            {
                t3 = t1 + t2;
                t1 = t2;
                t2 = t3;
            }

            return t3;
    }
}

void example1_dummy()
{
}
