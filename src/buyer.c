#include "../include/buyer.h"

USER currentUser;

void productDetail(WINDOW *pad, PRODUCT product){
    werase(pad);
    wrefresh(pad);

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(pad, 2, 2, "PRODUCT DETAILS");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));

    mvwprintw(pad, 6, 2, "Product Number : #%d",product.ProductNum);
    mvwprintw(pad, 7, 2, "Product Name   : %s",product.ProductName);
    mvwprintw(pad, 8, 2, "Price          : %.2f ( -%.1f%% )", product.Price - (product.Discount * product.Price)/100, product.Discount);
    mvwprintw(pad, 9, 2, "Original Price : %.2f",product.Price);
    mvwprintw(pad, 10, 2, "Category  : %s",product.Category);
    mvwprintw(pad, 11, 2, "Seller    : %s",product.SellerName);
    mvwprintw(pad, 12, 2, "Rating    : %.1f",product.Rating);
    mvwprintw(pad, 13, 2, "Purchases : %d",product.Purchases);
    mvwprintw(pad, 14, 2, "Stock     : %d",product.Stock);
    mvwprintw(pad, 15, 2, "Description : %s",product.Description);

    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    char *choices[]={
        "[ BACK ]",
        "[ ADD TO CART ]",
        "[ ADD TO WISHLIST ]"
    };
    int choice = -1, currentChoice = 0;
    while(1){
        int pos_x = 2;
        for(int i = 0; i < 3; i++){
            if(currentChoice == i){
                wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                mvwprintw(pad, 17, pos_x, "%s", choices[i]);
                wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
            } else {
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(pad, 17, pos_x, "%s", choices[i]);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            }
            pos_x += strlen(choices[i]) + 2;
        }
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
        switch(getch()){
            case KEY_LEFT:
                if(currentChoice > 0) currentChoice--;
                else currentChoice = 2;
                break;
            case KEY_RIGHT:
                if(currentChoice < 2) currentChoice++;
                else currentChoice = 0;
                break;
            case 10: 
                choice = currentChoice;
                break;
        }
        if(choice != -1) break;
    }

    switch(choice){
        case 0: break;
        case 1: addToCart(pad, currentUser, product);
                break;
        case 2: addToWishlist(pad, currentUser, product);
                break;
    }

    werase(pad);
    wrefresh(pad);
    return;
}

int searchState = 0;
void header(WINDOW *pad, char *str, int choice){
    switch(choice){
        case 1: 
            wattron(pad, COLOR_PAIR(TITLE_COLOR));
            fancyTextGenerate(pad, 1, 4, "POPULAR");
            wattroff(pad, COLOR_PAIR(TITLE_COLOR));
            wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            mvwprintw(pad, 4, 4, "(Use the arrow keys to navigate & Enter to select the product & 'q' to go back)");
            wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

            break;
        case 2:
            wattron(pad, COLOR_PAIR(TITLE_COLOR)); 
            fancyTextGenerate(pad, 1, 4, "BEST SELLING");
            wattroff(pad, COLOR_PAIR(TITLE_COLOR));
            wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            mvwprintw(pad, 4, 4, "(Use the arrow keys to navigate & Enter to select the product & 'q' to go back)");
            wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            break;
        case 3:
            wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            mvwprintw(pad, 1, 4, "Enter the Product Name :");
            wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            mvwprintw(pad, 2, 4, "┌─────────────────────────────────────────────────────────┐");
            mvwprintw(pad, 3, 4, "|                                                         |");
            mvwprintw(pad, 4, 4, "└─────────────────────────────────────────────────────────┘");
            mvwprintw(pad, 5, 4, "(Use the arrow keys to navigate & Enter to select the product & 'q' to go back)");
            wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
            if(searchState == 0){
                echo();
                curs_set(1);
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwgetnstr(pad, 3, 6, str, 99);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                curs_set(0);
                noecho();
                searchState = 1;
            }else{
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(pad, 3, 6, "%s", str);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
            }break;
        case 4:
            wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            mvwprintw(pad, 1, 4, "Enter the Category :");
            wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            mvwprintw(pad, 2, 4, "┌─────────────────────────────────────────────────────────┐");
            mvwprintw(pad, 3, 4, "|                                                         |");
            mvwprintw(pad, 4, 4, "└─────────────────────────────────────────────────────────┘");
            mvwprintw(pad, 5, 4, "(Use the arrow keys to navigate & Enter to select the product & 'q' to go back)");
            wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
            if(searchState == 0){
                echo();
                curs_set(1);
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwgetnstr(pad, 3, 6, str, 99);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                curs_set(0);
                noecho();
                searchState = 1;
            }else{
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(pad, 3, 6, "%s", str);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
            }break;
        case 5:
            wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            mvwprintw(pad, 1, 4, "Enter the Brand name :");
            wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
            wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            mvwprintw(pad, 2, 4, "┌─────────────────────────────────────────────────────────┐");
            mvwprintw(pad, 3, 4, "|                                                         |");
            mvwprintw(pad, 4, 4, "└─────────────────────────────────────────────────────────┘");
            mvwprintw(pad, 5, 4, "(Use the arrow keys to navigate & Enter to select the product & 'q' to go back)");
            wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
            prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
            if(searchState == 0){
                echo();
                curs_set(1);
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwgetnstr(pad, 3, 6, str, 99);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                curs_set(0);
                noecho();
                searchState = 1;
            }else{
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(pad, 3, 6, "%s", str);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
            }break;

    }
}

