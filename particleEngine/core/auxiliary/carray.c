#include <assert.h>
#include <stdlib.h>
#include <string.h>

void addItem(void** zarray, int* zarray_length, int* zarray_size, int zpadding, void* zitem, int zitem_size)
{
    assert(zarray_length != NULL && zarray_size != NULL);

    // Check to see if we need to reallocate the array
    if (*zarray_size < *zarray_length + 1)
    {
        // Reallocate the array and expand it by zpadding
        if (*zarray == NULL)
            (*zarray) = malloc(zitem_size * (*zarray_size + zpadding));
        else
            (*zarray) = realloc(*zarray, zitem_size * (*zarray_size + zpadding));

        // Set the new array size
        (*zarray_size) += zpadding;
    }

    assert(*zarray != NULL);

    // Add the new item to it, or zero it out if zitem equals null
    if (zitem == NULL)
        memset(*zarray + (*zarray_length * zitem_size), 0, zitem_size);
    else
        memcpy(*zarray + (*zarray_length * zitem_size), zitem, zitem_size);

    // Increment the length
    ++(*zarray_length);
}

void removeItem(void* zarray, int* zarray_length, int zitem_index, int zitem_size)
{
    // Shift the memory over
    memcpy(zarray + zitem_index * zitem_size, zarray + (zitem_index + 1) * zitem_size, zitem_size * (*zarray_length - zitem_index - 1));

    // Clear the now garbage item at the end of the array
    memset(zarray + (*zarray_length - 1) * zitem_size, 0, zitem_size);

    // Decrement the length
    --(*zarray_length);
}
