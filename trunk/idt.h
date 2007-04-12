#ifndef IDT_H
#define IDT_H

#include "kPortIO.h"
#include "ktypes.h"

namespace kernel {

    typedef void (*interrupt_handler) ();

    class idt {
        private:

            struct {

                kWord offset1;
                kWord selector;
                kWord unused:5;
                kWord zero:3;
                kWord pattern:5;
                kWord ring:2;
                kWord present:1;
                kWord offset2;

            } __attribute__ ((__packed__)) static table[256];

            const int count = 256;

        public:

            void load_idt(void);

            void install_interrupt(interrupt_handler pointer, )

    }; //end class idt

} //end namspace kernel

#endif
