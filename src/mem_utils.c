#include "mem_utils.h"
#include <stdlib.h>

void *mem_alloc(unsigned long size) {
  int i;
  int j;
  void **new_mem_array;

  if (_s_mem_array == NULL) 
    _s_mem_array = calloc(_s_mem_array_size, sizeof(*_s_mem_array));

  // find a free spot for the new pointer
  for (i = 0; i < _s_mem_array_size; i++) {
    if (_s_mem_array[i] == NULL) {
      _s_mem_array[i] = malloc(size);
      return _s_mem_array[i];
    }
  }

  // if code reached here, then memory array is full
  // expand the memory array by double the size
  _s_mem_array_size *= 2;
  new_mem_array = realloc(_s_mem_array, _s_mem_array_size * sizeof(*_s_mem_array));
  if (new_mem_array == NULL) // reallocation failed
    return NULL;
  _s_mem_array = new_mem_array;
  for (j = i ; j < _s_mem_array_size; j++)
    _s_mem_array[j] = NULL;

  _s_mem_array[i] = malloc(size);

  return _s_mem_array[i];
}

void *mem_calloc(unsigned long count, unsigned long size) {
  int i;
  int j;
  void **new_mem_array;

  if (_s_mem_array == NULL) 
    _s_mem_array = calloc(_s_mem_array_size, sizeof(*_s_mem_array));

  // find a free spot for the new pointer
  for (i = 0; i < _s_mem_array_size; i++) {
    if (_s_mem_array[i] == NULL) {
      _s_mem_array[i] = calloc(count, size);
      return _s_mem_array[i];
    }
  }

  // if code reached here, then memory array is full
  // expand the memory array by double the size
  _s_mem_array_size *= 2;
  new_mem_array = realloc(_s_mem_array, _s_mem_array_size * sizeof(*_s_mem_array));
  if (new_mem_array == NULL) // reallocation failed
    return NULL;
  _s_mem_array = new_mem_array;
  for (j = i ; j < _s_mem_array_size; j++)
    _s_mem_array[j] = NULL;

  _s_mem_array[i] = calloc(count, size);

  return _s_mem_array[i];
}

void *mem_realloc(void *ptr, unsigned long size) {
  int i;

  for (i = 0; i < _s_mem_array_size; i++) {
    if (_s_mem_array[i] == ptr) {
      _s_mem_array[i] = realloc(ptr, size);
      return _s_mem_array[i];
    }
  }

  return mem_alloc(size);
}

void mem_free(void *ptr) {
  int i;

  for (i = 0; i < _s_mem_array_size; i++) {
    if (_s_mem_array[i] == ptr) {
      free(_s_mem_array[i]);
      _s_mem_array[i] = NULL;
      break;
    }
  }
}

void mem_free_all(void) {
  int i;

  for (i = 0; i < _s_mem_array_size; i++)
    if (_s_mem_array[i] != NULL)
      free(_s_mem_array[i]);

  free(_s_mem_array);
}
