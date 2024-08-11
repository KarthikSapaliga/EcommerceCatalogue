#ifndef PRODUCT_H
#define PRODUCT_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "user.h"
#include "defcolor.h"
#include "dbconnect.h"

typedef struct{
    int ProductNum;
    char ProductName[50];
    char Description[500];
    char Category[20];
    float Rating;
    int Purchases;
    int Stock;
    float Price;
    float Discount;
    int SellerID;
    char SellerName[50];
}PRODUCT;

PRODUCT *getProducts(int *numOfProducts);
void displayProduct(WINDOW *pad, int y, int x, PRODUCT product);
PRODUCT *getPopularProduct(PRODUCT *products, int numOfProducts);
PRODUCT *getBestsellingProduct(int *numOfProducts);
PRODUCT searchProductByNum(int pnum, int *status);
PRODUCT *searchProductByName(char *str, int *numOfRes);
PRODUCT *searchProductByCategory(char *str, int *numOfRes);
PRODUCT *searchProductByBrand(char *str, int *numOfRes);
void addToCart(WINDOW *pad, USER user, PRODUCT product);
void addToWishlist(WINDOW *pad, USER user, PRODUCT product);
int removeFromCart(PRODUCT *cart, int *num, int target, USER user);
void removeAllFromCart(PRODUCT *wishlist, int *num, USER user);
int removeFromWishlist(PRODUCT *wishlist, int *num, int target, USER user);
PRODUCT *getCart(USER user, int *numOfRes);
PRODUCT *getWishlist(USER user, int *numOfRes);
void addToWishlist(WINDOW *pad, USER user, PRODUCT product);
void orderCart(WINDOW *pad, PRODUCT *cart, int *n, USER user);

void addProductToList(PRODUCT p);
int removeFromProductList(int ProductNum, int SellerID);
PRODUCT *getSellerProductList(int UserID, int *numOfProducts);

#endif