#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "Boleto.h"
#include "Graph.h"
#define INFINITE 99999

/**
 * @brief La función "New_Ticket" crea un nuevo objeto de billete con el precio, la distancia, el 
 * tiempo, el aeropuerto de inicio y el aeropuerto de destino dados.
 * 
 * @param price El precio del billete.
 * @param distance El parámetro de distancia representa la distancia entre los aeropuertos de inicio y
 * fin en el billete.
 * @param time El parámetro "tiempo" representa la duración del vuelo en minutos.
 * @param start El aeropuerto de partida del billete. Es de tipo Aeropuerto* y contiene información
 * como el ID del aeropuerto, el código IATA, la ciudad, el nombre y la hora UTC.
 * @param end El parámetro "fin" es un puntero a una estructura de aeropuerto que representa el
 * aeropuerto de destino del billete.
 * 
 * @return un puntero a una estructura de Ticket.
 */
Ticket* New_Ticket(int price, int distance, int time, Airport* start, Airport* end){
  Ticket* tck = (Ticket*) malloc( sizeof(Ticket) );
  if( tck )
  {
    Airport* start_copy = (Airport*) malloc( sizeof(Airport) );
    if(start){
      Airport* end_copy = (Airport*) malloc( sizeof(Airport) );
      if(end){
        end_copy->id = end->id;
        strcpy(end_copy->iata_code, end->iata_code);
        strcpy(end_copy->city, end->city);
        strcpy(end_copy->name, end->name);
        end_copy->utc_time = end->utc_time;

        start_copy->id = start->id;
        strcpy(start_copy->iata_code, start->iata_code);
        strcpy(start_copy->city, start->city);
        strcpy(start_copy->name, start->name);
        end_copy->utc_time = start->utc_time;

        tck->price = price;  
        tck->distance = distance;
        tck->time = time;
      }
      else{
        free(start_copy);
        free(tck);
        tck = NULL;
      }
    }
    else{
      free(tck);
      tck = NULL;
    }
  }
  return tck;
}

/**
 * @brief La función "Delete_Ticket" libera la memoria asignada para un objeto de ticket y establece el
 * puntero del ticket en NULL.
 * 
 * @param ticket Un puntero a un objeto Ticket que debe eliminarse.
 */
void Delete_Ticket( Ticket* ticket )
{
  assert( ticket );
  free(ticket->start);
  free(ticket->end);
  free(ticket);
  ticket = NULL;
}

/**
 * @brief La función "swapTickets" intercambia dos elementos en una matriz de punteros de Ticket.
 * 
 * @param tickets Una serie de punteros a objetos Ticket.
 * @param index1 El índice del primer ticket de la matriz.
 * @param index2 El índice del segundo billete que se va a canjear.
 */
void swapTickets(Ticket* tickets[], int index1, int index2) {
   Ticket* temp = tickets[index1];
   tickets[index1] = tickets[index2];
   tickets[index2] = temp;
}

/**
 * @brief La función TicketPrint imprime información sobre un billete, incluida la información del 
 * aeropuerto de salida y llegada, el tiempo del vuelo y el precio del billete.
 * 
 * @param ticket Puntero a una estructura de ticket.
 */
void TicketPrint(Ticket* ticket){
  if(ticket){
    printf("Departure airport information: \n");
    printf("    - IATA: %s. Name: %s\n",ticket->start->iata_code,ticket->start->name);
    printf("Arrival airport: information\n");
    printf("    - IATA: %s. Name: %s\n",ticket->end->iata_code,ticket->end->name);
    printf("Flight time: %d minutes\n", ticket->time);
    printf("Ticket price: %d.00 MXN\n", ticket->price);
  }
}

/**
 * @brief La función "Wallet_New" crea una nueva billetera con una capacidad determinada.
 * 
 * @param capacity El parámetro de capacidad representa la cantidad máxima de boletos que puede
 * contener la billetera.
 * 
 * @return un puntero a una estructura de Wallet recién creada.
 */
Wallet* Wallet_New(int capacity){
    Wallet* new = (Wallet*)malloc(sizeof(Wallet));
  if(new){
    new->len = 0;
    new->capacity = capacity;
    new->boletos = (Ticket*)malloc(capacity * sizeof(Ticket));
    if(!new->boletos){
      free(new);
      new = NULL;
    }
  }
  return new;
}

