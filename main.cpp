#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "product.cpp"
#include "cart.cpp"
#include "discountStratergy.cpp"
#include "byOneGetOneFreeDiscount.cpp"
#include "percentageDiscount.cpp"

void displayItems(vector<Product *> products)
{
    cout << "The list of available items are :" << endl;
    for (auto item : products)
    {
        cout << "{ Name : " << item->GetName();
        cout << " , price : " << item->GetPrice();
        cout << " , available_status : " << item->IsAvailable() << " }";
        cout << endl;
    }
}

int main()
{
    // Create a list of products
    vector<Product *> products = {
        new Product("Laptop", 1000, true),
        new Product("Headphones", 50, true),
        new Product("keyboard", 200, true),
    };

    // to display the list of all available items in store
    displayItems(products);
    cout << endl;

    // Create a cart object
    Cart cart;
    cart.AddItem(products[0]);

    cout << "PRINT 1 :" << endl;
    cart.Print();
    // Add products to the cart
    cart.AddItem(products[0], 7); // Add 2 laptops
    cart.AddItem(products[1], 3); // Add 3 headphones
    cart.AddItem(products[2], 3);

    // Print the cart contents and total bill
    cout << "PRINT 2 :" << endl;
    cart.Print();

    // Remove a product from the cart
    cart.RemoveItem(products[1]); // Remove headphones
    cart.AddItem(products[2]);

    // Print the updated cart contents and total bill
    cout << "PRINT 3 :" << endl;
    cart.Print();

    // Change the discount strategy to PercentageDiscountStrategy (e.g., 10% discount)
    DiscountStrategy *percentage_discount_strategy = new PercentageDiscountStrategy(10.0);

    // Calculate the discounted price
    double discounted_price = cart.GetTotalPrice() - percentage_discount_strategy->GetDiscountAmount(&cart);
    // cout << "discounted_price " << discounted_price << endl;
    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price);

    // Print the cart contents with the percentage discount applied
    cout << "PRINT 4 :" << endl;
    cart.UpdateQuantity(products[2], 3);
    cart.Print();

    // Change the discount strategy to BuyOneGetOneFreeDiscountStrategy
    DiscountStrategy *bogo_discount_strategy = new BuyOneGetOneFreeDiscountStrategy;

    // Calculate the discounted price with the BuyOneGetOneFree discount
    discounted_price = cart.GetTotalPrice() - bogo_discount_strategy->GetDiscountAmount(&cart);
    // cout << "discounted_price bogo " << bogo_discount_strategy->GetDiscountAmount(&cart) << endl;

    // Assign the discounted price to the cart
    cart.SetTotalPrice(discounted_price);

    // Print the cart contents with the BuyOneGetOneFree discount applied
    cout << "PRINT 5 :" << endl;
    cart.Print();

    // Delete the products and discount strategy objects
    for (Product *product : products)
    {
        delete product;
    }

    delete percentage_discount_strategy;
    delete bogo_discount_strategy;

    return 0;
}