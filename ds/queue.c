/*
 * queue implementation in C using a linked list
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  int size;
} Queue;

Queue *create_queue();
void destroy_queue(Queue *queue);
bool is_empty(Queue *queue);
bool peek(Queue *queue, int *value);
bool enqueue(Queue *queue, int value);
bool dequeue(Queue *queue, int *value);

int main() {
  Queue *queue = create_queue();
  if (queue == NULL) {
    printf("failed to create queue\n");
    return 1;
  }

  enqueue(queue, 1);
  enqueue(queue, 2);
  enqueue(queue, 3);
  enqueue(queue, 4);
  enqueue(queue, 5);

  int dequeue_value;
  dequeue(queue, &dequeue_value);
  printf("dequeue value: %d\n", dequeue_value);

  int peek_value;
  peek(queue, &peek_value);
  printf("peek value: %d\n", peek_value);

  destroy_queue(queue);
  return 0;
}

Queue *create_queue() {
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) {
    return NULL;
  }

  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
  return queue;
}

void destroy_queue(Queue *queue) {
  Node *current_node = queue->head;
  
  while (current_node != NULL) {
    Node *temp = current_node;
    current_node = current_node->next;
    free(temp);
  }

  free(queue);
}

bool is_empty(Queue *queue) {
  return queue->size == 0;
}

bool peek(Queue *queue, int *value) {
  if (is_empty(queue)) {
    return false;
  }

  *value = queue->head->value;
  return true;
}

bool enqueue(Queue *queue, int value) {
  Node *new_node = malloc(sizeof(Node));
  if (new_node == NULL) {
    return false;
  }

  new_node->value = value;
  new_node->next = NULL;
  if (is_empty(queue)) {
    queue->head = new_node;
    queue->tail = new_node;
  } else {
    queue->tail->next = new_node;
    queue->tail = new_node;
  }

  queue->size++;
  return true;
}

bool dequeue(Queue *queue, int *value) {
  if (is_empty(queue)) {
    return false;
  }

  Node *old_head = queue->head;
  if (queue->size == 1) {
    queue->head = NULL;
    queue->tail= NULL;
  } else {
    queue->head = queue->head->next;
  }
  *value = old_head->value;
  free(old_head);

  queue->size--;
  return true;
}
