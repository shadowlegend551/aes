#ifndef SUBBYTES_H
#define SUBBYTES_H

#include "types.h"

typedef byte Block[16];

byte sub_byte(byte b);

// Performs the SubBytes operation.
void sub_bytes(Block* block);

// Reverses the SubBytes operation.
void sub_bytes_reverse(Block* block);

#endif