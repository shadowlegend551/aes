#ifndef KEYGEN_H
#define KEYGEN_H

#include "types.h"

// Access keys as arrays of double words (4 bytes).
typedef byte Key128[16];
typedef Key128* Keychain128[11];

Keychain128* generate_round_keys128(Key128* initial_key);

#endif