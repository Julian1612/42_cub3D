#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

int executer(char **argv, char **env, int i, int fd_tmp)
{
	argv[i] = NULL;
	dup2(fd_tmp, STDIN_FILENO);
	close(fd_tmp);
	execve(argv[0], argv, env);
	return(printf("error"));
}


int main(int argc, char **argv, char **env)
{
	int i = 0;
	int fd_tmp = dup(STDIN_FILENO);
	int fd[2];
	(void) argc;

	while(argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while(argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
		{
			if (i != 2)
				return(printf("error"));
			else if (chdir(argv[1]))
				return(printf("error"));
		}
		else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			if (fork() == 0)
			{
				if (executer(argv, env, i, fd_tmp))
					return(1);
			}
			else
			{
				close(fd_tmp);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
				fd_tmp = dup(STDIN_FILENO);
			}
		}
		else if (i != 0 && strcmp(argv[i], "|") == 0)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd_tmp);
				if (executer(argv, env, i, fd_tmp))
					return(1);
			}
			else
			{
				close(fd[1]);
				close(fd_tmp);
				fd_tmp = fd[0];
			}
		}
	}
	close(fd_tmp);
	return(0);
}
