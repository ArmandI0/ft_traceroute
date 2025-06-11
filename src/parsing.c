#include "../ft_traceroute.h"

/*
	This function parse and add the right flag to the cmd structure
	
	input	: the string that contain the flag and a pointeur to the struct cmd
	output	: in case of a parsing error, exit programme and free cmd struct
*/
void addFlag(char *flag, cmd *command)
{
	// -- options
    if (ft_strcmp(flag, "--help") == 0)
    {
		ft_printf_fd(STDOUT_FILENO, "Usage: traceroute [OPTION...] HOST\n");
		ft_printf_fd(STDOUT_FILENO, "Print the route packets trace to network host.\n");
		ft_printf_fd(STDOUT_FILENO, "\n--help                 give this help list\n");
        freeAndExit(command, EXIT_SUCCESS);
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
    ft_memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int status = getaddrinfo(addr, NULL, &hints, &res);
    if (status != 0) {
        ft_printf_fd(STDERR_FILENO, "ft_ping: unknown host %s\n", addr);
		freeAndExit(command, EXIT_FAILURE);
    }
	char *ip = inet_ntoa(((struct sockaddr_in *)res->ai_addr)->sin_addr);
    ft_strlcpy(command->raw_address , ip, INET_ADDRSTRLEN - 1);
	command->addr = res;
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
			freeaddrinfo(command->addr);
			command->addr = NULL;
			addAddr(av[i], command);
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

