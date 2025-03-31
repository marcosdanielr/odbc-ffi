#include "../include/db_connection.h"
#include <CUnit/Basic.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_connect_db(void) {
  const char *conninfo = getenv("TEST_DATABASE_URL");

  CU_ASSERT_PTR_NOT_NULL_FATAL(conninfo);

  SQLRETURN ret = connect_db(conninfo);

  CU_ASSERT_EQUAL(ret, SQL_SUCCESS);

  close_db();
}

void test_close_db(void) {
  SQLRETURN ret;

  const char *conninfo = getenv("TEST_DATABASE_URL");
  ret = connect_db(conninfo);
  CU_ASSERT_EQUAL(ret, SQL_SUCCESS);

  close_db();
}

int main() {
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  CU_pSuite suite = CU_add_suite("Test Suite for db_connection", NULL, NULL);
  if (NULL == suite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(suite, "Test Connect DB", test_connect_db) ||
      NULL == CU_add_test(suite, "Test Close DB", test_close_db)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_run_tests();
  CU_cleanup_registry();

  return CU_get_error();
}
