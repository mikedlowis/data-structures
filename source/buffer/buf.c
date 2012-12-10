/**
    @file buf.c
    @brief See header for details
    $Revision$
    $HeadURL$
*/
#include <stdlib.h>
#include "buf.h"

buf_t* buf_new(size_t size)
{
    buf_t* buf = NULL;
    if (size > 0)
    {
        buf         = (buf_t*) malloc( sizeof(buf_t) );
        buf->buffer = (void**) malloc( sizeof(void*) * size );
        buf->size   = size;
        buf->reads  = 0;
        buf->writes = 0;
    }
    return buf;
}

void buf_free(buf_t* buf, int free_contents)
{
    if (NULL != buf)
    {
        buf_clear(buf,free_contents);
        free( buf->buffer );
        free( buf );
    }
}

size_t buf_size(buf_t* buf)
{
    return (NULL == buf) ? (size_t)0 : (size_t)buf->size;
}

int buf_empty(buf_t* buf)
{
    return (NULL == buf) ? 1 : (buf->reads == buf->writes);
}

int buf_full(buf_t* buf)
{
    int full = 1;
    if (NULL != buf)
    {
        full  = !buf_empty(buf);
        full &= ((buf->reads % buf->size) == (buf->writes % buf->size));
    }
    return full;
}

void buf_clear(buf_t* buf, int free_contents)
{
    if (NULL != buf)
    {
        if (free_contents)
        {
            while ( !buf_empty(buf) )
            {
                free( buf_read(buf) );
            }
        }
        buf->reads  = 0;
        buf->writes = 0;
    }
}

void* buf_read(buf_t* buf)
{
    void* data = NULL;
    if ((NULL != buf) && !buf_empty(buf))
    {
        data = buf->buffer[ buf->reads % buf->size ];
        buf->reads++;
    }
    return data;
}

int buf_write(buf_t* buf, void* data)
{
    int success = 0;
    if ((NULL != buf) && !buf_full(buf))
    {
        buf->buffer[ buf->writes % buf->size ] = data;
        buf->writes++;
        success = 1;
    }
    return success;
}

