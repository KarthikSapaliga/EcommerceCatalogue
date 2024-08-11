#include "../include/user.h"
#include "../include/auth.h" // included here to avoid circular dependency issue

#define WIDTH 50
#define HEIGHT 22

void getPassword(WINDOW *win, int y, int x, char *password){
    noecho();
    int pswdIdx = 0; 
    int ch;
    wmove(win, y, x);
    while((ch = wgetch(win)) != '\n'){
        wrefresh(win);
        if(ch == KEY_BACKSPACE || ch == 127 || ch == 8 || ch == 330){
            if(pswdIdx > 0) {
                pswdIdx--;
                mvwaddch(win, y, x + pswdIdx, ' ');
                wmove(win, y, x + pswdIdx);
            }
        } else if(isprint(ch) && pswdIdx < 19){
            password[pswdIdx++] = ch;
            waddch(win, '*');
        }
        wrefresh(win);
    }
    password[pswdIdx] = '\0';
    echo();
}

int login(USER *user){

    WINDOW *login_win;
    
    setlocale(LC_ALL, "");
    initscr();
    initiallize_colors();
    cbreak();
    keypad(stdscr, TRUE);
    
    int start_y = (LINES - HEIGHT)/2;
    int start_x = ( COLS - WIDTH )/2;
    refresh();

    login_win = newwin(HEIGHT, WIDTH, start_y, start_x);
    wattron(login_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    box(login_win,0,0);
    wattroff(login_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    keypad(login_win, TRUE);
    wrefresh(login_win);

    wattron(login_win, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(login_win, 2, (WIDTH - 3*5)/2, "LOGIN");
    wattroff(login_win, COLOR_PAIR(TITLE_COLOR));

    echo();
    wattron(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(login_win, 7, 6, "Enter username : ");
    wattroff(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(login_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(login_win, 8, 6, "┌────────────────────────────────────┐");
    mvwprintw(login_win, 9, 6, "|                                    |");
    mvwprintw(login_win, 10, 6, "└────────────────────────────────────┘");
    wattroff(login_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(login_win, 12, 6, "Enter password : ");
    wattroff(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(login_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(login_win, 13, 6, "┌────────────────────────────────────┐");
    mvwprintw(login_win, 14, 6, "|                                    |");
    mvwprintw(login_win, 15, 6, "└────────────────────────────────────┘");
    wattroff(login_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    curs_set(1);
    wattron(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwgetnstr(login_win, 9, 8, user->userName, 19);
    getPassword(login_win, 14, 8, user->password);
    wattroff(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    curs_set(0);
    noecho();

    char *choices[] = {
        "[ SUBMIT ]",
        "[ RESET  ]",
        "[  BACK  ]"
    };

    curs_set(0);
    wattron(login_win, COLOR_PAIR(HIGHLIGHT_COLOR));
    mvwprintw(login_win, 18, 6, "%s", choices[0]);
    wattroff(login_win, COLOR_PAIR(HIGHLIGHT_COLOR));

    wattron(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(login_win, 18, 20, "%s", choices[1]);
    mvwprintw(login_win, 18, 34, "%s", choices[2]);
    wattroff(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    wrefresh(login_win);

    noecho();
    int currentChoice = 1, choice = 0, key;
    while(1){
        key = wgetch(login_win);
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
                choice = currentChoice;
                break;
            default:
                break;
        }
        if(choice != 0) break;
        for(int i = 0; i < 3; i++){
            if(currentChoice == i + 1){
                wattron(login_win, COLOR_PAIR(HIGHLIGHT_COLOR));
                mvwprintw(login_win, 18, 6 + 14 * i, "%s", choices[i]);
                wattroff(login_win, COLOR_PAIR(HIGHLIGHT_COLOR));
            } else {
                wattron(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(login_win, 18, 6 + 14 * i, "%s", choices[i]);
                wattroff(login_win, COLOR_PAIR(BLUE_TEXT_COLOR));
            }
        }
        wrefresh(login_win);
    }

	if(choice != 1){
		curs_set(1);
        werase(login_win);
        wrefresh(login_win);
    	delwin(login_win);
    	endwin();
		return choice;
	}

    int status = auth_user(user);
    if(status == 1){
        wattron(login_win, COLOR_PAIR(GREEN_BG));
        mvwprintw(login_win, 18, 6, "[          Login Successfull         ]");
        wattroff(login_win, COLOR_PAIR(GREEN_BG));
    }else if(status == 0){
        wattron(login_win, COLOR_PAIR(RED_BG));
        mvwprintw(login_win, 18, 6, "[    Invalid username or password    ]");
        wattroff(login_win, COLOR_PAIR(RED_BG));
    }else if(status == -1){
        wattron(login_win, COLOR_PAIR(RED_BG));
        mvwprintw(login_win, 18, 6, "[     Database Connection Failed     ]");
        wattroff(login_win, COLOR_PAIR(RED_BG));
    }
    
    wrefresh(login_win);
    sleep(1);
    curs_set(1);
    werase(login_win);
    wrefresh(login_win);
    delwin(login_win);
    endwin();
    return status;
}

char *strupr(char *str) {
    char *orig = str;
    while (*str) {
        *str = toupper(*str);
        str++;
    }
    return orig;
}

int signup(USER *user){
    WINDOW *signup_win;
    
    setlocale(LC_ALL, "");
    initscr();
    initiallize_colors();
    cbreak();
    keypad(stdscr, TRUE);
    
    int start_y = (LINES - HEIGHT - 5)/2;
    int start_x = ( COLS - WIDTH )/2;
    refresh();

    signup_win = newwin(HEIGHT+5, WIDTH, start_y, start_x);
    wattron(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    box(signup_win,0,0);
    wattroff(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    keypad(signup_win, TRUE);

    wattron(signup_win, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(signup_win, 2, (WIDTH - 3*6)/2, "SIGNUP");
    wattroff(signup_win, COLOR_PAIR(TITLE_COLOR));

    wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(signup_win, 7, 6, "Enter username : ");
    wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(signup_win, 8, 6, "┌────────────────────────────────────┐");
    mvwprintw(signup_win, 9, 6, "|                                    |");
    mvwprintw(signup_win, 10, 6, "└────────────────────────────────────┘");
    wattroff(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(signup_win, 12, 6, "Enter password : ");
    wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(signup_win, 13, 6, "┌────────────────────────────────────┐");
    mvwprintw(signup_win, 14, 6, "|                                    |");
    mvwprintw(signup_win, 15, 6, "└────────────────────────────────────┘");
    wattroff(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(signup_win, 17, 6, "Enter your role (BUYER or SELLER) : ");
    wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(signup_win, 18, 6, "┌────────────────────────────────────┐");
    mvwprintw(signup_win, 19, 6, "|                                    |");
    mvwprintw(signup_win, 20, 6, "└────────────────────────────────────┘");
    wattroff(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    wrefresh(signup_win);

    echo();
    curs_set(1);
    wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwgetnstr(signup_win, 9, 8, user->userName, 19);
    getPassword(signup_win, 14, 8, user->password);
    mvwgetnstr(signup_win, 19, 8, user->userType, 19);
    wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    curs_set(0);
    


    while(strcmp(strupr(user->userType),"SELLER")!=0 && strcmp(strupr(user->userType),"BUYER")!=0){
        wattron(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        mvwprintw(signup_win, 19, 6, "|                                    |");
        wattroff(signup_win, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
        mvwgetnstr(signup_win, 19, 8, user->userType, 19);
        wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    }
    strcpy(user->userType, strupr(user->userType));
    noecho();

    char *choices[] = {
        "[ SUBMIT ]",
        "[ RESET  ]",
        "[  BACK  ]"
    };

    curs_set(0);
    wattron(signup_win, COLOR_PAIR(HIGHLIGHT_COLOR));
    mvwprintw(signup_win, 23, 6, "%s", choices[0]);
    wattroff(signup_win, COLOR_PAIR(HIGHLIGHT_COLOR));

    wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(signup_win, 23, 20, "%s", choices[1]);
    mvwprintw(signup_win, 23, 34, "%s", choices[2]);
    wrefresh(signup_win);
    wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));

    int currentChoice = 1, choice = 0, key;
    while(1){
        key = wgetch(signup_win);
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
                choice = currentChoice;
                break;
            default:
                break;
        }
        if(choice != 0) break;
        for(int i = 0; i < 3; i++){
            if(currentChoice == i + 1){
                wattron(signup_win, COLOR_PAIR(HIGHLIGHT_COLOR));
                mvwprintw(signup_win, 23, 6 + 14 * i, "%s", choices[i]);
                wattroff(signup_win, COLOR_PAIR(HIGHLIGHT_COLOR));
            } else {
                wattron(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(signup_win, 23, 6 + 14 * i, "%s", choices[i]);
                wattroff(signup_win, COLOR_PAIR(BLUE_TEXT_COLOR));
            }
        }
        wrefresh(signup_win);
    }

    if(choice != 1){
		curs_set(1);
        werase(signup_win);
        wrefresh(signup_win);
    	delwin(signup_win);
    	endwin();
		return choice;
	}

    int status = create_user(user);
    if(status == 1){
        mvwprintw(signup_win, 23, 6, "[          Signup Successfull         ]");
    }else if(status == -1){
        mvwprintw(signup_win, 23, 6, "[     Database Connection Failed     ]");
    }

    curs_set(1);
    wrefresh(signup_win);
    sleep(1);
    werase(signup_win);
    wrefresh(signup_win);
    delwin(signup_win);
    endwin();
    return choice;
}

