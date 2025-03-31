#include "../include/db_connection.h"

SQLHENV env;
SQLHDBC dbc;

SQLRETURN connect_db(const char *conninfo) {
  SQLRETURN ret;
  ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
  if (ret != SQL_SUCCESS)
    return ret;

  ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
  if (ret != SQL_SUCCESS)
    return ret;

  ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
  if (ret != SQL_SUCCESS)
    return ret;

  ret = SQLDriverConnect(dbc, NULL, (SQLCHAR *)conninfo, SQL_NTS, NULL, 0, NULL,
                         SQL_DRIVER_COMPLETE);
  return ret;
}

void close_db() {
  SQLFreeHandle(SQL_HANDLE_DBC, dbc);
  SQLFreeHandle(SQL_HANDLE_ENV, env);
}
