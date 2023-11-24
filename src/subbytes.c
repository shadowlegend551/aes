#include "subbytes.h"
#include "tables.h"
#include "types.h"

byte sub_byte(byte b)
{
    // Erase first nibble.
    byte x_index = b & 0x0f;

    // Shift first nibble to be the second one.
    byte y_index = b >> 4;

    return sbox[y_index][x_index];
}


byte sub_byte_reverse(byte b)
{
    byte x_index = b & 0x0f;
    byte y_index = b >> 4;

    return sbox_reverse[y_index][x_index];
}


void sub_bytes(Block* block)
{
    int BLOCK_BYTE_SIZE = 16;
    byte* block_iterator = block;

    for(int i = 0; i < BLOCK_BYTE_SIZE; i++)
    {
        *block_iterator = sub_byte(*block_iterator);
        block_iterator++;
    }
}


void sub_bytes_reverse(Block* block)
{
    int BLOCK_BYTE_SIZE = 16;
    byte* block_iterator = block;

    for(int i = 0; i < BLOCK_BYTE_SIZE; i++)
    {
        *block_iterator = sub_byte_reverse(*block_iterator);
        block_iterator++;
    }
}