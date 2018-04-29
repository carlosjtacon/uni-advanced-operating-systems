#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_functions.h"

int main ()
{
    char *initpath = mypwd();
    command C;
    int r;

    printf ("Type commands (type exit to finish and help to print info)\n");

    do              // Read commands and show them
    {
        init_command (&C);

        char *cwd = mypwd();
        printf ("%s@minishell: %s $ ", getenv("USER"), strrchr(cwd, '/'));
        free(cwd);

        r = read_command (&C, stdin);

        if (r < 0)
            fprintf (stderr, "\nError %d: %s\n",
                             -r, err_messages[-r]);
        else
        {
            //show_command(&C);
            exec_cmd(&C, initpath);
        }

        free_command (&C);
    }
    while (r==0);   // Repeat until error or EOF

    free(initpath);

    return 0;
}