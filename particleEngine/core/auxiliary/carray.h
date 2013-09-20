#ifndef CARRAY_H_INCLUDED
#define CARRAY_H_INCLUDED

#ifndef NULL
#define NULL ((void*)0)
#endif


/**
 * Appends an item to an array.
 *
 * \param zarray[in,out]        A pointer to the array that will be resized.
 * \param zarray_length[in,out] A pointer to the length of the array. Will be incremented.
 * \param zarray_size[in,out]   A pointer to the size of the array, may be modified.
 * \param zpadding[in]          If the array is reallocated, zpadding extra unused \e items (not bytes) will be
 *                              added. A higher padding means less reallocations for future calls to the function.
 * \param zitem[in]             A pointer to the item to be appended.
 * \param zitem_size[in]        The size of the items (in bytes) in the array.
 **/
void addItem(void** zarray, int* zarray_length, int* zarray_size, int zpadding, void* zitem, int zitem_size);

/**
 * Removes an item from an array.
 *
 * \param zarray[in,out]        The array that will be modified.
 * \param zarray_length[in,out] A pointer to the length of the array. Will be decremented.
 * \param zitem_index[in]       The index of the item to be removed.
 * \param zitem_size[in]        The size of the items (in bytes) in the array.
 **/
 void removeItem(void* zarray, int* zarray_length, int zitem_index, int zitem_size);

#endif // CARRAY_H_INCLUDED
