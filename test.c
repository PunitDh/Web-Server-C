#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void launch(struct Server *server) {
	char buffer[30000];
	int address_length = sizeof(server->address);
	int new_socket;

	while (1) {
		printf("====== WAITING FOR CONNECTION ======\n");	
		new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
		read(new_socket, buffer, 30000);
		printf("%s\n", buffer);
		char *hello = "Hello world";
		write(new_socket, hello, strlen(hello));
		close(new_socket);
	}
}

int main() {
	struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
	server.launch(&server);
}