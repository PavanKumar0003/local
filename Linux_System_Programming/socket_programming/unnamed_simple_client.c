#include<stdio.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
#include<error.h>
#include<stdlib.h>
#include<unistd.h>

struct sockaddr_un client_add;

int main()
{

	int isocket_ID;
	int client_len;

	char Data_Buff[100];
	char ch[100];

	/*1. Create a socket and check whether socket is created or not*/
	if((isocket_ID = socket(AF_UNIX, SOCK_STREAM, 0))<0)
		perror(":socket creation Failed on Client\n");
	
	/*2.type setup */
	client_add.sun_family =  AF_UNIX;		//Family Local Communication on Unix
	strcpy(client_add.sun_path, "abc_socket");	//"abc_socket" is file name on current path
	client_len = sizeof(client_add);		//find length of server address

	/*3. Connect to the Server*/
	if(connect(isocket_ID, (struct sockaddr *) &client_add, client_len) == -1)
	{
		perror("Connection Failed on Client");
		exit(1);
	}

	/*6. Read/Write From Client*/
		
	//if(recv(isocket_ID, ch, strlen(ch)), 0);
	strcpy(Data_Buff, "echo from Client...");
	write(isocket_ID, Data_Buff, sizeof(Data_Buff));
	read(isocket_ID, ch, sizeof(ch));
	printf("Data from server = %s\n", ch);			//Read from client in to ch buffer
		
	/*7. Close the Socket Once R/W Operation completed*/
	close(isocket_ID);
	exit(0);
}


