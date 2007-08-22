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

#ifndef TEXTSINK_H
#define TEXTSINK_H

#include "../ktypes.h"
#include "../dataMacro.h"
#include "../kPortIO.h"

namespace vga {

    enum vga_color {
        black = 0, blue = 1, green = 2, cyan = 3,
        red = 4, magenta = 5, brown = 6, 
        light_grey = 7, dark_grey = 8, 
        light_blue = 9, light_green = 10,
        light_cyan = 11, light_red = 12,
        light_magenta = 13, light_brown = 14,
        white = 15 };

    class setFore {
    protected:
        vga_color color;

    public:

        setFore(vga_color new_color) : color(new_color) { }

        friend class textSink;
    };

    class setBack: public setFore {
    public:

        setBack(vga_color new_color) : setFore(new_color) { }

        friend class textSink;
    };

    class textSink {
        public:

            textSink();
            textSink(vga_color fore, vga_color back);
            ~textSink();

            textSink& operator<< (char c);
            textSink& operator<< (sString string);
            
            textSink& operator<< (int i);
            textSink& operator<< (unsigned int ui);
            textSink& operator<< (long l);
            textSink& operator<< (unsigned long ul);
            textSink& operator<< (bool b);

            //effectors
            textSink& operator<< (setBack color);
            textSink& operator<< (setFore color);
            void backspace();

            void setTextColor(vga_color newColor);
            vga_color getTextColor();

            void setBackColor(vga_color newColor);
            vga_color getBackColor();

            bool scroll(kWord lines);
            void clear();

            bool putCursor(kWord pos);
            void putCursor(void);

        private:

            //point to the begining of vga memory
            static kByte* const vgaMemory;
            static kWord  offset;

            union {

                kByte value;
                struct {
                    kByte foreground:4;
                    kByte background:4;
                } __attribute__ ((__packed__)) colors;

            } attribute;

            //note these are actually twice the line chars and maxchars
            //because the chars and attributes are interleaved
            const static int LINE_CHARS;
            const static int MAX_CHARS;
    }; //end class textSink

} //end namespace vga

#endif
