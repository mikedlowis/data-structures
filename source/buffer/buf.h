/**
    @file buf.h
    @brief Implementation of a circular buffer.
    $Revision$
    $HeadURL$
*/
#ifndef BUF_H
#define BUF_H

#ifdef __cplusplus
extern "C" {
#endif

/** A structure defining a circular buffer */
typedef struct {
    void** buffer; /**< Pointer to the buffer */
    size_t size    /**< Size of the allocated buffer */;
    size_t reads   /**< Total number of reads that have occurred */;
    size_t writes  /**< Total number of writes that have occrurred */;
} buf_t;

/**
 * @brief Creates a new buffer.
 *
 * @param size The fixed size of the new buffer.
 *
 * @return Pointer to the new buffer.
 */
buf_t* buf_new(size_t size);

/**
 * @brief Frees the provided buffer and optionally any unread contents.
 *
 * @param buf           The buffer to free.
 * @param free_contents Whether unread contents should also be freed.
 */
void buf_free(buf_t* buf, int free_contents);

/**
 * @brief Returns the size of the provided buffer.
 *
 * @param buf The buffer on which to operate.
 *
 * @return The size of the buffer.
 */
size_t buf_size(buf_t* buf);

/**
 * @brief Returns whether the buffer is empty.
 *
 * @param buf The buffer on which to operate.
 *
 * @return 1 if the buffer is empty 0 otherwise.
 */
int buf_empty(buf_t* buf);

/**
 * @brief Returns whether the buffer is full.
 *
 * @param buf The buffer on which to operate.
 *
 * @return 1 if the buffer is full 0 otherwise.
 */
int buf_full(buf_t* buf);

/**
 * @brief Clears all unread data from the provided buffer.
 *
 * @param buf           The buffer to clear.
 * @param free_contents Whether the unread contents should also be freed.
 */
void buf_clear(buf_t* buf, int free_contents);

/**
 * @brief Reads an item from the provided buffer.
 *
 * @param buf The buffer to read from.
 *
 * @return Pointer to the data read from the buffer. NULL If no data was read.
 */
void* buf_read(buf_t* buf);

/**
 * @brief Writes data to the provided buffer.
 *
 * @param buf  The buffer to write to.
 * @param data The data to write.
 *
 * @return 1 on successful write 0 otherwise.
 */
int buf_write(buf_t* buf, void* data);

#ifdef __cplusplus
}
#endif

#endif /* BUF_H */
