#include "../include/fancytext.h"

void fancyTextGenerate(WINDOW *win, int y, int x, char *str){
    for(int i = 0; str[i]!='\0'; i++){
        switch(str[i]){
            case ' ':
                mvwprintw( win, y, x , " ");
                mvwprintw(win, y+1, x, " ");
                mvwprintw(win, y+2, x, " ");
                x += 2; 
                break;
            case '_':
                mvwprintw( win, y, x , " ");
                mvwprintw(win, y+1, x, " ");
                mvwprintw(win, y+2, x, "═");
                x += 1; 
                break;
            case 'A':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "╠═╣");
                mvwprintw(win, y+2, x, "╩ ╩");
                x += 3;
                break;
            case 'B':    
                mvwprintw( win, y, x , "╔╗ ");
                mvwprintw(win, y+1, x, "╠╩╗");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
            case 'C':    
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "║  ");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
            case 'D':    
                mvwprintw( win, y, x , "╔╦╗");
                mvwprintw(win, y+1, x, " ║║");
                mvwprintw(win, y+2, x, "═╩╝");
                x += 3;
                break;
            case 'E':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "║╣ ");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
            case 'F':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "╠╣ ");
                mvwprintw(win, y+2, x, "╚  ");
                x += 3;
                break;
            case 'G':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "║ ╦");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
            case 'H':
                mvwprintw( win, y, x , "╦ ╦");
                mvwprintw(win, y+1, x, "╠═╣");
                mvwprintw(win, y+2, x, "╩ ╩");
                x += 3;
                break;
            case 'I':
                mvwprintw( win, y, x , "╦");  
                mvwprintw(win, y+1, x, "║");  
                mvwprintw(win, y+2, x, "╩");  
                x += 1;
                break;
            case 'J':
                mvwprintw( win, y, x , " ╦");   
                mvwprintw(win, y+1, x, " ║");   
                mvwprintw(win, y+2, x, "╚╝");   
                x += 2;
                break;
            case 'K':
                mvwprintw( win, y, x , "╦╔═");
                mvwprintw(win, y+1, x, "╠╩╗");
                mvwprintw(win, y+2, x, "╩ ╩");
                x += 3;
                break;
            case 'L':
                mvwprintw( win, y, x , "╦  ");
                mvwprintw(win, y+1, x, "║  ");
                mvwprintw(win, y+2, x, "╩═╝");
                x += 3;
                break;
            case 'M':
                mvwprintw( win, y, x , "╔╦╗");
                mvwprintw(win, y+1, x, "║║║");
                mvwprintw(win, y+2, x, "╩ ╩");
                x += 3;
                break;
            case 'N':
                mvwprintw( win, y, x , "╔╗╔");
                mvwprintw(win, y+1, x, "║║║");
                mvwprintw(win, y+2, x, "╝╚╝");
                x += 3;
                break;
            case 'O':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "║ ║");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
            case 'P':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "╠═╝");
                mvwprintw(win, y+2, x, "╩  ");
                x += 3;
                break;
            case 'Q':
                mvwprintw( win, y, x , "╔═╗ "); 
                mvwprintw(win, y+1, x, "║═╬╗");
                mvwprintw(win, y+2, x, "╚═╝╚");
                x += 4;
                break;
            case 'R':
                mvwprintw( win, y, x , "╦═╗");
                mvwprintw(win, y+1, x, "╠╦╝");
                mvwprintw(win, y+2, x, "╩╚═");
                x += 3;
                break;
            case 'S':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "╚═╗");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
            case 'T':
                mvwprintw( win, y, x , "╔╦╗");
                mvwprintw(win, y+1, x, " ║ ");
                mvwprintw(win, y+2, x, " ╩ ");
                x += 3;
                break;
            case 'U':
                mvwprintw( win, y, x , "╦ ╦");
                mvwprintw(win, y+1, x, "║ ║");
                mvwprintw(win, y+2, x, "╚═╝"); 
                x += 3;
                break;
            case 'V':
                mvwprintw( win, y, x , "╦  ╦");
                mvwprintw(win, y+1, x, "╚╗╔╝");
                mvwprintw(win, y+2, x, " ╚╝ "); 
                x += 5;
                break;
            case 'W':
                mvwprintw( win, y, x , "╦ ╦");
                mvwprintw(win, y+1, x, "║║║");
                mvwprintw(win, y+2, x, "╚╩╝");
                x += 3;
                break;
            case 'X':
                mvwprintw( win, y, x , "═╗ ╦");
                mvwprintw(win, y+1, x, "╔╩╦╝");
                mvwprintw(win, y+2, x, "╩ ╚═");
                x += 3;
                break;
            case 'Y':
                mvwprintw( win, y, x , "╦ ╦");
                mvwprintw(win, y+1, x, "╚╦╝");
                mvwprintw(win, y+2, x, " ╩ ");
                x += 3;
                break;
            case 'Z':
                mvwprintw( win, y, x , "╔═╗");
                mvwprintw(win, y+1, x, "╔═╝");
                mvwprintw(win, y+2, x, "╚═╝");
                x += 3;
                break;
        }
    }
}
