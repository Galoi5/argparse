#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define NOERROR     0
#define MALLOCERROR 1
#define OPTNONAME   2
#define OPTNODESC   3
int errno = 0;

int _isvalidopt(char* opt)
{
    if ((opt[0] == '-' && opt[1] != '-' && opt[1] != '\0') || (!strncmp(opt, "--", 2) && opt[2] != '\0'))
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
    int k;

    optcount = _countopts(argc, argv);
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

    mallocerror:

        k = 0;
        while (k < optcount)
        {
            free(rawopts[k]);
            k++;
        }
        free(rawopts);
        errno = MALLOCERROR;
        return (NULL);
}


int main(int argc, char** argv)
{
    int i = 0;
    char** opts = _getopts(argc, argv);
    while (i < _countopts(argc, argv))
    {
        printf("%s\n", opts[i]);
        i++;
    }
}