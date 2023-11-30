#ifndef  BOLETO_INC
#define  BOLETO_INC
#define TAM_MAX 16

#include "List.h"
#include "Graph.h"

typedef struct{
  int price;
  int distance;
  int time;
  Airport* start;
  Airport* end;
} Ticket;

typedef struct{
  int len;
  int capacity;
  Ticket* boletos;
} Wallet;

Ticket* New_Ticket(int price, int distance, int time, Airport* start, Airport* end);
void Delete_Ticket( Ticket* ticket );
void swapTickets(Ticket* tickets[], int index1, int index2);
void TicketPrint(Ticket* ticket);

Wallet* Wallet_New(int capacity);
void Wallet_Delete(Wallet* wallet);
void Wallet_insert(Wallet* wallet, int price, int distance, int time, Airport* start, Airport* end);
void Wallet_Pop(Wallet* wallet, int index);
void Wallet_Print(Wallet* wallet);
bool Wallet_IsFull( Wallet* wallet );
bool Wallet_IsEmpty( Wallet* wallet );
size_t Wallet_Len( Wallet* wallet );
size_t Wallet_Capacity( Wallet* wallet );

#endif