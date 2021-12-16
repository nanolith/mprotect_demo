#pragma once

long example1_fib(long x)
    __attribute__ ((section ("example")))
    __attribute__ ((aligned (65536)));

#ifdef __OpenBSD__
extern char ch
    __attribute__ ((section (".plt")))
    __attribute__ ((aligned (65536)));
#endif
