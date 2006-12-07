#include "vgaTextSink.h"
#include "ktypes.h"
#include "dataMacro.h"
#include "kPortIO.h"

using namespace kernel;

vgaTextSink::vgaTextSink() {

	//points to the begining of vga memory
	__vgaMemory = (char*)0xB8000;

	//offset into vga Memory
	__offset = 0;

	//the color of the text
	__color = 0x07;

	clear();

} //end constructor

vgaTextSink::~vgaTextSink() { }

vgaTextSink& vgaTextSink::operator<< (char c) {

	//move to the next line for a newline
	if(c == '\n')
		__offset += LINE_CHARS % __offset;

	else {
		//if the screen is full
		//scroll it up about half way
		if(__offset > MAX_CHARS)
			scroll(10);

		__vgaMemory[__offset] = c;
		__vgaMemory[__offset + 1] = __color;
		__offset += 2;

	} //end else

	return *this;

} //end operator<< ()

vgaTextSink& vgaTextSink::operator<< (sString string) {

	//loop through the string untill the null
	//zero outputing charicters to the screen
	for(int i = 0; string[i] != '\0'; i++)
		*this << string[i];

	return *this;

}//end operator<< ()

void vgaTextSink::backspace(void) {

	if(__offset > 0) {

		__offset-= 2;
		__vgaMemory[__offset] = ' ';
		__vgaMemory[__offset + 1] = 0x07;

	} //end if
} //end backspace

bool vgaTextSink::scroll(unsigned short lines) {

	if(lines > 25)
		return false;

	int src = lines * LINE_CHARS;
	int dest = 0;

	//copy the lines to scroll the screen up
	while(src < __offset) {

		__vgaMemory[dest]= __vgaMemory[src];
		src++;
		dest++;

	} //end while

	//clear the rest of the screen
	while(dest < MAX_CHARS) {

		__vgaMemory[dest] = ' ';
		__vgaMemory[dest + 1] = __color;
		dest += 2;

	} //end while

	return true;
} //end scroll()

void vgaTextSink::clear(void) {

	for(int i = 0; i < MAX_CHARS; i +=2) {

		__vgaMemory[i] = ' ';
		__vgaMemory[i + 1] = __color;

	} //end for

} //end clear()

//move the cursor to the absolute position
//on the screen
//pos must be [0, MAX_CHARS)
bool vgaTextSink::putCursor(unsigned short pos) { 

	if(pos >= MAX_CHARS)
		return false;

	__offset = pos * 2;

	//write the low byte of the value
	outb(0x3D4, 0x0F);

	outb(0x3D5, lowByte(pos));


	//write the high byte of the value

	outb(0x3D4, 0x0E);

	outb(0x3D5, highByte(pos));



	return true;

} //end putCursor

//set the color of the text
void vgaTextSink::setColor(char color) {

	__color = color;

} //end setColor()

//get the color value of the text
char vgaTextSink::getColor(void) {

	return __color;

} //end getColor

//move the cursor to the current value of __offset

void vgaTextSink::putCursor(void) {



	//write the low byte of the __offset

	outb(0x03D4, 0x0F);

	outb(0x03D5, lowByte(__offset));



	//write the high byte of the __offset

	outb(0x03D4, 0x0E);

	outb(0x03D5, highByte(__offset));



} //end putCursor