/**
 * @brief La función Wallet_Delete libera la memoria asignada para una estructura Wallet y establece el
 * puntero en NULL.
 * 
 * @param wallet Un puntero a una estructura de Wallet.
 */
void Wallet_Delete(Wallet* wallet){
  if(wallet){
    free(wallet->boletos);
    free(wallet);
    wallet = NULL;
  }
}

/**
 * @brief  función Wallet_insert inserta un nuevo ticket en una billetera si no está llena.
 * 
 * @param wallet Puntero a una estructura de Wallet.
 * @param price El precio del billete.
 * @param distance El parámetro de distancia representa la distancia del vuelo en kilómetros.
 * @param time El parámetro "tiempo" representa la duración del vuelo en minutos.
 * @param start El parámetro "inicio" es un puntero a un objeto Aeropuerto que representa el aeropuerto
 * inicial del billete.
 * @param end El parámetro "fin" es un puntero a un objeto Aeropuerto, que representa el aeropuerto de
 * destino del billete.
 */
void Wallet_insert(Wallet* wallet, int price, int distance, int time, Airport* start, Airport* end){
  if(wallet){
    if(!Wallet_IsFull(wallet)){
      wallet->boletos[wallet->len] = *New_Ticket(price, distance, time, start, end);
      wallet->len++;
    }
  }
}

/**
 * @brief La función Wallet_Pop elimina un boleto de una billetera y desplaza los boletos restantes para
 * llenar el espacio vacío.
 * 
 * @param wallet Puntero a una estructura de Wallet.
 * @param index El parámetro de índice representa la posición del ticket en la billetera que debe
 * eliminarse.
 */
void Wallet_Pop(Wallet* wallet, int index){
  if(wallet){
    if(Wallet_Len(wallet) > 0){
      Ticket tmp = wallet->boletos[index];
      //Recorrer los elementos para evitar espacios vacios entre boletos
      for(size_t i = index; i < wallet->len; i++){
        swapTickets(&wallet->boletos, i, i+1);
      }
        wallet->len--;
    }
  }
}

/**
 * @brief La función Wallet_Print imprime los detalles de los tickets almacenados en una billetera.
 * 
 * @param wallet Un puntero a una estructura de Wallet.
 */
void Wallet_Print(Wallet* wallet){
  if(Wallet_Len(wallet) > 0){
    for(size_t i = 0; i < Wallet_Len(wallet); i++){
      printf("Ticket #1: \n");
      TicketPrint(&wallet->boletos[i]);
      printf("\n");
    }
    printf("-------------------------------------\n");
  }
  else{
    printf("Your wallet does not have yet a booked flight\n");
  }
}

/**
 * @brief La función comprueba si una billetera está llena comparando su longitud con su capacidad.
 * 
 * @param wallet El parámetro vallet es un puntero a una estructura Wallet.
 * 
 * @return un valor booleano, ya sea verdadero o falso.
 */
bool Wallet_IsFull( Wallet* wallet ){
  return wallet->len==wallet->capacity;
}

/**
 * @brief La función Wallet_IsEmpty comprueba si una billetera está vacía o no.
 * 
 * @param wallet El parámetro wallet es un puntero a un objeto Wallet.
 * 
 * @return un valor booleano que indica si la billetera está vacía o no.
 */
bool Wallet_IsEmpty( Wallet* wallet ){
  return wallet->len==0;
}

/**
 * @brief La función Wallet_Len devuelve la longitud de un objeto Wallet.
 * 
 * @param wallet El parámetro wallet es un puntero a un objeto Wallet.
 * 
 * @return la longitud de la billetera.
 */
size_t Wallet_Len( Wallet* wallet ){
  return wallet->len;
}

/**
 * @brief La función Wallet_Capacity devuelve la capacidad de un objeto Wallet.
 * 
 * @param wallet El parámetro wallet es un puntero a un objeto Wallet.
 * 
 * @return la capacidad de la billetera.
 */
size_t Wallet_Capacity( Wallet* wallet ){
  return wallet->capacity;
}
