# ifndef ft_traceroute
# define ft_traceroute

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <stdbool.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <errno.h>
# include <signal.h>
# include <netinet/udp.h>
# include "lib/libft/src/libft.h"
# include <netinet/ip.h>

# define SRC_PORT   47528
# define DEST_PORT  33434
# define HOPS_MAX   64
# define TIME_TO_WAIT 1

extern	volatile sig_atomic_t g_signal_received;

typedef struct command
{
    int			    socket;
    int             recv_socket;
    struct addrinfo *addr;
    char            raw_address[INET_ADDRSTRLEN];
	char			*packet;
    double          *start_time;
}				cmd;


cmd*    parseEntry(char **av);
void    freeAndExit(cmd *command, int exit_code);
cmd*    initCommandStruct(void);
void 	setSignalAction(void);
void    createSocket(cmd *command);
void    traceroute(cmd *command);



#endif