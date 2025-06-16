#include "../ft_traceroute.h"

cmd* initCommandStruct(void)
{
	cmd *command;

	command = malloc(sizeof(cmd));
	if (!command)
		return NULL;
    command->packet = NULL;
    command->socket = -1;
    command->recv_socket = -1;
    command->addr = NULL;
    command->waiting_time = -1;
    command->hops_max = -1;

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
        if (command->recv_socket != -1)
            close(command->recv_socket);
        free(command);
    }
    exit(exit_code);
}

