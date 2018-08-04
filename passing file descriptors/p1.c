#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>

#define ADDRESS "mysocket"



void function(int sig){

    int usfd;
    struct sockaddr_un userv_addr;
    int userv_len, ucli_len;

    usfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (usfd == -1)
        perror("\nsocket  ");

    bzero(&userv_addr, sizeof(userv_addr));
    userv_addr.sun_family = AF_UNIX;
    strcpy(userv_addr.sun_path, ADDRESS);

    userv_len = sizeof(userv_addr);

    if (connect(usfd, (struct sockaddr *)&userv_addr, userv_len) == -1)
        perror("\n connect ");

    else
        printf("\nconnect succesful");
    int pass;
    pass = recv_fd(usfd);
    
    send(pass, "hello1", 6, 0);

    send_to(usfd, pass);
    kill(shm_arr[5], SIGUSR1);
    shm_arr[5]=(shm_arr[5]+1)%4;
    shm_arr[5]++;

    
}

int send_fd(int socket, int fd_to_send)
{
    struct msghdr socket_message;
    struct iovec io_vector[1];
    struct cmsghdr *control_message = NULL;
    char message_buffer[1];
    /* storage space needed for an ancillary element with a paylod of length is CMSG_SPACE(sizeof(length)) */
    char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];
    int available_ancillary_element_buffer_space;

    /* at least one vector of one byte must be sent */
    message_buffer[0] = 'F';
    io_vector[0].iov_base = message_buffer;
    io_vector[0].iov_len = 1;

    /* initialize socket message */
    memset(&socket_message, 0, sizeof(struct msghdr));
    socket_message.msg_iov = io_vector;
    socket_message.msg_iovlen = 1;

    /* provide space for the ancillary data */
    available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));
    memset(ancillary_element_buffer, 0, available_ancillary_element_buffer_space);
    socket_message.msg_control = ancillary_element_buffer;
    socket_message.msg_controllen = available_ancillary_element_buffer_space;

    /* initialize a single ancillary data element for fd passing */
    control_message = CMSG_FIRSTHDR(&socket_message);
    control_message->cmsg_level = SOL_SOCKET;
    control_message->cmsg_type = SCM_RIGHTS;
    control_message->cmsg_len = CMSG_LEN(sizeof(int));
    *((int *)CMSG_DATA(control_message)) = fd_to_send;

    return sendmsg(socket, &socket_message, 0);
}

int main(int argc, char *argv[])
{

    size_t size;
    key_t mykey;
    int shmid,pid;
    pid = getpid();
    size = 5*sizeof(int);
    mykey = ftok(".",'x');
    shmid = shmget(mykey, size, IPC_CREAT|0666);
    shm_arr = (int*)shmat(shmid,NULL,0);


    struct sockaddr_un userv_addr, ucli_addr;
    int userv_len, ucli_len;

    int usfd = socket(AF_UNIX, SOCK_STREAM, 0);
    perror("socket");

    bzero(&userv_addr, sizeof(userv_addr));

    userv_addr.sun_family = AF_UNIX;
    strcpy(userv_addr.sun_path, ADDRESS);
    unlink(ADDRESS);
    userv_len = sizeof(userv_addr);

    if (bind(usfd, (struct sockaddr *)&userv_addr, userv_len) == -1)
        perror("server: bind");

    listen(usfd, 5);

    ucli_len = sizeof(ucli_addr);


    int nusfd = accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len);


    shm_arr[shm_arr[0]] =pid;
    
    signal(SIGUSR1, function);

    if([shm_arr[0] == 1)
    {
        if(argc!=2)
        printf("\n usage ./a.out port_no");

        int sfd;
        struct sockaddr_in serv_addr;
        int port_no=atoi(argv[1]);

        bzero(&serv_addr,sizeof(serv_addr));

        if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
        perror("\n socket");
        else printf("\n socket created successfully\n");

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port_no);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
        perror("\n connect : ");
        else printf("\nconnect succesful");

        send(sfd, "hello", 5, 0);

        shm_arr[0]++;

        int x = send_fd(nusfd, sfd);

        kill(shm_arr[5], SIGUSR1);
        shm_arr[5]=(shm_arr[5]+1)%4;
        shm_arr[5]++;
        
    }


    

    
        
    //printf("x %d", x);
}
