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
        // using the product class for microwave - base class
        new Product("Microwave", 900, true),

        // products using derived classes
        new Laptop("MacBook air", 1000, true, 13, 16, 512),
        new Headphone("AirPods Pro", 200, true, "wireless", "Apple"),
        new Keyboard("Mechanical Keyboard", 100, true, "mechanical", "Razer"),
        new Mouse("Gaming Mouse", 50, true, "wired", "Logitech"),
        new Monitor("27-inch 4K Monitor", 300, true, 27, "4K"),
    };

    // to display the list of all available items in store
    displayItems(products);
    cout << endl;

    // Create a cart object
    Cart cart;

    // Add products to the cart ( product number , quantity )
    cart.AddItem(products[0], 7); // Add laptops
    cart.AddItem(products[1], 5); // Add headphones
    cart.AddItem(products[2], 3); // Add keyboard
    cart.AddItem(products[3], 2); // Add charger
    cart.AddItem(products[4], 4); // Add mouse
    cart.AddItem(products[5], 1); // Add monitor

    cout << "--> Cart Items and Total Bill Without Any Discount : " << endl;
    cart.Print();

    // Remove a product from the cart ( product number )
    cout << "--> Removing a product from the cart :" << endl;
    cart.RemoveItem(products[5]); // Remove headphones
    cart.Print();

    // to update the quantity of a product
    cout << "--> updating a product quantity in the cart :" << endl;
    cart.UpdateQuantity(products[4], 12);
    cart.Print();

    // Change the discount strategy to PercentageDiscountStrategy (e.g., 10% discount)
    cout << "--> Applying percentage discount stratergy : ex-10%" << endl;
    DiscountStrategy *percentage_discount_strategy = new PercentageDiscountStrategy(10);
    // Calculate the discounted price
    double discounted_price = cart.GetTotalPrice() - percentage_discount_strategy->GetDiscountAmount(&cart);
    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price);
    cart.Print();

    // Change the discount strategy to BuyOneGetOneFreeDiscountStrategy
    cout << "--> Applying buy one get one discount stratergy : " << endl;
    DiscountStrategy *buy_one_get_one_discount = new BuyOneGetOneFreeDiscountStrategy;
    // Calculate the discounted price with the BuyOneGetOneFree discount
    discounted_price = cart.GetTotalPrice() - buy_one_get_one_discount->GetDiscountAmount(&cart);
    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price);
    // Print the cart contents with the BuyOneGetOneFree discount applied
    cart.Print();

    // Change the discount strategy to percentage + BuyOneGetOneFreeDiscountStrategy
    cout << "--> Applying buy-one-get-one + percentage discount stratergy : " << endl;
    DiscountStrategy *buy_one_get_one_discount2 = new BuyOneGetOneFreeDiscountStrategy;
    // Calculate the discounted price with the BuyOneGetOneFree discount
    double discounted_price2 = cart.GetTotalPrice() - buy_one_get_one_discount2->GetDiscountAmount(&cart);
    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price2);
    DiscountStrategy *percentage_discount_strategy2 = new PercentageDiscountStrategy(10);
    // Calculate the discounted price
    discounted_price2 -= percentage_discount_strategy2->GetDiscountAmount(&cart);
    cout << "DC " << discounted_price2 << endl;
    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price2);
    cart.Print();

    // Delete the products and discount strategy objects
    for (Product *product : products)
    {
        delete product;
    }

    delete percentage_discount_strategy;
    delete percentage_discount_strategy2;

    delete buy_one_get_one_discount;
    delete buy_one_get_one_discount2;

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
