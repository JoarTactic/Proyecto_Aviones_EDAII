#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
#include "Graph.h"
#include "Interfaz.h"
#include "Boleto.h"

#define MAX_VERTICES 10
#define INFINITE 1000000.0



int main(void) {
  Graph* grafo = Graph_New(MAX_VERTICES, eGraphType_UNDIRECTED ); 

  Graph_AddVertex( grafo, 100, "MEX", "Ciudad de México", "Aeropuerto Internacional Licenciado Benito Juarez",  -6 );
  Graph_AddVertex( grafo, 200, "ACA", "Acapulco", "Aeropuerto Internacional General Juan N. Alvarez",  -6 );
  Graph_AddVertex( grafo, 300, "AGU", "Aguascalientes", "Aeropuerto Internacional Jesús Terán Paredo",  -6 );
  Graph_AddVertex( grafo, 400, "CPE", "Campeche", "Aeropuerto Internacional Ingeniero Alberto Acuña Ongay",  -6 );
  Graph_AddVertex( grafo, 500, "CUN", "Cancún", "Aeropuerto Internacional de Cancún",  -5 );
  Graph_AddVertex( grafo, 600, "CYW", "Celaya", "Aeropuerto Nacional Capitán Rogelio Castillo",  -6 );
  Graph_AddVertex( grafo, 700, "CTM", "Chetumal", "Aeropuerto Intenacional de Chetumal",  -5 );
  Graph_AddVertex( grafo, 800, "CZA", "Chichen Itza", "Aeropuerto Internacional de Chichen Itza",  -6 );
  Graph_AddVertex( grafo, 900, "CUU", "Chihuahua", "Aeropuerto Internacional General Roberto Fierro Villalobos",  -6 );
  Graph_AddVertex( grafo, 1000, "CUA", "Ciudad Constitución", "Aeropuerto de Ciudad Constitución",  -7 );

  

  Graph_AddWeightedEdge( grafo, 100, 200, 307 );
  Graph_AddWeightedEdge( grafo, 100, 300, 422 );
  Graph_AddWeightedEdge( grafo, 100, 400, 899 );
  Graph_AddWeightedEdge( grafo, 100, 500, 1285 );
  Graph_AddWeightedEdge( grafo, 100, 600, 227 );
  Graph_AddWeightedEdge( grafo, 100, 700, 1135 );
  Graph_AddWeightedEdge( grafo, 100, 800, 1118 );
  Graph_AddWeightedEdge( grafo, 100, 900, 1245 );
  Graph_AddWeightedEdge( grafo, 100, 1000, 1434 );
  
  Graph_AddWeightedEdge( grafo, 200, 300, 603 );
  Graph_AddWeightedEdge( grafo, 200, 400, 1034 );
  Graph_AddWeightedEdge( grafo, 200, 500, 1435 );
  Graph_AddWeightedEdge( grafo, 200, 600, 438 );
  Graph_AddWeightedEdge( grafo, 200, 700, 1226 );
  Graph_AddWeightedEdge( grafo, 200, 800, 1266 );
  Graph_AddWeightedEdge( grafo, 200, 900, 1472 );
  Graph_AddWeightedEdge( grafo, 200, 1000, 1538 );

  Graph_AddWeightedEdge( grafo, 300, 400, 1246 );
  Graph_AddWeightedEdge( grafo, 300, 500, 1600 );
  Graph_AddWeightedEdge( grafo, 300, 600, 197 );
  Graph_AddWeightedEdge( grafo, 300, 700, 1503 );
  Graph_AddWeightedEdge( grafo, 300, 800, 1443 );
  Graph_AddWeightedEdge( grafo, 300, 900, 860 );
  Graph_AddWeightedEdge( grafo, 300, 1000, 1019 );

  Graph_AddWeightedEdge( grafo, 400, 500, 401 );
  Graph_AddWeightedEdge( grafo, 400, 600, 1087 );
  Graph_AddWeightedEdge( grafo, 400, 700, 271 );
  Graph_AddWeightedEdge( grafo, 400, 800, 233 );
  Graph_AddWeightedEdge( grafo, 400, 900, 1850 );
  Graph_AddWeightedEdge( grafo, 400, 1000, 2244 );
  
  Graph_AddWeightedEdge( grafo, 500, 600, 1457 );
  Graph_AddWeightedEdge( grafo, 500, 700, 320 );
  Graph_AddWeightedEdge( grafo, 500, 800, 169 );
  Graph_AddWeightedEdge( grafo, 500, 900, 2102 );
  Graph_AddWeightedEdge( grafo, 500, 1000, 2567 );
  
  Graph_AddWeightedEdge( grafo, 600, 700, 1335 );
  Graph_AddWeightedEdge( grafo, 600, 800, 1295 );
  Graph_AddWeightedEdge( grafo, 600, 900, 1042 );
  Graph_AddWeightedEdge( grafo, 600, 1000, 1208 );

  Graph_AddWeightedEdge( grafo, 700, 800, 238 );
  Graph_AddWeightedEdge( grafo, 700, 900, 2121 );
  Graph_AddWeightedEdge( grafo, 700, 1000, 2508 );

  Graph_AddWeightedEdge( grafo, 800, 900, 1981 );
  Graph_AddWeightedEdge( grafo, 800, 1000, 2182 );

  Graph_AddWeightedEdge( grafo, 900, 1000, 692 );

  menuPrincipal(grafo);
  
  
  Graph_Delete( &grafo );
  assert( grafo == NULL );
}