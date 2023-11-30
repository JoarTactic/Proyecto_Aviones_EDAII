#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "Interfaz.h"
#include "HT_Users.h"
#include "Graph.h"
#include "Boleto.h"

/**
 * @brief La función "menuPrincipal" muestra un menú para un programa llamado "Líneas SkyNet México" y
 * permite al usuario realizar diversas acciones como iniciar sesión, registrarse, mostrar usuarios,
 * eliminar una cuenta o salir del programa.
 * 
 * @param g El parámetro "g" es un puntero a un objeto Graph.
 */
void menuPrincipal( Graph* g ){
  Hash_table* tabla = HT_New( HASH_TABLE_SIZE );
  assert( tabla );                         // el programa se detiene si la tabla no se pudo crear
  assert( HT_IsEmpty( tabla ) == true );   // la tabla recién se creó, debe estar vacía

  int option = 0;
  bool menu = true;
  while(menu){
      system("clear");
    printf("%d", option);
      printf("-------------------------------------\n");
      printf("  Welcome to SkyNet Mexico Lines\n");
      printf("-------------------------------------\n");
      printf("Choose an option:\n");
      printf("1. Log in\n");            // Iniciar sesion
      printf("2. Sign up\n");           // Registrarse
      printf("3. Show users\n");        // Mostart Usuarios registrados
      printf("4. Delete account\n");    // Eliminar cuenta
      printf("5. Go out\n");
      printf("-------------------------------------\n");
      printf("Option: ");
      scanf("%d", &option);

      switch(option)
      {
          case 1:
          {
              system("clear");
              bool log_in = Log_In( tabla );
              if( log_in ) menuCliente( g );
              else printf("Could not log in, try again");
              getchar();
              getchar();
              break;
          }
          case 2:
          {
              system("clear");
              Sing_Up( tabla );
              getchar();
              getchar();
              break;
          }
          case 3:
          {
              system("clear");
              Show_Users( tabla );
              getchar();
              getchar();
              break;
          }
          case 4:
          {
              system("clear");
              Delete_Account( tabla );
              getchar();
              //getchar();
              break;
          }
          case 5:
          {
              system("clear");
              printf("Thanks for using SkyNet Mexico Lines");
              getchar();
              menu = false;
              break;
          }
          default:
          {
              printf("Invalid option.\n");
              getchar();
              menuPrincipal( g );
              break;
          }
      }
  }
  HT_Delete( &tabla );
  assert( tabla == NULL );
}

/**
 * @brief La función "menuCliente" muestra un menú para que el usuario elija opciones relacionadas con la
 * reserva de billetes, la visualización de viajes reservados o la baja.
 * 
 * @param g El parámetro "g" es un puntero a un objeto Graph, que probablemente representa una
 * estructura de datos de gráfico utilizada para almacenar información sobre rutas de vuelo y
 * conexiones.
 * @param wallet El parámetro "billetera" es un puntero a un objeto Wallet. Se utiliza para realizar un
 * seguimiento de los viajes reservados y otra información relacionada con las transacciones del
 * cliente.
 * 
 * @return vacío.
 */
void menuCliente( Graph* g, Wallet* wallet)
{
  system("clear");
  printf("-------------------------------------\n");
  printf("  Welcome to SkyNet Mexico Lines\n");
  printf("-------------------------------------\n");
  printf("Choose an option:\n");
  printf("1. Reserve ticket\n");
  printf("2. Your booked trips\n");
  printf("3. Sign off\n");
  printf("-------------------------------------\n");
  printf("Opcion: ");
  int opcion;
  scanf("%d", &opcion);
  switch(opcion){
    case 1:
      system("clear");
      reservarTicket( g, wallet );
      break;
    case 2:
      system("clear");
      tusViajes(wallet);
      break;
    case 3:
      printf("\nThank you for using SkyNet Mexico Lines.\n");
      getchar();
      return;
      break;
    default:
      printf("Invalid option.\n");
      getchar();
      menuCliente( g , wallet);
      break;
  }
}

