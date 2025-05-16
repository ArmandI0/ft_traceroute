#include "../ft_traceroute.h"

/*
	This function parse and add the right flag to the cmd structure
	
	input	: the string that contain the flag and a pointeur to the struct cmd
	output	: in case of a parsing error, exit programme and free cmd struct
*/
void addFlag(char *flag, cmd *command)
{
	// -- options
    if (strcmp(flag, "--help") == 0)
    {
        command->help = true;
        return;
    }
}


/*
	This function it use for DNS resolve and parse the address
	
	input	: the string that contain the url or ip and a pointer to the struct command
	output	: exit and free
*/
void	addAddr(char *addr, cmd *command)
{
	struct addrinfo hints;
    struct addrinfo *res;
    
	//define search param to find adress
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int status = getaddrinfo(addr, NULL, &hints, &res);
    if (status != 0) {
        ft_printf_fd(STDERR_FILENO, "ft_ping: cannot resolve %s\n", addr);
		freeAndExit(command, EXIT_FAILURE);
    }
	command->addr = res;
	command->raw_address = addr;
}


bool	splitArgs(char **av, cmd* command)
{
	for (size_t i = 1; av[i] != NULL; i++)
	{
		if (av[i][0] == '-')
			addFlag(av[i], command);
		else if (command->addr == NULL)
			addAddr(av[i], command);
		else
		{
			ft_printf_fd(STDERR_FILENO, "Only one destination are required\n");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

cmd* parseEntry(char **av)
{
	cmd *command = initCommandStruct();
	if (command == NULL)
	{
        ft_printf_fd(STDERR_FILENO, "malloc fail: %s\n", strerror(errno));
		return NULL;
	}

	int status = splitArgs(av, command);

	if (status == EXIT_FAILURE)
		freeAndExit(command, EXIT_FAILURE);
	return command;
}

