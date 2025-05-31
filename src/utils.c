#include "../ft_traceroute.h"

void    createSocket(cmd *command)
{
    int sockfd = -1;
    
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0)
    {
        ft_printf_fd(STDERR_FILENO, "socket : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
    command->socket = sockfd;
}