/**
 * @brief La función "reservarTicket" permite al usuario reservar un vuelo seleccionando los aeropuertos de
 * salida y llegada, mostrando la información del vuelo y ofreciendo opciones para confirmar o cancelar
 * la reserva.
 * 
 * @param g Puntero a un objeto Graph que representa la red de aeropuertos y vuelos.
 * @param wallet El parámetro "billetera" es un puntero a un objeto Wallet. Se utiliza para realizar un
 * seguimiento de la información financiera del usuario, como su saldo y su historial de transacciones.
 * El objeto Wallet se utiliza para almacenar información sobre el billete de avión que el usuario
 * desea reservar, como el precio del billete, la distancia.
 */
void reservarTicket( Graph* g, Wallet* wallet)
{
  system("clear");
  printf("-------------------------------------\n");
  printf("              Booking\n");
  printf("-------------------------------------\n");
  printf("List of airports:\n");
  Graph_AirportsPrint( g );
  printf("-------------------------------------\n");
  
  char code1[4];
  printf("\nDeparture airport: ");
  scanf( "%3s", code1 );
  int idx1 = Graph_GetIndexByIATA(g , code1);
  
  char code2[4];
  printf("\nArrival airport: ");
  scanf( "%3s", code2 );
  int idx2 = Graph_GetIndexByIATA(g , code1);
  if( idx1 == -1 || idx2 == -1 ){
    printf("Invalid airport code. Press Enter to continue\n");
    printf("-------------------------------------\n");
    getchar();
    reservarTicket( g, wallet );
  }
  else{
    int dist = Graph_GetWeight( g, idx1, idx2 );
    int time_flight = dist/14;
    int ticket_price = dist*2 + 500;
    printf("-------------------------------------\n");
    printf("**Flight info:**\n");
    printf("%s --> %s \n", code1, code2);
    printf("Distance: %d km\n", dist);
    printf("Flight time: %d minutes\n", time_flight);
    printf("Ticket price: %d.00 MXN\n", ticket_price);
    printf("-------------------------------------\n");
    printf("Choose an option:\n");
    printf("1. Buy flight\n");
    printf("2. Go back to reserve tickets menu\n");
    printf("3. Go back to main menu\n");
    printf("-------------------------------------\n");
    printf("Opcion: ");
    int opcion;
    scanf("%d", &opcion);
    switch(opcion){
      case 1:
        system("clear");
        printf("-------------------------------------\n");
        printf("**Flight info:**\n");
        printf("Distance: %d km\n", dist);
        printf("Flight time: %d minutes\n", time_flight);
        printf("Ticket price: %d.00 MXN\n", ticket_price);
        printf("-------------------------------------\n");
        printf("Choose an option:\n");
        printf("1. Confirm booking\n");
        printf("2. Cancel booking\n");
        printf("-------------------------------------\n");
        printf("Opcion: ");
        int opcion2;
        scanf("%d", &opcion2);
        switch(opcion2){
          case 1:
            Airport* start = Graph_GetDataByIndex( g, idx1 );
            Airport* end = Graph_GetDataByIndex( g, idx2 ); 

            Wallet_insert(wallet, ticket_price, dist, time_flight, start, end);

            printf("Your flight was booked sucessfully!.\n");
            printf("Press Enter to continue\n");
            printf("-------------------------------------\n");
            getchar();
            break;
          case 2:
            menuCliente( g, wallet);
              break;
            default:
              printf("Invalid option.\n");
              break;
        }
      case 2:
        system("clear");
        reservarTicket( g, wallet);
        break;
      case 3:
        menuCliente( g, wallet);
        break;
      default:
        printf("Invalid option.\n");
        break;
    }  
  }
}

/**
 * @brief La función “tusViajes” permite al usuario cancelar un vuelo desde su billetera
 * o volver al menú principal.
 * 
 * @param wallet El parámetro "wallet" es un puntero a un objeto Wallet.
 */
void tusViajes(Wallet* wallet){
  system("clear");
  printf("-------------------------------------\n");
  Wallet_Print(wallet);
  printf("-------------------------------------\n");
  printf("Choose an option:\n");
  printf("1. Cancel a flight\n");
  printf("2. Go back to main menu\n");
  printf("-------------------------------------\n");
  printf("Opcion: ");
  int opcion;
  scanf("%d", &opcion);
  switch(opcion){
    case 1:
      printf("Please type the IATA code of the flight you want cancel");
      char code[4];
      scanf("%3s", code);
      Wallet_Pop(wallet, *code);
    break;
    case 2:
    menuCliente( wallet);
    break;
    default:
    printf("Invalid option.\n");
    break;
  }
}
