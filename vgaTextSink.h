#ifndef VGATEXTSINK_H
#define VGATEXTSINK_H


#include "ktypes.h"

#define LINE_CHARS 160
#define MAX_CHARS 4000

namespace kernel {

class vgaTextSink {
public:

	vgaTextSink();
	~vgaTextSink();

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

	char* __vgaMemory;
	unsigned short	__offset;
	char __color;

}; //end class vgaTextSink

} //end namespace kernal

#endif
