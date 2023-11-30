#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

//----------------------------------------------------------------------
//                           Vertex stuff:
//----------------------------------------------------------------------

/**
 * @brief La función comprueba si un vértice tiene vecinos.
 * 
 * @param v Un puntero a un objeto Vertex.
 * 
 * @return el valor de v->vecinos, que es un valor booleano.
 */
bool Vertex_HasNeighbors( Vertex* v )
{
   assert( v );

   return v->neighbors;
}

/**
 * @brief Hace que cursor libre apunte al inicio de la lista de vecinos. 
 * Se debe de llamar siempre que se vaya a iniciar un recorrido de dicha lista.
 *
 * @param v El vértice de trabajo (es decir, el vértice del cual queremos obtener
 * la lista de vecinos).
 */
void Vertex_Start( Vertex* v )
{
   assert( v );

   List_Cursor_front( v->neighbors );
}

/**
 * @brief Mueve al cursor libre un nodo adelante.
 *
 * @param v El vértice de trabajo.
 *
 * @pre El cursor apunta a un nodo válido.
 * @post El cursor se movió un elemento a la derecha en la lista de vecinos.
 */
void Vertex_Next( Vertex* v )
{
   List_Cursor_next( v->neighbors );
}

/**
 * @brief Indica si se alcanzó el final de la lista de vecinos.
 *
 * @param v El vértice de trabajo.
 *
 * @return true si se alcanazó el final de la lista; false en cualquier otro
 * caso.
 */
bool Vertex_End( const Vertex* v )
{
   return List_Cursor_end( v->neighbors );
}


/**
 * @brief Devuelve el índice del vecino al que apunta actualmente el cursor en la lista de vecinos
 * del vértice |v|.
 *
 * @param v El vértice de trabajo (del cual queremos conocer el índice de su vecino).
 *
 * @return El índice del vecino en la lista de vértices.
 *
 * @pre El cursor debe apuntar a un nodo válido en la lista de vecinos.
 */
Data* Vertex_GetNeighborIndex( const Vertex* v )
{
   return List_Cursor_get( v->neighbors );
}

/**
 * @brief Retoma los datos del vértice |v|.
 *
 * @param v El vértice de trabajo (del cual queremos conocer sus datos).
 *
 * @return Los datos del aeropuerto en el vertice.
 */
Airport* Vertex_GetData( const Vertex* v )
{
   return v->data;
}
//----------------------------------------------------------------------
//                     Funciones privadas
//----------------------------------------------------------------------

/**
 * @brief La función "buscar" busca una clave específica en una matriz de vértices y devuelve el índice del
 * vértice si se encuentra; de lo contrario, devuelve -1.
 * 
 * @param vertices Una matriz de objetos Vertex.
 * @param size El parámetro de tamaño representa el número de elementos en la matriz de vértices.
 * Indica la longitud o tamaño de la matriz.
 * @param key El parámetro clave es el valor que estamos buscando en la matriz de vértices.
 * 
 * @return el índice del vértice en la matriz `vértices` que tiene un `datos->id` igual a la `clave`.
 * Si no se encuentra dicho vértice, devuelve -1.
 */
static int find( Vertex vertices[], int size, int key )
{
   for( int i = 0; i < size; ++i )
   {
     if( vertices[i].data->id == key ) return i;
   }
   return -1;
}

/**
 * @brief La función comprueba si existe un índice determinado en la lista de vecinos de un vértice.
 * 
 * @param v Un puntero a un objeto Vertex.
 * @param index El parámetro de índice es un número entero que representa el índice del vecino que
 * intentamos encontrar en la lista de vecinos del vértice.
 * 
 * @return un valor booleano.
 */
static bool find_neighbor( Vertex* v, int index ){
  if( v->neighbors )
  {
    return List_Find( v->neighbors, index );
  }
  return false;
}

/**
 * @brief La función "insertar" agrega un nuevo vecino a un vértice determinado si aún no existe.
 * 
 * @param vertex Un puntero a una estructura Vertex. Es probable que esta estructura contenga
 * información sobre un vértice en un gráfico, como su índice y una lista de sus vecinos.
 * @param index El parámetro de índice representa el índice del vértice vecino que queremos insertar en
 * la lista de vecinos del vértice actual.
 * @param weight El parámetro de peso representa el peso del borde entre el vértice actual y el vértice
 * vecino en el índice dado.
 */
