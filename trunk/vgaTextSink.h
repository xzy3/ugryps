#ifndef VGATEXTSINK_H
#define VGATEXTSINK_H

#include "ktypes.h"

namespace kernel {

class vgaTextSink {
public:

	vgaTextSink();
	~vgaTextSink();

    //!@brief put the vga in 80x25 text mode
    void init();

	vgaTextSink& operator<< (char c);
	vgaTextSink& operator<< (sString string);
	vgaTextSink& operator<< (unsigned int i);
	void backspace();

	void setColor(char newColor);
	char getColor();

	bool scroll(unsigned short lines);
	void clear();

	bool putCursor(unsigned short pos);
	void putCursor(void);

private:

    //point to the begining of vga memory
	static char* const __vgaMemory;
	unsigned short	__offset;
	char __color;

    const static int LINE_CHARS;
    const static int MAX_CHARS;
}; //end class vgaTextSink

} //end namespace kernal

#endif
