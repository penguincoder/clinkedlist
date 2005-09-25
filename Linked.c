#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "List.h"

void MakeList ( List *mylist, short (*Compare) ( const Element Data1, const Element Data2 ) )	{
	mylist->RootNode = malloc ( sizeof( Node ) );
	if ( mylist->RootNode == NULL )
        return; /* out of memory */
	mylist->Compare = Compare;
	mylist->RootNode->Previous = NULL;
	mylist->RootNode->Next = NULL;
	mylist->RootNode->NodeElement = NULL;
	mylist->size = 0;
}

Node *Find ( List *mylist, Element Data )	{
	Node *n = mylist->RootNode;
    do  {
		if ( mylist->Compare ( n->NodeElement, Data ) == 0 )
			return n;
		n = n->Next;
	} while ( n != mylist->RootNode );

    /* not found */
	return NULL;
}

Node *Get ( List *mylist, unsigned long index )	{
	unsigned long i, halfsize;
	Node *GetPtr;

    /* gotta check for special case get's */
    if ( index == 0 )
        return mylist->RootNode;
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

short InsertAt ( List *mylist, Element Data, Node *Pos )	{
	Node *New = NULL;
	
	if ( mylist->size == 0 )	{
        New = mylist->RootNode;
        New->Next = NULL;
        New->Previous = NULL;
	} else {
    	New = malloc ( sizeof( Node ) );
	    if ( New == NULL )
            return 0;
	    New->Next = Pos;
    }
	
    New->NodeElement = Data;
	mylist->size++;
	
	if ( Pos != NULL )	{
		New->Previous = Pos->Previous;
		Pos->Previous = New;
	}
	if ( New->Previous != NULL )
		New->Previous->Next = New;
    return 1;
}

short IsEmpty ( List *mylist )	{
	return mylist->size == 0;
}

unsigned long ListSize ( List *mylist ) {
    return mylist->size;
}

short Push ( List *mylist, Element Data )	{
	return InsertAt ( mylist, Data, mylist->RootNode );
}

Element Pop ( List *mylist )	{
	Node *Return = NULL, *Next = NULL;
	Element data = NULL;
	Return = mylist->RootNode;
	
    if ( Return != NULL )   {
        Next = Return->Next;
    	mylist->RootNode = Next;
	    data = Return->NodeElement;
        if ( Return->Previous != NULL )
            Return->Previous->Next = Next;
        if ( Next != NULL ) {
            Next->Previous = Return->Previous;
            if ( Next->Previous == Next )
                Next->Previous = NULL;
            if ( Next->Next == Next )
                Next->Next = NULL;
        }
        free ( Return );
	    mylist->size--;
    }
	return data;
}

short Enqueue ( List *mylist, Element Data )	{
    if ( mylist->RootNode == NULL || mylist->RootNode->NodeElement == NULL )
        return InsertAt ( mylist, Data, mylist->RootNode );
	return InsertAt ( mylist, Data, mylist->RootNode->Previous );
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

void DeletePosition ( List *mylist, unsigned long index )	{
	Node *Deleted, *Prev, *Next;
	unsigned long i;
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
	
    next = NULL;
	node = mylist->RootNode;
	mylist->size = 0;
    if ( node == NULL )
        return;
    if ( node->Previous != NULL )
        node->Previous->Next = NULL;

    do  {
        next = node->Next;
		if ( node->NodeElement != NULL )
			free ( node->NodeElement );
		free ( node );
        node = next;
    } while ( node != NULL );
}