static void insert( Vertex* vertex, int index, int weight ){
  if( !vertex->neighbors ){
    vertex->neighbors = List_New();
  }
  if( vertex->neighbors && !find_neighbor( vertex, index ) ){
    List_Push_back( vertex->neighbors, index, weight );
  }
}

//----------------------------------------------------------------------
//                     Funciones públicas
//----------------------------------------------------------------------


/**
 * @brief Crea un nuevo grafo.
 *
 * @param size Número de vértices que tendrá el grafo. Este valor no se puede
 * cambiar luego de haberlo creado.
 *
 * @return Un nuevo grafo.
 *
 * @pre El número de elementos es mayor que 0.
 */
Graph* Graph_New( int size, eGraphType type ){
  assert( size > 0 );

  Graph* g = (Graph*) malloc( sizeof( Graph ) );
  if( g ){
    g->size = size;
    g->len = 0;
    g->type = type;

    g->vertices = (Vertex*) calloc( size, sizeof( Vertex ) );

    if( !g->vertices ){
      free( g );
      g = NULL;
    }
  }

  return g;
   // el cliente es responsable de verificar que el grafo se haya creado correctamente
}

/**
 * L@brief a función Graph_Delete elimina un gráfico y libera la memoria asignada para sus vértices 
 * y vecinos.
 * 
 * @param g Un puntero doble a una estructura Graph.
 */
void Graph_Delete( Graph** g ){
  assert( *g );

  Graph* graph = *g;
   // para simplificar la notación

  for( int i = 0; i < graph->size; ++i ){
    Vertex* vertex = &graph->vertices[ i ];
    // para simplificar la notación.
    // La variable |vertex| sólo existe dentro de este for.

    if( vertex->neighbors ){
      List_Delete( &(vertex->neighbors) );
    }
  }

  free( graph->vertices );
  free( graph );
  *g = NULL;
}

/**
 * @brief Devuelve una referencia al vértice indicado.
 *
 * Esta función puede ser utilizada con las operaciones @see Vertex_Start(), @see Vertex_End(), @see Vertex_Next().
 *
 * @param g          Un grafo
 * @param vertex_idx El índice del vértice del cual queremos devolver la referencia.
 *
 * @return La referencia al vértice vertex_idx.
 */
Vertex* Graph_GetVertexByIndex( const Graph* g, int vertex_idx ){
   assert( 0 <= vertex_idx && vertex_idx < g->len );

   return &(g->vertices[ vertex_idx ] );
}

/**
* @brief Devuelve una referencia al vértice indicado.
*
* Esta función puede ser utilizada con las operaciones @see Vertex_Start(), @see Vertex_End(), @see Vertex_Next().
*
* @param g   Un grafo
* @param key Llave de búsqueda (esto es, el |dato|) del vértice del cual queremos devolver la referencia.
*
* @return La referencia al vértice que coincida con key (esto es, con el |dato|).
*/
Vertex* Graph_GetVertexByKey( const Graph* g, int key )
{
  for( int i = 0; i < Graph_GetLen( g ); ++i ){
    if( g->vertices[ i ].data->id == key ){
      return &(g->vertices[i]);
    }
  }
  return NULL;
}

int Graph_Size( Graph* g ){
  return g->size;
}
/**
 * @brief Imprime un reporte del grafo
 *
 * @param g     El grafo.
 * @param depth Cuán detallado deberá ser el reporte (0: lo mínimo)
 */
void Graph_Print( Graph* g, int depth )
{
  for( int i = 0; i < g->len; ++i )
  {
    Vertex* vertex = Graph_GetVertexByIndex( g, i );
    // para simplificar la notación.

    printf( "[%d]%d=>", i, vertex->data->id );
    if( vertex->neighbors )
    {
      for(Vertex_Start(vertex); !Vertex_End(vertex); Vertex_Next(vertex) ){
        Data* d = Vertex_GetNeighborIndex( vertex );
        int neighbor_idx = d->index;

        printf( "%d->", Graph_GetDataByIndex( g, neighbor_idx )->id );
      }
    }
    printf( "Nil\n" );
  }
  printf( "\n" );
}

/**
 * @brief Crea un vértice a partir de los datos reales.
 *
 * @param g     El grafo.
 * @param data  Es la información.
 */