void printList(WINDOW *pad, PRODUCT *products, int num, char *str, int choice) {
    int padEndPos = 0;
    int y_offset = 0, highlight = 0, start_list = 7;
    
    header(pad, str,choice);

    curs_set(0);
    while (1) {
        for (int i = 0; i < num; i++) {
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
            case 'q': return;
            case KEY_UP:
                if (highlight > 0) highlight--;
                if (y_offset > 0) y_offset -= 7;
                break;
            case KEY_DOWN:
                if (highlight < num - 1) highlight++;
                if (y_offset < start_list + padEndPos * 7 - LINES) y_offset += 7;
                break;
            case 10:
                if(num!=0)productDetail(pad, products[highlight]);
                header(pad, str, choice);
                break;
        }
        padEndPos = 0;
    }
    curs_set(1);
}

int displayCart(WINDOW *pad, PRODUCT *cart, int *num){
    int  y = 8, x=4;

    werase(pad);
    wrefresh(pad);
    curs_set(0);

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(pad, 1, x, "CART");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 4, x, "(press 'q' to quit, arrow keys to navigate and enter to select choice");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    if(*num<1){
        mvwprintw(pad, 6, x, "'0' Products are in the Cart");
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
        sleep(1);
        return 'q';
    }

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    mvwprintw(pad, y, x, "┌─────────────────────────────────────────────────────────┐");
    for (int i = 0; i < *num; i++) {
        mvwprintw(pad, 1+y, x, "|");
        wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        mvwprintw(pad, 1+y, x+2, "[%d] %s",cart[i].ProductNum, cart[i].ProductName);
        wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        wattron(pad, COLOR_PAIR(TITLE_COLOR));
        mvwprintw(pad, 1+y, 58+x, "|");
        mvwprintw(pad, 2+y, x, "|");
        wattroff(pad, COLOR_PAIR(TITLE_COLOR));
        wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        mvwprintw(pad, 2+y, x+2, "Price : %.2f", cart[i].Price - (cart[i].Discount * cart[i].Price)/100);
        wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        wattron(pad, COLOR_PAIR(TITLE_COLOR));
        mvwprintw(pad, 2+y, 58+x, "|");
        mvwprintw(pad, 3+y, x, "|");
        mvwprintw(pad, 3+y, 58+x, "|");
        y+=3;
    }
    mvwprintw(pad, y, x, "└─────────────────────────────────────────────────────────┘");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    
    char *choices[]={
        "Order the Cart",
        "Remove from Cart"
    };

    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
    mvwprintw(pad, 6, 4, "%s",choices[0]);
    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 6, 20, "%s",choices[1]);
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    int choice = 0, y_offset=0;
    while (1) {     
        switch (getch()) {
            case 'q': return 'q';
            case KEY_LEFT: case KEY_RIGHT:
                choice = (choice + 1)%2;
                y_offset=0;
                if(choice == 0){
                    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(pad, 6, 4, "%s",choices[0]);
                    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));

                    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                    mvwprintw(pad, 6, 20, "%s",choices[1]);
                    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                }else{
                    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                    mvwprintw(pad, 6, 4, "%s",choices[0]);
                    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));

                    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(pad, 6, 20, "%s",choices[1]);
                    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                }   
                break;
            case KEY_UP : 
                y_offset -=2;
                break;
            case KEY_DOWN : 
                y_offset +=2;
                break;
            case 10:
                y_offset = y-5;
                prefresh(pad, y_offset, 0, 0, 0, LINES - 1, COLS - 1);
                if(choice == 0) orderCart(pad, cart, num, currentUser);
                if(choice == 1) {
                    wattron(pad, COLOR_PAIR(RED_FG));
                    mvwprintw(pad, y+1, 4, "Enter the Product Number :");
                    wattroff(pad, COLOR_PAIR(RED_FG)); 
                    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
                    mvwprintw(pad, y+2, 4, "┌─────────────────────────────────────────────────────────┐");
                    mvwprintw(pad, y+3, 4, "|                                                         |");
                    mvwprintw(pad, y+4, 4, "└─────────────────────────────────────────────────────────┘");
                    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
                    prefresh(pad, y_offset, 0, 0, 0, LINES - 1, COLS - 1);
                    echo();
                    curs_set(1);
                        int target;
                        char input[5];
                        wattron(pad, COLOR_PAIR(RED_FG));
                        mvwgetnstr(pad, y+3, 6, input, 4);
                        wattroff(pad, COLOR_PAIR(RED_FG)); 
                        target = atoi(input);
                    curs_set(0);
                    noecho();
                    int status = removeFromCart(cart, num, target, currentUser);
                    if(status == 0) mvwprintw(pad, y+5, 4, "Product removed from Cart Successfully");
                    if(status == 1) mvwprintw(pad, y+5, 4, "Product doesn't exist");
                    sleep(1);
                }
                return 1;
        }
        prefresh(pad, y_offset, 0, 0, 0, LINES - 1, COLS - 1);
    }
    curs_set(1);
}

