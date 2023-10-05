#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#include "product_factory.cpp"
#include "cart.cpp"
#include "discountStratergy.cpp"
#include "byOneGetOneFreeDiscount.cpp"
#include "percentageDiscount.cpp"

void displayItems(vector<Product *> products)
{
    cout << endl
         << "|-------------------: The list of product are :-------------------|" << endl;
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

    vector<Product *> products = {
        ProductFactory::CreateProduct("Product", "Laptop", 900, true, {}), // Base class product
        ProductFactory::CreateProduct("Laptop", "MacBook air", 1234, true, {"13", "16", "512"}),
        ProductFactory::CreateProduct("Headphone", "AirPods Pro", 212, true, {"wireless", "Apple"}),
        ProductFactory::CreateProduct("Keyboard", "Mechanical Keyboard", 100, true, {"mechanical", "Razer"}),
        ProductFactory::CreateProduct("Mouse", "Gaming Mouse", 50, true, {"wired", "Logitech"}),
        ProductFactory::CreateProduct("Monitor", "27-inch 4K Monitor", 300, true, {"27", "4K"}),
    };

    // to display the list of all available items in store
    displayItems(products);
    cout << endl;

    // Create a cart object
    Cart cart;

    // Add products to the cart ( product number , quantity )
    cart.AddItem(products[0], 7); // Add laptops
    cart.AddItem(products[1], 5); // Add macbook
    cart.AddItem(products[2], 3); // Add airpods
    cart.AddItem(products[3], 2); // Add keyboard
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
    // Calculate the discounted price
    // Assign the discounted price to the cart
    cout << "--> Applying percentage discount stratergy : ex-10%" << endl;
    DiscountStrategy *percentage_discount_strategy = new PercentageDiscountStrategy(10);
    double discounted_price = cart.GetTotalPrice() - percentage_discount_strategy->GetDiscountAmount(&cart);
    cart.SetTotalPrice(discounted_price);
    cart.Print();

    // Change the discount strategy to BuyOneGetOneFreeDiscountStrategy
    // Calculate the discounted price with the BuyOneGetOneFree discount
    // Assign the discounted price to the cart
    // Print the cart contents with the BuyOneGetOneFree discount applied
    cout << "--> Applying buy one get one discount stratergy : " << endl;
    DiscountStrategy *buy_one_get_one_discount = new BuyOneGetOneFreeDiscountStrategy;
    discounted_price = cart.GetTotalPrice() - buy_one_get_one_discount->GetDiscountAmount(&cart);
    cart.SetTotalPrice(discounted_price);
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
