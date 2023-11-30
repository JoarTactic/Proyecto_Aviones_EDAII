#ifndef  GRAPH_INC
#define  GRAPH_INC

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "List.h"

typedef struct{
  int id;
  char iata_code[4]; // son 4 letras más el final de cadena
  char city[25]; // ciudad
  char name[65]; // nombre del aeropuerto
  int  utc_time; // tiempo UTC del país (México es -6)
} Airport;

//----------------------------------------------------------------------
//                           Vertex stuff:
//----------------------------------------------------------------------
/**
 * @brief Declara lo que es un vértice.
 */
typedef struct
{
  Airport* data;
  List* neighbors;
} Vertex;

//----------------------------------------------------------------------
//                           Graph stuff:
//----------------------------------------------------------------------

/** Tipo del grafo.
 */
typedef enum
{
   eGraphType_UNDIRECTED, ///< grafo no dirigido
   eGraphType_DIRECTED    ///< grafo dirigido (digraph)
} eGraphType;

/**
 * @brief Declara lo que es un grafo.
 */
typedef struct
{
   Vertex* vertices; ///< Lista de vértices
   int size;      ///< Tamaño de la lista de vértices
   int len;  
   eGraphType type; ///< tipo del grafo, UNDIRECTED o DIRECTED
} Graph;
//----------------------------------------------------------------------
//                     Funciones privadas
//----------------------------------------------------------------------
bool Vertex_HasNeighbors( Vertex* v );
void Vertex_Start( Vertex* v );
void Vertex_Next( Vertex* v );
bool Vertex_End( const Vertex* v );
Data* Vertex_GetNeighborIndex( const Vertex* v );

static int find( Vertex vertices[], int size, int key );
static bool find_neighbor( Vertex* v, int index );
static void insert( Vertex* vertex, int index, int weight );

//----------------------------------------------------------------------
//                     Funciones públicas
//----------------------------------------------------------------------
Graph* Graph_New( int size, eGraphType type );
void Graph_Delete( Graph** g );
Vertex* Graph_GetVertexByIndex( const Graph* g, int vertex_idx );
void Graph_Print( Graph* g, int depth );
void Graph_AddVertex( Graph* g, int id, char iata_code[], char city[], char name[], int  utc_time);
Vertex* Graph_GetVertexByKey( const Graph* g, int key );
int Graph_GetSize( Graph* g );
bool Graph_AddEdge( Graph* g, int start, int finish );
int Graph_GetLen( const Graph* g );
Airport* Graph_GetDataByIndex( const Graph* g, int vertex_idx );
bool Graph_AddWeightedEdge( Graph* g, int start, int finish, int weight );
double Graph_GetWeight( Graph* g, int start, int finish );
int Graph_GetIndexByValue( const Graph* g, int value );
bool Graph_IsNeighborOf( Graph* g, Airport* dest, Airport* src );

void Graph_AirportsPrint( Graph* g );
int Graph_GetIndexByIATA(Graph* g , char name[]);

#endif   /* ----- #ifndef GRAPH_INC  ----- */