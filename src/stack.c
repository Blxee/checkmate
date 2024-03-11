#include "stack.h"
#include "mem_utils.h"


fifo_stack_t *stack_create(void) {
  fifo_stack_t *stack;

  stack = mem_alloc(sizeof(*stack));
  if (stack == NULL)
    return NULL;

  *stack = (fifo_stack_t){ .head = NULL, .size = 0 };

  return stack;
}


void stack_push(fifo_stack_t *stack, STACK_TYPE value) {
  stack_node_t *new;

  if (stack == NULL)
    return;

  // create new node with the value
  new = mem_alloc(sizeof(stack_node_t));
  new->value = value;

  // prepend the node to the stack and set it as head
  new->next = stack->head;
  stack->head = new;
  stack->size++;
}


STACK_TYPE stack_peek(fifo_stack_t *stack) {
  if (stack == NULL || stack->head == NULL)
    return 0;

  return stack->head->value;
}


STACK_TYPE stack_pop(fifo_stack_t *stack) {
  STACK_TYPE value;
  stack_node_t *next;

  if (stack == NULL || stack->head == NULL)
    return 0;

  // extract value and next from head
  value = stack->head->value;
  next = stack->head->next;

  // free the head and assign it to next
  mem_free(stack->head);
  stack->head = next;
  stack->size--;

  return value;
}


void stack_free(fifo_stack_t *stack) {
  stack_node_t *node, *next;

  if (stack == NULL)
    return;

  node = stack->head;

  // while there is next, free it
  while (node) {
    next = node->next;
    mem_free(node);
    node = next;
  }

  mem_free(stack);
}
