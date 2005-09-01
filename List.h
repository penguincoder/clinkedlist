#ifndef __List_h

typedef void *Element;

typedef struct NodeTag	{
	Element NodeElement;
	struct NodeTag *Next;
	struct NodeTag *Previous;
} Node;

typedef struct	{
	Node *RootNode;
	short (*Compare) ( const Element Data1, const Element Data2 );
	unsigned short size;
} List;

/* Initializes the list.
 * Compare compares two Elements. Should return a value < 0
 * if Data1 < Data2, 0 if equal, and a value > 1 if Data1 > Data2
 */
void MakeList ( List *mylist, short (*Compare) ( const Element Data1, const Element Data2 ) );

/* Returns a pointer to a node containing Element Data */
Node *Find ( List *mylist, Element Data );
/* Returns the index-th item in the List */
Node *Get ( List *mylist, unsigned short index );
/* Inserts Data in front of Node Pos into the List */
short InsertAt ( List *mylist, Element Data, Node *Pos );

/* Returns true if list size is 0 */
short IsEmpty ( List *mylist );

/* Pushes Data into mylist as if it were a stack */
short Push ( List *mylist, Element Data );
/* Pops the top Element off mylist, must free the returned Element when done */
Element Pop ( List *mylist );
/* Enqueues Data as if List were a queue */
short Enqueue ( List *mylist, Element Data );
/* Dequeues the front Element off mylist, must free the returned Element when done */
Element Dequeue ( List *mylist );

/* Deletes the Node containing Data */
void Delete ( List *mylist, Element Data );
/* Deletes the index-th item in List */
void DeletePosition ( List *mylist, unsigned short index );
/* Completely empties a List. Must call MakeList to use again */
void MakeEmpty ( List *mylist );

#endif
