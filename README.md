# ECOMMERCE CATALOG

[![Watch the video](https://github.com/KarthikSapaliga/EcommerceCatalogue/blob/main/img/ecommerce.png)](https://www.youtube.com/watch?v=O3VT125Swp8&t=1s)

## 📚 Project Overview

The **Ecommerce Catalog** is a terminal-based application designed for managing and browsing products in an online store. Built using C programming, this project utilizes the ncurses library to create an intuitive user interface within the terminal, with data being stored and managed in a MySQL database.

## 🎯 Key Features

- **Product Search:** Quickly search for products by name or category.
- **Product Details:** View detailed information including price, description, and stock availability.
- **Cart Management:** Add products to your cart, update quantities, and view the total price.
- **Order Summary:** Get a summary of your order before checkout.
- **Database Interaction:** Seamlessly retrieve and update product information from a MySQL database.

## 🛠️ Technologies Used

- **C Programming:** Core functionality and database interactions.
- **ncurses Library:** Provides a smooth and responsive user interface within the terminal.
- **MySQL Database:** Stores and manages product data.

## 🗂️ Project Structure
```
📂 include
    ├── auth.h
    ├── buyer.h
    ├── dbconnect.h
    ├── defcolor.h
    ├── fancytext.h
    ├── menu.h
    ├── product.h
    ├── seller.h
    └── user.h
📂 res
    └── Ecommerce.sql 
📂 src
    ├── auth.c
    ├── buyer.c
    ├── dbconnect.c
    ├── defcolor.c
    ├── fancytext.c
    ├── main.c
    ├── menu.c
    ├── product.c
    ├── seller.c
    └── user.c
⚙️ Makefile
📝 README.md
```

## MySQL Data Import
### Create a user
```
CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON Ecommerce.* TO 'username'@'localhost';
FLUSH PRIVILEGES;
```
### Import the data
```
cd res/
mysql -u username -p Ecommerce < Ecommerce.sql
```

## 🤝 Contributing
Contributions are welcome! Please open an issue or submit a pull request with any improvements or new features.
