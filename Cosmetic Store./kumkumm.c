#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int stock;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;
const char *DATABASE_FILE = "products.txt";

// Function to save products to file
void saveProductsToFile() {
    FILE *file = fopen(DATABASE_FILE, "w");
    if (!file) {
        return;
    }
    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d|%s|%f|%d\n", products[i].id, products[i].name, products[i].price, products[i].stock);
    }
    fclose(file);
}

// Function to load products from file
void loadProductsFromFile() {
    FILE *file = fopen(DATABASE_FILE, "r");
    if (!file) {
        return;
    }
    while (fscanf(file, "%d|%[^|]|%f|%d\n", &products[productCount].id, products[productCount].name, &products[productCount].price, &products[productCount].stock) == 4) {
        productCount++;
    }
    fclose(file);
}

// Function to add product
int addProduct(int id, const char* name, float price, int stock) {
    if (productCount >= MAX_PRODUCTS) {
        return -1; // Product list is full
    }
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            return -2; // ID already exists
        }
    }
    products[productCount].id = id;
    strcpy(products[productCount].name, name);
    products[productCount].price = price;
    products[productCount].stock = stock;
    productCount++;
    saveProductsToFile();
    return 0; // Success
}

// Function to get product info
void getProducts(char* buffer) {
    if (productCount == 0) {
        strcpy(buffer, "No products available.\n");
        return;
    }
    for (int i = 0; i < productCount; i++) {
        char product_info[200];
        sprintf(product_info, "ID: %d | Name: %s | Price: %.2f | Stock: %d\n", 
                products[i].id, products[i].name, products[i].price, products[i].stock);
        strcat(buffer, product_info);
    }
}
