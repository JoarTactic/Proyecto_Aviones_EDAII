
#include "HT_Users.h"
#include "List.h"
//----------------------------------------------------------------------
//            Funciones de la interfaz de Usuario de la HT
//----------------------------------------------------------------------

/**
 * @brief Muestra los usuarios registrados en ese momento.
 *
 * @param ht Referencia a la tabla hash.
 */
void Show_Users( Hash_table* ht )
{
    assert( ht );
    if( HT_IsEmpty( ht ) )
    {
        fprintf( stderr, "No registered user.");
    }
    else{
        fprintf( stderr, "\t------- REGISTERED USERS -------");
        for( size_t i = 0; i < ht->capacity; ++i )
        {
            if( ht->table[i].state == USED_CELL )
            {
                printf( "\n[%02ld]   Name: %s"
                        "       Mail: %s"
                        "   Password: %c***\n"
                        "Credit Card: ************%04ld\n", 
                        i, ht->table[ i ].name,ht->table[ i ].mail, ht->table[ i ].password[0], 
                        ht->table[ i ].credit_card % 10000 );
            }
        }
    }
}

/**
 * @brief Elimina un usuario.
 *
 * @param ht Referencia a la tabla hash.
 */
void Delete_Account( Hash_table* ht )
{
    getchar();
    assert( ht );

    Show_Users( ht );
    Users user;
    if( HT_IsEmpty( ht ) )
    {
        fprintf( stderr, "There are no registered users");
        return;
    }
    else{
        bool search = false;
        while( search != true )
        {
            fprintf( stderr, "\nEnter the name of the user you want to delete: ");
            fgets( user.name, TAM, stdin );

            if( !HT_Search( ht, &user ) )
            {
                fprintf( stderr, "The user doesn't exist, enter it again");
            }
            else{ 
                search = true;
                if( HT_Remove( ht, user.name ) )
                {
                    fprintf( stderr, "\n\tUser successfully deleted!");
                }
                else{
                    fprintf( stderr, "The user could not be deleted, please try again");
                }
            }
        }
    }
}

/**
 * @brief Verifica al usuario que está iniciando sesion.
 *
 * @param ht Referencia a la tabla hash.
 *
 * @return true si el usuario y contraseña son correctos; false en caso contrario.
 */
bool Log_In( Hash_table* ht )
{
    getchar();
    assert( ht );

    Users user;
    if( HT_IsEmpty( ht ) )
    {
        fprintf( stderr, "There are no registered users");
        return false;
    }
    else{
        fprintf( stderr, "\t------- LOGGING IN -------");
        bool search = false;
        while( search != true )
        {
            fprintf( stderr, "\nEnter username: ");
            fgets( user.name, TAM, stdin );

            if( !HT_Search( ht, &user ) )
            {
                fprintf( stderr, "The user doesn't exist, enter it again");
            }
            else{ 
                search = true;
            }
        }

        Users temp;
        fprintf( stderr, "\nPassword: ");
        fgets( temp.password, TAM_PSW, stdin );

        if( !strcmp( user.password, temp.password ) )
        {
            fprintf( stderr, "Incorrect password");
            return false;
        }
        else{
            return true;
        }
    }
}


/**
 * @brief Reune la información necesaria para registrar a un usuario nuevo.
 *
 * @param ht Referencia a la tabla hash
 */
