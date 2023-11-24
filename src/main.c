#include <stdio.h>

#include "../include/shiftrows.h"
#include "../include/encode.h"
#include "../include/keygen.h"
#include "../include/types.h"

void print_block(Block* block)
{
    for(int i = 0; i < 16; i++)
    {
        printf("%c, ", (*block)[i]);
    }
    printf("\n");
}

int main(void)
{
    Block* block = data_block128("1234123412341234", 16);
    
    Key128* key = (char*)"aaaaaaaaaaaaaaaa";
    Key128* key1 = (char*)"aaaaaaaaaaaaaaab";


    pipeline(block, key);
    print_block(block);
    reverse_pipeline(block, key);
    print_block(block);
    
    //key_pass128(block, key);
    //shift_rows128(block);
    //print_block(block);
    return 0;
}