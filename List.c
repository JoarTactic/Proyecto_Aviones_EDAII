#include "List.h"
#include <stdio.h>

/**
 * La función "new_node" crea un nuevo nodo con el índice y el peso dados y le devuelve un puntero.
 * 
 * @param index El parámetro de índice representa el índice o la posición del nodo en una estructura de
 * datos. Normalmente se utiliza para identificar o localizar un nodo específico dentro de la
 * estructura de datos.
 * @param weight El parámetro de peso representa el peso del nodo. Es un valor entero que indica la
 * importancia o significado del nodo en un contexto particular.
 * 
 * @return un puntero a un nodo recién creado.
 */
static Node* new_node( int index, int weight )
{
  Node* n = (Node*) malloc( sizeof( Node ) );
    if( n != NULL ){
      Data* d = (Data*) malloc( sizeof( Data ) );
      if( d != NULL ){
        d->index = index;
        d->weight = weight;

        n->data = d;
        n->next = NULL;
        n->prev = NULL;
      }
      else{free( n );}
   }

   return n;
}

/**
 * La función `List_New` crea una nueva lista e inicializa sus punteros primero, último y cursor en
 * NULL.
 * 
 * @return un puntero a una estructura de Lista recién asignada.
 */
List* List_New()
{
   List* lst = (List*) malloc( sizeof(List) );
   if( lst )
   {
      lst->first = lst->last = lst->cursor = NULL;
   }

   return lst;
}

/**
 * La función `List_Delete` elimina todos los elementos de una lista vinculada y libera la memoria.
 * 
 * @param p_list p_list es un puntero a un puntero a una estructura de Lista.
 */
void List_Delete( List** p_list )
{
   assert( *p_list );

   while( (*p_list)->first )
   {
      List_Pop_back( *p_list );
   }

   free( *p_list );
   *p_list = NULL;
}

/**
 * La función agrega un nuevo nodo con datos y peso al final de una lista vinculada.
 * 
 * @param list Un puntero a una estructura de Lista, que contiene información sobre la lista vinculada,
 * como el primer y último nodo.
 * @param data El parámetro "datos" es un valor entero que representa los datos que se almacenarán en
 * el nuevo nodo.
 * @param weight El parámetro "peso" en la función List_Push_back representa el peso asociado con los
 * datos que se agregan a la lista. Se utiliza para almacenar información adicional o metadatos
 * relacionados con el elemento de datos.
 */
void List_Push_back( List* list, int data, int weight )
{
   Node* n = new_node( data, weight );
   assert( n );

   if( list->first != NULL )
   {
      list->last->next = n;
      n->prev = list->last;
      list->last = n;
   }
   else
   {
      list->first = list->last = list->cursor = n;
   }
}

/**
 * La función elimina el último elemento de una lista vinculada.
 * 
 * @param list El parámetro "lista" es un puntero a una estructura de Lista.
 */
void List_Pop_back( List* list )
{
   assert( list->first );
   // ERR: no podemos borrar nada de una lista vacía

   if( list->last != list->first )
   {
      Node* x = list->last->prev;
      free( list->last );
      x->next = NULL;
      list->last = x;
   }
   else
   {
      free( list->last );
      list->first = list->last = list->cursor = NULL;
   }
}

/**
 * La función comprueba si una lista determinada está vacía o no.
 * 
 * @param list Un puntero a una estructura de lista.
 * 
 * @return un valor booleano.
 */
bool List_Is_empty( List* list )
{
   return !list->first;
}

/**
 * @brief Busca la primer ocurrencia con la llave key y si la encuentra coloca ahí al cursor.
 *
 * @param list Referencia a una lista.
 * @param key La llave de búsqueda.
 *
 * @return true si encontró el elemento; false en caso contrario.
 * @post Si hubo una ocurrencia el cursor es movido a esa posición; en caso contrario el cursor no se mueve.
 */
bool List_Find( List* list, int key )
{
  //Node* start = list->first;
  List_Cursor_front( list );
  while( !List_Cursor_end( list ) ){
    Data* valores = List_Cursor_get( list );
    int valor = valores->index;
    if( valor == key ){
      return true;
    }
    List_Cursor_next( list );
  }
  return false;
}

/**
 * La función coloca el cursor de una lista en el primer elemento.
 * 
 * @param list Un puntero a una estructura de lista.
 */
void List_Cursor_front( List* list )
{
   list->cursor = list->first;
}

/**
 * La función mueve el cursor de una lista al último elemento.
 * 
 * @param list Un puntero a una estructura de Lista.
 */
void List_Cursor_back( List* list )
{
   list->cursor = list->last;
}

/**
 * La función mueve el cursor al siguiente nodo en una lista vinculada y devuelve verdadero si tiene
 * éxito.
 * 
 * @param list Un puntero a una estructura de Lista.
 * 
 * @return el valor actualizado del cursor después de moverlo al siguiente nodo de la lista.
 */
bool List_Cursor_next( List* list )
{
   list->cursor = list->cursor->next;
   return list->cursor;
}

/**
 * La función comprueba si el cursor de una lista determinada está al final.
 * 
 * @param list Un puntero a una estructura de Lista.
 * 
 * @return un valor booleano.
 */
bool List_Cursor_end( List* list )
{
   return list->cursor == NULL;
}

/**
 * La función List_Cursor_get devuelve los datos almacenados en la posición actual del cursor en una
 * lista.
 * 
 * @param list Un puntero a una estructura de Lista.
 * 
 * @return los datos almacenados en el nodo señalado por el cursor en la lista dada.
 */
Data*  List_Cursor_get( List* list )
{
   assert( list->cursor );

   return list->cursor->data;
}

/**
 * @brief Aplica la función fn() a cada elemento de la lista. La función fn() es una función unaria.
 *
 * @param list Una lista.
 * @param fn Función unaria que será aplicada a cada elemento de la lista.
 */
void List_For_each( List* list, void (*fn)( int, int ) )
{
   Node* it = list->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL )
   {
      fn( it->data->index, it->data->weight );

      it = it->next;
   }
}