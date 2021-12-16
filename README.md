mprotect demo
=============

This is a simple demo of using mprotect along with some ELF section hackery on
BSD / Linux in order to allow a program to disable functions at runtime by
removing the execute bit from their segments.  This requires some mad hackery
and is probably not that portable.  Currently, this relies on the linker placing
two sections defined one right after another in sections that are one right
after the other as well as the runtime loader respecting these placements.

This is a proof of concept. When used in conjunction with OpenBSD pledge or
Linux seccomp to prevent mprotect from ever adding back execute bits to segments
in memory, this allows a program to disable functionality at runtime.

This is useful during privilege separation.  The process can not only shed
privileges via chroot, pledge, unveil, or loading a seccomp policy, but it can
also shed functions it will never call.  This shedding of functions can happen
at any time permissible by the OS and runtime.  So, for instance, config parsing
functions or API calls to other processes can be shed once they are no longer
needed. Any code paths that would call these function groups would cause the
application to crash instead of calling them, reducing the ability for a remote
attacker to "trick" software into calling functions it should not call.
