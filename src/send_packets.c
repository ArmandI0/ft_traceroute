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

void preparePacket(int ttl, cmd *command)
{
	static int	dest_port = DEST_PORT;
    int         packet_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 9; // IP Header + [UDP header = 8bytes] [Data = 9 bytes]
    char        *packet = malloc(packet_len);

    
    if (packet == NULL)
    {
        ft_printf_fd(STDERR_FILENO, "malloc : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
    memset(packet, 0, packet_len);

    // Set les options du IP header
    struct iphdr *ip_header = (struct iphdr*)packet;

    ip_header->version = 4;
    ip_header->ihl = 5;
    ip_header->tos = 0;
    ip_header->tot_len = htons(packet_len);
    ip_header->id = htons(getpid());
    ip_header->frag_off = 0;
    ip_header->ttl = ttl;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->check = 0;

    // Option du UDP header
    struct udphdr *udp_header = (struct udphdr*)(packet + sizeof(struct iphdr));
    int udp_len = sizeof(struct udphdr) + 9;
    
    udp_header->uh_sport = htons(SRC_PORT);
    udp_header->uh_dport = htons(dest_port);
    udp_header->uh_ulen = htons(udp_len);
    udp_header->uh_sum = 0;
	udp_header->uh_sum = checksum(udp_header, sizeof(struct udphdr) + 9);

    ip_header->check = checksum(ip_header, sizeof(struct iphdr));

	dest_port++;
    command->packet = packet;
}


int    sendPacket(cmd *command)
{
	int status = 0;
    int packet_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 9;

	status = sendto(command->socket, command->packet, packet_len, 0, command->addr->ai_addr, command->addr->ai_addrlen);
    if (status == -1)
    {
        ft_printf_fd(STDERR_FILENO, "sendto : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
    free(command->packet);
    command->packet = NULL;
    return status;
}

void    traceroute(cmd *command)
{
    static int ttl = 1;

    while (ttl <= HOPS_MAX && g_signal_received)
    {
        for (int i = 0; i < 3; i++)
        {
            preparePacket(ttl, command);
            sendPacket(command);
            ft_printf_fd(STDOUT_FILENO, "i = %d\n", i);
            sleep(1);
        }
    }
}