int displayWishlist(WINDOW *pad, PRODUCT *wishlist, int *num){
    int  y = 8, x=4;

    werase(pad);
    wrefresh(pad);
    curs_set(0);

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    fancyTextGenerate(pad, 1, x, "WISHLIST");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 4, x, "(press 'q' to quit, arrow keys to navigate and enter to select choice");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    if(*num<1){
        mvwprintw(pad, 6, x, "'0' Products are in the Wishlist");
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
        sleep(1);
        return 'q';
    }

    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    mvwprintw(pad, y, x, "┌─────────────────────────────────────────────────────────┐");
    for (int i = 0; i < *num; i++) {
        mvwprintw(pad, 1+y, x, "|");
        wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        mvwprintw(pad, 1+y, x+2, "[%d] %s",wishlist[i].ProductNum, wishlist[i].ProductName);
        wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        wattron(pad, COLOR_PAIR(TITLE_COLOR));
        mvwprintw(pad, 1+y, 58+x, "|");
        mvwprintw(pad, 2+y, x, "|");
        wattroff(pad, COLOR_PAIR(TITLE_COLOR));
        wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        mvwprintw(pad, 2+y, x+2, "Price : %.2f", wishlist[i].Price - (wishlist[i].Discount * wishlist[i].Price)/100);
        wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        wattron(pad, COLOR_PAIR(TITLE_COLOR));
        mvwprintw(pad, 2+y, 58+x, "|");
        mvwprintw(pad, 3+y, x, "|");
        mvwprintw(pad, 3+y, 58+x, "|");
        y+=3;
    }
    mvwprintw(pad, y, x, "└─────────────────────────────────────────────────────────┘");
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    
    char *choices[]={
        "Add to Cart",
        "Remove from Wishlist"
    };

    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
    mvwprintw(pad, 6, 4, "%s",choices[0]);
    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, 6, 20, "%s",choices[1]);
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    int choice = 0, y_offset=0;
    
    while (1) {     
        switch (getch()) {
            case 'q': return 'q';
            case KEY_LEFT: case KEY_RIGHT:
                choice = (choice + 1)%2;
                y_offset=0;
                if(choice == 0){
                    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(pad, 6, 4, "%s",choices[0]);
                    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));

                    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                    mvwprintw(pad, 6, 20, "%s",choices[1]);
                    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                }else{
                    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                    mvwprintw(pad, 6, 4, "%s",choices[0]);
                    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));

                    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(pad, 6, 20, "%s",choices[1]);
                    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                }   
                break;
            case KEY_UP : 
                y_offset -=2;
                break;
            case KEY_DOWN : 
                y_offset +=2;
                break;
            case 10:
                y_offset = y-5;
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwprintw(pad, y+1, 4, "Enter the Product Number :");
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR)); 
                wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
                mvwprintw(pad, y+2, 4, "┌─────────────────────────────────────────────────────────┐");
                mvwprintw(pad, y+3, 4, "|                                                         |");
                mvwprintw(pad, y+4, 4, "└─────────────────────────────────────────────────────────┘");
                wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
                prefresh(pad, y_offset, 0, 0, 0, LINES - 1, COLS - 1);
                echo();
                curs_set(1);
                int target;
                char input[5];
                wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                mvwgetnstr(pad, y+3, 6, input, 4);
                wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR)); 
                target = atoi(input);

                if(choice == 0) {
                    int status = 0;

                    PRODUCT product = searchProductByNum(target, &status);

                    if(status == 1){
                        addToCart(pad, currentUser, product);
                    } else {
                        mvwprintw(pad, y+5, 4, "Invalid Product Number");
                        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
                    } 
                }
                if(choice == 1) {
                    int status = removeFromWishlist(wishlist, num, target, currentUser);
                    if(status == 0) mvwprintw(pad, y+5, 4, "Product removed from Wishlist Successfully");
                    if(status == 1) mvwprintw(pad, y+5, 4, "Product doesn't exist");
                }
                curs_set(0);
                noecho();
                return 1;
        }
        prefresh(pad, y_offset, 0, 0, 0, LINES - 1, COLS - 1);
    }
    curs_set(1);
}

