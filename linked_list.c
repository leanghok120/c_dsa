/*
 * singly linked list implementation in C
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *create_node(int data, Node *next);
void free_list(Node *head);
void print_list(Node *head);

int main() {
  Node *tail = create_node(3, NULL);
  Node *body = create_node(2, tail);
  Node *head = create_node(1, body);

  print_list(head);

  free_list(head);
  return 0;
}

Node *create_node(int data, Node *next) {
  Node *node = malloc(sizeof(Node));
  node->data = data;
  node->next = next;

  return node;
}

void free_list(Node *head) {
  Node *curr = head;
  while (curr != NULL) {
    Node *next = curr->next;
    free(curr);
    curr = next;
  }
}

void print_list(Node *head) {
  Node *curr = head;
  while (curr != NULL)  {
    printf("%d\n", curr->data);
    curr = curr->next;
  }
}
