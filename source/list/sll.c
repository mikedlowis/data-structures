#include <stdlib.h>
#include "sll.h"

sll_t* sll_new(void)
{
    sll_t* list = (sll_t*)malloc( sizeof( sll_t ) );
    list->head = NULL;
    list->tail = NULL;
    return list;
}

sll_node_t* sll_new_node(void* contents)
{
    sll_node_t* node = (sll_node_t*)malloc( sizeof( sll_node_t ) );
    node->contents = contents;
    node->next = NULL;
    return node;
}

void sll_free(sll_t* list, int free_contents)
{
    if( NULL != list )
    {
        sll_node_t* node = list->head;
        while( NULL != node )
        {
            sll_node_t* next = node->next;
            sll_free_node( node, free_contents );
            node = next;
        }
        free( list );
    }
}

void sll_free_node(sll_node_t* node, int free_contents)
{
    if( NULL != node )
    {
        if( 1 == free_contents )
        {
            free( node->contents );
        }
        free( node );
    }
}

sll_node_t* sll_front( sll_t* list )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        node = list->head;
    }
    return node;
}

sll_node_t* sll_back( sll_t* list )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        node = list->tail;
    }
    return node;
}

unsigned int sll_length(sll_t* list)
{
    unsigned int length = 0;
    if( NULL != list)
    {
        sll_node_t* node = list->head;
        while( NULL != node )
        {
            node = node->next;
            length++;
        }
    }
    return length;
}

sll_node_t* sll_index(sll_t* list, unsigned int index)
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        unsigned int cur_index = 0;
        sll_node_t* cur_node = list->head;
        while( NULL != cur_node )
        {
            if( cur_index == index )
            {
                node = cur_node;
                break;
            }
            cur_node = cur_node->next;
            cur_index++;
        }
    }
    return node;
}

sll_node_t* sll_push_front( sll_t* list, void* contents )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        node = sll_new_node( contents );
        node->next = list->head;
        list->head = node;
        if( NULL == list->tail )
        {
            list->tail = node;
        }
    }
    return node;
}

sll_node_t* sll_push_back( sll_t* list, void* contents )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        node = sll_new_node( contents );
        node->next = NULL;
        if( NULL == list->tail )
        {
            list->head = node;
            list->tail = node;
        }
        else
        {
            list->tail->next = node;
            list->tail = node;
        }
    }
    return node;
}

sll_node_t* sll_pop_front( sll_t* list )
{
    sll_node_t* node = NULL;
    if( (NULL != list) && (NULL != list->head) )
    {
        node = list->head;
        list->head = node->next;
        if( node == list->tail )
        {
            list->tail = NULL;
        }
    }
    return node;
}

sll_node_t* sll_pop_back( sll_t* list )
{
    sll_node_t* node = NULL;
    if( NULL != list )
    {
        if ( list->head == list->tail )
        {
            node = list->head;
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            sll_node_t* next_tail = list->head;
            while( next_tail->next != list->tail )
            {
                next_tail = next_tail->next;
            }
            node = next_tail->next;
            next_tail->next = NULL;
            list->tail = next_tail;
        }
    }
    return node;
}

sll_node_t* sll_insert( sll_t* list, unsigned int index, void* contents)
{
    sll_node_t* new_node = NULL;
    if( 0 == index )
    {
        new_node = sll_push_front( list, contents );
    }
    else
    {
        sll_node_t* prev_node = sll_index( list, index - 1 );
        if( NULL != prev_node )
        {
            sll_node_t* next_node = prev_node->next;
            new_node = sll_new_node( contents );
            new_node->next = next_node;
            prev_node->next = new_node;
            if( NULL == next_node )
            {
                list->tail = new_node;
            }
        }
    }
    return new_node;
}

sll_node_t* sll_delete( sll_t* list, unsigned int index, int free_contents)
{
    sll_node_t* node = NULL;

    if (0 == index)
    {
        node = sll_pop_front(list);
        if (NULL != node)
        {
            sll_free_node(node,free_contents);
            node = sll_front(list);
        }
    }
    else
    {
        sll_node_t* prev = sll_index(list,index-1);
        node = (NULL == prev) ? NULL : prev->next;
        if (NULL != node)
        {
            prev->next = node->next;
            if (NULL == prev->next)
            {
                list->tail = prev;
            }
            sll_free_node(node,free_contents);
            node = prev->next;
        }
    }

    return node;
}