void orderCart(WINDOW *pad, PRODUCT *wishlist, int *n, USER user){
    werase(pad);
    wrefresh(pad);

    if(*n == 0){
        mvwprintw(pad, 1,4,"'0' item in the Cart");
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
        sleep(1);
        return;
    }

    int y = 3;
    float total=0, grand_total=0;

    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, 1, 2,"┌──────────────────────────────────────────────────────────────────────────────────────┐");
    mvwprintw(pad, 2, 2,"| P.No |          Product Name           |      Price      | Discount |      Total     |");
    mvwprintw(pad, 3, 2,"└──────────────────────────────────────────────────────────────────────────────────────┘");
    wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));

    for(int i=0; i<*n; i++){
        total = wishlist[i].Price - (wishlist[i].Price*wishlist[i].Discount)/100;
        grand_total += total;
        wattron(pad, COLOR_PAIR(TITLE_COLOR));
        mvwprintw(pad, y+1, 5,"%02d",wishlist[i].ProductNum);
        mvwprintw(pad, y+1, 13,"%.30s",wishlist[i].ProductName);
        mvwprintw(pad, y+1, 48,"%.2f",wishlist[i].Price);
        mvwprintw(pad, y+1, 64,"%.1f",wishlist[i].Discount);
        mvwprintw(pad, y+1, 77,"%.2f",total);
        wattron(pad, COLOR_PAIR(TITLE_COLOR));

        wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        mvwprintw(pad, y+1, 2,"|");
        mvwprintw(pad, y+1, 9,"|");
        mvwprintw(pad, y+1, 42," |");
        mvwprintw(pad, y+1, 61,"|");
        mvwprintw(pad, y+1, 72,"|");
        mvwprintw(pad, y+1, 89,"|");
        wattroff(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
        y++;
    }
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    mvwprintw(pad, y + 1, 2,"┌──────────────────────────────────────────────────────────────────────────────────────┐");
    mvwprintw(pad, y + 2, 2,"|                                                      Grand Total    |                |");
    mvwprintw(pad, y + 3, 2,"└──────────────────────────────────────────────────────────────────────────────────────┘");
    wattron(pad, COLOR_PAIR(MAGENTA_TEXT_COLOR));
    wattron(pad, COLOR_PAIR(TITLE_COLOR));
    mvwprintw(pad, y + 2, 77,"%.2f",grand_total);
    wattroff(pad, COLOR_PAIR(TITLE_COLOR));

    y+=4;
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    char *choices[]={
        "[ Purchace Now ]",
        "[     Back     ]"
    };

    int x = 30;
    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
    mvwprintw(pad, y, x, "%s",choices[0]);
    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    mvwprintw(pad, y, x + 16, "%s",choices[1]);
    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);

    int choice = 0;
    while (1) {     
        switch (getch()) {
            case KEY_LEFT: case KEY_RIGHT:
                choice = (choice + 1)%2;
                if(choice == 0){
                    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(pad, y, x, "%s",choices[0]);
                    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));

                    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                    mvwprintw(pad, y, x + 16, "%s",choices[1]);
                    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                }else{
                    wattron(pad, COLOR_PAIR(BLUE_TEXT_COLOR));
                    mvwprintw(pad, y, x, "%s",choices[0]);
                    wattroff(pad, COLOR_PAIR(BLUE_TEXT_COLOR));

                    wattron(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                    mvwprintw(pad, y, x + 16, "%s",choices[1]);
                    wattroff(pad, COLOR_PAIR(HIGHLIGHT_COLOR));
                }   
                break;
            case 10:
                if(choice == 0) {
                    wattron(pad, COLOR_PAIR(GREEN_FG));
                    mvwprintw(pad, y+2, 33, "Product Purchase Successful");
                    wattron(pad, COLOR_PAIR(GREEN_FG));
                    removeAllFromCart(wishlist,n,user);
                    free(wishlist);
                    wishlist = NULL;
                    *n = 0;
                    prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
                    sleep(1);
                }
                if(choice == 1) {
                    return;
                }
                return;
        }
        prefresh(pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    }
}

