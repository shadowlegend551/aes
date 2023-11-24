#include <stdio.h>
#include <stdlib.h>

#include "iolib.h"

char* readline(FILE* fp)
{
    int line_length = 0;
    char character;
    
    while((character = fgetc(fp)) != EOF && character != '\n')
    {
        line_length++;
    }

    // Take \n into account for fseek to work properly.
    if(character == '\n') { line_length++; }
    
    if(!line_length) { return NULL; }
    fseek(fp, -line_length, SEEK_CUR);

    char* string = malloc(line_length + 1);
    if(!string)
    {
        free(string);
        return NULL;
    }

    if(!fgets(string, line_length+1, fp))
    {
        free(string);
        return NULL;
    }
    
    return string;
}

char** readlines(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(!fp) { return NULL; }

    int list_length = 128;
    char** string_list = malloc(sizeof(char*) * list_length);
    int list_offset = 0;
    char* string;

    while((string = readline(fp)))
    {
        string_list[list_offset] = string;
        list_offset++;

        if(list_offset > list_length) { list_length *= 2; }
    }

    if(!list_offset)
    {
        free(string_list);
        return NULL;
    }

    char** string_list_holder = realloc(string_list, sizeof(char**) * list_offset);
    
    if(!string_list_holder)
    {
        free(string_list);
        return NULL;
    }
    string_list = string_list_holder;

    return string_list;
}

char* readfile(const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(!fp) { return NULL; }

    int string_length = 0;
    while(fgetc(fp) != EOF) { string_length++; }

    fseek(fp, 0, SEEK_SET);

    char* string = malloc(string_length + 1);
    if(!string)
    {
        fclose(fp);
        free(string);
        return NULL;
    }

    if(!fgets(string, string_length+1, fp))
    {
        fclose(fp);
        free(string);
        return NULL;
    }

    return string;
}

int writefile(const char* filename, const char* data)
{   
    FILE* fp;
    if(!(fp = fopen(filename, "w"))) { return NULL; }

    if(fputs(data, fp) == EOF)
    {
        fclose(fp);
        return NULL;
    }

    if(fclose(fp) == EOF) { return NULL; }
    
    return 0;
}
