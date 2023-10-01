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
        cout << "| Name : " << item->GetName() << " | price : " << item->GetPrice() << " | available_status : " << item->IsAvailable() << " " << endl;
        cout << "-------------------------------------------------------------------";
        cout << endl;
    }
}

int main()
{
    // Create a list of products
    vector<Product *> products = {
        new Laptop("MacBook air", 1000, true, 13, 16, 512),
        new Headphone("AirPods Pro", 200, true, "wireless", "Apple"),
        new Keyboard("Mechanical Keyboard", 100, true, "mechanical", "Razer"),
        new Mouse("Gaming Mouse", 50, true, "wired", "Logitech"),
        new Monitor("27-inch 4K Monitor", 300, true, 27, "4K"),
        new Product("Microwave", 9000, true),
    };

    // to display the list of all available items in store
    displayItems(products);
    cout << endl;

    // Create a cart object
    Cart cart;

    // Add products to the cart
    cart.AddItem(products[0], 7); // Add 2 laptops
    cart.AddItem(products[1], 5); // Add 3 headphones
    cart.AddItem(products[2], 3); // Add 2 keyboard
    cart.AddItem(products[3], 2); // Add 2 charger
    cart.AddItem(products[4], 4); // Add 3 mouse
    // cart.AddItem(products[5], 1); // Add 2 monitor
    cout << "PRINT 5 :" << endl;

    // cart.RemoveItem(products[5]); // Remove headphones
    // Remove a product from the cart

    // Change the discount strategy to PercentageDiscountStrategy (e.g., 10% discount)
    DiscountStrategy *percentage_discount_strategy = new PercentageDiscountStrategy(10);

    // Calculate the discounted price
    double discounted_price = cart.GetTotalPrice() - percentage_discount_strategy->GetDiscountAmount(&cart);
    // cout << "discounted_price " << discounted_price << endl;

    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price);

    // to update the quantity of a product
    // cart.UpdateQuantity(products[4], 4);

    // Change the discount strategy to BuyOneGetOneFreeDiscountStrategy
    DiscountStrategy *buy_one_get_one_discount = new BuyOneGetOneFreeDiscountStrategy;

    // Calculate the discounted price with the BuyOneGetOneFree discount
    discounted_price = cart.GetTotalPrice() - buy_one_get_one_discount->GetDiscountAmount(&cart);
    // cout << "discounted_price bogo " << buy_one_get_one_discount->GetDiscountAmount(&cart) << endl;

    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price);

    // Print the cart contents with the BuyOneGetOneFree discount applied
    cart.Print();

    // Delete the products and discount strategy objects
    for (Product *product : products)
    {
        delete product;
    }

    delete percentage_discount_strategy;
    delete buy_one_get_one_discount;

    return 0;
}

// Create a list of products
// vector<Product *> products = {
//     new Product("Laptop", 1000, true),
//     new Product("Headphones", 50, true),
//     new Product("keyboard", 200, true),
//     new Product("mouse", 60, true),
//     new Product("monitor", 400, true),
// };
