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
	#ifdef __APPLE__
		int packet_len = sizeof(struct ip) + sizeof(struct udphdr) + 9;
	#else
		int packet_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 9;
	#endif

		char *packet = malloc(packet_len);
		if (packet == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "malloc : %s\n", strerror(errno));
			freeAndExit(command, EXIT_FAILURE);
		}
		memset(packet, 0, packet_len);

	// IP HEADER
	#ifdef __APPLE__
		struct ip *ip_header = (struct ip *)packet;
		ip_header->ip_v = 4;
		ip_header->ip_hl = 5;
		ip_header->ip_tos = 0;
		ip_header->ip_len = htons(packet_len);
		ip_header->ip_id = htons(getpid());
		ip_header->ip_off = 0;
		ip_header->ip_ttl = ttl;
		ip_header->ip_p = IPPROTO_UDP;
		ip_header->ip_dst.s_addr = ((struct sockaddr_in *)command->addr->ai_addr)->sin_addr.s_addr;
		ip_header->ip_sum = 0;
	#else
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
	#endif

		// UDP HEADER
	#ifdef __APPLE__
		struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ip));
	#else
		struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));
	#endif

		int udp_len = sizeof(struct udphdr) + 9;
		udp_header->uh_sport = htons(SRC_PORT);
		udp_header->uh_dport = htons(dest_port);
		udp_header->uh_ulen = htons(udp_len);
		udp_header->uh_sum = 0;
		udp_header->uh_sum = checksum(udp_header, udp_len);

	#ifdef __APPLE__
		ip_header->ip_sum = checksum(ip_header, sizeof(struct ip));
	#else
		ip_header->check = checksum(ip_header, sizeof(struct iphdr));
	#endif

		dest_port++;
		command->packet = packet;
}


int    sendPacket(cmd *command)
{
	int status = 0;

	#ifdef __APPLE__
		int packet_len = sizeof(struct ip) + sizeof(struct udphdr) + 9;
	#else
		int packet_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 9;
	#endif

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

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    if (gettimeofday(&start, NULL) == -1) {
        perror("gettimeofday start");
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
            perror("gettimeofday end");
            freeAndExit(command, EXIT_FAILURE);
        }

        // Calculer le temps de réponse en millisecondes
        double elapsed_time = ((double)(end.tv_sec - start.tv_sec) * 1000.0) +
                              ((double)(end.tv_usec - start.tv_usec) / 1000.0);

        // Construire le résultat dans le buffer
        char *ip = inet_ntoa(((struct sockaddr_in *)&sender_addr)->sin_addr);
        snprintf(result_buffer, 64, "%.3f ms", elapsed_time);
        strncpy(ip_str, ip, INET_ADDRSTRLEN - 1);
        ip_str[INET_ADDRSTRLEN - 1] = '\0'; 

        return 1; // Paquet reçu
    }
    // Timeout, remplir le buffer avec "*"
    snprintf(result_buffer, 64, "*");
    return 0; // Pas de paquet reçu
}


void traceroute(cmd *command)
{
    static int ttl = 1;

    while (ttl <= HOPS_MAX && g_signal_received)
    {
        ft_printf_fd(STDOUT_FILENO, "%d  ", ttl); // Affiche le numéro du saut (TTL)

        for (int i = 0; i < 3; i++) // Trois tentatives par TTL
        {
            preparePacket(ttl, command);
            sendPacket(command);

            char result_buffer[64] = {0}; // Buffer pour stocker le résultat
            char ip_str[INET_ADDRSTRLEN] = {0};
            recvPacket(command, result_buffer, ip_str);
            (void)ip_str;
            if (i == 0)
                ft_printf_fd(STDOUT_FILENO, "%s  ", ip_str);
            ft_printf_fd(STDOUT_FILENO, "%s  ", result_buffer); // Affiche le résultat

            free(command->packet); // Libère la mémoire du paquet
            command->packet = NULL;

            usleep(500000); // Pause de 500 ms entre les envois
        }

        ft_printf_fd(STDOUT_FILENO, "\n"); // Nouvelle ligne après chaque TTL
        ttl++;
    }
}
