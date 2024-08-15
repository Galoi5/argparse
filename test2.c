#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MALLOCERROR 12

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
    stripped = (char*)malloc((strlen(opt) + 1) * sizeof(char)); // +1 for null terminator
    if (stripped == NULL)
        goto mallocerror;
    strcpy(stripped, opt);
    return (stripped);

mallocerror:
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
    char* temp;
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


int main(int argc, char** argv)
{
    int i = 0;
    printf("%d ", _countopts(argc, argv));
    while (i < argc)
    {
        printf("%s ", _strip(argv[i]));
        i++;
    }
    char** t = _getopts(argc, argv);
    printf("\n\n%s\n", t[1]); 
    // int j =0;
    // while (j < argc)
    // {
    //     printf("%s ", t[j]);
    //     j++;
    // }
}