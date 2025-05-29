#include "../ft_traceroute.h"

/*
    Input: pointer to the packet, sizeof(packet)
    Return: checksum result

    Description: Calcul le checksum du packet cree, utilisé pour vérifier l'intégrité des paquets ICMP.
*/
uint16_t checksum(void *buffer, size_t length) {
    uint16_t *data = (uint16_t *)buffer;
    uint32_t sum = 0;

    while (length > 1) {
        sum += *data++;
        length -= 2;
    }
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return (uint16_t)(~sum);
}

char* preparePacket(void)
{
	static int	dest_port = DEST_PORT;
    int         packet_len = 17; // [UDP header = 8bytes] [Data = 9 bytes]
    char        *packet = malloc(packet_len);

    
    if (packet == NULL)
        return NULL;
    memset(packet, 0, packet_len);
    struct udphdr   *udp_header = (struct udphdr*)packet;

    udp_header->uh_sport = SRC_PORT;
    udp_header->uh_dport = dest_port;
    udp_header->uh_sum = 0;
	udp_header->uh_sum = checksum(packet, packet_len); 
	dest_port++;
    return packet;
}

void    createSocket(cmd *command)
{
    int sockfd = -1;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);   // SOCK_RAW -> Socket brute pour tous les protocoles + filtre ICMP
    if (sockfd < 0)
    {
        ft_printf_fd(STDERR_FILENO, "socket : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }

    // Modifier le time to leave
    static int ttl = 1;

    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
        ft_printf_fd(STDERR_FILENO, "setsockopt : %s\n", strerror(errno));
		freeAndExit(command, EXIT_FAILURE);
    }
    command->socket_udp = sockfd;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);   // SOCK_RAW -> Socket brute pour tous les protocoles + filtre ICMP
    if (sockfd < 0)
    {
        ft_printf_fd(STDERR_FILENO, "socket : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
}

int sendAndRecv(cmd *command)
{
	int status = 0;
	status = sendto(command->socket_udp, command->packet, 17, 0, command->addr->ai_addr, command->addr->ai_addrlen);
    if (status == -1)
    {
        ft_printf_fd(STDERR_FILENO, "sendto : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
}

void    createAndSendPacket(cmd *command)
{
    command->packet = preparePacket();

    if (command->packet == NULL)
    {
        ft_printf_fd(STDERR_FILENO, "preparePacket : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
	createSocket(command);
	sendAndRecv(command);
}