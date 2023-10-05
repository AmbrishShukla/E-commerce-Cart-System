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

// function to display the item which are there in the product list
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

// Function to handle adding, updating, or removing items in the cart
void manageCart(Cart &cart, const vector<Product *> &products)
{
    char action;

    do
    {
        string product_name;
        int product_quantity;

        cout << "Enter the product name (case sensitive): ";
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

        if (product == nullptr)
        {
            cout << "Product not found." << endl;
        }
        else
        {

            // Determine the action: Add, Update, or Remove
            cout << "Add (a) / Update (u) / Remove (r) the product from your cart? (a/u/r): ";
            cin >> action;

            if (action == 'a')
            {
                cout << "Enter the product quantity: ";
                cin >> product_quantity;

                cart.AddItem(product, product_quantity);
            }
            else if (action == 'u')
            {
                cout << "Enter the product quantity: ";
                cin >> product_quantity;
                cart.UpdateQuantity(product, product_quantity);
            }
            else if (action == 'r')
            {
                cart.RemoveItem(product);
            }
        }

        cout << "Do you want to perform another action on your cart? (y/n): ";
        cin >> action;

    } while (action == 'y');
}

// driver code
int main()
{
    // Create a list of products
    vector<Product *> products = {
        ProductFactory::CreateProduct("Product", "laptop", 900, true, {}), // Base class product
        ProductFactory::CreateProduct("Laptop", "macbook", 1234, true, {"13", "16", "512"}),
        ProductFactory::CreateProduct("Headphone", "airpods", 212, true, {"wireless", "Apple"}),
        ProductFactory::CreateProduct("Keyboard", "keyboard", 100, true, {"mechanical", "Razer"}),
        ProductFactory::CreateProduct("Mouse", "mouse", 50, true, {"wired", "Logitech"}),
        ProductFactory::CreateProduct("Monitor", "monitor", 300, true, {"27", "4K"}),
    };

    displayItems(products);
    cout << endl;

    // Create a cart object
    Cart cart;

    // Manage the cart (add, update, or remove items)
    manageCart(cart, products);

    cout << "-------------------------------------------------------------------" << endl;
    cout << endl;

    // applying the discount stratergies
    // Calculate the discounted price with the
    // Assign the discounted price to the cart

    if (cart.GetTotalPrice() >= 1000 && cart.GetTotalPrice() < 5000)
    {
        cout << "-> You are eligible for 10% discount : " << endl;
        DiscountStrategy *percentage_discount_strategy = new PercentageDiscountStrategy(10);
        double discounted_price = cart.GetTotalPrice() - percentage_discount_strategy->GetDiscountAmount(&cart);
        cart.SetTotalPrice(discounted_price);
    }
    else if (cart.GetTotalPrice() >= 5000)
    {
        cout << "-> You are eligible for Buy-One-Get-One discount : " << endl;
        DiscountStrategy *buy_one_get_one_discount = new BuyOneGetOneFreeDiscountStrategy;
        double discounted_price = cart.GetTotalPrice() - buy_one_get_one_discount->GetDiscountAmount(&cart);
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