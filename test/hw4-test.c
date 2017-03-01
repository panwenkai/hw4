# define _GNU_SOURCE
#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
	pid_t parent_pid_true = getppid();
	pid_t parent_pid_test = 0;
	uid_t parent_euid;

	// Test1: Given pid is not the pid of the calling process's parent process.
	int return_value = syscall(400, parent_pid_test, &parent_euid);
	if (return_value < 0)
	{
		printf("Return value is: %d", return_value);
		perror("Given pid is not the pid of the calling process's parent process.");
	}

	// Test2: Given pid is the pid of the calling process's parent process.
	parent_pid_test = parent_pid_true;
	return_value = syscall(400, parent_pid_test, &parent_euid);
	printf("Return value is: %d", return_value);
	if (return_value < 0)
	{
		perror("The effective user of the parent is NOT root.");
	}


}

