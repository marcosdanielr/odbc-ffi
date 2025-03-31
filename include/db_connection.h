#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <sql.h>
#include <sqlext.h>

SQLRETURN connect_db(const char *conninfo);
void close_db();

#endif
