#ifndef  INTERFAZ_INC
#define  INTERFAZ_INC

#include "Graph.h"
#include "Boleto.h"

void menuPrincipal( Graph* g );
void registrarUsuario();
void inicioSesion();
void menuCliente( Graph* g, Wallet* wallet);

void reservarTicket( Graph* g, Wallet* wallet);
void tusViajes(Wallet* wallet);

#endif   /* ----- #ifndef INTERFAZ_INC  ----- */