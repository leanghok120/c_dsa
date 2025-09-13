/*
 * stack implementation in C using dynamic arrays
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int *data;
  int size;
  int capacity;
} Stack;

Stack *create_stack(int capacity);
void destroy_stack(Stack *stack);
bool is_full(Stack *stack);
bool is_empty(Stack *stack);
bool pop(Stack *stack, int *item);
bool push(Stack *stack, int item);
bool peek(Stack *stack, int *item);

int main() {
  Stack *stack = create_stack(10);
  if (stack == NULL) {
    printf("failed to create stack\n");
    return 1;
  }

  for (int i = 0; i < 1000; i++) {
    push(stack, i);
  }
  printf("stack size: %d\n", stack->size);

  int popped_value;
  pop(stack, &popped_value);
  printf("popped value: %d\n", popped_value);

  int peek_value;
  peek(stack, &peek_value);
  printf("peek value: %d\n", peek_value);

  destroy_stack(stack);

  return 0;
}

Stack *create_stack(int capacity) {
  if (capacity <= 0) {
    return NULL;
  }

  Stack *stack = malloc(sizeof(Stack));
  if (stack == NULL) {
    return NULL;
  }

  stack->data = malloc(sizeof(int) * capacity);
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  stack->capacity = capacity;
  stack->size = 0;
  return stack;
}

void destroy_stack(Stack *stack) {
  free(stack->data);
  free(stack);
}

bool is_full(Stack *stack) {
  return stack->size == stack->capacity;
}

bool is_empty(Stack *stack) {
  return stack->size == 0;
}

bool push(Stack *stack, int item) {
  if (is_full(stack)) {
    int new_capacity = stack->capacity * 2;
    int *new_data = realloc(stack->data, sizeof(int) * new_capacity);

    // check if realloc failed
    if (new_data == NULL) {
      return false;
    }

    stack->capacity = new_capacity;
    stack->data = new_data;
  }

  stack->data[stack->size] = item;
  stack->size++;
  return true;
}

bool pop(Stack *stack, int *item) {
  if (is_empty(stack)) {
    return false;
  }

  stack->size--;
  *item = stack->data[stack->size];
  return true;
}

bool peek(Stack *stack, int *item) {
  if (is_empty(stack)) {
    return false;
  }

  *item = stack->data[stack->size-1];
  return true;
}
