/*uGryps is a hobby microkernel operating system.
 *Copyright (C) 2007 Seth Sims
 *
 *This program is free software; you can redistribute it and/or
 *modify it under the terms of the GNU General Public Licence
 *as published by the Free Software Foundation; either version 2
 *of the License, or (at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program; if not, write to the Free Software
 *Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "textSink.h"

using namespace vga;

textSink::textSink() { } //end constructor

textSink::textSink(vga_color fore, vga_color back) {

    setTextColor(fore);
    setBackColor(back);

} //end constructor

textSink::~textSink() { }

textSink& textSink::operator<< (char c) {

	//move to the next line for a newline
	if(c == '\n')
		offset += LINE_CHARS - offset % LINE_CHARS;

    else if(c == '\r')
        offset -= offset % LINE_CHARS;

	else if(c >= ' ') {
		//if the screen is full
		//scroll it up about half way
		if(offset > MAX_CHARS * 2 - 1)
            scroll(10);

		vgaMemory[offset] = c;
		vgaMemory[offset + 1] = attribute.value;
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

/*
textSink& textSink::operator<< (kByte b) {

    const char digits[] = "0123456789ABCDEF";

    *this << "0x";

    kByte temp = (b >> 4) & 0xF;
    *this << (char)(digits[temp]);

    temp = b & 0xF;
    *this << (char)(digits[temp]);

    return *this;
} //end operator<<

textSink& textSink::operator<< (kWord w) {
    
    const char digits[] = "0123456789ABCDEF";
    *this << "0x";

    kByte temp = (w >> 12) & 0xF;
    *this << (char)(digits[temp]);

    temp = (w >> 8) & 0xF;
    *this << (char)(digits[temp]);

    temp = (w >> 4) & 0xF;
    *this << (char)(digits[temp]);

    temp = w & 0xF;
    *this << (char)(digits[temp]);

    return *this;
} //end operator<<

textSink& textSink::operator<< (kDWord dw) {

    const char digits[] = "0123456789ABCDEF";
    *this << "0x";

    kByte temp = (dw >> 28) & 0xF;
    *this << (char)(digits[temp]);

    temp = (dw >> 24) & 0xF;
    *this << (char)(digits[temp]);

    temp = (dw >> 20) & 0xF;
    *this << (char)(digits[temp]);

    temp = (dw >> 16) & 0xF;
    *this << (char)(digits[temp]);

    temp = (dw >> 12) & 0xF;
    *this << (char)(digits[temp]);

    temp = (dw >> 8) & 0xF;
    *this << (char)(digits[temp]);

    temp = (dw >> 4) & 0xF;
    *this << (char)(digits[temp]);

    temp = dw & 0xF;
    *this << (char)(digits[temp]);

    return *this;
} //end operator<<
*/
   
textSink& textSink::operator<< (int i) {

    if(i < 0)
        *this << '-' << (unsigned int) -i;

    else 
        *this << (unsigned int) i;

    return *this; 
} //end operator<<

textSink& textSink::operator<< (unsigned int ui) {

    const char digits[] = "0123456789";
    const unsigned int maxDigits = 35;

    char buf[maxDigits];
   
    unsigned int value = ui;
    unsigned int i = 1;

    do {

        buf[maxDigits - i] = digits[value % 10];
        value /= 10;
        i++;

    } while(value > 0);

    for(;i > 0;i--) {

        *this << buf[maxDigits - i];

    } //end for

    return *this; 
} //end operator<<

textSink& textSink::operator<< (long l) {
    *this << (int)l;

    return *this;
} //end operator<<

textSink& textSink::operator<< (unsigned long ul) {
    *this << (unsigned int)ul;

    return *this;
} //end operator<<

textSink& textSink::operator<< (bool b) {

    if(b)
        *this << "true";
    else
        *this << "false";

    return *this;
} //end operator<<

textSink& textSink::operator<< (setBack color) {

    setBackColor(color.color);
    return *this;

} //end operator<< 

textSink& textSink::operator<< (setFore color) {

    setTextColor(color.color);
    return *this;

} //end operator<<

void textSink::backspace(void) {

	if(offset > 0) {

		offset-= 2;
		vgaMemory[offset] = ' ';
		vgaMemory[offset + 1] = attribute.value;

	} //end if
} //end backspace

bool textSink::scroll(unsigned short lines) {

	if(lines > 25)
		return false;

	int src = lines * LINE_CHARS;
	int dest = 0;

	//copy the lines to scroll the screen up
	while(src < offset + 1) {

		vgaMemory[dest]= vgaMemory[src];
		src++;
		dest++;

	} //end while

    //move one ahead so we are on a char boundry
    dest++;

	//clear the rest of the screen
	while(dest < MAX_CHARS) {

		vgaMemory[dest] = ' ';
		vgaMemory[dest + 1] = attribute.value;
		dest += 2;

	} //end while

	return true;
} //end scroll()

void textSink::clear(void) {

	for(int i = 0; i < MAX_CHARS; i += 2) {

		vgaMemory[i] = ' ';
		vgaMemory[i + 1] = attribute.value;

	} //end for

    offset = 0;

} //end clear()

//set the color of the text
void textSink::setBackColor(vga_color color) {

    attribute.colors.background = color;

} //end setTextColor()

//get the color value of the text
vga_color textSink::getBackColor(void) {

	return (vga_color) (attribute.colors.background);

} //end getTextColor

void textSink::setTextColor(vga_color color) {

    attribute.colors.foreground = color;

} //end setBackColor

vga_color textSink::getTextColor() {

    return (vga_color) (attribute.colors.foreground);

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
kByte* const textSink::vgaMemory = reinterpret_cast<kByte* const>(0xB8000);

kWord textSink::offset = 0;

const int textSink::LINE_CHARS = 160;
const int textSink::MAX_CHARS = 4000;

