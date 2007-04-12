#include "idt.h"

using namespace kernel;

void idt::load_idt(void) {

    struct {

        kDWord base;
        kWord limit;
        kWord unused;

    } __attribute__ ((__packed__)) ptr;

    ptr.base = reinterpret_cast<kDWord>(table);
    ptr.limit = count & 0xFE;
    ptr.unused = 0;

    asm("lidt (%0)": :"p" (&ptr));
} //end load_idt
