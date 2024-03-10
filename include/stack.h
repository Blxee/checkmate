#ifndef STACK_H
#define STACK_H

#ifndef STACK_TYPE
#define STACK_TYPE void *
#endif // !STACK_TYPE

#include <stdlib.h>

typedef struct stack_node_s {
  STACK_TYPE value;
  struct stack_node_s *next;
} stack_node_t;

typedef struct stack_s {
  stack_node_t *head;
  unsigned int size;
} stack_t;

stack_t *stack_create(void);
void stack_push(stack_t *stack, STACK_TYPE value);
STACK_TYPE stack_pop(stack_t *stack);
void stack_free(stack_t *stack);

#endif // !STACK_H
