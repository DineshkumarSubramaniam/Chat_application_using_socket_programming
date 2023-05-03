/* Program to demonstrate the client in socket */

// inet_addr()
#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//bzero()
#include <strings.h> 
#include <sys/socket.h>
//read(), write(), close()
#include <unistd.h>
//#define SA struct sockaddr

//Ports are unsigned 16-bit integers (0-65535) that identify a specific process, or network service
int PORT = 8080;

// Function designed for chat between client and server.
void func(int connfd)
{
	char buff[1024];
	int n;
	// infinite loop for chat
	while(1)
	{
		// This function is used to set all the socket structures with null values
		bzero(buff, sizeof(buff));

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));

		// print buffer which contains the client contents
		printf("From client: %s\t To client : ", buff);

		// This function is used to set all the socket structures with null values
		bzero(buff, sizeof(buff));
		n = 0;

		// copy server message in the buffer 
		// if char contains \n means jump to client
		while ((buff[n++] = getchar()) != '\n');

		// and sending that buffer to client
		write(connfd, buff, sizeof(buff));


		// if msg contains Exit then server exit and chat ended
                
		if (strncmp("exit", buff, 4) == 0) 
		{
			printf("Server Exit...\n");
			break;
		} 
		


	}
}

// main function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	// domain, type, protocol
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// successful creation returns 0, for unsuccessful creation returns -1
	if (sockfd < 0) 
	{
		printf(" *socket creation failed* \n");
		exit(0);
	}

	else
	{
		printf(" *Socket successfully created* \n");
	}

	/* Erases the data in the n bytes of the memory starting at the location pointed to  by s
	   Arguments -> structure, size */       
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	// AF_INET -> Address from the Internet
	servaddr.sin_family = AF_INET;

	// INADDR_ANY -> the IP address of the local computer
	servaddr.sin_addr.s_addr = INADDR_ANY ;

	//Assigning port -> 8080
	servaddr.sin_port = PORT;

	// Binding newly created socket to given IP and verification
	// BIND is a nameserver service responsible for performing domain-name-to-IP conversion on Linux-based DNS servers


	if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) 
	{
		printf(" *Binding failed* \n");
		exit(0);
	}
	else
		printf(" *Binded successfully* \n");


	// Now server is ready to listen and verification
	// 1 ->socket that will be used to accept incoming connection requests using accept 
	// 2 -> specifies the maximum number of connections the kernel should queue for this socket

	if ((listen(sockfd, 10)) != 0)
	{
		printf(" *Listen failed* \n");
		exit(0);
	}
	else
		printf(" *Server listening* \n");


	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
	if (connfd < 0) 
	{
		printf(" *server failed to accept client* \n");
		exit(0);
	}
	else
		printf(" *server accepted the client* \n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}

