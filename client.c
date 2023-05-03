/* Program to demonstrate the client in socket */


// inet_addr()
#include <arpa/inet.h> 
#include <stdio.h>
#include <stdlib.h>
// for connect between server and client
#include <netdb.h>
#include <string.h>
//bzero()
#include <strings.h> 
#include <sys/socket.h>
//read(), write(), close()
#include <unistd.h>
//#define SA struct sockaddr

// global var
// Ports are unsigned 16-bit integers (0-65535) that identify a specific process, or network service
int PORT = 8080;

void func(int sockfd)
{
	char buff[1024];
	int n;
	// infinite loop to write
	while(1)
	{
		/* used to erase the buffer
		   This function is used to set all the socket structures with null values */
		bzero(buff, sizeof(buff));

		printf("To server: ");
		n = 0;

		// copy server message in the buffer
		// if char contains \n means jump to server
		while ((buff[n++] = getchar()) != '\n');

		// and sending that buffer to server
		write(sockfd, buff, sizeof(buff));

		/* used to erase the buffer
		   This function is used to set all the socket structures with null values */
		bzero(buff, sizeof(buff));

		// read the message from server and copy it in buffer
		read(sockfd, buff, sizeof(buff));

		// print buffer which contains the server contents
		printf("\tFrom Server : %s", buff);


		// if msg contains "Exit" then client exit and chat ended
                
		if ((strncmp(buff, "exit", 4)) == 0) 
		{
			printf("Client Exit...\n");
			break;
		} 
              
	}
}

int main()
{
	int sockfd, connfd;
	// Local computer ip
	char *ip = "127.0.0.1";
	//
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	// domain, type, protocol
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// condition's to check whether the socket created or not
	if (sockfd < 0) 
	{
		printf(" *socket creation failed* \n");
		exit(0); 
	}
	else
	{
		printf(" *Socket successfully created* \n");
	}
	/* erases the data in the n bytes of the memory starting at the location pointed to by s
	   Arguments -> structure, size */
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	// AF_INET -> Address from the Internet
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	//Assigning port  -> 8080
	servaddr.sin_port = PORT;

	// connect the client socket to server socket
	//if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!= 0)


	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))!= 0)
	{
		printf(" *connection with the server failed* \n");
		exit(0);
	}

	else
		printf(" *connected to the server* \n");


	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
