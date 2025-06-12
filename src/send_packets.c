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
	static int dest_port = DEST_PORT;
	int packet_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 9;
	char *packet = malloc(packet_len);

	if (packet == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "malloc : %s\n", strerror(errno));
		freeAndExit(command, EXIT_FAILURE);
	}
	ft_memset(packet, 0, packet_len);

	// IP HEADER
	struct iphdr *ip_header = (struct iphdr *)packet;

	ip_header->version = 4;
	ip_header->ihl = 5;
	ip_header->tos = 0;
	ip_header->tot_len = htons(packet_len);
	ip_header->id = htons(getpid());
	ip_header->frag_off = 0;
	ip_header->ttl = ttl;
	ip_header->protocol = IPPROTO_UDP;
	ip_header->daddr = ((struct sockaddr_in *)command->addr->ai_addr)->sin_addr.s_addr;
	ip_header->check = 0;

	// UDP HEADER
	struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));

	int udp_len = sizeof(struct udphdr) + 9;
	udp_header->uh_sport = htons(SRC_PORT);
	udp_header->uh_dport = htons(dest_port);
	udp_header->uh_ulen = htons(udp_len);
	udp_header->uh_sum = 0;
	udp_header->uh_sum = checksum(udp_header, udp_len);

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
    return status;
}


int     recvPacket(cmd *command, char *result_buffer, char *ip_str)
{
    int retval;
    fd_set rfds;
    struct timeval tv, start, end;

    FD_ZERO(&rfds);
    FD_SET(command->recv_socket, &rfds);

    tv.tv_sec = TIME_TO_WAIT;
    tv.tv_usec = 0;

    if (gettimeofday(&start, NULL) == -1) {
        ft_printf_fd(STDERR_FILENO, "gettimeofday : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }

    retval = select(command->recv_socket + 1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
    {
        ft_printf_fd(STDERR_FILENO, "select : %s\n", strerror(errno));
        freeAndExit(command, EXIT_FAILURE);
    }
    else if (retval)
    {
        char buffer[1024];
        struct sockaddr_storage sender_addr;
        socklen_t sender_addr_len = sizeof(sender_addr);

        ssize_t bytes_received = recvfrom(command->recv_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
        if (bytes_received == -1)
        {
            ft_printf_fd(STDERR_FILENO, "recvfrom : %s\n", strerror(errno));
            freeAndExit(command, EXIT_FAILURE);
        }

        if (gettimeofday(&end, NULL) == -1) {
            ft_printf_fd(STDERR_FILENO, "gettimeofday : %s\n", strerror(errno));
            freeAndExit(command, EXIT_FAILURE);
        }

        double elapsed_time = ((double)(end.tv_sec - start.tv_sec) * 1000.0) +
                              ((double)(end.tv_usec - start.tv_usec) / 1000.0);

        char *ip = inet_ntoa(((struct sockaddr_in *)&sender_addr)->sin_addr);
        snprintf(result_buffer, 64, "%.3f ms", elapsed_time);
        ft_strlcpy(ip_str, ip, INET_ADDRSTRLEN - 1);
        ip_str[INET_ADDRSTRLEN - 1] = '\0'; 
        return 1;
    }
    snprintf(result_buffer, 64, "*");
    return 0;
}


void traceroute(cmd *command)
{
    static int  ttl = 1;
    char        ip_str[INET_ADDRSTRLEN] = {0};
    int         status = 0;

    while (ttl <= HOPS_MAX && g_signal_received)
    {
        if (ttl == 1)
            ft_printf_fd(STDOUT_FILENO, "ft_traceroute to %s (%s), %d hops max\n",
                command->raw_address,
                command->raw_address,
                HOPS_MAX);
        ft_printf_fd(STDOUT_FILENO, "  %d   ", ttl);

        for (int i = 0; i < 3; i++)
        {
            preparePacket(ttl, command);
            sendPacket(command);

            char result_buffer[64] = {0};

            status = recvPacket(command, result_buffer, ip_str);
            if (i == 0 && status == 1)
                ft_printf_fd(STDOUT_FILENO, "%s  ", ip_str);
            ft_printf_fd(STDOUT_FILENO, "%s  ", result_buffer);

            free(command->packet);
            command->packet = NULL;
        }
        ft_printf_fd(STDOUT_FILENO, "\n");
        if(ft_strncmp(ip_str, command->raw_address, INET_ADDRSTRLEN) == 0)
            break;
        ttl++;
    }
}
