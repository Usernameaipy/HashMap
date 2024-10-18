#include "hash_map.h"

struct HashNode {
  char *key;
  int *values;
  int sizeVal;
  HashNode *next;
};

struct HashTable {
  HashNode **table;
  unsigned int valBacets;
};

struct AnsHash {
  int *values;
  int sizeVal;
};

char *strdup(const char *str) {
  unsigned int size = strlen(str);
  char *new_str = malloc(sizeof(char) * size + 1);
  for (unsigned int i = 0; i < size + 1; i++) {
    new_str[i] = str[i];
  }
  return new_str;
}

unsigned int hash(const char *str, int valBac) {
  unsigned int hash = 0;
  while (*str) {
    hash = (hash << 5) + *str++;
  }
  return hash % valBac;
}

HashTable *createTable(int sizeHash) {
  HashTable *tb = malloc(sizeof(HashTable));
  assert(tb != NULL);
  tb->table = malloc(sizeof(HashNode *) * sizeHash);
  assert(tb->table != NULL);
  for (int i = 0; i < sizeHash; i++) {
    tb->table[i] = NULL;
  }
  tb->valBacets = sizeHash;
  return tb;
}

void insert(HashTable *tables, const char *key, int value) {
  HashNode **tb = tables->table;
  unsigned int valBacets = tables->valBacets;
  unsigned int position = hash(key, valBacets);
  if (tb[position] == NULL) {
    HashNode *newNode = malloc(sizeof(HashNode));
    newNode->key = strdup(key);
    newNode->values = calloc(sizeof(int), 10);
    newNode->values[0] = value;
    newNode->sizeVal = 10;
    newNode->next = NULL;
    tb[position] = newNode;
  } else {
    int flag = 0;
    HashNode *node = tb[position];
    int *bacet = node->values;
    unsigned int sizeBacet = node->sizeVal;
    for (unsigned int i = 0; i < sizeBacet; i++) {
      if (bacet[i] == 0) {
        bacet[i] = value;
        flag = 1;
        break;
      }
    }
    if (flag != 1) {
      tb[position]->values = realloc(bacet, sizeBacet * 2 * sizeof(int));
      tb[position]->sizeVal = tb[position]->sizeVal * 2;
      bacet = node->values;
      assert(bacet != NULL);
      bacet[sizeBacet] = value;
      unsigned int newSize = tb[position]->sizeVal;
      for (unsigned int i = sizeBacet + 1; i < newSize; i++) {
        bacet[i] = 0;
      }
    }
  }
}

AnsHash *search(HashTable *table, const char *key) {
  unsigned int hash_t = hash(key, table->valBacets);
  HashNode **arr = table->table;
  AnsHash *result = NULL;
  if (arr[hash_t] != NULL) {
    HashNode *node = arr[hash_t];
    result = (AnsHash *)malloc(sizeof(AnsHash));
    assert(result != NULL);
    result->sizeVal = node->sizeVal;
    result->values = node->values;
  }
  return result;
}

void printBacet(AnsHash *bacet) {
  if (bacet != NULL) {
    for (int i = 0; i < bacet->sizeVal; i++) {
      (i == 0) ? printf("%d", bacet->values[i])
               : printf(" %d", bacet->values[i]);
    }
    printf("\n");
  }
}

void removeHash(HashTable *table) {
  int sizeTable = table->valBacets;
  HashNode **listBacet = table->table;
  for (int i = 0; i < sizeTable; i++) {
    if (listBacet[i] != NULL) {
      HashNode *node = listBacet[i];
      free(node->key);
      free(node->values);
      free(node);
    }
  }
  free(listBacet);
  free(table);
}