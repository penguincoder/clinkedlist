/* LinkList: a circular linked list implementation for the TI-92+ graphing calculator */

//#define USE_TI92PLUS

#ifdef USE_TI92PLUS

#define ENABLE_ERROR_RETURN
#define OPTIMIZE_ROM_CALLS
#define SAVE_SCREEN

#include <tigcclib.h>

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#include "List.h"

void PrintList ( List *mylist ) {
	Node *P;
	unsigned short i = 0;
	P = mylist->RootNode->Next;
	printf ( "[ " );
	for ( i = 0; i < mylist->size; i++ )	{
		printf ( "[%s] ", (char *)P->NodeElement );
		if ( P->Next == NULL )
			break;
		else
			P = P->Next;
	}
	printf ( "]\n" );
}

short CompareString ( const Element Data1, const Element Data2 )	{
	return strcmp ( Data1, Data2 );
}

#ifdef USE_TI92PLUS

void _main ( void )

#else

int main ( void )

#endif
{
	List mylist;
	int i;
	Element tmp;
	Node *FindPtr;
	
#ifdef USE_TI92PLUS
	ClrScr();
#endif
	
 	MakeList ( &mylist, CompareString ); 
	PrintList ( &mylist );

	for ( i = 0; i < 10; i++ )	{
		tmp = malloc ( sizeof( Element ) * 3 );
		sprintf ( tmp, "%d", i );
		Push ( &mylist, tmp );
	}
	
	free ( Dequeue ( &mylist ) );
	
	tmp = malloc ( sizeof( Element ) * 3 );
	sprintf ( tmp, "%d", 20 );
	FindPtr = Find ( &mylist, (Element)"3" );
	InsertAt ( &mylist, tmp, FindPtr ); 
	
	tmp = malloc ( sizeof( Element ) * 4 );
	sprintf ( tmp, "%s", "FOO" );
	Enqueue ( &mylist, tmp ); 
	
	tmp = malloc ( sizeof( Element ) * 4 );
	sprintf ( tmp, "%s", "BAR" );
	Enqueue ( &mylist, tmp );

	PrintList ( &mylist );
	MakeEmpty ( &mylist );

#ifdef USE_TI92PLUS
	/* wait on keyboard input to continue */
	ngetchx();
#endif

#ifndef USE_TI92PLUS
	return 0;
#endif
}

