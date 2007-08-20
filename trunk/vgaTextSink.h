#ifndef TEXTSINK_H
#define TEXTSINK_H

#include "../ktypes.h"

namespace vga {

    enum vga_color {
        black = 0, blue = 1, green = 2, cyan = 3,
        red = 4, magenta = 5, brown = 6, 
        light_grey = 7, dark_grey = 8, 
        light_blue = 9, light_green = 10,
        light_cyan = 11, light_red = 12,
        light_magenta = 13, light_brown = 14,
        white = 15 };

    class setForeground {
    protected:
        vga_color color;

    public:

        setForeground(vga_color new_color) : color(new_color) { }

        friend class textSink;
    };

    class setBackground : public setForeground {
    public:

        setBackground(vga_color new_color) : setForeground(new_color) { }

        friend class textSink;
    };

    class textSink {
        public:

            textSink();
            ~textSink();

            textSink& operator<< (char c);
            textSink& operator<< (sString string);
            textSink& operator<< (kDWord i);

            //effectors
            textSink& operator<< (setBackground&);
            textSink& operator<< (setForeground&);
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
            static char* const vgaMemory;
            kWord  offset;

            kByte attribute;

            const static int LINE_CHARS;
            const static int MAX_CHARS;
    }; //end class textSink

} //end namespace vga

#endif
