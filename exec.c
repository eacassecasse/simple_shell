#include <unistd.h>
#include "main.h"

/**
 * runCmd - Custom Function
 * @filename: String contains the filepath to exec
 * @args: an array of arguments to be exec  
 *
 * Description: Executes a command
 */
void runCmd(char *filename, char *args[])
{
	int res = execve(filename, args, NULL);

	if (res < 0)
		error("./shell");
}
