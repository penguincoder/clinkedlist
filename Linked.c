#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "List.h"

void FatalError ( const char *ErrorMessage ) {
  printf ( "%s\n", ErrorMessage );
  exit ( 1 );
}

void MakeList ( List *mylist, short (*Compare) ( const Element Data1, const Element Data2 ) )	{
	mylist->RootNode = malloc ( sizeof( Node ) );
	if ( mylist->RootNode == NULL )
		FatalError ( "MakeList: Could not allocate a Node" );
	mylist->Compare = Compare;
	mylist->RootNode->Previous = NULL;
	mylist->RootNode->Next = NULL;
	mylist->RootNode->NodeElement = NULL;
	mylist->size = 0;
}

Node *Find ( List *mylist, Element Data )	{
	Node *n;
	n = mylist->RootNode->Next;
	while ( n != mylist->RootNode )	{
		if ( mylist->Compare ( n->NodeElement, Data ) == 0 )
			return n;
		n = n->Next;
	}
	return NULL;
}

Node *Get ( List *mylist, unsigned short index )	{
	unsigned short i, halfsize;
	Node *GetPtr;
	if ( index > mylist->size )
		return (Node *)NULL;
	halfsize = mylist->size / 2;
	if ( index > halfsize )	{
		GetPtr = mylist->RootNode->Previous;
		for ( i = 0; i < index; i++ )
			GetPtr = GetPtr->Previous;
	}
	else	{
		GetPtr = mylist->RootNode->Next;
		for ( i = 0; i < index; i++ )
			GetPtr = GetPtr->Next;
	}
	return GetPtr;
}

void InsertAt ( List *mylist, Element Data, Node *Pos )	{
	Node *New;
	New = malloc ( sizeof( Node ) );
	if ( New == NULL )
		FatalError ( "InsertAt: Could not allocate new Node" );
	
	New->NodeElement = Data;
	
	if ( mylist->size == 0 )	{
		New->Previous = mylist->RootNode;
		New->Next = mylist->RootNode;
		mylist->RootNode->Previous = New;
		mylist->RootNode->Next = New;
		mylist->size++;
		return;
	}
	
	mylist->size++;
	New->Next = Pos;
	
	if ( Pos != NULL )	{
		New->Previous = Pos->Previous;
		Pos->Previous = New;
	}
	if ( New->Previous != NULL )
		New->Previous->Next = New;
}

short IsEmpty ( List *mylist )	{
	return mylist->size == 0;
}

void Push ( List *mylist, Element Data )	{
	InsertAt ( mylist, Data, mylist->RootNode->Next );
}

Element Pop ( List *mylist )	{
	Node *Return, *Next;
	Element data;
	Return = mylist->RootNode->Next;
	if ( Return == NULL )
		return (Element)NULL;
	Next = Return->Next;
	mylist->RootNode->Next = Next;
	data = Return->NodeElement;
	free ( Return );
	mylist->size--;
	return data;
}

void Enqueue ( List *mylist, Element Data )	{
	InsertAt ( mylist, Data, mylist->RootNode );
}

Element Dequeue ( List *mylist )	{
	return Pop ( mylist );
}

void Delete ( List *mylist, Element Data )	{
	Node *Deleted;
	Deleted = Find ( mylist, Data );
	if ( Deleted == NULL )
		return;
	if ( Deleted->Next != NULL )
		Deleted->Next->Previous = Deleted->Previous;
	if ( Deleted->Previous != NULL )
		Deleted->Previous->Next = Deleted->Next;
	free ( Deleted->NodeElement );
	free ( Deleted );
}

void DeletePosition ( List *mylist, unsigned short index )	{
	Node *Deleted, *Prev, *Next;
	unsigned short i;
	Deleted = mylist->RootNode;
	for ( i = 0; i < index; i++ )	{
		Deleted = Deleted->Next;
		if ( Deleted == NULL )
			return;
	}
	Prev = Deleted->Previous;
	Next = Deleted->Next;
	free ( Deleted->NodeElement );
	free ( Deleted );
	if ( Prev != NULL )
		Prev->Next = Next;
	if ( Next != NULL )
		Next->Previous = Prev;
	mylist->size--;
}

void MakeEmpty ( List *mylist )	{
	Node *node, *next;
	unsigned short i = 0;
	next = NULL;
	node = mylist->RootNode;
	
	for ( i = 0; i <= mylist->size; i++ )	{
		next = node->Next;
		if ( node->NodeElement != NULL )
			free ( node->NodeElement );
		free ( node );
		node = next;
	}
	mylist->size = 0;
}
