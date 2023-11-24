#ifndef IOLIB_H
#define IOLIB_H


/*
* Standard input-output -functions.
*/

// Reads stdin until newline is encountered.
char* readstdinline(void);

// Reads stdin until a specified character.
char* readstdinuntil(char TERMINATING_CHARACTER);


/*
* File input-output -functions.
*/

// Reads one line from a file.
char* readline(FILE* fp);

// Reads all lines in a file.
char** readlines(const char* filename);

// Reads a file to a string.
char* readfile(const char* filename);

// Writes to a file truncating it first.
int writefile(const char* filename, const char* data);

#endif