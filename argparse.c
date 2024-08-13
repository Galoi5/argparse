#include "argparse.h"

int newarg(const char* longname, const char* shortname, const char* description, int argcount)
{
    if (!strcmp(longname, "\0") && !strcmp(shortname, "\0"))
    {
        perror("Argument must contain a non empty long name or short name.");
        return (-1);
    }
    arg* new_arg = malloc(sizeof(arg));
    if (new_arg == NULL)
        goto error;
    new_arg->long_name = malloc(sizeof(char) * (strlen(longname) + 1));
    if (new_arg->long_name == NULL )
        goto error;
    new_arg->short_name = malloc(sizeof(char) * (strlen(shortname) + 1));
    if (new_arg->short_name == NULL )
        goto error;
    new_arg->description = malloc(sizeof(char) * (strlen(description) + 1));
    if (new_arg->description == NULL )
        goto error;

    
    error:
        free(new_arg);
        perror("An error occured.");
        return (-1);
}