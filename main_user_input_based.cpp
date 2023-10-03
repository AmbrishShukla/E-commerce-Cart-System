#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <map>
using namespace std;

#include "product.cpp"
#include "cart.cpp"
#include "discountStratergy.cpp"
#include "byOneGetOneFreeDiscount.cpp"
#include "percentageDiscount.cpp"
#include "laptop.cpp"
#include "headphone.cpp"
#include "keyboard.cpp"
#include "mouse.cpp"
#include "monitor.cpp"

void displayItems(vector<Product *> products)
{
    cout << "|-------------------: The list of product are :-------------------|" << endl;
    cout << endl;
    for (auto item : products)
    {
        cout << "| Name : " << item->GetName() << " | price : $" << item->GetPrice() << " | available_status : " << item->IsAvailable() << " " << endl;
        cout << "-------------------------------------------------------------------";
        cout << endl;
    }
}
int main()
{
    // Create a list of products
    vector<Product *> products = {
        // using the product class for laptop - base class
        new Product("laptop", 900, true),

        // products using derived classes
        new Laptop("macbook", 1234, true, 13, 16, 512),
        new Headphone("airpods", 212, true, "wireless", "Apple"),
        new Keyboard("keyboard", 100, true, "mechanical", "Razer"),
        new Mouse("mouse", 50, true, "wired", "Logitech"),
        new Monitor("monitor", 300, true, 27, "4K"),
    };

    displayItems(products);
    cout << endl;
    // Create a cart object
    Cart cart;

    // Ask the user for the products they want to add to their cart
    char add_another_product;
    do
    {
        string product_name;
        int product_quantity;

        cout << "Enter the product name (case sensitive): ";
        cin >> product_name;

        cout << "Enter the product quantity: ";
        cin >> product_quantity;

        // Find the product in the list of products
        Product *product = nullptr;
        for (Product *item : products)
        {
            if (item->GetName() == product_name)
            {
                product = item;
                break;
            }
        }

        // If the product is not found, print an error message and continue
        if (product == nullptr)
        {
            cout << "Product not found." << endl;
            cout << "Do you want to add another product to your cart? (y/n): ";
            cin >> add_another_product;
            continue;
        }

        // Add the product to the cart
        cart.AddItem(product, product_quantity);

        // Ask the user if they want to add another product to their cart
        cout << "Do you want to add another product to your cart? (y/n): ";
        cin >> add_another_product;
    } while (add_another_product == 'y');

    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;

    // updating or removing items from the cart
    char checkout;
    cout << "Do you want to update any item from cart ? (y/n): ";
    cin >> checkout;
    while (checkout == 'y')
    {
        string product_name;
        int product_quantity;

        cout << "Enter the product name (case sensitive): ";
        cin >> product_name;

        cout << "Enter the product updated quantity: ";
        cin >> product_quantity;

        // Find the product in the list of products
        Product *product = nullptr;
        for (Product *item : products)
        {
            if (item->GetName() == product_name)
            {
                product = item;
                break;
            }
        }

        // If the product is not found, print an error message and continue
        if (product == nullptr)
        {
            cout << "Product not found." << endl;
            cout << "Do you want to update any item from cart ? (y/n): ";
            cin >> checkout;
            continue;
        }

        // Add the product to the cart
        cart.UpdateQuantity(product, product_quantity);

        // Ask the user if they want to add another product to their cart
        cout << "Do you want to update any item from cart ? (y/n): ";
        cin >> checkout;
    }

    // to remove a product :
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;

    // updating or removing items from the cart
    char remove;
    cout << "do you want to remove any item from cart (y/n): ";
    cin >> remove;
    while (remove == 'y')
    {
        string product_name;

        cout << "Enter the product name to be removed (case sensitive): ";
        cin >> product_name;

        // Find the product in the list of products
        Product *product = nullptr;
        for (Product *item : products)
        {
            if (item->GetName() == product_name)
            {
                product = item;
                break;
            }
        }

        // If the product is not found, print an error message and continue
        if (product == nullptr)
        {
            cout << "Product not found." << endl;
            cout << "do you want to remove any item from cart (y/n): ";
            cin >> remove;
            continue;
        }

        // Add the product to the cart
        cart.RemoveItem(product);

        // Ask the user if they want to add another product to their cart
        cout << "do you want to remove any item from cart (y/n): ";
        cin >> remove;
    }
    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;

    // applying the discount stratergies
    if (cart.GetTotalPrice() >= 1000 && cart.GetTotalPrice() < 5000)
    {
        cout << "-> You are eligible for 10% discount : " << endl;
        DiscountStrategy *percentage_discount_strategy = new PercentageDiscountStrategy(10);
        // Calculate the discounted price
        double discounted_price = cart.GetTotalPrice() - percentage_discount_strategy->GetDiscountAmount(&cart);
        // Assign the discounted price to the cart
        cart.SetTotalPrice(discounted_price);
    }
    else if (cart.GetTotalPrice() >= 5000)
    {
        cout << "-> You are eligible for Buy-One-Get-One discount : " << endl;
        DiscountStrategy *buy_one_get_one_discount = new BuyOneGetOneFreeDiscountStrategy;
        // Calculate the discounted price with the BuyOneGetOneFree discount
        double discounted_price = cart.GetTotalPrice() - buy_one_get_one_discount->GetDiscountAmount(&cart);
        // Assign the discounted price to the cart
        cart.SetTotalPrice(discounted_price);
    }

    // Print the cart contents
    cout << endl;
    cout << "-----------------------------: BILL :------------------------------" << endl;

    cart.Print();

    // Delete the products and discount strategy objects
    for (Product *product : products)
    {
        delete product;
    }

    return 0;
}