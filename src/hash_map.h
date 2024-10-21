#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Гарантируеться что в бакетах хранять лишь не нулевые значения
typedef struct HashNode HashNode;
typedef struct HashTable HashTable;
typedef struct AnsHash AnsHash;
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
char *strdup(const char *);
// Хэш функция
unsigned int hash(const char *, int);
// Создание таблицы, применять только в первый раз, единственный параметр -
// количество начальных элементов HashTable
HashTable *createTable(int);
/*Добавление элемента в хэш таблицу
Первый параметр - сама таблица
Второй параметр - ключ для значения
Третий параметр - само значение*/
void insert(HashTable *, const char *, int);
/*Изменяет количество бакетов в Таблице*/
void addBacet(HashTable *, unsigned int);
/*Удаляет весь бакет хранящийся по заданному хэшу*/
void rmForHash(HashTable *, const char *);
/*Проверяет существует ли бакет по задонному ключу*/
bool checkBacet(HashTable *, const char *);
/*Ищет необходимый бакет по ключу
Возвращает структуру типа AnsHash*/
AnsHash *search(HashTable *, const char *);
/*Вывод в stdout структуры типа AnsHash*/
void printBacet(AnsHash *);
/*Полностью удаляет Hash Table*/
void removeHash(HashTable *);
#endif