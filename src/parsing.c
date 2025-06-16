#include "../ft_traceroute.h"

/*
	This function parse and add the right flag to the cmd structure
	
	input	: the string that contain the flag and a pointeur to the struct cmd
	output	: in case of a parsing error, exit programme and free cmd struct
*/
bool addFlag(char *flag, cmd *command, char *next_arg)
{
	bool	skip_the_next_args = false;
	// -- options
    if (ft_strcmp(flag, "--help") == 0 || ft_strcmp(flag, "-h") == 0)
    {
		ft_printf_fd(STDOUT_FILENO, "Usage: ft_traceroute [OPTION...] HOST\n");
		ft_printf_fd(STDOUT_FILENO, "Print the route packets trace to network host.\n");
		ft_printf_fd(STDOUT_FILENO, "\n--help                 give this help list\n");
		ft_printf_fd(STDOUT_FILENO, "-w                     wait NUM seconds for response (default: 3)\n");
		ft_printf_fd(STDOUT_FILENO, "-m                     set maximal hop count (default: 64)\n");
		freeAndExit(command, EXIT_SUCCESS);
    }
    else if (flag[0] == '-' && flag[1] == 'w')
    {
        char *value = NULL;
        if (flag[2]) 
            value = &flag[2];
        else if (next_arg != NULL)
        {
			value = next_arg;
			skip_the_next_args = true;
		}
		else
		{
			ft_printf_fd(STDOUT_FILENO, "ft_traceroute: option requires an argument 'w'\n");
			ft_printf_fd(STDOUT_FILENO, "Try 'ft_traceroute --help'\n");
			freeAndExit(command, EXIT_FAILURE);
		}
		int wait_time = ft_atoi(value);
		char *tmp = ft_itoa(wait_time);

        if (wait_time <= 0 || ft_strcmp(tmp, value) != 0 || wait_time > 60)
        {
			free(tmp);
            ft_printf_fd(STDOUT_FILENO, "ft_traceroute: ridiculous waiting time '%s'\n", value);
            freeAndExit(command, EXIT_FAILURE);
        }
		free(tmp);
		command->waiting_time = wait_time;
    }
	else if (flag[0] == '-' && flag[1] == 'm')
    {
        char *value = NULL;
        if (flag[2]) 
            value = &flag[2];
        else if (next_arg != NULL)
        {
			value = next_arg;
			skip_the_next_args = true;
		}
		else
		{
			ft_printf_fd(STDOUT_FILENO, "ft_traceroute: option requires an argument 'm'\n");
			ft_printf_fd(STDOUT_FILENO, "Try 'traceroute --help'\n");
			freeAndExit(command, EXIT_FAILURE);
		}
		int hops_max = ft_atoi(value);
		char *tmp = ft_itoa(hops_max);

        if (hops_max <= 0 || ft_strcmp(tmp, value) != 0 || hops_max > 255)
        {
			free(tmp);
            ft_printf_fd(STDOUT_FILENO, "ft_traceroute: invalid hops value '%s'\n", value);
            freeAndExit(command, EXIT_FAILURE);
        }
		free(tmp);
		command->hops_max = hops_max;
    }
	else
	{
        ft_printf_fd(STDOUT_FILENO, "ft_traceroute: unrecognized option '%s'\n", flag);
        ft_printf_fd(STDOUT_FILENO, "Try 'ft_traceroute --help'\n");
		freeAndExit(command, EXIT_FAILURE);
	}
	return skip_the_next_args;
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
		bool	skip_next_arg = false;
		if (av[i][0] == '-' && av[i][1] != '\0')
			skip_next_arg =  addFlag(av[i], command, av[i + 1]);
		else if (command->addr == NULL)
			addAddr(av[i], command);
		else
		{
			freeaddrinfo(command->addr);
			command->addr = NULL;
			addAddr(av[i], command);
		}
		if (skip_next_arg == true)
			i++;
	}
	if (command->addr == NULL)
	{
		ft_printf_fd(STDOUT_FILENO, "traceroute: missing host operand\n");
        ft_printf_fd(STDOUT_FILENO, "Try 'traceroute --help'\n");
		freeAndExit(command, EXIT_FAILURE);
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

