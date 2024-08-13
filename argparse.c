#include "argparse.h"

int countopts(int argc, char** argv) // counts any options given by - or --
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (i < argc)
    {
        if (!strncmp(argv[i], "-", 1) || !strncmp(argv[i], "--", 2))
            count++;
        i++;
    }
    return (count);
}

char** getopts(int argc, char** argv)
{
    int i;
    int j;

    char** opts = malloc(countopts(argc, argv) * sizeof(char*));
    if (opts == NULL)
        goto error;
    i = 0;
    j = 0;
    while (i < argc)
    {
        if (!strncmp(argv[i], "-", 1) || !strncmp(argv[i], "--", 2))
        {
            if (!strncmp(argv[i], "-", 1) && !(argv[i][1] == '-'))
            {

            }
            opts[j] = malloc()
            
            // strcpy(opts[j], argv[i]);
            // if (opts[j] == NULL)
            //     goto error;
            j++;
        }
        i++;
    }
    return (opts);

    error:
        int k = 0;

        while (k < countopts(argc, argv))
        {
            free(opts[k]);  
            k++;
        }
        free(opts);
        return (NULL);
}

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