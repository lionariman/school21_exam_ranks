#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PIPEIN 1
#define PIPEOUT 0
#define STDIN 0
#define STDOUT 1

typedef struct s_cmd
{
    char **args;
    int pipe[2];
    int prev_pipe;
    int type[2];
} t_cmd;

void err()
{
    write(2, "error: fatal\n", strlen("error: fatal\n"));
    exit(1);
}

int list_len(t_cmd *list, int start, char **av)
{
    int end, len;

    end = start;
    while (av[end] && strcmp(av[end], ";") && strcmp(av[end], "|"))
        end++;
    len = end - start;
    if (len > 0)
    {
        list->args = &av[start];
        list->type[0] = list->type[1];
        if (!av[end])
            list->type[1] = 0;
        else if (!strcmp(av[end], "|"))
            list->type[1] = 1;
        else
            list->type[1] = 2;
        av[end] = NULL;
        list->prev_pipe = list->pipe[PIPEOUT];
    }
    return (end);
}

void exec_cmd(t_cmd *list, char **en)
{
    pid_t pid;
    int status, ex;

    if (list->type[1] == 1 || list->type[0] == 1)
        if (pipe(list->pipe))
            err();
    if ((pid = fork()) < 0)
        err();
    if (pid == 0)
    {
        if (list->type[1] == 1)
            if (dup2(list->pipe[PIPEIN], STDOUT) < 0)
                err();
        if (list->type[0] == 1)
            if (dup2(list->prev_pipe, STDIN) < 0)
                err();
        if ((ex = execve(list->args[0], list->args, en)) < 0)
        {
            write(2, "error: cannot execute ", strlen("error: cannot execute "));
            write(2, list->args[0], strlen(list->args[0]));
            write(2, "\n", 1);
        }
        exit(ex);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (list->type[1] == 1 || list->type[0] == 1)
        {
            close(list->pipe[PIPEIN]);
            if (list->type[1] != 1)
                close(list->pipe[PIPEOUT]);
        }
        if (list->type[0] == 1)
            close(list->prev_pipe);
    }
}

int main(int ac, char **av, char **en)
{
    t_cmd list;
    int i, start;

    i = 0;
    if (ac > 1)
    {
        while (i < ac && av[++i])
        {
            start = i;
            i = list_len(&list, i, av);

            if (!strcmp(av[start], "cd"))
            {
                if (i - start != 2)
                    write(2, "error: cd: bad arguments\n", strlen("error: cd: bad arguments\n"));
                else if (chdir(list.args[1]) < 0)
                {
                    write(2, "error: cd: cannot change directory to ", strlen("error: cd: cannot change directory to "));
                    write(2, list.args[1], strlen(list.args[1]));
                    write(2, "\n", 1);
                }
            }
            else if (i > start)
                exec_cmd(&list, en);
        }
    }
    return (0);
}