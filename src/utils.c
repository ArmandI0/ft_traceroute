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

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        ft_printf_fd(STDERR_FILENO, "recv socket : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        ft_printf_fd(STDERR_FILENO, "bind : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
    command->recv_socket = sockfd;
}