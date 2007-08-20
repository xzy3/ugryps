#include "vga/textSink.h"
#include "ktypes.h"
#include "dataMacro.h"
#include "kPortIO.h"

using namespace vga;

textSink::textSink() {

	//offset into vga Memory
	offset = 0;

	//the color of the text
    setTextColor(light_grey);
    setBackColor(black);

} //end constructor

textSink::~textSink() { }

textSink& textSink::operator<< (char c) {

	//move to the next line for a newline
	if(c == '\n')
		offset += offset % LINE_CHARS ;

	else if(c >= ' ') {
		//if the screen is full
		//scroll it up about half way
		if(offset > MAX_CHARS)
			scroll(10);

		vgaMemory[offset] = c;
		vgaMemory[offset + 1] = attribute;
		offset += 2;

	} //end else

	return *this;

} //end operator<< ()

textSink& textSink::operator<< (sString string) {

	//loop through the string untill the null
	//zero outputing charicters to the screen
	for(int i = 0; string[i] != '\0'; i++)
		*this << string[i];

	return *this;

}//end operator<< ()

void textSink::backspace(void) {

	if(offset > 0) {

		offset-= 2;
		vgaMemory[offset] = ' ';
		vgaMemory[offset + 1] = 0x07;

	} //end if
} //end backspace

bool textSink::scroll(unsigned short lines) {

	if(lines > 25)
		return false;

	int src = lines * LINE_CHARS;
	int dest = 0;

	//copy the lines to scroll the screen up
	while(src < offset) {

		vgaMemory[dest]= vgaMemory[src];
		src++;
		dest++;

	} //end while

	//clear the rest of the screen
	while(dest < MAX_CHARS) {

		vgaMemory[dest] = ' ';
		vgaMemory[dest + 1] = attribute;
		dest += 2;

	} //end while

	return true;
} //end scroll()

void textSink::clear(void) {

	for(int i = 0; i < MAX_CHARS; i +=2) {

		vgaMemory[i] = ' ';
		vgaMemory[i + 1] = attribute;

	} //end for

} //end clear()

//set the color of the text
void textSink::setTextColor(vga_color color) {

    attribute &= 0xF0;
	attribute |= color << 4;  

} //end setTextColor()

//get the color value of the text
vga_color textSink::getTextColor(void) {

	return (vga_color) (attribute >> 8);

} //end getTextColor

void textSink::setBackColor(vga_color color) {

    attribute &= 0xF;
    attribute |= color;

} //end setBackColor

vga_color textSink::getBackColor() {

    return (vga_color) (attribute & 0xF);

} //end getBackColor

//move the cursor to the absolute position
//on the screen
//pos must be [0, MAX_CHARS)
bool textSink::putCursor(kWord pos) { 

	if(pos >= MAX_CHARS)
		return false;

	offset = pos * 2;

	//write the low byte of the value
	outb(0x3D4, 0x0F);
	outb(0x3D5, lowByte(pos));

	//write the high byte of the value
	outb(0x3D4, 0x0E);
	outb(0x3D5, highByte(pos));

	return true;

} //end putCursor


//move the cursor to the current value of offset
void textSink::putCursor(void) {

    //write the low byte of the offset
    outb(0x03D4, 0x0F);
    outb(0x03D5, lowByte(offset));

	//write the high byte of the offset
	outb(0x03D4, 0x0E);
	outb(0x03D5, highByte(offset));

} //end putCursor

//point to the begining of vga memory
char* const textSink::vgaMemory = reinterpret_cast<char* const>(0xB8000);

const int textSink::LINE_CHARS = 160;
const int textSink::MAX_CHARS = 4000;

