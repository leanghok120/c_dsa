/*
 * binary tree implementation in C
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left;
  struct Node *right;
} Node;

Node *create_node(int value) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return node;
  }
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void print_tree(Node *root) {
  if (root == NULL) return;

  printf("%d\n", root->value);
  print_tree(root->left);
  print_tree(root->right);
}

int main() {
  Node *n1 = create_node(1);
  Node *n2 = create_node(2);
  Node *n3 = create_node(3);
  Node *n4 = create_node(4);

  n1->left = n2;
  n1->right = n3;
  n3->left = n4;

  print_tree(n1);

  free(n1);
  free(n2);
  free(n3);
  free(n4);

  return 0;
}
