#include "../include/menu.h"

void print_choices(WINDOW *win, int y, int x, char *choices[], int n, int currentChoice){
    int maxPerColumn = (n+1)/2;

    for(int i=0; i<n; i++){
        int row = i % maxPerColumn;
        int col = (i/maxPerColumn)*(strlen(choices[i]) + 4);

        if(currentChoice == i+1){
            wattron  (win, COLOR_PAIR( HIGHLIGHT_COLOR ));
            mvwprintw(win, y+row, x+col,"%s", choices[i]);
            wattroff (win, COLOR_PAIR( HIGHLIGHT_COLOR ));
        }else{
            wattron  (win, COLOR_PAIR( BLUE_TEXT_COLOR ));
            mvwprintw(win, y+row,x+col,"%s",choices[i]);
            wattroff (win, COLOR_PAIR( BLUE_TEXT_COLOR ));
        }
    }
    wrefresh(win);
}

int displayMenu(char *title, int height, int width, char *choices[], int numOfChoices, int padding){
    WINDOW *menu;

    noecho();
    curs_set(0);

    if (LINES < height || COLS < width) {
        endwin();
        printf("Terminal window is too small. Minimum size required: %dx%d\n", width, height);
        return 1;
    }
    
    int start_y = (LINES - height)/2;
    int start_x = ( COLS - width )/2;

    menu = newwin(height, width, start_y, start_x);
    keypad(menu, TRUE);
    wattron(menu, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    box(menu, 0, 0);
    wattroff(menu, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(menu, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(menu, 2, (width - strlen(title)*3 - 2)/2, title);
    wattroff(menu, COLOR_PAIR(TITLE_COLOR));

    wattron(menu, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    char instruction[] = "(Use the arrow keys to navigate and press Enter to select the choice)";
    mvwprintw(menu, 5, (width-strlen(instruction))/2, "%s", instruction);
    wattroff(menu, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    wrefresh(menu);
    
    WINDOW *subwin = derwin(menu, height - 6, width - 2*padding, 6, padding);
    keypad(subwin, TRUE);

    int currentChoice = 1, choice = 0, key;

    print_choices(subwin, 1, 4, choices, numOfChoices, currentChoice);

    int maxPerColumn = (numOfChoices + 1)/2;
    while(1){
        key = wgetch(menu);
        switch(key){
            case KEY_UP:
                if (currentChoice > 1) 
                    currentChoice--;
                else 
                    currentChoice = numOfChoices;
                break;

            case KEY_DOWN:
                if (currentChoice < numOfChoices) 
                    currentChoice++;
                else 
                    currentChoice = 1;
                break;

            case KEY_LEFT:
                if (currentChoice >= 1 && currentChoice <= maxPerColumn) 
                    currentChoice += maxPerColumn;
                else
                    currentChoice -= maxPerColumn;
                break;

            case KEY_RIGHT:
                if(currentChoice >= 1 && currentChoice <= maxPerColumn) 
                    currentChoice += maxPerColumn;
                else
                    currentChoice -= maxPerColumn;
                break;

            case 10:
                choice = currentChoice;
                break;

            default: break;
        }
        if(numOfChoices%2 !=0 && currentChoice > numOfChoices){
            currentChoice -= maxPerColumn;
        }
        print_choices(subwin, 1, 4, choices, numOfChoices, currentChoice);
        if(choice != 0) break;
    }

    curs_set(1);
    echo();

    werase(subwin);
    wrefresh(subwin);
    werase(menu);
    wrefresh(menu);
    delwin(subwin);
    delwin(menu);

    return choice;
}