#include<stdio.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<error.h>
#include<stdlib.h>
#include<unistd.h>

struct sockaddr_un server_add;
struct sockaddr_un client_add;

int main()
{

	int isocket_ID;
	int iclient_ID;
	int server_len, client_len;

	char Data_Buff[100];
	/*0. Unlink First with abc local socket*/
	unlink("abc_socket");

	/*1. Create a socket and check whether socket is created or not*/
	if((isocket_ID = socket(AF_LOCAL, SOCK_STREAM, 0))<0)
		perror("socket creation Failed");
	
	/*2.Initalize strucure*/
	server_add.sun_family =  AF_UNIX;		//Family Local Communication on Unix
	strcpy(server_add.sun_path, "abc_socket");	//Path for data transfer "abc_socket" is file name on current path
	server_len = sizeof(server_add);		//find length of server address

	/*3.Bind*/
	if(bind(isocket_ID, (struct sockaddr *) &server_add, server_len) == -1)	//Bind a socket to isocket_ID
		perror("Binding error");

	/*4.Listen() -> Search for client's for max 5*/
	if(listen(isocket_ID, 5) == -1)
		perror("Listen error");

	/*Accept from the client and perform Read/Write Operations CONTINUOUSLY */
	while(1)
	{
		char ch[100];

		client_len = sizeof(client_add);	//client length

		/*5. Accept the client for the connection*/
		if((iclient_ID=accept(isocket_ID, (struct sockaddr *) &client_add, &client_len)) == -1)
			perror("Accept error");
		sleep(5);
		
		/*6. Read/Write From Client*/
		//if(recv(isocket_ID, ch, strlen(ch)), 0);
		read(iclient_ID, ch, sizeof(ch));			//Read from client in to ch buffer
		printf("Data from client = %s\n", ch);
		strcpy(Data_Buff, "echo from Server...");		//copy msg to data to be send buffer
		write(iclient_ID, Data_Buff, sizeof(Data_Buff));	//send msg to client

		/*7. Close the Socket Once R/W Operation completed*/
		close(iclient_ID);
	}
}


