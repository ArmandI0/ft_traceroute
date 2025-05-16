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
# include <error.h>
# include <netinet/udp.h>
# include "lib/libft/src/libft.h"

# define SRC_PORT 47528
# define DEST_PORT 33434

extern	volatile sig_atomic_t g_signal_received;

typedef	struct udp_packet_infos
{
	char    *data;
    char    *source_address;
    double  *time_of_response;

}   packet;

typedef struct routeurs_infos
{
    int ttl;

    
    struct routeurs_infos   *next;
    struct routeurs_infos   *prev;
}   nodes;

typedef struct command
{
    bool		    help;   // --help
    int			    socket;
    struct addrinfo *addr;
    char            *raw_address;
    nodes           *nodes;
}				cmd;


cmd*    parseEntry(char **av);
void    freeAndExit(cmd *command, int exit_code);
cmd*    initCommandStruct(void);

#endif