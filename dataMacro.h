#ifndef DATAMACRO_H
#define DATAMACRO_H

#include "ktypes.h"

//returns the most significant byte in a two byte word
static __inline__ kByte highByte(kWord value) {

	return ((value >> 8) & 0xFF);

} //end highByte

//returns the least significant byte in a two byte word
static __inline__ kByte lowByte(kWord value) {

	return (value & 0xFF);

} //end lowByte

//returns the high word of a dword value
static __inline__ kWord highWord(kDWord value) {

	return (value & 0xFFFF);

} //end highWord

//returns the low word of a dword value
static __inline__ kWord lowWord(kDWord value) {

	return ((value >> 16) & 0xFFFF);

} //end lowWord

#endif
