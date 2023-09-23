#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define RECEIPT_HEADER_LINE_1  "MyKitchen\n" // 24
#define RECEIPT_HEADER_LINE_2  "Taft Avenue, Manila\n" // 29
#define RECEIPT_HEADER_LINE_3  "Your Receipt\n" // 26

#define RECEIPT_FOOTER_LINE_1  "Thank you very much!\n" // 24
#define RECEIPT_FOOTER_LINE_2  "See you again!" // 29
#define RECEIPT_LENGTH  40

#define MAX_PRODUCTS    3
#define AMOUNT          99.00
#define TAX             0.12
#define TIP1            0.15
#define TIP2            0.18
#define TIP3            0.20

char productNames[MAX_PRODUCTS][64] = {
    "Fried Chicken Rice\t",
    "Tapsilog\t\t",
    "Sinigang Hotdog\t\t"
};

float productPrices[MAX_PRODUCTS] = {
    99.00,
    75.00,
    65.00
};

int productCart[MAX_PRODUCTS];

void printReceipt(int date);
void printLine();

void resetProductCart();
void listProducts();
void initiateOrderTaker();
void initiateOrderTakerDateInput();
int  addToCart();
void displayCart();

void dateParser(int date);

float getTax(float gross);

int isValidProduct(int _productId);

void main() {
    resetProductCart();
    printf("%s\n%s\n", 
        "[OrderTaker] > Main Menu",
        "Waiter! pa-order naman ako ng (?)\n"
    );

    system("cls");
    listProducts();
    initiateOrderTaker();
}

void listProducts()
{
    printf("[OrderTaker] > Main Menu > Products\n");
    printf("[ID]\t[Name]\t\t\t[Price]\n");
    for(int i = 0; i < MAX_PRODUCTS; i++)
    {
        printf("%d.]\t%sP%8.2f\n", i + 1, productNames[i], productPrices[i]);
    }
}

void initiateOrderTaker()
{
    int productId = -1;
    printf("Select Product ID (0 to complete order):\n> ");

    if(scanf("%d", &productId) != 1) {
        // this ^ receives an invalid input (if what is inputted is not an integer), then proceeds to this error catching code
        int c;

        // - medyo complex, pero this while loop catches any output from the terminal,
        // - until it returns EOF (end of file), until then, it will not output anything,
        // - avoiding the previous spamming initiateOrderTaker again and again.
        while ((c = getchar()) != EOF && c != '\n') continue;

        printf("[ERROR]: Invalid input. Please try again.\n");
        productId = -1;
        return initiateOrderTaker();
    }

    if(!isValidProduct(productId))
    {
        printf("[ERROR]: Invalid product Id. Please try again.\n");
        return initiateOrderTaker();
    }
    if(productId == 0)
    {
        return initiateOrderTakerDateInput();
    }
    addToCart(productId - 1);
    displayCart();
    return initiateOrderTaker();
}

void initiateOrderTakerDateInput()
{
    printf("%s%s%s",
        "[OrderTaker] > Main Menu > Products > Confirm > Date\n",
        "Input the date today:",
        "\n> "
    );
    int inputDate;
    if(scanf("%d", &inputDate) != 1) {
        int c;

        while ((c = getchar()) != EOF && c != '\n') continue;

        printf("[ERROR]: Invalid input. Please try again.\n");
        inputDate = -1;
        return initiateOrderTakerDateInput();
    }

    printReceipt(inputDate);
}

void printReceipt(int date)
{
    system("cls");
    printLine();
    printf(
        "%24s%29s%26s\n\n", 
        RECEIPT_HEADER_LINE_1,
        RECEIPT_HEADER_LINE_2,
        RECEIPT_HEADER_LINE_3
    );
    dateParser(date); printf("\n");
    printLine();

    int totalItems = 0;
    float grandPrice = 0.0;
    float totalPrice = 0.0;
    for(int i = 0; i < MAX_PRODUCTS; i++)
    {
        if(productCart[i] == 0) continue;
        else {
            totalItems += productCart[i];
            totalPrice += productCart[i] * (productPrices[i] - getTax(productPrices[i]));
            grandPrice += productCart[i] * productPrices[i];
            printf("%s\n", productNames[i]);
            printf("%10d x %.2f", productCart[i], productPrices[i]);
            printf("%22.2f", productCart[i] * productPrices[i]);
            printf("\n\n");
        }
    }
    printLine();
    printf("Total %2d item(s)", totalItems);
    printf("%24.2f\n", totalPrice);

    printf("Sales Tax");
    printf("%31.2f\n", getTax(totalPrice));
    printLine();

    printf("Grand Total");
    printf("%29.2f\n\n", grandPrice);
    
    printf("Tip Guide:");
    printf("%18s15%% = %5.2f\n%28s18%% = %5.2f\n%28s20%% = %5.2f\n\n", "", grandPrice * TIP1, "", grandPrice * TIP2, "", grandPrice * TIP3);

    printf("%5s%13s",
        RECEIPT_FOOTER_LINE_1,
        RECEIPT_FOOTER_LINE_2
    );
    resetProductCart();
}

void dateParser(int date)
{
    int mm, dd, yyy;
    yyy = date % 10000;
    dd = date / 10000 % 100;
    mm = date / 1000000;

    printf("%d/%d/%d", mm, dd, yyy);
}

void printLine()
{
    for(int i = 0; i < RECEIPT_LENGTH; i++)
    {
        printf("-");
    }
    printf("\n");
}

void resetProductCart()
{
    for(int i = 0; i < MAX_PRODUCTS; i++)
    {
        productCart[i] = 0;
    }
}

int addToCart(int productId)
{
    if(!isValidProduct(productId)) return 0;
    productCart[productId]++;
    return 1;
}

void displayCart()
{
    system("cls");
    listProducts();
    printLine();
    printf("\n[Current Cart Items]\n");
    for(int i = 0; i < MAX_PRODUCTS; i++)
    {
        if(productCart[i] == 0) continue;
        else {
            printf("%s x%d\n", productNames[i], productCart[i]);
        }
    }
}

int isValidProduct(int _productId)
{
    return (_productId > MAX_PRODUCTS || _productId < 0) ? 0 : 1;
}

float getTax(float gross)
{
    return gross * 0.12;
}
