#include "../include/auth.h"

int auth_user(USER *user){
    MYSQL *conn;
    int dbstatus = connect_db(&conn);

    if(dbstatus == -1) exit(EXIT_FAILURE);

    char query[200];
    snprintf(query, sizeof(query),
    "SELECT * FROM Users WHERE UserName='%s' AND Password='%s';", user->userName, user->password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    int numOfRow = (int)mysql_num_rows(res);
    MYSQL_ROW row; 
    if((row = mysql_fetch_row(res))){
        user->userID = atoi(row[0]);
        strcpy(user->userType, row[3]);    
    }

    mysql_free_result(res);
    mysql_close(conn);

    return numOfRow;
}

int create_user(USER *user){
    MYSQL *conn;
    int dbstatus = connect_db(&conn);

    if(dbstatus == -1) exit(EXIT_FAILURE);

    char query[500];
     snprintf(query, sizeof(query),
    "insert into Users(Username,Password,UserType) values('%s','%s','%s');", user->userName, user->password, user->userType);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }
    return 1;
}