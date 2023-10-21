#include <string.h>
#include "main.h"

/**
 * execcmd - Custom Function
 *
 * Description: Constructor for the execcmd struct
 *
 * Return: A pointer to the cmd_t structure
 */
struct cmd *execcmd(void)
{
	struct execcmd *cmd;

	cmd = malloc(sizeof(*cmd));

	if (!cmd)
	{
		error("Failed to create the EXECCMD");
		return (NULL);
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;

	return ((struct cmd *)cmd);
}

/**
 * redircmd - Custom Function
 * @sc: Command to execute
 * @f: File to redirect from
 * @ef: File to redirect to
 * @mode: Type of redirection I/O
 * @fd: File descriptor
 *
 * Description: Construct for the redircmd struct
 *
 * Return: A pointer to a cmd_t structure
 */
struct cmd *redircmd(struct cmd *sc, char *f, char *ef, int mode, int fd)
{
	struct redircmd *cmd;

	cmd = malloc(sizeof(*cmd));

	if (!cmd)
	{
		error("Failed to construct");
		return (NULL);
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = sc;
	cmd->file = f;
	cmd->efile = ef;
	cmd->mode = mode;
	cmd->fd = fd;

	return ((struct cmd *)cmd);
}

/**
 * pipecmd - Custom Function
 * @left: The left part of a piped cmd
 * @right: The right part of a piped cmd
 *
 * Description: Construct for the pipecmd struct
 *
 * Return: A pointer to a cmd_t structure
 */
struct cmd *pipecmd(struct cmd *left, struct cmd *right)
{
	struct pipecmd *cmd;

	cmd = malloc(sizeof(*cmd));

	if (!cmd)
	{
		error("Failed to construct");
		return (NULL);
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;

	return ((struct cmd *)cmd);
}

/**
 * listcmd - Custom Function
 * @left: The left part of a piped cmd
 * @right: The right part of a piped cmd
 *
 * Description: Construct for the listcmd struct
 *
 * Return: A pointer to a cmd_t structure
 */
struct cmd *listcmd(struct cmd *left, struct cmd *right)
{
	struct listcmd *cmd;

	cmd = malloc(sizeof(*cmd));

	if (!cmd)
	{
		error("Failed to construct");
		return (NULL);
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;

	return ((struct cmd *)cmd);
}

