#include "vgaTextSink.h"
#include "ktypes.h"
#include "dataMacro.h"
#include "kPortIO.h"

using namespace kernel;

vgaTextSink::vgaTextSink() {

	//offset into vga Memory
	__offset = 0;

	//the color of the text
	__color = 0x07;

} //end constructor

vgaTextSink::~vgaTextSink() { }

void vgaTextSink::init() {

    //misc register
    outb(0x3C2, 0x67);
    ioWait();

    //CRTC
    outb(0x3D4, 0x00);  outb(0x3D5, 0x5F);
    outb(0x3D4, 0x01);  outb(0x3D5, 0x4F);
    outb(0x3D4, 0x02);  outb(0x3D5, 0x50);
    outb(0x3D4, 0x03);  outb(0x3D5, 0x82);
    outb(0x3D4, 0x04);  outb(0x3D5, 0x55);
    outb(0x3D4, 0x05);  outb(0x3D5, 0x81);
    outb(0x3D4, 0x06);  outb(0x3D5, 0xBF);
    outb(0x3D4, 0x07);  outb(0x3D5, 0x1F);
    outb(0x3D4, 0x08);  outb(0x3D5, 0x00);
    outb(0x3D4, 0x09);  outb(0x3D5, 0x4F);
    outb(0x3D4, 0x10);  outb(0x3D5, 0x0D);
    outb(0x3D4, 0x11);  outb(0x3D5, 0x0E);
    outb(0x3D4, 0x12);  outb(0x3D5, 0x00);
    outb(0x3D4, 0x13);  outb(0x3D5, 0x00);
    outb(0x3D4, 0x14);  outb(0x3D5, 0x00);
    outb(0x3D4, 0x15);  outb(0x3D5, 0x50);
    outb(0x3D4, 0x16);  outb(0x3D5, 0x9C);
    outb(0x3D4, 0x17);  outb(0x3D5, 0x0E);
    outb(0x3D4, 0x18);  outb(0x3D5, 0x8F);
    outb(0x3D4, 0x19);  outb(0x3D5, 0x28);
    outb(0x3D4, 0x20);  outb(0x3D5, 0x1F);
    outb(0x3D4, 0x21);  outb(0x3D5, 0x96);
    outb(0x3D4, 0x22);  outb(0x3D5, 0xB9);
    outb(0x3D4, 0x23);  outb(0x3D5, 0xA3);
    outb(0x3D4, 0x24);  outb(0x3D5, 0xFF);

    //sequencer register
    outb(0x3C4, 0x00);  outb(0x3C5, 0x03);
    outb(0x3C4, 0x01);  outb(0x3C5, 0x00);
    outb(0x3C4, 0x02);  outb(0x3C5, 0x03);
    outb(0x3C4, 0x03);  outb(0x3C5, 0x00);
    outb(0x3C4, 0x04);  outb(0x3C5, 0x02);

    //GC
    outb(0x3CE, 0x00);  outb(0x3CF, 0x00);
    outb(0x3CE, 0x01);  outb(0x3CF, 0x00);
    outb(0x3CE, 0x02);  outb(0x3CF, 0x00);
    outb(0x3CE, 0x03);  outb(0x3CF, 0x00);
    outb(0x3CE, 0x04);  outb(0x3CF, 0x00);
    outb(0x3CE, 0x05);  outb(0x3CF, 0x10);
    outb(0x3CE, 0x06);  outb(0x3CF, 0x0E);
    outb(0x3CE, 0x07);  outb(0x3CF, 0x00);
    outb(0x3CE, 0x08);  outb(0x3CF, 0xFF);

    //AC
    inb(0x3DA); outb(0x3C0, 0x00); outb(0x3C0, 0x00);
    inb(0x3DA); outb(0x3C0, 0x01); outb(0x3C0, 0x01);
    inb(0x3DA); outb(0x3C0, 0x02); outb(0x3C0, 0x02);
    inb(0x3DA); outb(0x3C0, 0x03); outb(0x3C0, 0x03);
    inb(0x3DA); outb(0x3C0, 0x04); outb(0x3C0, 0x04);
    inb(0x3DA); outb(0x3C0, 0x05); outb(0x3C0, 0x05);
    inb(0x3DA); outb(0x3C0, 0x06); outb(0x3C0, 0x14);
    inb(0x3DA); outb(0x3C0, 0x07); outb(0x3C0, 0x07);
    inb(0x3DA); outb(0x3C0, 0x08); outb(0x3C0, 0x38);
    inb(0x3DA); outb(0x3C0, 0x09); outb(0x3C0, 0x39);
    inb(0x3DA); outb(0x3C0, 0x10); outb(0x3C0, 0x3A);
    inb(0x3DA); outb(0x3C0, 0x11); outb(0x3C0, 0x3B);
    inb(0x3DA); outb(0x3C0, 0x12); outb(0x3C0, 0x3C);
    inb(0x3DA); outb(0x3C0, 0x13); outb(0x3C0, 0x3D);
    inb(0x3DA); outb(0x3C0, 0x14); outb(0x3C0, 0x3E);
    inb(0x3DA); outb(0x3C0, 0x15); outb(0x3C0, 0x3F);
    inb(0x3DA); outb(0x3C0, 0x16); outb(0x3C0, 0x0C);
    inb(0x3DA); outb(0x3C0, 0x17); outb(0x3C0, 0x00);
    inb(0x3DA); outb(0x3C0, 0x18); outb(0x3C0, 0x0F);
    inb(0x3DA); outb(0x3C0, 0x19); outb(0x3C0, 0x08);
    inb(0x3DA); outb(0x3C0, 0x20); outb(0x3C0, 0x00);

}

vgaTextSink& vgaTextSink::operator<< (char c) {

	//move to the next line for a newline
	if(c == '\n')
		__offset += LINE_CHARS % __offset;

	else if(c >= ' ') {
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

//point to the begining of vga memory
char* const vgaTextSink::__vgaMemory = reinterpret_cast<char* const>(0xB8000);

const int vgaTextSink::LINE_CHARS = 160;
const int vgaTextSink::MAX_CHARS = 4000;

