#include "../ft_traceroute.h"


char* preparePacket(cmd *command)
{
    static int  seq = 0;
    int         packet_len = 17; // [UDP header = 8bytes] [Data = 9 bytes]
    char        *packet = malloc(packet_len);
    
    if (packet == NULL)
        return NULL;
    memset(packet, 0, packet_len);
    struct udphdr   *udp_header = (struct udphdr*)packet;

    udp_header->uh_sport = SRC_PORT;
    udp_header->uh_dport = DEST_PORT;
    udp_header->uh_sum
    return packet;
}

void    createAndSendPacket(cmd *command)
{
    command->packet = preparePacket(command);
    if (command->packet == NULL)
    {
        perror("malloc");
        freeAndExit(command, EXIT_FAILURE);
    }
    createSocket(command);
    // sendPacket(command);
    // recvPacket(command);
}