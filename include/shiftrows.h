#ifndef SHIFTROWS_H
#define SHIFTROWS_H

#include "types.h"

typedef byte BlockRow[4];
typedef byte Block[16];

dword wrapping_dword_shift_l(dword row, int amount);

// Performs the ShiftRows operation.
void shift_rows(Block* block);

// Reverses the ShiftRows operation.
void shift_rows_reverse(Block* block);

#endif