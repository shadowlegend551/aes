#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "iolib.h"

char* readstdinline(void)
{
    int buffer_size = 128;
    char* buffer = malloc(buffer_size);
    if(!buffer) { return NULL; }

    int write_offset = 0;
    char character;
    char* realloc_holder;

    while(1)
    {
        if((read(STDIN_FILENO, &character, 1)) == -1)
        {
            free(buffer);
            return NULL;
        }

        if(character == '\n')
        {
            break;
        }

        if(write_offset == buffer_size)
        {
            buffer_size *= 2;
            realloc_holder = realloc(buffer, buffer_size);
            if(!realloc_holder)
            {
                free(buffer);
                return NULL;
            }
            buffer = realloc_holder;
        }

        buffer[write_offset] = character;
        write_offset++;
    }

    realloc_holder = realloc(buffer, write_offset+1);
    if(!realloc_holder)
    {
        free(buffer);
        return NULL;
    }

    buffer = realloc_holder;
    buffer[write_offset] = '\0';

    return buffer;
}


char* readstdinuntil(char TERMINATING_CHARACTER)
{
    int buffer_size = 128;
    char* buffer = malloc(buffer_size);
    if(!buffer) { return NULL; }

    int write_offset = 0;
    char character;
    char* realloc_holder;

    while(1)
    {
        if((read(STDIN_FILENO, &character, 1)) == -1)
        {
            free(buffer);
            return NULL;
        }

        if(character == TERMINATING_CHARACTER)
        {
            break;
        }

        if(write_offset == buffer_size)
        {
            buffer_size *= 2;
            realloc_holder = realloc(buffer, buffer_size);
            if(!realloc_holder)
            {
                free(buffer);
                return NULL;
            }
            buffer = realloc_holder;
        }

        buffer[write_offset] = character;
        write_offset++;
    }

    realloc_holder = realloc(buffer, write_offset+1);
    if(!realloc_holder)
    {
        free(buffer);
        return NULL;
    }

    buffer = realloc_holder;
    buffer[write_offset] = '\0';

    return buffer;
}
