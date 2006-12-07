#include "idt.h"
#include "stdlib.h"
#include "vgaTextSink.h"
#include "multiboot.h"

extern "C" int kmain(unsigned long, unsigned long);

int kmain(unsigned long magicNumber, unsigned long multiboot_info) {


	//test the charicter writer
	//kernel::kout << 'a' << 'b' << 'c' << 'd' << "efghijklmnopqrstuvwxyz";

	//kernel::kout << std::endl;



	//test the string writing funcion
	//kernel::kout << "Now ive sang my abc's next time wont you sing with me?";

	//kernel::kout << std::endl;


	idt_entry test = {1,2,3,4,5,6,7,8};

	//test the cursor mover
	//kernel::kout.putCursor(0);

	return 0;
} //end main