void Sing_Up( Hash_table* ht )
{
    getchar();
    Users user;

    fprintf( stderr, "\t-----DATA FOR REGISTRATION-----\n" );
    fprintf( stderr, "Name: " );
    fgets(user.name, TAM, stdin);

    fprintf( stderr, "Mail: " );
    fgets(user.mail, TAM, stdin);

    char pass1[ TAM_PSW ];
    fprintf( stderr, "Password (4 characters): " );
    fgets(pass1, TAM_PSW, stdin);

    char pass2[ TAM_PSW ];
    fprintf( stderr, "Confirm Password: " );
    fgets(pass2, TAM_PSW, stdin);

    while( strcmp( pass1, pass2 ) )
    {
        fprintf( stderr, "Password doesn't match! Enter it again: ");
        fgets(pass2, TAM_PSW, stdin);
    }
    strcpy(user.password, pass2);

    fprintf( stderr, "Credit Card (16 numbers): " );
    scanf("%ld", &user.credit_card);

    if( HT_Insert( ht, &user ) )
    {
        fprintf( stderr, "\t¡Successful registration!" );
    }
    else{
        fprintf( stderr, "Registration couldn't be successful, please try again");
    }
}



//----------------------------------------------------------------------
//                     Funciones privadas
//----------------------------------------------------------------------


/**
 * @brief Calcula el índice para la HT de una cadena de caracteres
 *
 * @param s que es la cadena a la que le vamos a calcular su índice
 *
 * @return Un entero que será usado como índice de la HT.
 */
size_t h_gon99( char* s, size_t m )
{
    size_t res;
    for( res=0; *s; ++s)
    {
        res = 131 * res + *s; 
    }

    return res % m;
}

/**
 * @brief Calcula un nuevo índice para la HT de una cadena de caracteres en
 * caso de una colisión
 *
 * @param key que es la cadena a la que le vamos a calcular su índice e i que
 * es el indice calculado previamente con h_gon99()
 *
 * @return Un entero que será usado como nuevo índice para la HT.
 */
static char probe( char* key, size_t i )
{
   return i + 1;
}

/**
 * @brief Retoma la información del numero de registros
 *
 * @param Una tabla hash
 *
 * @return El numero de registros en la HT
 */
int Len( Hash_table* ht )
{
    return ht->len;
}


/**
 * @brief Crea una nueva tabla hash
 *
 * @param capacity Número de celdas (slots) que tendrá la tabla. Es recomendable utilizar
 * un valor mayor al número de elementos que se quiere guardar
 * 
 * @return Una referencia a una tabla hash
 */
Hash_table* HT_New( size_t capacity )
{
   Hash_table* ht = ( Hash_table* )malloc( sizeof( Hash_table ) );
   if( NULL != ht )
   {
      ht->len = 0;
      ht->capacity = capacity;

      ht->table = ( Users* ) malloc( capacity * sizeof( Users ) );
      if( NULL != ht->table )
      {
         for( int i = 0; i < ht->capacity; ++i )
         {
            ht->table[ i ].state = EMPTY_CELL;
            // en esta aplicación los ID's son enteros positivos

            strncpy(ht->table[ i ].password, "", TAM_PSW );
         }
      }
      else
      {
         free( ht );
         ht = NULL;
      }
   }

   return ht;
}

/**
 * @brief Destruye una tabla hash
 *
 * @param ht La dirección de una referencia a una tabla hash
 */
void HT_Delete( Hash_table** ht )
{
   assert( ht );

   free( (*ht)->table );
   free( *ht );
   *ht = NULL;
}

/**
 * @brief Inserta el campo |name| en la tabla hash.
 *
 * @param ht Referencia a una tabla hash
 * @param user Referencia a un usuario a registrar
 *
 * @return true si el elemento pudo ser insertado; false en caso contrario (elemento
 * duplicado, tabla llena, etc).
 */
bool HT_Insert( Hash_table* ht, Users* user )
{
   assert( ht );
   assert( !HT_IsFull(ht) );

   int pos;
   // índice que se actualizará en cada colisión

   // calcula una hash key base
   int home = pos = h_gon99( user->name, ht->capacity );

   int i = 0;

   // si el slot está desocupado, se salta el while; en caso contrario entra a buscar uno.
   // Asumimos que hay más slots que datos a guardar:
    while( ht->table[ pos ].state == -3 )
    {
      // no aceptamos duplicados:
      if( ht->table[ pos ].name == user->name )
      {
         //Llave duplicada
         return false;
      }

      pos = ( home + probe( user->name, i ) ) % ht->capacity;
      ++i;
    }

    strncpy(ht->table[ pos ].name, user->name, TAM );
    strncpy(ht->table[ pos ].mail, user->mail, TAM );
    strncpy(ht->table[ pos ].password, user->password, TAM_PSW );
    ht->table[ pos ].credit_card = user->credit_card;
    ht->table[ pos ].state = USED_CELL;

   ++ht->len;

   return true;
}

