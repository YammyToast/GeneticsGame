#include <unistd.h>
#include <stdio.h>

#include "net.cpp"

int main(int argc, char **argv)
{
    // Getopt Vars
    int index;
    int c;
    // Arg Vars
    char *savefile = NULL;


    opterr = 0;

    while ((c = getopt(argc, argv, "s:")) != -1)
    {
        switch (c)
        {
            case 's':
                savefile = optarg;
                break;

        }
    }
    // Write read args
    printf("sarg = %s\n", savefile);
    // Write unread args
    for(index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    return 0;
}