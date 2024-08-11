#include "../include/product.h"

PRODUCT *getProducts(int *numOfProducts){
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res, *res2;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Products")) {
        fprintf(stderr, "SELECT * FROM Products failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    *numOfProducts = (int)mysql_num_rows(res);
    PRODUCT *products = malloc(*numOfProducts * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        products[i].ProductNum = atoi(row[0]);
        strncpy(products[i].ProductName, row[1], 50 );
        strncpy(products[i].Description, row[2], 500);
        strncpy(products[i].Category,    row[3], 20 );
        products[i].Rating    = atof(row[4]);
        products[i].Purchases = atoi(row[5]);
        products[i].Stock     = atoi(row[6]);
        products[i].Price     = atof(row[7]);
        products[i].Discount  = atof(row[8]);
        products[i].SellerID  = atoi(row[9]);
        i++;
    }
    mysql_free_result(res);

    if (mysql_query(conn, " select UserName from Users u, Products p where p.SellerID = u.UserID;")) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    for(int i=0; i< *numOfProducts; i++){
        row = mysql_fetch_row(res2);
        strcpy(products[i].SellerName, row[0]);
    }
    mysql_free_result(res2);
    mysql_close(conn);

    return products;
}

void displayProduct(WINDOW *pad, int y, int x, PRODUCT product){
    mvwprintw(pad, y, x, "┌─────────────────────────────────────────────────────────┐");
    mvwprintw(pad, 1+y, x, "|  [%d] %s",product.ProductNum, product.ProductName);
    mvwprintw(pad, 1+y, 58+x, "|");
    mvwprintw(pad, 2+y, x, "|  Price : %.2f",product.Price);
    mvwprintw(pad, 2+y, 58+x, "|");
    mvwprintw(pad, 3+y, x, "|  After Discount : %.2f ( -%.2f%% )", product.Price - (product.Discount * product.Price)/100, product.Discount);
    mvwprintw(pad, 3+y, 58+x, "|");
    mvwprintw(pad, 4+y, x, "|  Category : %s | Brand/Seller Name: %s", product.Category, product.SellerName);
    mvwprintw(pad, 4+y, 58+x, "|");
    mvwprintw(pad, 5+y, x, "|  Rating : %f | Purchases : %d | Available : %d ", product.Rating, product.Purchases, product.Stock);
    mvwprintw(pad, 5+y, 58+x, "|");
    mvwprintw(pad, y+6, x, "└─────────────────────────────────────────────────────────┘");
}

void insertionSort(PRODUCT *products, int numOfProducts, float *scores) {
    for (int i = 1; i < numOfProducts; i++) {
        PRODUCT key = products[i];
        float keyScore = scores[i];
        int j = i - 1;

        while (j >= 0 && scores[j] < keyScore) {
            products[j + 1] = products[j];
            scores[j + 1] = scores[j];
            j = j - 1;
        }
        products[j + 1] = key;
        scores[j + 1] = keyScore;
    }
}

PRODUCT *getPopularProduct(PRODUCT *products, int numOfProducts){
    PRODUCT *popular = (PRODUCT *)malloc(10 * sizeof(PRODUCT));
    
    //max purchase
    int maxPurchases = 0;
    for(int i=0; i<numOfProducts; i++){
        if(maxPurchases < products[i].Purchases){
            maxPurchases = products[i].Purchases;
        }
    }

    //calc popularity score
    float score[numOfProducts];
    for(int i=0; i<numOfProducts; i++){
        score[i] = ((products[i].Rating / 5) + ((float)products[i].Purchases / maxPurchases)) * 50;
    }

    //sort data
    insertionSort(products, numOfProducts, score);

    for(int i=0; i<10; i++){
        popular[i] = products[i];
    }

    return popular;
}

PRODUCT *getBestsellingProduct(int *numOfProducts){
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res, *res2;
    MYSQL_ROW row;

    if (mysql_query(conn, " select * from Products p join (select Category, max(Purchases) as maxp from Products group by Category) as mp on mp.Category=p.Category and mp.maxp=p.Purchases")) {
        fprintf(stderr, "SELECT * FROM Products failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    *numOfProducts = (int)mysql_num_rows(res);
    PRODUCT *products = malloc(*numOfProducts * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        products[i].ProductNum = atoi(row[0]);
        strncpy(products[i].ProductName, row[1], 50 );
        strncpy(products[i].Description, row[2], 500);
        strncpy(products[i].Category,    row[3], 20 );
        products[i].Rating    = atof(row[4]);
        products[i].Purchases = atoi(row[5]);
        products[i].Stock     = atoi(row[6]);
        products[i].Price     = atof(row[7]);
        products[i].Discount  = atof(row[8]);
        products[i].SellerID  = atoi(row[9]);
        i++;
    }
    mysql_free_result(res);

    if (mysql_query(conn, " select UserName from Users u, Products p where p.SellerID = u.UserID;")) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    for(int i=0; i< *numOfProducts; i++){
        row = mysql_fetch_row(res2);
        strcpy(products[i].SellerName, row[0]);
    }
    mysql_free_result(res2);
    mysql_close(conn);

    return products;
}

PRODUCT searchProductByNum(int pnum, int *status){
    PRODUCT Result;
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res,*res2;
    MYSQL_ROW row;

    char query[1000];
    snprintf(query, sizeof(query),
    "SELECT * FROM Products WHERE ProductNum=%d;", pnum);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return Result;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return Result;
    }

    int numOfRes = (int)mysql_num_rows(res);
    if (numOfRes == 0) {
        *status = 0;
        mysql_free_result(res);
        mysql_close(conn);
        return Result;
    } else {
        *status = 1;
    }

    row = mysql_fetch_row(res);
    Result.ProductNum = atoi(row[0]);
    strncpy(Result.ProductName, row[1], 50 );
    strncpy(Result.Description, row[2], 500);
    strncpy(Result.Category,    row[3], 20 );
    Result.Rating    = atof(row[4]);
    Result.Purchases = atoi(row[5]);
    Result.Stock     = atoi(row[6]);
    Result.Price     = atof(row[7]);
    Result.Discount  = atof(row[8]);
    Result.SellerID  = atoi(row[9]);
    
    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             "SELECT UserName FROM Users u, Products p WHERE p.SellerID = u.UserID AND ProductNum=%d;", pnum);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    row = mysql_fetch_row(res2);
    strcpy(Result.SellerName, row[0]);
    
    mysql_free_result(res2);
    mysql_close(conn);

    return Result;
}

PRODUCT *searchProductByName(char *str, int *numOfRes){

    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res,*res2;
    MYSQL_ROW row;

    char query[1000];
    snprintf(query, sizeof(query),
    "SELECT * FROM Products WHERE LOWER(ProductName) LIKE LOWER('%%%s%%');", str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    *numOfRes = (int)mysql_num_rows(res);
    PRODUCT *Result = malloc(*numOfRes * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        Result[i].ProductNum = atoi(row[0]);
        strncpy(Result[i].ProductName, row[1], 50 );
        strncpy(Result[i].Description, row[2], 500);
        strncpy(Result[i].Category,    row[3], 20 );
        Result[i].Rating    = atof(row[4]);
        Result[i].Purchases = atoi(row[5]);
        Result[i].Stock     = atoi(row[6]);
        Result[i].Price     = atof(row[7]);
        Result[i].Discount  = atof(row[8]);
        Result[i].SellerID  = atoi(row[9]);
        i++;
    }

    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             "SELECT UserName FROM Users u, Products p WHERE p.SellerID = u.UserID AND LOWER(ProductName) LIKE LOWER('%%%s%%');", str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    i=0;
    while ((row = mysql_fetch_row(res2))){
        strcpy(Result[i].SellerName, row[0]);
        i++;
    }
    

    mysql_free_result(res2);
    mysql_close(conn);

    return Result;
}

PRODUCT *searchProductByCategory(char *str, int *numOfRes){
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res, *res2;
    MYSQL_ROW row;

    char query[1000];
    snprintf(query, sizeof(query),
    "SELECT * FROM Products WHERE LOWER(Category) LIKE LOWER('%%%s%%');", str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    *numOfRes = (int)mysql_num_rows(res);
    PRODUCT *Result = malloc(*numOfRes * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        Result[i].ProductNum = atoi(row[0]);
        strncpy(Result[i].ProductName, row[1], 50 );
        strncpy(Result[i].Description, row[2], 500);
        strncpy(Result[i].Category,    row[3], 20 );
        Result[i].Rating    = atof(row[4]);
        Result[i].Purchases = atoi(row[5]);
        Result[i].Stock     = atoi(row[6]);
        Result[i].Price     = atof(row[7]);
        Result[i].Discount  = atof(row[8]);
        Result[i].SellerID  = atoi(row[9]);
        i++;
    }

    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             "SELECT UserName FROM Users u, Products p WHERE p.SellerID = u.UserID AND LOWER(Category) LIKE LOWER('%%%s%%');", str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    i=0;
    while ((row = mysql_fetch_row(res2))){
        strcpy(Result[i].SellerName, row[0]);
        i++;
    }

    mysql_free_result(res2);

    mysql_close(conn);

    return Result;
}

PRODUCT *searchProductByBrand(char *str, int *numOfRes){
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res, *res2;
    MYSQL_ROW row;

    char query[1000];
    snprintf(query, sizeof(query),
    "SELECT Products.* FROM Products JOIN Users ON Products.SellerID = Users.UserID WHERE Users.UserType = 'SELLER' AND LOWER(Users.UserName) LIKE LOWER('%%%s%%');", str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    *numOfRes = (int)mysql_num_rows(res);
    PRODUCT *Result = malloc(*numOfRes * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        Result[i].ProductNum = atoi(row[0]);
        strncpy(Result[i].ProductName, row[1], 50 );
        strncpy(Result[i].Description, row[2], 500);
        strncpy(Result[i].Category,    row[3], 20 );
        Result[i].Rating    = atof(row[4]);
        Result[i].Purchases = atoi(row[5]);
        Result[i].Stock     = atoi(row[6]);
        Result[i].Price     = atof(row[7]);
        Result[i].Discount  = atof(row[8]);
        Result[i].SellerID  = atoi(row[9]);
        i++;
    }

    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             "SELECT UserName FROM Users u, Products p WHERE p.SellerID = u.UserID AND LOWER(UserName) LIKE LOWER('%%%s%%');", str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    i=0;
    while ((row = mysql_fetch_row(res2))){
        strcpy(Result[i].SellerName, row[0]);
        i++;
    }
    mysql_free_result(res2);

    mysql_close(conn);

    return Result;
}

int removeFromCart(PRODUCT *cart, int *num, int target, USER user){
    int flag =-1;
    for(int i=0; i<*num; i++){
        if(target == cart[i].ProductNum){
            flag = i;
            break;
        }
    }

    if(flag == -1) return 1;

    for(int i=flag; i<*num; i++){
        cart[i]=cart[i+1];
    }
    *num = *num - 1;

    MYSQL *conn;
    connect_db(&conn);

    char query[200];
    snprintf(query,sizeof(query),
    "delete from Cart where ProductID=%d and UserID=%d",target,user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return 0;
}

int removeFromWishlist(PRODUCT *wishlist, int *num, int target, USER user){
    int flag =-1;
    for(int i=0; i<*num; i++){
        if(target == wishlist[i].ProductNum){
            flag = i;
            break;
        }
    }

    if(flag == -1) return 1;

    for(int i=flag; i<*num; i++){
        wishlist[i]=wishlist[i+1];
    }
    *num = *num - 1;

    MYSQL *conn;
    connect_db(&conn);

    char query[200];
    snprintf(query,sizeof(query),
    "delete from Wishlist where ProductID=%d and UserID=%d",target,user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return 0;
}

void removeAllFromCart(PRODUCT *wishlist, int *num, USER user){
    MYSQL *conn;
    connect_db(&conn);

    char query[200];
    snprintf(query, sizeof(query),"UPDATE Products p JOIN Cart c ON p.ProductNum = c.ProductID SET p.stock = p.stock - 1 WHERE c.UserID =%d;",user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    snprintf(query, sizeof(query)," delete from Cart where UserID=%d;",user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    mysql_close(conn);
}

PRODUCT *getCart(USER user, int *numOfRes){
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res,*res2;
    MYSQL_ROW row;

    char query[1000];
    snprintf(query, sizeof(query),
    "select * from Products p, Cart c where c.ProductID = p.ProductNum and c.UserID = %d;", user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    *numOfRes = (int)mysql_num_rows(res);
    PRODUCT *Result = malloc(*numOfRes * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        Result[i].ProductNum = atoi(row[0]);
        strncpy(Result[i].ProductName, row[1], 50 );
        strncpy(Result[i].Description, row[2], 500);
        strncpy(Result[i].Category,    row[3], 20 );
        Result[i].Rating    = atof(row[4]);
        Result[i].Purchases = atoi(row[5]);
        Result[i].Stock     = atoi(row[6]);
        Result[i].Price     = atof(row[7]);
        Result[i].Discount  = atof(row[8]);
        Result[i].SellerID  = atoi(row[9]);
        i++;
    }

    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             " select UserName from Users u, Products p, Cart c where u.UserID = p.SellerID and p.ProductNum = c.ProductID and c.UserID = %d;", user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    i=0;
    while ((row = mysql_fetch_row(res2))){
        strcpy(Result[i].SellerName, row[0]);
        i++;
    }
    

    mysql_free_result(res2);
    mysql_close(conn);

    return Result;
}

void addToCart(WINDOW *pad, USER user, PRODUCT product){

    int num =0, flag = 0;
    PRODUCT *cart = getCart(user,&num);

    for(int i=0; i<num; i++){
        if(product.ProductNum == cart[i].ProductNum){
            flag = 1;
        }
    }

    if(flag==0){
        MYSQL *conn;
        connect_db(&conn);

        char query[2000];

        snprintf(query, sizeof(query),"insert into Cart values('%d', '%d');", user.userID, product.ProductNum );
        if (mysql_query(conn, query)) {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            return;
        }

        mysql_close(conn);
        mvwprintw(pad, LINES-1, 2, "Product is Added to Cart\n");
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
        sleep(1);
        return;
    }
    mvwprintw(pad, LINES-1, 2, "Add to Cart Failed\n");
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    sleep(1);

}

PRODUCT *getWishlist(USER user, int *numOfRes){

    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res,*res2;
    MYSQL_ROW row;

    char query[1000];
    snprintf(query, sizeof(query),
    "select * from Products p, Wishlist w where w.ProductID = p.ProductNum and w.UserID = %d;", user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    *numOfRes = (int)mysql_num_rows(res);
    PRODUCT *Result = malloc(*numOfRes * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        Result[i].ProductNum = atoi(row[0]);
        strncpy(Result[i].ProductName, row[1], 50 );
        strncpy(Result[i].Description, row[2], 500);
        strncpy(Result[i].Category,    row[3], 20 );
        Result[i].Rating    = atof(row[4]);
        Result[i].Purchases = atoi(row[5]);
        Result[i].Stock     = atoi(row[6]);
        Result[i].Price     = atof(row[7]);
        Result[i].Discount  = atof(row[8]);
        Result[i].SellerID  = atoi(row[9]);
        i++;
    }

    mysql_free_result(res);

    snprintf(query, sizeof(query), 
             " select UserName from Users u, Products p, Wishlist w where u.UserID = p.SellerID and p.ProductNum = w.ProductID and w.UserID = %d;", user.userID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    res2 = mysql_store_result(conn);

    if (res2 == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    i=0;
    while ((row = mysql_fetch_row(res2))){
        strcpy(Result[i].SellerName, row[0]);
        i++;
    }

    mysql_free_result(res2);
    mysql_close(conn);

    return Result;
}

void addToWishlist(WINDOW *pad, USER user, PRODUCT product){
    int num =0, flag = 0;
    PRODUCT *wishlist = getWishlist(user,&num);

    for(int i=0; i<num; i++){
        if(product.ProductNum == wishlist[i].ProductNum){
            flag = 1;
        }
    }

    if(flag==0){
        MYSQL *conn;
        connect_db(&conn);

        char query[2000];

        snprintf(query, sizeof(query),"insert into Wishlist values('%d', '%d');", user.userID, product.ProductNum );
        if (mysql_query(conn, query)) {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            return;
        }

        mysql_close(conn);
        mvwprintw(pad, LINES-1, 2, "Product is Added to Wishlist\n");
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
        sleep(1);
        return;
    }
    mvwprintw(pad, LINES-1, 2, "Add to Wishlist Failed\n");
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    sleep(1);
}

void addProductToList(PRODUCT p){
    MYSQL *conn;
    int dbstatus = connect_db(&conn);

    if(dbstatus == -1) exit(EXIT_FAILURE);

    char query[1000];
    snprintf(query, sizeof(query), "INSERT INTO Products (ProductName, Description, Category, Rating, Purchases, Stock, Price, Discount, SellerID) VALUES ('%s', '%s', '%s', %f, %d, %d, %f, %f, %d)",
                 p.ProductName, p.Description, p.Category, p.Rating, p.Purchases, p.Stock, p.Price, p.Discount, p.SellerID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
    
}

int removeFromProductList(int ProductNum, int SellerID){
    MYSQL *conn;
    int dbstatus = connect_db(&conn);

    if(dbstatus == -1) exit(EXIT_FAILURE);

    char query[1000];
    snprintf(query, sizeof(query),"SELECT * FROM Products WHERE ProductNum=%d AND SellerID=%d;",ProductNum,SellerID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    int numOfProducts = (int)mysql_num_rows(res);
    if(numOfProducts==0){
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    snprintf(query, sizeof(query), "DELETE FROM Products WHERE ProductNum=%d AND SellerID=%d;",ProductNum,SellerID);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

PRODUCT * getSellerProductList(int UserID, int *numOfProducts){
    MYSQL *conn;
    connect_db(&conn);

    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[100];
    snprintf(query, sizeof(query),"SELECT * FROM Products WHERE SellerID=%d;",UserID);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    *numOfProducts = (int)mysql_num_rows(res);
    PRODUCT *products = malloc(*numOfProducts * sizeof(PRODUCT));

    int i = 0;
    while ((row = mysql_fetch_row(res))) {
        products[i].ProductNum = atoi(row[0]);
        strncpy(products[i].ProductName, row[1], 50 );
        strncpy(products[i].Description, row[2], 500);
        strncpy(products[i].Category,    row[3], 20 );
        products[i].Rating    = atof(row[4]);
        products[i].Purchases = atoi(row[5]);
        products[i].Stock     = atoi(row[6]);
        products[i].Price     = atof(row[7]);
        products[i].Discount  = atof(row[8]);
        products[i].SellerID  = atoi(row[9]);
        i++;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return products;
}