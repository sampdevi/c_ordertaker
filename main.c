#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RECEIPT_HEADER_LINE_1  "MyKitchen\n" // 24
#define RECEIPT_HEADER_LINE_2  "Taft Avenue, Manila\n" // 29
#define RECEIPT_HEADER_LINE_3  "Your Receipt\n" // 26
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

void printReceipt(char date);
void printLine();

void resetProductCart();
void listProducts();
void initiateOrderTaker();
void initiateOrderTakerDateInput();
int  addToCart();

void dateParser(int date);

int isValidProduct(int _productId);

void main() {
    resetProductCart();
    printf("%s\n%s\n", 
        "[OrderTaker] > Main Menu",
        "Waiter! pa-order naman ako ng (?)\n"
    );

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
    printf("%sSelect Product ID (0 to complete order):\n> ");
    scanf("%d", &productId);

    if(!isValidProduct(productId))
    {
        printf("[ERROR]: Invalid product Id. Please try again.");
        return initiateOrderTaker();
    }
    if(productId == 0)
    {
        return initiateOrderTakeDateInput();
    }
    addToCart(productId - 1);
}

void initiateOrderTakerDateInput()
{
    printf("%s%s%s"
        "[OrderTaker] > Main Menu > Products > Confirm > Date",
        "Input the date today:",
        "\n> "
    );
    char inputDate[64];
    scanf("%s", inputDate);

    printReceipt(inputDate);
}

void printReceipt(char date)
{
    printLine();
    printf(
        "%24s%29s%26s\n\n", 
        RECEIPT_HEADER_LINE_1,
        RECEIPT_HEADER_LINE_2,
        RECEIPT_HEADER_LINE_3
    );
    print("%s", date);
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
            printf("%30.2f", productCart[i] * productPrices[i]);
            printf("\n\n");
        }
    }
    printLine();
    printf("Total %d item(s)", totalItems);
    printf("%40d\n", grandPrice);
    
    resetProductCart();
}

void dateParser(int date)
{
    int mm, dd, yyy;
    yyy = date % 10000;
    dd = date / 10000 % 100;
    mm = date / 1000000;

    printf("%s/%s/%s", mm, dd, yyy);
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


int isValidProduct(int _productId)
{
    return (_productId > MAX_PRODUCTS || _productId < 0);
}

// date
// total_price = gross x 1.12
// tax = gross x 0.12
// gross = total_price / (1 + TAX)

float computeTotal (int nOrders)
{
    float fTotal;
    fTotal = nOrders * AMOUNT;
    return fTotal;
}

float getTotalPrice(float gross)
{
    return gross * 1.12;
}

float getTax(float gross)
{
    return gross * 0.12;
}

float getGross(float total_price)
{
    return total_price / (1 + TAX);
}
