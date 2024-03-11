#include <stdio.h>
#define STACK_TYPE int
#include "stack.h"

int main(void) {
  stack_t *my_stack = stack_create();

  printf("my_stack->head == NULL\n");
  printf("%s\n", my_stack->head == NULL ? "true" : "false");
  printf("\n");

  printf("my_stack->size == 0\n");
  printf("%s\n", my_stack->size == 0 ? "true" : "false");
  printf("\n");

  stack_push(my_stack, 7);

  printf("my_stack->head != NULL\n");
  printf("%s\n", my_stack->head != NULL ? "true" : "false");
  printf("\n");

  printf("my_stack->size == 1\n");
  printf("%s\n", my_stack->size == 1 ? "true" : "false");
  printf("\n");

  printf("my_stack->head->next == NULL\n");
  printf("%s\n", my_stack->head->next == NULL ? "true" : "false");
  printf("\n");

  stack_push(my_stack, 3);

  printf("my_stack->head->next != NULL\n");
  printf("%s\n", my_stack->head->next != NULL ? "true" : "false");
  printf("\n");

  printf("my_stack->size == 2\n");
  printf("%s\n", my_stack->size == 2 ? "true" : "false");
  printf("\n");

  stack_free(my_stack);
}
