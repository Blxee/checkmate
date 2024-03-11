#ifndef STACK_H
#define STACK_H

#ifndef STACK_TYPE
#define STACK_TYPE void *
#endif // !STACK_TYPE


typedef struct stack_node_s {
  STACK_TYPE value;
  struct stack_node_s *next;
} stack_node_t;


typedef struct fifo_stack_s {
  stack_node_t *head;
  unsigned int size;
} fifo_stack_t;


fifo_stack_t *stack_create(void);
void stack_push(fifo_stack_t *stack, STACK_TYPE value);
STACK_TYPE stack_peek(fifo_stack_t *stack);
STACK_TYPE stack_pop(fifo_stack_t *stack);
void stack_free(fifo_stack_t *stack);

#endif // !STACK_H
