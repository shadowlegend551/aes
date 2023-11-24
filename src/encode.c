#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "keygen.h"
#include "shiftrows.h"
#include "subbytes.h"
#include "tables.h"
#include "types.h"


// Returns a block initialized to zeroes.
Block* zeros_block128()
{
    Block* zeros_block = malloc(sizeof(Block));
    
    for(int i = 0; i < 128; i++)
    {
        *zeros_block[i] = (byte)0;
    }

    return zeros_block;
}


// Returns a block initialized to a maximum of 16 bytes of data.
Block* data_block128(byte* data, int data_length)
{
    Block* block = malloc(sizeof(Block));

    data_length = (data_length > 16) ? 16 : data_length;

    for(int i = 0; i < data_length; i++)
    {
        (*block)[i] = data[i];
    }

    return block;
}


byte galois256(byte b1, byte b2)
{
    word result = 0x00;
    word w1 = (word)b1;
    word w2 = (word)b2;

    for(int i = 0; i < 8; i++)
    {
        if(w2 & 0x01)
            result ^= w1;

        w1 <<= 1;

        if(w1 & 0x100)
            w1 ^= 0x11b;

        w2 >>= 1;
    }

    return (byte)result;
}


void key_pass128(Block* block, Key128* key)
{
    for(int i = 0; i < 16; i++)
    {
        (*block)[i] = (*block)[i] ^ (*key)[i];
    }
}


void pipeline(Block* block, Key128* key)
{
    Keychain128* kc = generate_round_keys128(key);
    
    key_pass128(block, (*kc)[0]);
    
    for(int i = 1; i < 11; i++)
    {
        sub_bytes(block);
        shift_rows(block);
        key_pass128(block, (*kc)[i]);
    }
}

void reverse_pipeline(Block* block, Key128* key)
{
    Keychain128* kc = generate_round_keys128(key);
    
    for(int i = 10; i > 0; i--)
    {
        key_pass128(block, (*kc)[i]);
        shift_rows_reverse(block);
        sub_bytes_reverse(block);
    }

    key_pass128(block, (*kc)[0]);
}
