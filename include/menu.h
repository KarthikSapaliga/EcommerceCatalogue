#ifndef MENU_H
#define MENU_H

#include <string.h>
#include <ncurses.h>
#include "defcolor.h"
#include "fancytext.h"

int displayMenu(char *title, int height, int width, char *choices[], int numOfChoices, int padding);

#endif