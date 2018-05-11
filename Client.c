/*******************************************************************************
 * Conor Ryan - Socket Programming - C					       *
 * Basic UDP Client 							       *
 * March 2018			       				               *
 *******************************************************************************/

//Header for bzero
#include <string.h>
//Header for exit
#include <stdlib.h>
//Header for read/write
#include <unistd.h>
//Header for printf
#include <stdio.h>
//Header for sockets
#include <netdb.h>

//Error function to display error messages
void error (char *msg)
{
	printf("%s",msg);
	exit(0);
}
//Main Function
int main (int argc, char *argv[])
{
	//Variables to store port number and status values
	int sock, port, status;

	//Structures to hold connection information
	struct sockaddr_in server;
	struct hostent *serv;

	//Array of characters to hold data sent/recieved
	char buffer [256];

	//Integer to store length of server structure
	int slength = sizeof(server);

	//Checks the program is given 3 arguements when run
	if (argc < 3)

		//Sends error message to error function
		error("To use: ./TCPClient IPAddress PortNo\n");

	//Converts arguement 2 from string to integer and stores as "port"
	port = atoi(argv[2]);

	//Takes arguement 1 and returns structure of type hostent
	serv = gethostbyname(argv[1]);

	//Checks if serv structure is empty
	if (serv == NULL)

		//Sends error message to error function
                error("No such host!\n");

	//Attempts to create socket and passes status value to "sock"
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	//Checks the status value in sock
	if (sock < 0)

		//Sends error message to error function
		error("Error opening socket!\n");

	//Zeroes server structure and slength integer
	bzero((char *) &server, slength);

	//Sets connection type as internet
	server.sin_family = AF_INET;

	//Copys server address from serv structure to server structure, along with server address length
	bcopy((char *)serv->h_addr, (char *)&server.sin_addr.s_addr, serv->h_length);

	//Takes value in "port", converts to network byte order and adds into port field of server structure
	server.sin_port = htons(port);

	//Asks user to input message to be sent
	printf("\nPlease enter message: ");

	//Empties the buffer
	bzero(buffer,256);

	//Takes the input from the user and adds to the buffer array
	fgets(buffer,255,stdin);

	//Attempts to write info contained in the buffer to the socket, passes status value to "status"
	status = sendto(sock,buffer,sizeof(buffer),0,(struct sockaddr *)&server,slength);

	//Checks the status value in "status"
	if (status < 0)

		//Sends error message to error function
		error("Message failed to Send!\n");

	//Prints data recieved from server stored in the buffer
	printf("\nMessage Sent!\n");

	//return 0 for lols
	return 0;
}
