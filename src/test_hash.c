#include "test_hash.h"
#include <check.h>

START_TEST(createTableIsPositiv) {
  HashTable *table = createTable(10);
  _ck_assert_ptr(table, !=, ERROR);
  removeHash(table);
}
END_TEST

START_TEST(createTableIsLarge) {
  HashTable *table = createTable(100000);
  _ck_assert_ptr(table, !=, ERROR);
  removeHash(table);
}
END_TEST

START_TEST(createTableIsNegativ) {
  HashTable *table = createTable(-49);
  if (table) {
    removeHash(table);
  }
  _ck_assert_ptr(table, ==, ERROR);
}
END_TEST

START_TEST(createTableIsNull) {
  HashTable *table = createTable(0);
  _ck_assert_ptr(table, ==, ERROR);
  if (table) {
    removeHash(table);
  }
}
END_TEST

START_TEST(insertNormal) {
  HashTable *table = createTable(10);
  insert(table, "key1", 98);
  insert(table, "key6", 67);
  insert(table, "key8", 19082);
  ck_assert_int_eq(checkBacet(table, "key1"), OK);
  ck_assert_int_eq(checkBacet(table, "key6"), OK);
  ck_assert_int_eq(checkBacet(table, "key8"), OK);
  AnsHash *ansOne = search(table, "key1");
  AnsHash *ansTwo = search(table, "key6");
  AnsHash *ansThree = search(table, "key8");
  _ck_assert_ptr(ansOne->values, !=, NULL);
  _ck_assert_ptr(ansTwo->values, !=, NULL);
  _ck_assert_ptr(ansThree->values, !=, NULL);
  removeHash(table);
  free(ansOne);
  free(ansTwo);
  free(ansThree);
}
END_TEST

START_TEST(insertIsNotTable) {
  HashTable *table = createTable(-78);
  insert(table, "key1", 98);
  insert(table, "key6", 67);
  insert(table, "key8", 19082);
  ck_assert_int_eq(checkBacet(table, "key1"), ERROR);
  ck_assert_int_eq(checkBacet(table, "key6"), ERROR);
  ck_assert_int_eq(checkBacet(table, "key8"), ERROR);
  AnsHash *ansOne = NULL;
  AnsHash *ansTwo = NULL;
  AnsHash *ansThree = NULL;
  ansOne = search(table, "key1");
  ansTwo = search(table, "key6");
  ansThree = search(table, "key8");
  _ck_assert_ptr(ansOne, ==, NULL);
  _ck_assert_ptr(ansTwo, ==, NULL);
  _ck_assert_ptr(ansThree, ==, NULL);
  if (table) {
    removeHash(table);
  }
}
END_TEST

// START_TEST(insertIsNotKey){

// }
// END_TEST

// START_TEST(insertIsNotValue){

// }
// END_TEST

// START_TEST(insertNullValue){

// }
// END_TEST

Suite *HashTableTest(void) {
  Suite *suite = suite_create("HashTable");
  TCase *tcase = tcase_create("HashTable");

  // Создание Таблицы
  tcase_add_test(tcase, createTableIsPositiv);
  tcase_add_test(tcase, createTableIsLarge);
  tcase_add_test(tcase, createTableIsNegativ);
  tcase_add_test(tcase, createTableIsNull);

  // Вставка элемента в таблицу
  // P.S гарантируеться что элементы не равны нулю
  tcase_add_test(tcase, insertNormal);
  tcase_add_test(tcase, insertIsNotTable);

  suite_add_tcase(suite, tcase);

  return suite;
}

int main() {
  Suite *suite = HashTableTest();
  SRunner *sRunner = srunner_create(suite);
  srunner_set_fork_status(sRunner, CK_NOFORK);
  srunner_run_all(sRunner, CK_VERBOSE);
  int total_tests = srunner_ntests_run(sRunner);
  int failed_tests = srunner_ntests_failed(sRunner);
  srunner_free(sRunner);
  printf("Всего выполнено тестов: %d\n", total_tests);
  printf("Провалено тестов: %d\n", failed_tests);
  return 0;
}