void Graph_AddVertex( Graph* g, int id, char iata_code[], char city[], char name[], int  utc_time ){
  assert( g->len < g->size );
  Airport* airport = (Airport*)malloc(sizeof(Airport));
  if(airport){
    Vertex* vertex = &g->vertices[ g->len ];
    airport->id = id;
    strcpy(airport->iata_code, iata_code);
    strcpy(airport->city, city);
    strcpy(airport->name, name);
    airport->utc_time = utc_time;
    vertex->data = airport;
    vertex->neighbors = NULL;
    g->len++;
  }
}

int Graph_GetSize( Graph* g )
{
   return g->size;
}


/**
 * @brief Inserta una relación de adyacencia del vértice |start| hacia el vértice |finish|.
 *
 * @param g      El grafo.
 * @param start  Vértice de salida (el dato)
 * @param finish Vertice de llegada (el dato)
 *
 * @return false si uno o ambos vértices no existen; true si la relación se creó con éxito.
 *
 * @pre El grafo no puede estar vacío.
 */
bool Graph_AddEdge( Graph* g, int start, int finish )
{
   assert( g->len > 0 );

   // obtenemos los índices correspondientes:
   int start_idx = find( g->vertices, g->size, start );
   int finish_idx = find( g->vertices, g->size, finish );
  
   if( start_idx == -1 || finish_idx == -1 ) return false;
   // uno o ambos vértices no existen

   insert( &g->vertices[ start_idx ], finish_idx, 0.0 );
   // insertamos la arista start-finish

   if( g->type == eGraphType_UNDIRECTED ) insert( &g->vertices[ finish_idx ], start_idx, 0.0 );
   // si el grafo no es dirigido, entonces insertamos la arista finish-start

   return true;
}

/**
 * @brief La función Graph_GetSize devuelve el tamaño de un gráfico.
 * 
 * @param g El parámetro "g" es un puntero a una estructura gráfica.
 * 
 * @return El tamaño del gráfico.
 */
int Graph_GetLen( const Graph* g )
{
   return g->len;
}

/**
 * @brief Devuelve la información asociada al vértice indicado.
 *
 * @param g          Un grafo.
 * @param vertex_idx El índice del vértice del cual queremos conocer su información.
 *
 * @return La información asociada al vértice vertex_idx.
 */

bool Graph_AddWeightedEdge( Graph* g, int start, int finish, int weight ){
  assert( g->len > 0 );

  // obtenemos los indices correspondientes:
  int start_idx = find( g->vertices, g->size, start );
  int finish_idx = find( g->vertices, g->size, finish );

  if( start_idx == -1 || finish_idx == -1 ){
    return false;
  }
  insert( &g->vertices[ start_idx ], finish_idx, weight );
  // insertamos la arista start-finish

  if( g->type == eGraphType_UNDIRECTED ){ 
    insert( &g->vertices[ finish_idx ], start_idx, weight );
  }
  // si el grafo no es dirigido, entonces insertamos la arista finish_idx
  return true;
}


/**
 * @brief La función Graph_GetWeight devuelve el peso del borde entre dos vértices en un gráfico.
 * 
 * @param g Un puntero a la estructura Graph.
 * @param start El vértice inicial de la arista para la que queremos encontrar el peso.
 * @param finish El parámetro "finalizar" en la función Graph_GetWeight es un número entero que
 * representa el índice o identificador del vértice para el que queremos encontrar el peso en el
 * gráfico.
 * 
 * @return el peso del borde entre los vértices inicial y final en el gráfico. Si no hay ningún borde
 * entre los vértices o si uno o ambos vértices no existen en el gráfico, la función devuelve -1.
 */
double Graph_GetWeight( Graph* g, int start, int finish ){
  assert(g->len > 0);

  //obtenemos los índices correspondientes
  int start_idx = find( g->vertices, g->size, start );
  int finish_idx = find(g->vertices, g->size, finish);

  if(start_idx == -1 || finish_idx == -1) return false;
  //uno o ambos vértices no existen
  Vertex* vertex = &g->vertices[start_idx];
  //recorre la lista de vecinos
  for(Vertex_Start(vertex); !Vertex_End(vertex); Vertex_Next(vertex)){
    Data* neighbor = Vertex_GetNeighborIndex( vertex );
    //if( Graph_GetDataByIndex( g, neighbor->index )->id == finish ) return neighbor->weight;
    if(neighbor->index == finish_idx) return neighbor->weight;
  }
  return -1;
}


