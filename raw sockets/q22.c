#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int s;
    struct sockaddr_in src_addr;
    char packet[50];

    if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
    {
        perror("error:");
        exit(EXIT_FAILURE);
    }

    memset(packet, 0, sizeof(packet));
    socklen_t *len = (socklen_t *)sizeof(src_addr);
    int fromlen = sizeof(src_addr);

    // while (42)
    {
        if (recvfrom(s, &packet, sizeof(packet), 0,
                     (struct sockaddr *)&src_addr, &fromlen) < 0)
            perror("uh oh:");

        printf("\n\nIP Header\n");
        unsigned short iphdrlen;
        struct sockaddr_in source, dest;
        struct iphdr *ip = (struct iphdr *)(packet);
        memset(&source, 0, sizeof(source));
        source.sin_addr.s_addr = ip->saddr;
        memset(&dest, 0, sizeof(dest));
        dest.sin_addr.s_addr = ip->daddr;

        printf("\t|-Version : %d\n", (unsigned int)ip->version);

        printf("\t|-Internet Header Length : %d DWORDS or %d Bytes\n",
               (unsigned int)ip->ihl, ((unsigned int)(ip->ihl)) * 4);

        printf("\t|-Type Of Service : %d\n", (unsigned int)ip->tos);

        printf("\t|-Total Length : %d Bytes\n", ntohs(ip->tot_len));

        printf("\t|-Identification : %d\n", ntohs(ip->id));

        printf("\t|-Time To Live : %d\n", (unsigned int)ip->ttl);

        printf("\t|-Protocol : %d\n", (unsigned int)ip->protocol);

        printf("\t|-Header Checksum : %d\n", ntohs(ip->check));

        printf("\t|-Source IP : %s\n", inet_ntoa(source.sin_addr));

        printf("\t|-Destination IP : %s\n", inet_ntoa(dest.sin_addr));

        int i = sizeof(struct iphdr); /* print the payload */
        for (; i < sizeof(packet); i++)
        {
            printf("%c", packet[i]);
        }
        printf("\n");
    }
    return (0);
}