/**
 * @brief Verifica si la tabla hash está vacía o no.
 *
 * @param ht Referencia a una tabla hash.
 *
 * @return true la tabla hash está vacía; false en caso contrario.
 */
bool HT_IsEmpty( const Hash_table* ht )
{
   return ht->len == 0;
}

/**
 * @brief Verifica si la tabla hash está llena o no.
 *
 * @param ht Referencia a una tabla hash.
 *
 * @return true la tabla hash está llena; false en caso contrario.
 */
bool HT_IsFull( const Hash_table* ht )
{
   return ht->len == ht->capacity;
}


/**
 * @brief Busca en la tabla hash los datos de usuario correspondiente a la llave 
 * name del empleado.
 *
 * @param ht Referencia a una tabla hash.
 * @param user Argumento que guardará los datos del usuario (en caso de que éste 
 * exista en la tabla hash)
 *
 * @return true si el elemento fue encontrado; false en caso contrario.
 */
bool HT_Search( const Hash_table* ht, Users* user )
{
   assert( ht );
   assert( ht->len > 0 );

   int home = h_gon99( user->name, ht->capacity);
   int pos = home;

   bool found = false;
   if( strcmp( ht->table[ pos ].name, user->name ) )
   {
      found = true;
   }
   else if( ht->table[ pos ].state == EMPTY_CELL )
   {
      found = false;
   }
   else
   {
      int i = 0;
      while( ht->table[ pos ].state != EMPTY_CELL && found == false )
      {
         pos = ( home + probe( user->name, i ) ) % ht->capacity;
         ++i;

         if( strcmp( ht->table[ pos ].name, user->name ) )
         {
            found = true;
         }
      }
   }

   bool ret_val = false;
   if( found )
   {
        strncpy(ht->table[ pos ].name, user->name, TAM );
        strncpy(ht->table[ pos ].mail, user->mail, TAM );
        strncpy(ht->table[ pos ].password, user->password, TAM_PSW );
        ht->table[ pos ].credit_card = user->credit_card;
        ht->table[ pos ].state = DELETED_CELL;
        ret_val = true;
   }
   return ret_val;
}

/**
 * @brief Elimina una entrada en la tabla hash.
 *
 * @param ht Referencia a una tabla hash.
 * @param name La llave de la entrada que se desea eliminar.
 *
 * @return true si el elemento existía; false si el elemento no existe.
 */
bool HT_Remove( Hash_table* ht, char* name )
{
   int home = h_gon99( name, ht->capacity);

    if( strcmp( ht->table[home].name, name ) )
    {
        strncpy(ht->table[home].name, " ", TAM);
        strncpy(ht->table[home].mail, " ", TAM);
        strncpy(ht->table[home].password, " ", TAM_PSW );
        ht->table[home].credit_card = 0;
        ht->table[home].state = DELETED_CELL;

        --ht->len;

        return true;
    }
    else{
        int new_pos = home;
        int i = 0;

        while( ht->table[new_pos].state != EMPTY_CELL )
        {
            new_pos = ( home + probe( name, i ) ) % ht->capacity;
            ++i;

            if( strcmp( ht->table[new_pos].name, name ) )
            {
                ht->table[home].state = DELETED_CELL;
                strcpy(ht->table[home].name, " ");
                strcpy(ht->table[home].mail, " ");
                strcpy(ht->table[home].password, " ");
                ht->table[home].credit_card = 0;

                --ht->len;
                return true;
            }
        }

        return false;
    }
}