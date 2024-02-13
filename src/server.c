#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sockfd, newsockfd, portno, clilen, n;
    //sockfd, newsockfd are file descriptiors. Array subscriptis into the file descriptor table
    //These two variables store the values returned by the socke system call and the acept system call
    char buffer[256];

    //Define a structure containing an internet address

    struct sockaddr_in serv_addr; //server address
    struct sockaddr_in cli_addr; //client address

    /*
    struct sockaddr_in {
        short sin_family; //must be AF_INET
        u_short sin_port; //port number
        struct in_addr sin_addr; //internet address
        char sin_zero[8]; //not used
    }
    */
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    /*take 3 argument: address domain, type of socket, protocol
    adddress domain: There is only two possible address domain: Unix domain for two processes which share a common
    file system, and Internet domain for any two hosts on the Internet

    type of socket: stream socket which character are red in a continous stream as if from a file or pipe
    datagram socket, which read in chunks

    protocol: If this argument is zero, the operating system will choose the most appropriate protocol -> Will
    choose TCP for stream socket andn UDP for datagram socket

    The socket system call return an entry into the file descriptor table. This value is used for
    all subsequent references to this socket. If the socket call fails, it returns -1

    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    // set all values in a buffer to zero. Take a pointer to the buffer and the size of the buffer
    portno = atoi(argv[1]); //port number server is comunicating. Used atoi to convert digit to int
    serv_addr.sin_family = AF_INET;//should away be set to symbolic constant AF_INET
    serv_addr.sin_port = htons(portno); // htons() convert a port number to network byte order 
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    /*for server code,it aways contain the IP address of the machine the code is runing
        sumbolic onstant INADDR_ANY is used to get this address
    */
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    /*
        The bind syscall binds the socket to an address. Take three arguments: socket file descriptor, the address
        to which is bound, and the size of the addres to be bound
        The second arg is a poirnte rto struct sockaddr, but we passed sockaddr_in, and a cast is used
        This can be fails, if the socket is being used
    */
    listen(sockfd, 5);
    /*
        listen() syscall allows the process to listen on the socket for connections.
        1st arg is socket file descriptor, second is the size of the backlog queue.
        The backlog queue is the number of connections that can be waiting while the process is handling a particular
        connection. This should be set to 5, the maximum size permitted by most systems
        https://www.linuxhowtos.org/data/6/listen.txt -> more info
    */
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
    /*
        The accept(0) syscall make the process block until a client connects
        Wake the process when a connection from a client has been successfully established
        Return a file descriptor. All new communication should be done using the new file descriptor

    */
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
        error("ERROR reading from socket");
    }
    printf("Here is the message: %s\n", buffer);
    /*        The read call uses the new file descriptor, which returned by accept
        Read() will also block until there is something for it to read to the socket after the client
        executed write
    */
    n = write(newsockfd, "I got your message", 18);
    if (n < 0) {
        error("ERROR writing to socket");
    }

    return 0;

}
