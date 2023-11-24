#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/keygen.h"
#include "../include/shiftrows.h"
#include "../include/tables.h"
#include "../include/types.h"

dword Rcon128[10] = 
    {0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,
     0x20000000,0x40000000,0x80000000,0x1b000000,0x36000000};


dword g(dword dw, int rc)
{
    byte* bp = &dw;
    
    dw = wrapping_dword_shift_l(dw, 1);

    bp[0] = sub_byte(bp[0]);
    bp[1] = sub_byte(bp[1]);
    bp[2] = sub_byte(bp[2]);
    bp[3] = sub_byte(bp[3]);

    dw = dw ^ Rcon128[rc];

    return dw;
}


Keychain128* generate_round_keys128(Key128* initial_key)
{
    // Iterates over key in 32bit chunks.
    dword* previous_key_dw_pointer = initial_key;
    dword* new_key_dw_pointer;
    Keychain128* keychain = malloc(sizeof(Keychain128));
    if(!keychain)
    {
        free(keychain);
        return NULL;
    }
    (*keychain)[0] = initial_key;


    Key128* previous_key = initial_key;
    Key128* new_key;
    dword g_dword;

    for(int i = 1; i < 11; i++)
    {
        new_key = malloc(sizeof(Key128));
        new_key_dw_pointer = new_key;
        if(!new_key)
        {
            free(new_key);
            return NULL;
        }

        new_key_dw_pointer[0] = previous_key_dw_pointer[0]
                                ^ g(previous_key_dw_pointer[3], i);

        new_key_dw_pointer[1] = new_key_dw_pointer[0]
                                ^ previous_key_dw_pointer[1];

        new_key_dw_pointer[2] = new_key_dw_pointer[1]
                                ^ previous_key_dw_pointer[2];

        new_key_dw_pointer[3] = new_key_dw_pointer[2]
                                ^ previous_key_dw_pointer[3];

        (*keychain)[i] = new_key;
        previous_key = new_key;
        previous_key_dw_pointer = previous_key;
    }

    return keychain;
}
