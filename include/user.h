#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <unistd.h>
#include "defcolor.h"
#include "fancytext.h"

typedef struct {
    int userID;
    char userName[21];
    char password[21];
    char userType[7];
} USER;

int signup(USER *);
int login(USER *);

#endif