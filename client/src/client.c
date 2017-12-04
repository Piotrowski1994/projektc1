#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  char buffer1[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*tworzenie socketu udp*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*ustawianie wartosci*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);


  addr_size = sizeof serverAddr;

  while(1){
    printf("Wpisz wiadomosc do servera:\n");
    fgets(buffer,1024,stdin);
    printf("wpisales: %s",buffer);

    nBytes = strlen(buffer) + 1;

    /*wyslanie wiadmomosci*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

    /*otrzymanie wiadomosci*/
                nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

    printf("otrzymano z servera: %s\n",buffer);
  }

  return 0;
}

