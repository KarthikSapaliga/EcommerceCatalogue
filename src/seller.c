#include "../include/seller.h"

USER currUser;

void sellProduct(WINDOW *pad){
    char pname[50], desc[500], category[20], temp[10];
    float price, discount;
    int stock;
    
    werase(pad);
    wrefresh(pad);
    PRODUCT product;

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(pad, 1, 4,"SELL  PRODUCT");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 5, 4, "Enter the product name : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 6, 4, "┌──────────────────────────────────────────┐");
    mvwprintw(pad, 7, 4, "|                                          |");
    mvwprintw(pad, 8, 4, "└──────────────────────────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 5, 50, "Enter the category : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 6, 50, "┌──────────────────────────┐");
    mvwprintw(pad, 7, 50, "|                          |");
    mvwprintw(pad, 8, 50, "└──────────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 10, 4, "Enter the product description : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 11, 4, "┌────────────────────────────────────────────────────────────────────────┐");
    mvwprintw(pad, 12, 4, "|                                                                        |");
    mvwprintw(pad, 13, 4, "└────────────────────────────────────────────────────────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 15, 4, "Enter the price : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 16, 4, "┌────────────────────┐");
    mvwprintw(pad, 17, 4, "|                    |");
    mvwprintw(pad, 18, 4, "└────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 15, 30, "Enter the discount : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 16, 30, "┌────────────────────┐");
    mvwprintw(pad, 17, 30, "|                    |");
    mvwprintw(pad, 18, 30, "└────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 15, 56, "Enter the Stock : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 16, 56, "┌────────────────────┐");
    mvwprintw(pad, 17, 56, "|                    |");
    mvwprintw(pad, 18, 56, "└────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    curs_set(1);
    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwgetnstr(pad, 7, 6, pname, 49);
    mvwgetnstr(pad, 7, 52, category, 19);
    mvwgetnstr(pad, 12, 6, desc, 499);

    mvwgetnstr(pad, 17, 6, temp, 9);
    price = atof(temp);
    mvwgetnstr(pad, 17, 32, temp, 9);
    discount = atof(temp);
    mvwgetnstr(pad, 17, 58, temp, 9);
    stock = atoi(temp);
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    curs_set(0);

    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    
    strcpy(product.ProductName, pname);
    strcpy(product.Category, category);
    strcpy(product.Description, desc);
    product.Price = price;
    product.Discount = discount;
    product.Stock = stock;
    product.Rating = 0;
    product.Purchases = 0;
    product.SellerID = currUser.userID;

    addProductToList(product);

    werase(pad);
    wrefresh(pad);
}

void removeProduct(WINDOW *pad){
    char temp[10];
    int pnum;

    werase(pad);
    wrefresh(pad);

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(pad, 1, 4,"REMOVE  PRODUCT");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 5, 4, "Enter the product number of the product : ");
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 6, 4, "┌──────────────────────────────────────────┐");
    mvwprintw(pad, 7, 4, "|                                          |");
    mvwprintw(pad, 8, 4, "└──────────────────────────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    
    curs_set(1);
    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwgetnstr(pad, 7, 6, temp, 9);
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    pnum = atoi(temp);
    curs_set(0);

    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    int status = removeFromProductList(pnum, currUser.userID);

    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    if(status == 0){
        mvwprintw(pad, 10, 4, "Product Removed Successfully");
    }else{
        mvwprintw(pad, 10, 4, "Couldn't remove the product");
    }
    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));

    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    sleep(1);

    werase(pad);
    wrefresh(pad);
}

void displaySellerProducts(WINDOW *pad){
    werase(pad);
    wrefresh(pad);
    curs_set(0);

    int num = 0;
    PRODUCT *products = getSellerProductList(currUser.userID, &num);

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(pad, 1, 4,"PRODUCTS  SOLD");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 5, 4, "(Press 'q' to quit and arrow keys to navigate)");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    int padEndPos = 0, flag = 0;
    int y_offset = 0, highlight = 0, start_list = 7;

    while (1) {
        for (int i = 0; i < num; i++) {
            strcpy(products[i].SellerName, currUser.userName);
            if (highlight == i) {
                wattron(pad, COLOR_PAIR(TITLE_COLOR));
                displayProduct(pad, start_list + 7 * (padEndPos++), 4, products[i]);
                wattroff(pad, COLOR_PAIR(TITLE_COLOR));
            } else {
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                displayProduct(pad, start_list + 7 * (padEndPos++), 4, products[i]);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            }
        }

        prefresh(pad, y_offset, 0, 0, 0, LINES - 1, COLS - 1);

        switch (getch()) {
            case 'q': 
                flag = 1;
                break;
            case KEY_UP:
                if (highlight > 0) highlight--;
                if (y_offset > 0) y_offset -= 7;
                break;
            case KEY_DOWN:
                if (highlight < num - 1) highlight++;
                if (y_offset < start_list + padEndPos * 7 - LINES) y_offset += 7;
                break;
        }
        if(flag == 1) break;
        padEndPos = 0;
    }

    werase(pad);
    wrefresh(pad);
}

int sellerScript(USER user){
    currUser = user;
    char *choices[] = { 
        "01) Sell New Product  ",
        "02) Remove Product    ",
        "03) Display Products  ",
        "04) Logout            ",
        "05) Exit              "
    };

    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);

    WINDOW *pad = newpad(200,COLS);

    while(1){
        curs_set(0);
        int choice = displayMenu("SELLER_MENU", 12, 90, choices, 5, 18);
        werase(pad);
        switch(choice){
            case 1: sellProduct(pad);
                break;
            case 2: removeProduct(pad);
                break;
            case 3: displaySellerProducts(pad);
                break;
            case 4:
                delwin(pad);
                endwin();
                return 9;
                break;
            case 5:
                delwin(pad);
                endwin();
                return 10;
                break;
        }
        clear();
        refresh();
    }

    delwin(pad);
    endwin();

    return 0;
}