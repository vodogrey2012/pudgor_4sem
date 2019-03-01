#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "obj_dict.h"

#define ADDRESS struct node* p = ( struct node*)( t + 1)

#define LEFT 1
#define RIGHT 0

static struct node
{
    char* word;
    unsigned int index;
    struct node* left;
	struct node* right;
};

static struct node* node_newnode( struct node* node , int where , const char* wr)
{
	if( where == LEFT)
	{
		node->left = ( struct node*)calloc(1 , sizeof( struct node));
		node = node->left;
	}
	else
	{
		node->right = ( struct node*)calloc(1 , sizeof( struct node));
		node = node->right;
	}

	node->word = ( char*)calloc( (strlen( wr) + 1) , sizeof( char));
	sprintf( node->word , "%s" , wr);
	node->index = 1;
	node->left = NULL;
	node->right = NULL;

	return node;
}

static struct node* node_addword( struct node* node , const char* wr)
{
	struct node* ret = node;

	int compare = strcmp( node->word , wr);
	if( compare == 0)
	{
		node->index++;
		return NULL;
	}
	else if( compare > 0)
	{
		if( node->left != NULL)
			ret = node_addword( node->left , wr);
		else
			ret = node_newnode( node , LEFT , wr);
	}
	else
	{
		if( node->right != NULL)
			ret = node_addword( node->right , wr);
		else
			ret = node_newnode( node , RIGHT , wr);
	}
	
	return ret;

}

static void dictionary_addword( struct dictionary_fn* t , const char* wr)
{
    ADDRESS;
	node_addword( p , wr);
}

static void node_print( struct node* node)
{
	if( node->left)
		node_print( node->left);
	if( node->right)
		node_print( node->right);

	if( node->index != 0)
		printf("%s \t %d \n" , node->word , node->index);
	return;
}

static void dictionary_print( struct dictionary_fn* t)
{
    ADDRESS;

	node_print( p);
}

static void node_destroy( struct node* node)
{
	if( node->left)
	{
		node_destroy( node->left);
		free( node->left);
	}
	if( node->right)
	{
		node_destroy( node->right);
		free( node->right);
	}
	free( node->word);
}


static void dictionary_destroy( struct dictionary_fn* t)
{
    ADDRESS;
    node_destroy( p);
	free( t);
}



struct dictionary_fn* dictionary_create_tree()
{
    struct dictionary_fn* t = ( struct dictionary_fn*)calloc( sizeof( struct dictionary_fn) + sizeof( struct node) , 1);
    
    t->addword = &dictionary_addword;
    t->print = &dictionary_print;
    t->destroy = &dictionary_destroy;

   	ADDRESS;

    p->word = ( char*)calloc(1 , 1);
    p->index = 0;
    p->left = NULL;
	p->right = NULL;

    return t;
}
















