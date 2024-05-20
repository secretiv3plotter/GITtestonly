#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

typedef struct product {
    char generic_name[50];
    char name[50];
    char unit[50];
    double price;
    char product_code[20];
}product;

void generate_product_code(product*);
void add(product*, int*);
void display(product*, int*);
void search(product*, int*, char*);
void modify(product*, int*, char*);
void revenue(product*, int*);

int main (){
    product catalog[1000];
    int product_count[1000];
    int n;

    do{
        printf("\nALING NENA'S GROCERY STORE MANAGER\n");
        printf("1. Add new product.\n");
        printf("2. Display all products.\n");
        printf("3. Search for a product.\n");
        printf("4. Modify product info.\n");
        printf("5. Calculate revenue per day.\n");
        printf("6. Exit\n");
        printf("Enter menu number: ");
        scanf("%i", &n);
        printf("\n");

        switch (n){
            case 1:
                int m;
                printf("Enter the number of products you want to add: ");
                scanf("%i", &m);
                while(m != 0){
                    add(catalog, product_count);
                    m--;
                }
                break;
            case 2:
                display(catalog, product_count);
                break;
            case 3:
                char search_term[50];
                printf("Enter search term: ");
                scanf("%*[\n]%[^\n]", search_term);
                search(catalog, product_count, search_term);
                break;
            case 4:
                char id[20];
                printf("Enter the product code: ");
                scanf("%*[\n]%[^\n]", id);
                modify(catalog, product_count, id);
                break;
            case 5:
                revenue(catalog, product_count);
                break;
            case 6:
                printf("Exiting program...\n");
                sleep(1);
                break;
            default:
                printf("Please re-enter a valid menu number.\n");
                printf("\n");
                sleep(1);
        }

    } while(n != 6);

    return 0;
}

void generate_product_code(product *prod){ // function to generate product code based on first letters of generic name, brand, and timestamp
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    sprintf(prod->product_code, "%c%c%04d%02d%02d%02d%02d%02d",
            prod->generic_name[0], prod->name[0],
            local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
            local->tm_hour, local->tm_min, local->tm_sec);
}


void add(product *catalog, int *product_count){ //function to add a product and checks if it is already in the system
    char generic[50], brand[50], unit[50]; 
    double price;
    int flag = 0;

    printf("\nEnter generic product: ");
    scanf("%*[\n]%[^\n]", generic);
    printf("Enter brand name: ");
    scanf("%*[\n]%[^\n]", brand);
    printf("Enter price: ");
    scanf("%lf", &price);
    printf("Enter unit of measure: ");
    scanf("%*[\n]%[^\n]", unit);    

    for (int i = 0; i < *product_count-1; i++) {
        if (strstr(catalog[i].generic_name, generic) != NULL &&
            strstr(catalog[i].name, brand) != NULL &&
            strstr(catalog[i].unit, unit) != NULL &&
            catalog[i].price == price) {
                flag++;
                printf("\nProduct is already in the system!\n");
                sleep(1);
                break;
        }
    }
    if(flag == 0){
        strcpy(catalog[*product_count].generic_name, generic);
        strcpy(catalog[*product_count].name, brand);
        catalog[*product_count].price = price;
        strcpy(catalog[*product_count].unit, unit);
        generate_product_code(&catalog[*product_count]);
        (*product_count)++;
        printf("Product added successfully.\n");
    }
}

void display(product *catalog, int *product_count) { //function to display all products in the catalog
    printf("PRODUCTS IN THE CATALOG:\n\n");
    sleep(1);
    for (int i = 0; i < *product_count; i++) {
        printf("Generic Name: %s\n", catalog[i].generic_name);
        printf("Brand: %s\n", catalog[i].name);
        printf("Price: %.2lf ", catalog[i].price);
        printf("%s\n", catalog[i].unit);
        printf("Product Code: %s\n\n", catalog[i].product_code);
    }
    sleep(1);
}

void search(product *catalog, int *product_count, char *search_term){ // function to search for a product
    printf("SEARCH RESULTS:\n\n");
    int count = 0;
    for (int i = 0; i < *product_count; i++) {
        if (strstr(catalog[i].generic_name, search_term) != NULL ||
            strstr(catalog[i].name, search_term) != NULL ||
            strstr(catalog[i].unit, search_term) != NULL ||
            strstr(catalog[i].product_code, search_term) != NULL ||
            catalog[i].price == atof(search_term)) {
            printf("Generic Name: %s\n", catalog[i].generic_name);
            printf("Brand: %s\n", catalog[i].name);
            printf("Price: %.2f ", catalog[i].price);
            printf("%s\n", catalog[i].unit);
            printf("Product Code: %s\n\n", catalog[i].product_code);
            count++;
        }
    }
    if(count == 0){
        printf("Product not found.\n");
    }
    sleep(1);
}

void modify(product *catalog, int *product_count, char *id) { // function to make info modifications to a product
    int flag = 0;
    for (int i = 0; i < *product_count; i++) {
        if (strstr(catalog[i].product_code, id) != NULL) {
            flag++;
            int n;
            do{ 
                printf("\n1. Change generic name.\n");
                printf("2. Change brand name.\n");
                printf("3. Change price.\n");
                printf("4. Change unit of measure.\n");
                printf("5. Generate new product code.\n");
                printf("6. Done.\n");
                printf("Enter option number: ");
                scanf("%d", &n);
                printf("\n");

                switch (n) {
                case 1:
                    printf("Enter new generic product: ");
                    scanf("%*[\n]%[^\n]", catalog[i].generic_name);
                    generate_product_code(&catalog[i]);
                    break;
                case 2:
                    printf("Enter new brand name: ");
                    scanf("%*[\n]%[^\n]", catalog[i].name);
                    generate_product_code(&catalog[i]);
                    break;
                case 3:
                    printf("Enter new price: ");
                    scanf("%lf", &catalog[i].price);
                    break;
                case 4:
                    printf("Enter new unit of measure: ");
                    scanf("%*[\n]%[^\n]", catalog[i].unit);
                    break;
                case 5:
                    generate_product_code(&catalog[i]);
                    break;
                case 6:
                    break;
                default:
                    printf("Re-enter a valid option.\n");
                }
            }while(n != 6);
        break;
        }
    }
    if(flag == 0){
        printf("Product not found.\n");
    }    
}

void revenue(product *catalog, int *product_count) { //function to calculate revenue per day
    double total_revenue = 0;

    for (int i = 0; i < *product_count; i++) {
        double products_sold;
        printf("How many %s %s did you sell today? ", catalog[i].name, catalog[i].generic_name);
        scanf("%lf", &products_sold);
        total_revenue += products_sold * catalog[i].price;
    }
    printf("Total revenue for today is %.2lf\n", total_revenue);
    sleep(1);
}
