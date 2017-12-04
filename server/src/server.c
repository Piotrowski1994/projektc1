

/*
============================================================================
Name        : zad.c
Author      :
Version     :
Copyright   : Your copyright notice
Description : Hello World in C, Ansi-style
============================================================================
*/


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  /*tworzenie socketu*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*ustawienie wartosci*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = "127.0.0.1";
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*utworzenie servera*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));


  addr_size = sizeof serverStorage;

  while(1){
    /* otrzymanie wiadomosci */
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

    /*zmiana malych litera na male*/
    //for(i=0;i<nBytes-1;i++)
    //  buffer[i] = toupper(buffer[i]);
    /*wyswietlenie otrzymanej wiadomosci*/
    printf("wyslane do klienta: %s\n",buffer);
    /*odeslanie wiadomosci*/
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  }

  return 0;
}
