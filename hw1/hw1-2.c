#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    while (1)
    {
        printf("osh> ");
        fflush(stdout);

        char *arg[20];
        for (int i = 0; i < 20; i++)
            arg[i] = NULL;

        char input[20];
        fgets(input, 20, stdin);

        int cur = 0;
        char *p = strtok(input, " \n");
        while (p)
        {
            arg[cur] = p;
            cur++;

            p = strtok(NULL, " \n");
        }

            if (strcmp(arg[0], "exit") == 0)
            {
                printf("Process end\n");
                return 0;
            }

        pid_t pid = fork();

        if (pid < 0)
        {
            printf("fork fail\n");
            exit(1);
        }
        else if (pid == 0 && execvp(arg[0], arg) < 0)
        {
            printf("wrong instruction\n");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}
