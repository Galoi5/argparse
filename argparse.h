#ifndef ARGPARSE_H
#define ARGPARSE_H

typedef struct arg
{
    const char* long_name;
    const char* short_name;
    const char* description;
    int arg_count; // the number of folliwng arguments the option depends on. 0 is none
} arg;

typedef struct argparse
{
    const char* prog_name;
    const char* version;
    const char* author;
    const char* help;
    arg** args;
} argparse;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int countopts(int argc, char** argv);
char** getopts(int argc, char** argv);


// util functions


int newarg(const char* longname, const char* shortname, const char* description, int argcount);
int parse();
int killparse(); //free everything

#endif