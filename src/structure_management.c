#include "../ft_traceroute.h"

cmd* initCommandStruct(void)
{
	cmd *command;

	command = malloc(sizeof(cmd));
	if (!command)
		return NULL;
    command->help =false;
    command->socket = -1;
    command->recv_socket = -1;
    command->addr = NULL;
    command->nodes = NULL;

    return command;
}

void freeAndExit(cmd *command, int exit_code)
{
    if (command != NULL) {
        if (command->addr != NULL)
            freeaddrinfo(command->addr);
        if (command->packet != NULL)
            free(command->packet);
        if (command->socket != -1)
            close(command->socket);
        free(command);
    }
    exit(exit_code);
}    