#ifndef ENCODE_H
#define ENCODE_H

#include "types.h"

typedef byte Key128[16];
typedef Key128* Keychain128[11];
typedef byte Block[16];

Block* zeros_block128();

Block* data_block128(byte* data, int data_length);

byte galois256(byte b1, byte b2);

void key_pass128(Block* block, Key128* key);

void pipeline(Block* block, Key128* key);

#endif