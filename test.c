#include "argparse.c"

int main(int argc, char** argv)
{
    printf("count: %d", countopts(argc, argv));
}