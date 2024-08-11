#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "user.h"
#include "dbconnect.h"

int auth_user(USER *user);
int create_user(USER *user);

#endif