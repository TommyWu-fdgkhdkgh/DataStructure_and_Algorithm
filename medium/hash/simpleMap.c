#include <stdio.h>
#include <stdlib.h>

// hash function     : divide
// overflow handling : chaining

#define SIZE_OF_HASH_TABLE 100

typedef struct element element;
struct element {
  int key;
  int data;
  element *next;
};

element *hash_table[SIZE_OF_HASH_TABLE];

int hash_function(int key) {
  return key % SIZE_OF_HASH_TABLE;
}

element *search(int key) {
  int homeBucket = hash_function(key);

  element **current = &hash_table[homeBucket];
  for(;*current;current = &((*current)->next)) {
    if((*current)->key == key) {
      break;
    }
  }

  return *current;
}

void set(int key, int data) {
  int homeBucket = hash_function(key);

  element **current = &hash_table[homeBucket];
  for(;*current;current = &((*current)->next)) {
    if((*current)->key == key) {
      break;
    }
  }

  if(*current != NULL) {
    printf("Set failed. The key has been set.\n");
  }

  *current = (element *)malloc(sizeof(element));
  (*current)->key = key;
  (*current)->data = data;
}

void delete(int key) {
  int homeBucket = hash_function(key); 

  element *last = NULL;
  element *now  = hash_table[homeBucket];

  while(now) {
    if(now->key == key) {
      if(last == NULL) {
        hash_table[homeBucket] = now->next;
      } else {
        last->next = now->next;
      }
      free(now);
      break;
    }

    last = now;
    now = now->next;
  }
}

void update(int key, int data) {
  element *e = search(key);
  if(!e) { 
    printf("update failed, the key hasn't set.\n");
  } else {
    e->data = data;
  }
}

int main(int argc, char *argv[]) {
  for(int i = 0;i < SIZE_OF_HASH_TABLE;i++) {
    hash_table[i] = NULL;
  }

  set(1, 10);
  printf("%d\n", search(1)->data); 
  
  set(101, 100);
  printf("%d\n", search(1)->data); 
  printf("%d\n", search(101)->data); 

  update(1, 101);
  printf("%d\n", search(1)->data); 

  delete(1);
  if(!search(1)) {
    printf("delete suc!\n");
  }
  printf("%d\n", search(101)->data); 

  update(1, 10);

  return 0;
}
