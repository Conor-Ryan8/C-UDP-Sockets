/*******************************************************************************
 * Conor Ryan - Socket Programming					       *
 * Basic UDP Server 							       *
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
#include <netinet/in.h>

//Error function to display error messages
void error (char *msg)
{
	//Print the message passed to the function
	printf("%s",msg);

	//Exit the program
	exit(1);
}
//Main Function
int main (int argc, char *argv[]){

	//Variables to store port number and status values
	int sock, port, status;

	//Structure to hold connection information
	struct sockaddr_in server;

	//Array of characters to hold data sent/recieved
	char buffer [256];

	//Integer to store length of client & server structures
	int slength = sizeof(server);

	//Checks the program is given 2 arguements when run
	if (argc < 2)

		//Sends error message to error function
		error("To use: ./UDPServer PortNo\n");

	//Converts arguement 1 from string to integer and stores as "port"
	port = atoi(argv[1]);

	//Attempts to create socket and passes status value to "sock"
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	//Checks if socket creation worked by reading the status value in "sock"
	if (sock < 0)

		//Sends error message to error function
		error("Error opening socket!\n");

	//Zeroes server structure and slength integer
	bzero((char *) &server, slength);

	//Sets connection type as internet in family field of the serverstructure
	server.sin_family = AF_INET;

	//Takes value in "port", converts to network byte order and adds into port field of the server structure
	server.sin_port = htons(port);

	//Sets incoming address in the server structure to any
	server.sin_addr.s_addr = INADDR_ANY;

	//Attempts to bind the socket, checking bind does not return a null value indicating failure
	if (bind(sock, (struct sockaddr *) &server, slength) < 0)

		//Sends error message to error function
		error("Error on binding!\n");

	//Attempt to recieve message from the socket, passing status value to "status"
	status = recvfrom(sock, buffer, sizeof(buffer) -1, 0, NULL, 0);

	//Check to see if message was recieved by reading the status value "status"
	if (status < 0)

		//Sends error message to error function
		error("Message transmission failed!\n");

	//Display recieved message to the user
	printf("\nMessage recieved: %s\n",buffer);

	//Returns 0 for the lols
	return 0;
}


