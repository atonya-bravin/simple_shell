#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * run_command - check for the availability of the command file in path
 *
 * @command: the command passed in by user
 *
 * Return: Always return nothing
 */

void run_command(char *command)
{
	struct stat buff;
	char *command_path;
	char *execution_arguments[5];

	command_path = malloc(sizeof(char) * strlen(command));
	strcat(command_path, command);

	if (stat(command_path, &buff) == 0)
	{
		execution_arguments[0] = command_path;
		execution_arguments[1] = NULL;
		execution_arguments[2] = NULL;
		if (execve(command_path, execution_arguments, NULL) == -1)
		{
			perror("Error:");
		}
	}
	perror("Error");
	exit(EXIT_FAILURE);
	free(command_path);

}
/**
 * main - starting point of the project
 *
 * @argc :the number of parameters provided by the user
 * @argv :the argument list provided by the user
 *
 * Return: 0(success) or 1(fail)
 */

int main(int argc, char **argv)
{
	bool continue_compiling = true;
	char *command_holder;
	size_t command_length = 0;
	char *clean_command_holder;
	bool successful = true;
	char *command;
	int process_id;

	(void)argv;
	if (argc != 1)
	{
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (continue_compiling)
	{
		printf("$ ");
		if (getline(&command_holder, &command_length, stdin) == -1)
		{
			successful = false;
			break;
		}
		clean_command_holder = malloc(sizeof(char) * strlen(command_holder));
		strncpy(clean_command_holder, command_holder, (strlen(command_holder) - 1));
		if (strcmp(clean_command_holder, "exit") == 0)
			continue_compiling = false;
		command = strtok(clean_command_holder, " ");
		process_id = fork();
		if (process_id != 0)
			wait(NULL);
		else
			run_command(command);
	}
	if (successful)
	{
		free(command_holder);
		free(clean_command_holder);
	}
	printf("\n");
	return (0);
}
