#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ncurses.h>
#include "../include/menu.h"    
#include "../include/user.h"
#include "../include/buyer.h"
#include "../include/seller.h"
#include "../include/defcolor.h"
#include "../include/fancytext.h"

#define HEIGHT 18
#define WIDTH 90

int home(){
    WINDOW *mainScr;
    setlocale(LC_ALL, "");
    initscr();
    clear();
    cbreak();
    initiallize_colors();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(0);

    if (LINES < HEIGHT || COLS < WIDTH) {
        endwin();
        printf("Terminal window is too small. Minimum size required: %dx%d\n", WIDTH, HEIGHT);
        exit(EXIT_SUCCESS);
    }
    
    int start_y = (LINES - HEIGHT)/2;
    int start_x = ( COLS - WIDTH )/2;

    mainScr = newwin(HEIGHT, WIDTH, start_y, start_x);
    keypad(mainScr, TRUE);
    
    wattron(mainScr, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    box(mainScr,0,0);
    wattroff(mainScr, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(mainScr, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(mainScr, 2, (WIDTH-strlen("WELCOME TO"))/2, "WELCOME TO");
    wattroff(mainScr, COLOR_PAIR(BLUE_TEXT_COLOR));
    
    wattron(mainScr, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(mainScr, 3, (WIDTH-18*3+2)/2, "ECOMMERCE CATLOGUE");
    wattroff(mainScr, COLOR_PAIR(TITLE_COLOR));
    wrefresh(mainScr);

    int padding = 7;
    WINDOW * subwin = derwin(mainScr, 8, WIDTH - 2*padding, 6, padding);

    wattron(subwin, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(subwin, 1, 0, "Explore a wide range of products at your fingertips. Use the arrow keys to  navigate through categories and products, and press Enter to make your selection. Whether you're browsing or ready to buy, our catalogue makes shopping easy and convenient.");
    mvwprintw(subwin, 6, 0, "Note : Restart the Program if Products are Not Displayed Properly");
    wattroff(subwin, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    wrefresh(subwin);

    char *choices[]={
        " Sign In ",
        " Sign Up ",
        " Exit "
    };

    wattron(mainScr, COLOR_PAIR(HIGHLIGHT_COLOR));
    mvwprintw(mainScr, 15, 31, "%s", choices[0]);
    wattroff(mainScr, COLOR_PAIR(HIGHLIGHT_COLOR));

    wattron(mainScr, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(mainScr, 15, 42, "%s", choices[1]);
    mvwprintw(mainScr, 15, 53, "%s", choices[2]);
    wattroff(mainScr, COLOR_PAIR(BLUE_TEXT_COLOR));
    wrefresh(mainScr);

    int currentChoice = 1, key;
    while(1){
        key = wgetch(mainScr);
        switch(key){
            case KEY_LEFT:
                if(currentChoice > 1) currentChoice--;
                else currentChoice = 3;
                break;
            case KEY_RIGHT:
                if(currentChoice < 3) currentChoice++;
                else currentChoice = 1;
                break;
            case 10: 
                echo();
                curs_set(1);
                delwin(subwin);
                delwin(mainScr);
                endwin();
                return currentChoice;
                break;
        }

        for(int i = 0; i < 3; i++){
            if(currentChoice == i + 1){
                wattron(mainScr, COLOR_PAIR(HIGHLIGHT_COLOR));
                mvwprintw(mainScr, 15, 31 + 11*i, "%s", choices[i]);
                wattroff(mainScr, COLOR_PAIR(HIGHLIGHT_COLOR));
            } else {
                wattron(mainScr, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(mainScr, 15, 31 + 11*i, "%s", choices[i]);
                wattroff(mainScr, COLOR_PAIR(BLUE_TEXT_COLOR));
            }
        }
        wrefresh(mainScr);
    }

    echo();
    curs_set(1);
    delwin(subwin);
    delwin(mainScr);
    endwin();
}

int main(){
    
    USER currentUser;
    int authStatus;
    /*************************
     [authStatus]
     0  : invalid credentials
     1  : auth success
     2  : reset
     3  : back
     -1 : db connect fail
    **************************/
   int userStatus;

    while(1){
        int choice = home();
        switch(choice){
            case 1: authStatus =  login(&currentUser); break;
            case 2: authStatus = signup(&currentUser); break;
            case 3: exit(EXIT_SUCCESS);
        }

        if(authStatus == -1) exit(EXIT_FAILURE);

        while(authStatus == 0 || authStatus == 2){
            switch(choice){
                case 1: authStatus =  login(&currentUser); break;
                case 2: authStatus = signup(&currentUser); break;
            }   
        }

        if(authStatus == 1){
            if(strcmp(currentUser.userType, "BUYER" )==0){
                userStatus = buyerScript(currentUser);
            }
            if(strcmp(currentUser.userType, "SELLER")==0){
                userStatus = sellerScript(currentUser);
            }
        }
        if(userStatus == 10) exit(EXIT_SUCCESS);
    }

    return 0;
}