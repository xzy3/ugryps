#ifndef STDLIB_H
#define STDLIB_H

#include "vga/textSink.h"

namespace kernel {

	vga::textSink kout;

} //end namespace kernel

namespace std {

	const static char endl = '\n';

} //end namespace std
#endif
