#pragma once

long example1_fib(long x)
    __attribute__ ((section ("example")))
    __attribute__ ((aligned (65536)));

void example1_dummy()
    __attribute__ ((section ("example2")))
    __attribute__ ((aligned (65536)));
