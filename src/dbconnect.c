#include "../include/dbconnect.h"

const char *server = "localhost";
const char *username = "username";
const char *password = "password";
const char *database = "Ecommerce"; 

int connect_db(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (*conn == NULL) {
        return -1;
    }

    if (!mysql_real_connect(*conn, server, username, password, database, 3306, NULL, 0)) {
        mysql_close(*conn);
        return -1;
    }
    return 1;
}

