#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// void show(int fork_id)
// {
//     printf("Fork %d. I'm the child %d, my parent is %d.\n", fork_id, getpid(), getppid());
// }

void show(int fork_id)
{
    printf("Fork %d. I'm the child %d, my parent is %d.\n", fork_id, getpid(), getppid());
}

int main()
{
    printf("Main Process ID: %d\n\n", getpid());

    pid_t pid;
    pid = fork(); // Fork 1

    if (pid == 0)
    {
        show(1);
    }
    else
    {
        wait(NULL); // 1 wait
        // printf("start 1");
    }

    pid = fork(); // 2 fork
    if (pid > 0)
    {
        wait(NULL);
        pid = fork(); // 4 gene

        if (pid > 0)
        {
            wait(NULL);
            pid = fork();

            if (pid == 0)
            {
                show(4);
            }
        }
        else
        {
            pid = fork();

            if (pid > 0)
            {
                show(3);
            }
            else
            {
                show(4);
            }
        }
    }
    else
    {
        show(2);
    }

    return 0;
}