int buyerScript(USER user){
    currentUser = user;

    int numOfProducts=0,ch=0;
    char str[100];

    char *choices[] = { 
        "01) Popular Products           ",
        "02) Best Selling               ",
        "03) Search Products by Name    ",
        "04) Search Products by Category",
        "05) Search Products by Brand   ",
        "06) Display the Cart           ",
        "07) Display the Wishlist       ",
        "08) Order the Cart             ",
        "09) Logout                     ",
        "10) Exit                       "
    };

    PRODUCT *products = getProducts(&numOfProducts);
    PRODUCT *searchResult;
    PRODUCT *cart;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);

    WINDOW *pad = newpad(200,COLS);

    while(1){
        curs_set(0);
        int choice = displayMenu("BUYER_MENU", 15, 90, choices, 10, 10);
        werase(pad);
        
        switch(choice){
            case 1: PRODUCT *popular = getPopularProduct(products, numOfProducts);
                    printList(pad, popular, 10, "POPULAR", 1);
                    free(popular);
                break;
            case 2: PRODUCT *bestselling = getBestsellingProduct(&numOfProducts);
                    printList(pad, bestselling, numOfProducts, "BEST_SELLING", 2);
                    free(bestselling);
                break;
            case 3: header(pad, str, 3);
                    searchResult = searchProductByName(str,&numOfProducts);
                    printList(pad, searchResult, numOfProducts, str, 3);
                    free(searchResult);
                    searchState = 0;
                break;
            case 4: header(pad, str, 4);
                    searchResult = searchProductByCategory(str,&numOfProducts);
                    printList(pad, searchResult, numOfProducts, str, 4);
                    free(searchResult);
                    searchState = 0;
                break;
            case 5: header(pad, str, 5);
                    searchResult = searchProductByBrand(str,&numOfProducts);
                    printList(pad, searchResult, numOfProducts, str, 5);
                    free(searchResult);
                    searchState = 0; 
                break;
            case 6: cart = getCart(user, &numOfProducts);
                    ch = 0;
                    while(ch != 'q'){
                        ch = displayCart(pad,cart,&numOfProducts);
                    }
                break;
            case 7: PRODUCT *wishlist = getWishlist(user, &numOfProducts);
                    ch = 0;
                    while(ch != 'q'){
                        ch = displayWishlist(pad,wishlist,&numOfProducts);
                    }
                break;
            case 8: 
                    cart = getCart(user, &numOfProducts);
                    orderCart(pad, cart, &numOfProducts, user);
                break;
            case 9: 
                delwin(pad);
                endwin();
                free(products);
                return 9;
                break;
            case 10: 
                delwin(pad);
                endwin();
                free(products);
                return 10;
                break;
        }
        
        clear();
        refresh();
    }
    delwin(pad);
    endwin();

    free(products);
    return 0;
}