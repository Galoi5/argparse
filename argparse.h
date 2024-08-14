#ifndef ARGPARSE_H
#define ARGPARSE_H

/* includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* error codes and global errno*/
#define NOERROR     0
#define MALLOCERROR 1
#define OPTNONAME   2
#define OPTNODESC   3
int errno = 0;

/* option struct */
typedef struct opt
{
    const char* long_name;
    const char* short_name;
    const char* description;
    int arg_count; 
    struct opt *next;
} opt;

/* util functions */
int _isvalidopt(char* opt); //returns 1 if opt is valid and 0 if not
char* _strip(char* opt);    //once option is valid, strip the - or --
int _countopts(int argc, char** argv); //count number of options
char** _getopts(int argc, char** argv); //get options



int _validateargs(char** argv, char** optlst);


/* parse arguments and options */
char** parse(int argc, char** argv);
opt* newopt(const char* longname, const char* shortname, const char* description, int argcount); //register new option
int killparse(); //free everything

#endif