#include "argparse.h"

int _isvalidopt(char* opt)
{
    if ((opt[0] == '-' && opt[1] != '-' && opt[1] != '\0') || (!strncmp(opt, "--", 2) && opt[2] != '\0' && opt[2] != '-'))
        return (1);
    return (0);
}

char* _strip(char* opt)
{
    char* stripped;

    if (opt[0] == '-' && opt[1] != '-')
        opt++;
    else
        opt += 2;
    stripped = (char*)malloc(strlen(opt) * sizeof(char)); // +1 -1 = 0 
    if (stripped == NULL)
        goto mallocerror;
    strcpy(stripped, opt);
    return (stripped);

    mallocerror:
        free(stripped);
        errno = MALLOCERROR;
        return (NULL);
}

int _countopts(int argc, char** argv)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (i < argc)
    {
        if (_isvalidopt(argv[i]))
            count++;
        i++;
    }
    return (count);
}

char** _getopts(int argc, char** argv)
{
    char** rawopts;
    int optcount;
    int i;
    int j;

    optcount = _countopts(argc, argv);
    if (optcount == 0)
        return NULL;
    rawopts = malloc(optcount * sizeof(char*));
    if (rawopts == NULL)
        goto mallocerror;
    i = 0;
    j = 0;
    while (i < argc)
    {
        if (_isvalidopt(argv[i]))
        {
            rawopts[j] = _strip(argv[i]);
            if (rawopts[j] == NULL)
                goto mallocerror;
            j++;
        }
        i++;
    }
    return rawopts;

mallocerror:
    for (int k = 0; k < j; k++)
    {
        free(rawopts[k]);
    }
    free(rawopts);
    errno = MALLOCERROR;
    return NULL;
}

char** parse(int argc, char** argv)
{

}






opt* newopt(const char* longname, const char* shortname, const char* description, int argcount)
{
    if (longname == NULL && shortname == NULL)
        goto noname;
    if (description == NULL)
        goto nodesc;
    opt* new = (opt*)malloc(sizeof(opt));
    if (new == NULL)
        goto mallocerror;
    new->long_name = (const char*)malloc((strlen(longname) + 1) * sizeof(char));
    new->short_name = (const char*)malloc((strlen(longname) + 1) * sizeof(char));
    new->description = (const char*)malloc((strlen(longname) + 1) * sizeof(char));
    new->arg_count = argcount;
    new->next = NULL;
    return (new);

    mallocerror:
        free(new);
        free(new->long_name);
        free(new->short_name);
        free(new->description);
        errno = MALLOCERROR;
        return (NULL);
    noname:
        errno = OPTNONAME;
        return (NULL);
    nodesc:
        errno = OPTNODESC;
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










