// Unit Test Framework Includes
#include "test.h"

// File To Test
#include "list.h"
#include "mem.h"

static void test_setup(void) { }

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
TEST_SUITE(List) {
    //-------------------------------------------------------------------------
    // Test list_new function
    //-------------------------------------------------------------------------
    TEST(Verify_list_new_returns_newly_allocated_empty_list)
    {
        list_t* list = list_new();
        CHECK( NULL != list );
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release( list );
    }

    //-------------------------------------------------------------------------
    // Test list_new_node function
    //-------------------------------------------------------------------------
    TEST(Verify_list_new_node_returns_newly_allocated_node_with_given_contents)
    {
        list_node_t* node = list_new_node( mem_box(0) );
        CHECK( NULL != node );
        CHECK( 0 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        mem_release( node );
    }

    //-------------------------------------------------------------------------
    // Test list_front function
    //-------------------------------------------------------------------------
    TEST(Verify_list_front_returns_NULL_if_list_is_empty)
    {
        list_t list = { NULL, NULL };
        CHECK( NULL == list_front( &list ) );
    }

    TEST(Verify_list_front_returns_the_head_of_the_list)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };
        CHECK( &node1 == list_front( &list ) );
    }

    //-------------------------------------------------------------------------
    // Test list_back function
    //-------------------------------------------------------------------------
    TEST(Verify_list_back_returns_NULL_if_list_is_empty)
    {
        list_t list = { NULL, NULL };
        CHECK( NULL == list_back( &list ) );
    }

    TEST(Verify_list_back_returns_the_tail_of_the_list)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };
        CHECK( &node2 == list_back( &list ) );
    }

    //-------------------------------------------------------------------------
    // Test list_size function
    //-------------------------------------------------------------------------
    TEST(Verify_list_size_returns_0_when_list_is_empty)
    {
        list_t* list = list_new();
        CHECK( 0 == list_size( list ) );
        mem_release( list );
    }

    TEST(Verify_list_size_returns_1_when_list_is_length_1)
    {
        list_node_t node1 = { NULL, NULL };
        list_t list = { &node1, &node1 };

        CHECK( 1 == list_size( &list ) );
    }

    TEST(Verify_list_size_returns_2_when_list_is_length_2)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };

        CHECK( 2 == list_size( &list ) );
    }

    //-------------------------------------------------------------------------
    // Test list_empty function
    //-------------------------------------------------------------------------
    TEST(Verify_list_empty_returns_true_when_head_and_tail_are_null)
    {
        list_t list = { NULL, NULL };
        CHECK( 1 == list_empty( &list ) );
    }

    TEST(Verify_list_empty_returns_false_when_head_is_not_null)
    {
        list_t list = { (list_node_t*)0x1234, NULL };
        CHECK( 0 == list_empty( &list ) );
    }

    TEST(Verify_list_empty_returns_false_when_tail_is_not_null)
    {
        list_t list = { NULL, (list_node_t*)0x1234 };
        CHECK( 0 == list_empty( &list ) );
    }

    //-------------------------------------------------------------------------
    // Test list_prev function
    //-------------------------------------------------------------------------
    TEST(Verify_list_prev_returns_NULL_when_list_is_empty)
    {
        list_t list = { NULL, NULL };
        list_node_t bogus = { NULL, NULL };
        CHECK( NULL == list_prev(&list, NULL) );
        CHECK( NULL == list_prev(&list, &bogus) );
    }

    TEST(Verify_list_prev_returns_NULL_when_given_NULL)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( NULL == list_prev(&list, NULL) );
    }

    TEST(Verify_list_prev_returns_NULL_when_given_node_not_present)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_node_t bogus = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( NULL == list_prev(&list, &bogus) );
    }

    TEST(Verify_list_prev_returns_NULL_when_given_node_at_head)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( NULL == list_prev(&list, &node1) );
    }

    TEST(Verify_list_prev_returns_previous_node)
    {
        list_node_t node4 = { NULL, NULL };
        list_node_t node3 = { NULL, &node4 };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( &node1 == list_prev(&list, &node2) );
        CHECK( &node2 == list_prev(&list, &node3) );
        CHECK( &node3 == list_prev(&list, &node4) );
    }

    //-------------------------------------------------------------------------
    // Test list_at function
    //-------------------------------------------------------------------------
    TEST(Verify_list_at_returns_NULL_when_list_is_empty)
    {
        list_t list = { NULL, NULL };
        CHECK( NULL == list_at( &list, 0 ) );
    }

    TEST(Verify_list_at_returns_NULL_when_index_out_of_range)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( NULL == list_at( &list, 3 ) );
    }

    TEST(Verify_list_at_returns_node_at_index_0_of_3_element_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( &node1 == list_at( &list, 0 ) );
    }

    TEST(Verify_list_at_returns_node_at_index_1_of_3_element_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( &node2 == list_at( &list, 1 ) );
    }

    TEST(Verify_list_at_returns_node_at_index_2_of_3_element_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( &node3 == list_at( &list, 2 ) );
    }

    //-------------------------------------------------------------------------
    // Test list_index_of function
    //-------------------------------------------------------------------------
    TEST(Verify_list_index_of_returns_negative_one_when_list_is_empty)
    {
        list_t list = { NULL, NULL };
        list_node_t bogus = { NULL, NULL };
        CHECK( -1 == list_index_of(&list, &bogus) );
    }

    TEST(Verify_list_index_of_returns_negative_one_when_node_is_not_found)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        list_node_t bogus = { NULL, NULL };
        CHECK( -1 == list_index_of(&list, &bogus) );
    }

    TEST(Verify_list_index_of_returns_list_size_when_node_is_null)
    {
        list_t list0 = { NULL, NULL };
        CHECK( 0 == list_index_of(&list0, NULL) );

        list_node_t node1_1 = { NULL, NULL };
        list_t list1 = { &node1_1, &node1_1 };
        CHECK( 1 == list_index_of(&list1, NULL) );

        list_node_t node2_2 = { NULL, NULL};
        list_node_t node2_1 = { NULL, &node2_2 };
        list_t list2 = { &node2_1, &node2_2 };
        CHECK( 2 == list_index_of(&list2, NULL) );

        list_node_t node3_3 = { NULL, NULL };
        list_node_t node3_2 = { NULL, &node3_3 };
        list_node_t node3_1 = { NULL, &node3_2 };
        list_t list3 = { &node3_1, &node3_3 };
        CHECK( 3 == list_index_of(&list3, NULL) );
    }

    TEST(Verify_list_index_of_returns_zero_for_first_item_in_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( 0 == list_index_of(&list, &node1) );
    }

    TEST(Verify_list_index_of_returns_zero_for_second_item_in_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( 1 == list_index_of(&list, &node2) );
    }

    TEST(Verify_list_index_of_returns_zero_for_third_item_in_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( 2 == list_index_of(&list, &node3) );
    }

    //-------------------------------------------------------------------------
    // Test list_push_front function
    //-------------------------------------------------------------------------
    TEST(Verify_list_push_front_pushes_to_empty_list)
    {
        list_t* list = list_new();
        list_node_t* node = list_push_front( list, mem_box(0x1234) );
        CHECK( NULL != node );
        CHECK( 0x1234 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        CHECK( node == list->head );
        CHECK( node == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_push_front_pushes_to_front_of_list_of_length_1)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_push_front( list, mem_box(0x1234) );
        list_node_t* node2 = list_push_front( list, mem_box(0x1235) );
        CHECK( 0x1235 == mem_unbox(list->head->contents) );
        CHECK( node1 == list->head->next );
        CHECK( node2 == list->head );
        CHECK( node1 == list->tail );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_push_back function
    //-------------------------------------------------------------------------
    TEST(Verify_list_push_back_pushes_to_empty_list)
    {
        list_t* list = list_new();
        list_node_t* node = list_push_back( list, mem_box(0x1234) );
        CHECK( NULL != node );
        CHECK( 0x1234 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        CHECK( node == list->head );
        CHECK( node == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_push_back_pushes_to_back_of_list_of_length_1)
    {
        list_t* list = list_new();
        list_push_back( list, mem_box(0x1234) );
        list_node_t* node = list_push_back( list, mem_box(0x1235) );
        CHECK( NULL != node );
        CHECK( 0x1235 == mem_unbox(node->contents) );
        CHECK( NULL == node->next );
        CHECK( node != list->head );
        CHECK( node == list->tail );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_pop_front function
    //-------------------------------------------------------------------------
    TEST(Verify_pop_front_returns_null_if_list_is_empty)
    {
        list_t list = { NULL, NULL };
        CHECK( NULL == list_pop_front( &list ) );
    }

    TEST(Verify_pop_front_removes_a_node_from_the_front_of_a_list_of_length_1)
    {
        list_node_t node1 = { NULL, NULL };
        list_t list = { &node1, &node1 };
        CHECK( &node1 == list_pop_front( &list ) );
        CHECK( NULL == list.head );
        CHECK( NULL == list.tail );
    }

    TEST(Verify_pop_front_removes_a_node_from_the_front_of_a_list_of_length_2)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };
        CHECK( &node1 == list_pop_front( &list ) );
        CHECK( &node2 == list.head );
        CHECK( &node2 == list.tail );
    }

    TEST(Verify_pop_front_removes_a_node_from_the_front_of_a_list_of_length_3)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( &node1 == list_pop_front( &list ) );
        CHECK( &node2 == list.head );
        CHECK( &node3 == list.tail );
    }

    //-------------------------------------------------------------------------
    // Test list_pop_back function
    //-------------------------------------------------------------------------
    TEST(Verify_pop_back_does_nothing_if_list_is_empty)
    {
        list_t list = { NULL, NULL };
        CHECK( NULL == list_pop_back( &list ) );
    }

    TEST(Verify_pop_back_removes_a_node_from_the_back_of_a_list_of_length_1)
    {
        list_node_t node1 = { NULL, NULL };
        list_t list = { &node1, &node1 };
        CHECK( &node1 == list_pop_back( &list ) );
        CHECK( NULL == list.head );
        CHECK( NULL == list.tail );
    }

    TEST(Verify_pop_back_removes_a_node_from_the_back_of_a_list_of_length_2)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };
        CHECK( &node2 == list_pop_back( &list ) );
        CHECK( &node1 == list.head );
        CHECK( &node1 == list.tail );
    }

    TEST(Verify_pop_back_removes_a_node_from_the_back_of_a_list_of_length_3)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        CHECK( &node3 == list_pop_back( &list ) );
        CHECK( &node1 == list.head );
        CHECK( &node2 == list.tail );
    }

    //-------------------------------------------------------------------------
    // Test list_insert function
    //-------------------------------------------------------------------------
    TEST(Verify_insert_should_insert_into_empty_list)
    {
        list_t* list = list_new();
        list_node_t* node = list_insert( list, 0, mem_box(0x1234) );
        CHECK( node != NULL );
        CHECK( node->next == NULL );
        CHECK( mem_unbox(node->contents) == 0x1234 );
        CHECK( list->head == node );
        CHECK( list->tail == node );
        mem_release(list);
    }

    TEST(Verify_insert_should_push_to_the_front_of_the_list_if_index_is_0)
    {
        list_t* list = list_new();
        list_insert( list, 0, mem_box(0x1234) );
        list_node_t* node = list_insert( list, 0, mem_box(0x1235) );
        CHECK( node != NULL );
        CHECK( node->next != NULL );
        CHECK( mem_unbox(list->head->contents) == 0x1235 );
        CHECK( list->head == node );
        CHECK( list->tail != node );
        mem_release(list);
    }

    TEST(Verify_insert_should_insert_at_the_given_index_if_index_is_non_zero)
    {
        list_t* list = list_new();
        list_insert( list, 0, mem_box(0x1236) );
        list_insert( list, 0, mem_box(0x1235) );
        list_insert( list, 0, mem_box(0x1234) );
        list_node_t* node = list_insert( list, 1, mem_box(0x1237) );
        CHECK( node != NULL );
        CHECK( node->next != NULL );
        CHECK( mem_unbox(list->head->next->contents) == 0x1237 );
        mem_release(list);
    }

    TEST(Verify_insert_should_set_the_tail_of_the_list_if_index_is_the_last_item)
    {
        list_t* list = list_new();
        list_insert( list, 0, mem_box(0x1236) );
        list_insert( list, 0, mem_box(0x1235) );
        list_node_t* node = list_insert( list, 2, mem_box(0x1234) );
        CHECK( node != NULL );
        CHECK( node->next == NULL );
        CHECK( mem_unbox(list->tail->contents) == 0x1234 );
        mem_release(list);
    }

    TEST(Verify_insert_should_return_null_if_index_out_of_range)
    {
        list_t* list = list_new();
        list_insert( list, 0, mem_box(0x1236) );
        list_insert( list, 0, mem_box(0x1235) );
        list_node_t* node = list_insert( list, 3, mem_box(0x1234) );
        CHECK( node == NULL );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_insert_after function
    //-------------------------------------------------------------------------
    TEST(Verify_insert_after_should_to_insert_to_head_if_node_is_null_and_list_is_empty)
    {
        list_t* list = list_new();
        list_node_t* node = list_insert_after(list, NULL, mem_box(0x1234) );
        CHECK( node == list->head );
        CHECK( node == list->tail );
        CHECK( NULL == node->next );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_to_head_if_node_is_null_and_list_is_populated)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_insert_after(list, NULL, mem_box(0x0666));
        list_node_t* node2 = list_insert_after(list, NULL, mem_box(0x4242));
        CHECK( node2 == list->head );
        CHECK( node1 == list->tail );
        CHECK( node1 == node2->next );
        CHECK( NULL == node1->next );
        list_node_t* node3 = list_insert_after(list, NULL, mem_box(0x1234));
        CHECK( node3 == list->head );
        CHECK( node1 == list->tail );
        CHECK( node2 == node3->next );
        CHECK( node1 == node2->next );
        CHECK( NULL == node1->next );
        mem_release(list);
    }

    TEST(Verify_insert_after_can_build_list_linearly)
    {
        list_t* list = list_new();
        list_node_t* node1 = list_insert_after(list, list->tail, mem_box(0x1234));
        CHECK( node1 == list->head );
        CHECK( node1 == list->tail );
        CHECK( NULL == node1->next );
        list_node_t* node2 = list_insert_after(list, list->tail, mem_box(0x4321));
        CHECK( node1 == list->head );
        CHECK( node2 == list->tail );
        CHECK( node2 == node1->next );
        CHECK( NULL == node2->next );
        list_node_t* node3 = list_insert_after(list, list->tail, mem_box(0x4242));
        CHECK( node1 == list->head );
        CHECK( node3 == list->tail );
        CHECK( node2 == node1->next );
        CHECK( node3 == node2->next );
        CHECK( NULL == node3->next );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_after_the_head_node)
    {
        list_node_t* node;
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        node = list_insert_after( list, list_front(list), mem_box(0x1235) );
        CHECK( node != NULL );
        CHECK( node->next == NULL );
        CHECK( list->tail == node );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_after_the_tail_node)
    {
        list_node_t* node;
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        list_push_back(list, mem_box(0x1234));
        node = list_insert_after( list, list_back(list), mem_box(0x1234) );
        CHECK( node != NULL );
        CHECK( node->next == NULL );
        CHECK( list_at(list, 2) == node );
        CHECK( list->tail == node );
        mem_release(list);
    }

    TEST(Verify_insert_after_should_insert_after_an_inner_node)
    {
        list_node_t* node;
        list_t* list = list_new();
        list_push_back(list, mem_box(0x1234));
        node = list_push_back(list, mem_box(0x1234));
        list_push_back(list, mem_box(0x1234));
        node = list_insert_after( list, node, mem_box(0x1234) );
        CHECK( node != NULL );
        CHECK( node->next == list->tail );
        CHECK( node == list_at(list,2) );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_delete function
    //-------------------------------------------------------------------------
    TEST(Verify_delete_does_nothing_if_list_is_empty)
    {
        list_t list = { NULL, NULL };
        CHECK( NULL == list_delete( &list, 0) );
    }

    TEST(Verify_delete_deletes_the_first_element_of_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_push_back(list,mem_box(0x1234));
        CHECK( NULL == list_delete( list, 0) );
        CHECK( list->head == NULL );
        CHECK( list->tail == NULL );
        mem_release(list);
    }

    TEST(Verify_delete_deletes_the_first_element_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_push_back(list,mem_box(0x1234));
        list_push_back(list,mem_box(0x1235));
        CHECK( NULL != list_delete( list, 0) );
        CHECK( list->head != NULL );
        CHECK( list->tail != NULL );
        CHECK( list->head == list->tail );
        CHECK( mem_unbox(list->head->contents) == 0x1235 );
        mem_release(list);
    }

    TEST(Verify_delete_deletes_element_1_of_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_push_back(list,mem_box(0x1234));
        list_push_back(list,mem_box(0x1235));
        list_push_back(list,mem_box(0x1236));
        CHECK( NULL != list_delete( list, 1) );
        CHECK( 2 == list_size( list ) );
        CHECK( list->head != NULL );
        CHECK( list->tail != NULL );
        CHECK( list->head != list->tail );
        mem_release(list);
    }

    TEST(Verify_delete_deletes_element_1_of_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_push_back(list,mem_box(0x1234));
        list_push_back(list,mem_box(0x1235));
        CHECK( NULL == list_delete( list, 1) );
        CHECK( list->head != NULL );
        CHECK( list->tail != NULL );
        CHECK( list->head == list->tail );
        CHECK( mem_unbox(list->head->contents) == 0x1234 );
        mem_release(list);
    }

    //-------------------------------------------------------------------------
    // Test list_delete_node function
    //-------------------------------------------------------------------------
    TEST(Verify_delete_node_does_nothing_if_list_is_empty)
    {
        list_t list = { NULL, NULL };
        list_node_t bogus = { NULL, NULL };
        list_delete_node(&list, NULL);
        CHECK( NULL == list.head);
        CHECK( NULL == list.tail);
        list_delete_node(&list, &bogus);
        CHECK( NULL == list.head);
        CHECK( NULL == list.tail);
    }

    TEST(Verify_delete_node_does_nothing_if_given_node_not_in_list)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        list_node_t bogus = { NULL, &node2 };
        list_delete_node(&list, &bogus);
        CHECK( &node2 == bogus.next );
        CHECK( &node1 == list.head );
        CHECK( &node2 == node1.next );
        CHECK( &node3 == node2.next );
        CHECK( NULL == node3.next );
        CHECK( &node3 == list.tail );
    }

    TEST(Verify_delete_node_deletes_the_head_node_of_a_list_of_length_1)
    {
        list_node_t node1 = { NULL, NULL };
        list_t list = { &node1, &node1 };
        list_delete_node(&list, &node1);
        CHECK( NULL == node1.next );
        CHECK( NULL == list.head );
        CHECK( NULL == list.tail );
    }

    TEST(Verify_delete_node_deletes_the_first_element_of_a_list_of_length_2)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };
        list_delete_node(&list, &node1);
        CHECK( NULL == node1.next );
        CHECK( &node2 == list.head );
        CHECK( NULL == node2.next );
        CHECK( &node2 == list.tail );
    }

    TEST(Verify_delete_node_deletes_the_second_element_of_a_list_of_length_2)
    {
        list_node_t node2 = { NULL, NULL };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node2 };
        list_delete_node(&list, &node2);
        CHECK( NULL == node2.next );
        CHECK( &node1 == list.head );
        CHECK( NULL == node1.next );
        CHECK( &node1 == list.tail );
    }

    TEST(Verify_delete_node_deletes_the_first_element_of_a_list_of_length_3)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        list_delete_node(&list, &node1);
        CHECK( NULL == node1.next );
        CHECK( &node2 == list.head );
        CHECK( &node3 == node2.next );
        CHECK( NULL == node3.next );
        CHECK( &node3 == list.tail );
    }

    TEST(Verify_delete_node_deletes_the_second_element_of_a_list_of_length_3)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        list_delete_node(&list, &node2);
        CHECK( NULL == node2.next );
        CHECK( &node1 == list.head );
        CHECK( &node3 == node1.next );
        CHECK( NULL == node3.next );
        CHECK( &node3 == list.tail );
    }

    TEST(Verify_delete_node_deletes_the_third_element_of_a_list_of_length_3)
    {
        list_node_t node3 = { NULL, NULL };
        list_node_t node2 = { NULL, &node3 };
        list_node_t node1 = { NULL, &node2 };
        list_t list = { &node1, &node3 };
        list_delete_node(&list, &node3);
        CHECK( NULL == node3.next );
        CHECK( &node1 == list.head );
        CHECK( &node2 == node1.next );
        CHECK( NULL == node2.next );
        CHECK( &node2 == list.tail );
    }

    //-------------------------------------------------------------------------
    // Test list_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_list_clear_does_nothing_for_an_empty_list)
    {
        list_t* list = list_new();
        list_clear(list);
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_clear_clears_a_list_of_length_1)
    {
        list_t* list = list_new();
        list_push_front(list,mem_box(0x1234));
        list_clear(list);
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_clear_clears_a_list_of_length_2)
    {
        list_t* list = list_new();
        list_push_front(list,mem_box(0x1234));
        list_push_front(list,mem_box(0x1234));
        list_clear(list);
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(list);
    }

    TEST(Verify_list_clear_clears_a_list_of_length_3)
    {
        list_t* list = list_new();
        list_push_front(list,mem_box(0x1234));
        list_push_front(list,mem_box(0x1234));
        list_push_front(list,mem_box(0x1234));
        list_clear(list);
        CHECK( NULL == list->head );
        CHECK( NULL == list->tail );
        mem_release(list);
    }
}
