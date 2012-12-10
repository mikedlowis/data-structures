// Unit Test Framework Includes
#include "UnitTest++.h"
#include <cstdlib>
#include <iostream>

// File To Test
#include "buf.h"

using namespace UnitTest;

//-----------------------------------------------------------------------------
// Begin Unit Tests
//-----------------------------------------------------------------------------
namespace {
    //-------------------------------------------------------------------------
    // Test buf_new function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_new_returns_a_new_buffer_of_the_desired_size)
    {
        buf_t* buf = buf_new(5);
        CHECK( NULL != buf );
        CHECK( NULL != buf->buffer );
        CHECK( 5 == buf->size );
        CHECK( 0 == buf->reads );
        CHECK( 0 == buf->writes );
        free( buf->buffer );
        free( buf );
    }

    TEST(Verify_buf_new_returns_null_if_passed_a_size_of_0)
    {
        CHECK( NULL == buf_new(0) );
    }

    //-------------------------------------------------------------------------
    // Test buf_free function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_free_does_nothing_when_pointer_is_NULL)
    {
        buf_free( NULL, 0 );
    }

    TEST(Verify_buf_free_frees_the_buffer)
    {
        buf_free( buf_new(5), 0 );
    }

    //-------------------------------------------------------------------------
    // Test buf_size function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_size_should_return_0_when_passed_NULL)
    {
        CHECK( 0 == buf_size(NULL) );
    }

    TEST(Verify_buf_size_should_return_the_size_of_the_buffer)
    {
        buf_t* buf = buf_new(5);
        CHECK( 5 == buf_size( buf ) );
        buf_free(buf,0);
    }

    //-------------------------------------------------------------------------
    // Test buf_empty function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_empty_returns_1_when_passed_NULL)
    {
        CHECK( 1 == buf_empty( NULL ) );
    }

    TEST(Verify_buf_empty_returns_1_when_buffer_is_empty)
    {
        buf_t buf = { NULL, 5, 1, 1 };
        CHECK( 1 == buf_empty( &buf ) );
    }

    TEST(Verify_buf_empty_returns_0_when_buffer_is_empty)
    {
        buf_t buf = { NULL, 5, 1, 2 };
        CHECK( 0 == buf_empty( &buf ) );
    }

    //-------------------------------------------------------------------------
    // Test buf_full function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_full_returns_1_if_passed_null)
    {
        CHECK( 1 == buf_full(NULL) );
    }

    TEST(Verify_buf_full_returns_1_if_buffer_is_full)
    {
        buf_t buf = { NULL, 5, 1, 6 };
        CHECK( 1 == buf_full( &buf ) );
    }

    TEST(Verify_buf_full_returns_0_if_buffer_empty)
    {
        buf_t buf = { NULL, 5, 1, 1 };
        CHECK( 0 == buf_full( &buf ) );
    }

    TEST(Verify_buf_full_returns_0_if_buffer_not_full)
    {
        buf_t buf = { NULL, 5, 1, 5 };
        CHECK( 0 == buf_full( &buf ) );
    }

    //-------------------------------------------------------------------------
    // Test buf_clear function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_clear_does_nothing_when_passed_null)
    {
        buf_clear(NULL,0);
    }

    TEST(Verify_buf_clears_the_buffer)
    {
        buf_t buf = { NULL, 5, 1, 5 };
        buf_clear( &buf, 0 );
        CHECK( buf.reads == 0 );
        CHECK( buf.writes == 0 );
    }

    TEST(Verify_buf_clears_the_buffer_and_frees_the_contents)
    {
        buf_t* buf = buf_new(3);
        buf_write( buf, (void*)malloc(sizeof(int)) );
        buf_write( buf, (void*)malloc(sizeof(int)) );
        buf_write( buf, (void*)malloc(sizeof(int)) );
        buf_clear( buf, 1 );
        CHECK( buf->reads == 0 );
        CHECK( buf->writes == 0 );
    }

    //-------------------------------------------------------------------------
    // Test buf_read function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_read_should_return_NULL_if_passed_NULL)
    {
        CHECK( NULL == buf_read(NULL) );
    }

    TEST(Verify_buf_read_should_return_NULL_if_buffer_is_empty)
    {
        buf_t* buf = buf_new(3);
        CHECK( NULL == buf_read( buf ) );
        buf_free(buf,0);
    }

    TEST(Verify_buf_read_should_return_the_next_piece_of_data_from_the_buffer)
    {
        void* data[] = { (void*)0x1234, (void*)0x4321, (void*)0x1221 };
        buf_t buf = { data, sizeof(data), 0, 3 };
        CHECK( (void*)0x1234 == buf_read(&buf) );
        CHECK( (void*)0x4321 == buf_read(&buf) );
        CHECK( (void*)0x1221 == buf_read(&buf) );
        CHECK( (void*)NULL == buf_read(&buf) );
    }

    //-------------------------------------------------------------------------
    // Test buf_write function
    //-------------------------------------------------------------------------
    TEST(Verify_buf_write_should_return_0_if_passed_NULL)
    {
        CHECK( 0 == buf_write(NULL,(void*)0x1234) );
    }

    TEST(Verify_buf_write_should_return_0_if_buffer_is_full)
    {
        buf_t buf = { NULL, 3, 0, 3 };
        CHECK( 0 == buf_write(&buf,(void*)0x1234) );
    }

    TEST(Verify_buf_write_should_return_1_if_data_successfully_wrote)
    {
        void* data[] = { (void*)0x1234, (void*)0x4321, (void*)0x1221 };
        buf_t buf = { data, sizeof(data), 0, 2 };
        CHECK( 1 == buf_write(&buf,(void*)0x1234) );
    }
}
