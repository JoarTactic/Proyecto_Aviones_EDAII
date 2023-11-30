#ifndef  HT_USERS_INC
#define  HT_USERS_INC

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define TAM 32
#define TAM_PSW 6

#define HASH_TABLE_SIZE 10

/**
 * @brief Estado de la celda. Está codificado en el campo |id| de @see Entry_table
 */
enum
{
   EMPTY_CELL =   -1,
   DELETED_CELL = -2,
   USED_CELL =    -3,
};


typedef struct
{
   char name[32];
   char mail[32];
   char password[6];
   long int credit_card;
   int state;
} Users;

typedef struct
{
  Users*  table;         ///< Es la tabla hash
  size_t  capacity;      ///< Es el número máximo de elementos que la tabla puede almacenar
  size_t  len;           ///< Es el número actual de elementos en la tabla
} Hash_table;


// ----- Funciones privadas -----
Hash_table* HT_New( size_t capacity );
bool HT_Remove( Hash_table* ht, char* name );
bool HT_Search( const Hash_table* ht, Users* user );
bool HT_IsFull( const Hash_table* ht );
bool HT_IsEmpty( const Hash_table* ht );
bool HT_Insert( Hash_table* ht, Users* user );
void HT_Delete( Hash_table** ht );
int Len( Hash_table* ht );
static char probe( char* key, size_t i );
size_t h_gon99( char* s, size_t m );
int h_str_sum( char* str, int m );

// ----- Funciones Usuario -----
void Sing_Up( Hash_table* ht );
void Show_Users( Hash_table* ht );
bool Log_In( Hash_table* ht );
void Delete_Account( Hash_table* ht );

#endif