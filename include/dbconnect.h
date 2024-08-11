#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int connect_db(MYSQL**conn);

#endif