/*
 * hashmap implementation in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define NAME_SIZE  255

typedef struct Person {
  char name[NAME_SIZE]; // key
  int age;              // value
  struct Person *next;  // for collisions
} Person;

typedef struct {
  Person **entries;
} Hashmap;

unsigned int hash(char *name) {
  unsigned int value = 0;
  for (int i = 0; name[i] != '\0'; i++) {
    value += name[i];
    value *= name[i];
  }
  return value % TABLE_SIZE;
}

Hashmap *hashmap_create() {
  Hashmap *hashmap = malloc(sizeof(Hashmap));
  hashmap->entries = malloc(sizeof(Person *) * TABLE_SIZE);
  for (int i = 0; i < TABLE_SIZE; i++) {
    hashmap->entries[i] = NULL;
  }
  return hashmap;
}

int hashmap_get(Hashmap *hashmap, char *key) {
  int i = hash(key);
  Person *entry = hashmap->entries[i];

  while (entry != NULL) {
    if (strcmp(entry->name, key) == 0) {
      return entry->age;
    }
    entry = entry->next;
  }
  return -1; // not found
}

void hashmap_set(Hashmap *hashmap, char *key, int value) {
  int i = hash(key);
  Person *entry = hashmap->entries[i];

  // check if key already exists → update
  while (entry != NULL) {
    if (strcmp(entry->name, key) == 0) {
      entry->age = value;
      return;
    }
    entry = entry->next;
  }

  // insert new at head
  Person *new_entry = malloc(sizeof(Person));
  strncpy(new_entry->name, key, NAME_SIZE - 1);
  new_entry->name[NAME_SIZE - 1] = '\0';
  new_entry->age = value;
  new_entry->next = hashmap->entries[i];
  hashmap->entries[i] = new_entry;
}

void hashmap_destroy(Hashmap *hashmap) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Person *entry = hashmap->entries[i];
    while (entry != NULL) {
      Person *tmp = entry;
      entry = entry->next;
      free(tmp);
    }
  }
  free(hashmap->entries);
  free(hashmap);
}

int main() {
  Hashmap *people = hashmap_create();

  hashmap_set(people, "leanghok", 13);
  hashmap_set(people, "old", 50);

  printf("%d\n", hashmap_get(people, "leanghok")); // 14
  printf("%d\n", hashmap_get(people, "old"));      // 50
  printf("%d\n", hashmap_get(people, "hello"));    // -1

  hashmap_destroy(people);
  return 0;
}
