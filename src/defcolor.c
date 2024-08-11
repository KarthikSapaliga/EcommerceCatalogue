#include "../include/defcolor.h"

void initiallize_colors(){
    start_color();
    init_pair(BLUE_TEXT_COLOR, COLOR_BLUE, COLOR_BLACK);
    init_pair(HIGHLIGHT_COLOR, COLOR_BLACK, COLOR_BLUE);
    init_pair(MAGENTA_TEXT_COLOR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(TITLE_COLOR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GREEN_BG, COLOR_BLACK, COLOR_GREEN);
    init_pair(GREEN_FG, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED_BG, COLOR_BLACK, COLOR_RED);
    init_pair(RED_FG, COLOR_RED, COLOR_BLACK);
}