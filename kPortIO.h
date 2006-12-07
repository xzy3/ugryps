#include "ktypes.h"



//functions to write to a dataport

static __inline__ void outb(kWord port, kByte value) {



	asm volatile("outb %0, %1"::"a"(value), "Nd" (port));



} //end outb



static __inline__ void outw(kWord port, kWord value) {



	asm volatile("outw %0, %1"::"a"(value), "Nd" (port));



} //end outw



static __inline__ void outl(kWord port, kDWord value) {



	asm volatile("outl %0, %1"::"a"(value), "Nd" (port));



} //end outl



//functions to read from a data port

static __inline__ kByte inb(kWord port) {



	kByte temp;

	asm volatile("inb %1, %0":"=a"(temp): "Nd" (port));

	return temp;



} //end inb



static __inline__ kWord inw(kWord port) {



	kWord temp;

	asm volatile("inw %1, %0":"=a"(temp): "Nd" (port));

	return temp;



} //end inw



static __inline__ kDWord inl(kWord port) {



	kDWord temp;

	asm volatile("inl %1, %0":"=a"(temp): "Nd" (port));

	return temp;



} //end inl



//delays so a piece of hardware can react to an command


static __inline__ void ioWait(void) {



	//port 0x80 is used for "checkpoints" during POST

	//the linux kernel seems to think its free for use

	outb(0x80, 0);



} //end ioWait