/**
 * @brief Devuelve la información asociada al vértice indicado.
 *
 * @param g          Un grafo.
 * @param vertex_idx El índice del vértice del cual queremos conocer su información.
 *
 * @return La información asociada al vértice vertex_idx.
 */
Airport* Graph_GetDataByIndex( const Graph* g, int vertex_idx )
{
  assert( 0 <= vertex_idx && vertex_idx < g->len );
  return g->vertices[ vertex_idx ].data;
}

/**
 * @brief La función `Graph_GetIndexByValue` devuelve el índice de un vértice en un gráfico en función 
 * de su valor.
 * 
 * @param g Puntero a una estructura Graph.
 * @param value El parámetro de valor es el valor que desea buscar en el gráfico. Representa el ID de
 * un vértice en el gráfico.
 * 
 * @return La función `Graph_GetIndexByValue` devuelve el índice del vértice en el gráfico cuyos datos
 * tienen el valor especificado. Si no se encuentra ningún vértice con el valor especificado, devuelve
 * -1.
 */
int Graph_GetIndexByValue( const Graph* g, int value )
{
    for(int index = 0; index < Graph_GetLen(g); ++index){
        Vertex* vertex = Graph_GetVertexByIndex(g, index);
        if(vertex->data->id == value) return index;
    }
    return -1;
}

/**
 * @brief La función comprueba si dos aeropuertos son vecinos en un gráfico.
 * 
 * @param g Un puntero a una estructura gráfica.
 * @param dest El parámetro "dest" es un puntero a un objeto "Aeropuerto", que representa el aeropuerto
 * de destino.
 * @param src El aeropuerto de origen desde el que queremos comprobar si es vecino del aeropuerto de
 * destino.
 * 
 * @return un valor booleano. Devuelve verdadero si el aeropuerto de destino es vecino del aeropuerto
 * de origen en el gráfico dado y falso en caso contrario.
 */
bool Graph_IsNeighborOf( Graph* g, Airport* dest, Airport* src )
{
    Airport* s = src;
    Airport* d = dest;
    int s_idx = -1;
    int d_idx = -1;
    for( int i = 0; i < g->len; ++i )
    {
        if( s->id == g->vertices[ i ].data->id ) s_idx = i;
        if( d->id == g->vertices[ i ].data->id ) d_idx = i;
    }

    if( s_idx == -1 && d_idx == -1) return false;

    Vertex* v = Graph_GetVertexByIndex( g, s_idx );
    for( Vertex_Start( v ); !Vertex_End( v ); Vertex_Next( v ) )
    {
      Data* neighbor = Vertex_GetNeighborIndex( v );
      if( neighbor->index == d_idx) return true;
    }
    return false;
}

/**
 * @brief La función Graph_AirportsPrint imprime el código IATA y la ciudad de cada aeropuerto en 
 * un gráfico determinado.
 * 
 * @param g Puntero a una estructura Graph.
 */
void Graph_AirportsPrint( Graph* g ){
  for( int i = 0; i < g->len; ++i )
  {
    Airport* data = Graph_GetDataByIndex(g, i);
    printf( "[%s] %s\n", data->iata_code , data->city);
  }
  printf( "\n" );
}

/**
 * @brief La función "Graph_GetIndexByIATA" busca un aeropuerto en un gráfico por su código IATA y 
 * devuelve su índice.
 * 
 * @param g Puntero a una estructura Graph.
 * @param name El parámetro de nombre es una matriz de caracteres que representa el código IATA de un
 * aeropuerto.
 * 
 * @return el índice del aeropuerto en el gráfico que coincide con el código IATA dado. Si no se
 * encuentra ninguna coincidencia, devuelve -1.
 */
int Graph_GetIndexByIATA(Graph* g , char name[]){
  for(int index = 0; index < Graph_GetLen(g); ++index){
    Airport* airport = Graph_GetDataByIndex(g, index);
    char text[4]; 
    strcpy(text, name);
    if(strcmp(airport->iata_code, text) == 0){
      return index;
    }
  }
  return -1;
}