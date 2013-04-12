#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/** A linked list node. */
typedef struct list_node_t
{
    /** Pointer to the contents the node */
    void* contents;
    /** Pointer to next node in the list. */
    struct list_node_t* next;
} list_node_t;

/** A singly linked list */
typedef struct list_t
{
    /** Pointer to the first element in the list */
    list_node_t* head;
    /** Pointer to the last element in the list */
    list_node_t* tail;
} list_t;

/**
 * @brief Creates a new empty linked list.
 *
 * @return A pointer to the newly created list.
 **/
extern list_t* list_new(void);

/**
 * @brief Creates a new node with given contents.
 *
 * @param contents Pointer to the contents of this node.
 *
 * @return Pointer to newly created node.
 */
list_node_t* list_new_node(void* contents);

/**
 * @brief Frees all memory used by a linked list.
 *
 * This function loops through the supplied list and frees all nodes.
 * Also frees contents if free_contents is passed a non-zero value.
 *
 * @param list          The list to be freed.
 * @param free_contents Whether or not to also free the contents of each node.
 **/
void list_free(list_t* list, bool free_contents);

/**
 * @brief Frees all memory used by a node.
 *
 * This function frees all memory allocated to a node. Also frees contents if
 * the free_contents is 1.
 *
 * @param node
 * @param free_contents
 */
void list_free_node(list_node_t* node, bool free_contents);

/**
 * @brief Returns pointer to first node in the list
 *
 * @param list The list from which to retrieve elements.
 *
 * @return Pointer to the first element in the list.
 */
list_node_t* list_front( list_t* list );

/**
 * @brief Returns pointer to the last element in the list.
 *
 * @param The list from which to retrieve elements.
 *
 * @return Pointer to the last element in the list.
 */
list_node_t* list_back( list_t* list );

/**
 * @brief Returns the number of elements in the list.
 *
 * This function loops through the supplied list and returns a count of the
 * number of elements contained in the list.
 *
 * @param list The list to be counted.
 *
 * @return The number of elements in the list.
 **/
size_t list_size(list_t* list);

/**
 * @brief Returns whether the list is empty or not.
 *
 * @param list The list to operate on.
 *
 * @return Whether the list is empty, 1 for true and 0 for false.
 */
bool list_empty(list_t* list);

/**
 * @brief   Return the node at the specified index in a linked list.
 *
 * This function loops through the linked list and returns the node in the list
 * at the specified index. Returns NULL if the index is out of range.
 *
 * @param list  The list to search for the supplied index.
 * @param index The index of the node to return.
 *
 * @return A pointer to the node at the supplied index, NULL if out of range.
 **/
list_node_t* list_at(list_t* list, size_t index);

/**
 * @brief Adds a new node to the front of an existing linked list.
 *
 * This function creates a new node and pushes it to the beginning of the given
 * list. The newly created node becomes the new head of the list.
 *
 * @param list     The list to operate on.
 * @param contents The contents of the new node.
 *
 * @return Pointer to the newly added node.
 **/
list_node_t* list_push_front( list_t* list, void* contents );

/**
 * @brief Adds a new node to the end of an existing linked list.
 *
 * This function creates a new node and pushes it to the end of the given list.
 * The newly created node becomes the new tail of the list.
 *
 * @param list     The list to operate on.
 * @param contents The contents of the new node.
 *
 * @return Pointer to the newly added node.
 **/
list_node_t* list_push_back( list_t* list, void* contents );

/**
 * @brief Removes and returns a pointer to the first element of the list.
 *
 * This function removes the first node from the list and frees it's associated
 * memory.
 *
 * @param list          The lsit to operate on.
 *
 * @return Pointer to the newly added node.
 **/
list_node_t* list_pop_front( list_t* list );

/**
 * @brief Removes and returns a pointer to the last element of the list.
 *
 * This function removes the last node from the list and frees it's associated
 * memory.
 *
 * @param list          The list to operate on.
 *
 * @return Pointer to the newly added node.
 **/
list_node_t* list_pop_back( list_t* list );

/**
 * @brief Inserts a new node in a linked list at the specified index.
 *
 * This function traverses the list to the desired index and inserts a new node
 * with the given contents at that position. The node previously at the desired
 * index becomes the child of the new node.
 *
 * @param list     The list to operate on.
 * @param index    The index where the new node will be inserted.
 * @param contents The contents of the new node.
 *
 * @return Pointer to the newly inserted node, NULL if index is out of range.
 **/
list_node_t* list_insert( list_t* list, size_t index, void* contents);

/**
 * @brief Deletes a node from the supplied list.
 *
 * This function traverses the list to the desired index and frees the memory
 * allocated for that node. If the deleted node has a child then the child is
 * reattached to the deleted node's parent. If free_contents is passed a
 * non-zero value then the node's contents pointer is also freed.
 *
 * @param list          The list to operate on.
 * @param index         The index of the node to delete.
 * @param free_contents Whether or not to also free the contents of the node.
 *
 * @return Pointer to the node that is now at the supplied index.
 **/
list_node_t* list_delete( list_t* list, size_t index, bool free_contents);

/**
 * @brief Deletes all elements in the provided list
 *
 * @param list          The list to be cleared
 * @param free_contents Whether or not to also free the contents of every node.
 *
 * @return A pointer to the cleared list.
 */
list_t* list_clear(list_t* list, bool free_contents);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
