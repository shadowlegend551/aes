#include "../include/shiftrows.h"
#include "../include/types.h"


// Didn't use bit shifts to preserve endianness agnosticity.
dword wrapping_dword_shift_l(dword dw, int amount)
{
    byte temp_byte;
    byte* bp = &dw;
    
    for(int i = 0; i < amount; i++)
    {
        temp_byte = bp[0];
        bp[0] = bp[1];
        bp[1] = bp[2];
        bp[2] = bp[3];
        bp[3] = temp_byte;
    }

    return dw;
}


dword wrapping_dword_shift_r(dword dw, int amount)
{
    byte* temp_byte;
    byte* bp = &dw;

    for(int i = 0; i < amount; i++)
    {
        temp_byte = bp[3];
        bp[3] = bp[2];
        bp[2] = bp[1];
        bp[1] = bp[0];
        bp[0] = temp_byte;
    }

    return dw;
}


void shift_rows(Block* block)
{
    // First row in block.
    dword* row = block[0];

    // First row stays as-is.

    row++;
    *row = wrapping_dword_shift_l(*row, 1);

    row++;
    *row = wrapping_dword_shift_l(*row, 2);

    // Shift fourth row to the left by 3.
    // Same as shifting to the right by one.
    row++;
    *row = wrapping_dword_shift_r(*row, 1);
}


void shift_rows_reverse(Block* block)
{
    // First row in block.
    dword* row = block[0];

    // First row stays as-is.

    row++;
    *row = wrapping_dword_shift_r(*row, 1);

    row++;
    *row = wrapping_dword_shift_r(*row, 2);

    // Shift fourth row to the right by 3.
    // Same as shifting to the left by one.
    row++;
    *row = wrapping_dword_shift_l(*row, 1);
}
