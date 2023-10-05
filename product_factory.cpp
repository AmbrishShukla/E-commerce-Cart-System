#include <iostream>
using namespace std;

#include "Product.cpp"
#include "laptop.cpp"
#include "headphone.cpp"
#include "keyboard.cpp"
#include "mouse.cpp"
#include "monitor.cpp"

// declarations for product classes
class Laptop;
class Headphone;
class Keyboard;
class Mouse;
class Monitor;

class ProductFactory
{
public:
    static Product *CreateProduct(const string &type, const string &name, double price, bool available, const vector<string> &additionalInfo);
};

// Implement the ProductFactory to create products
Product *ProductFactory::CreateProduct(const string &type, const string &name, double price, bool available, const vector<string> &additionalInfo)
{
    if (type == "Laptop")
    {
        if (additionalInfo.size() == 3)
        {
            int screenSize = stoi(additionalInfo[0]);
            int ramSize = stoi(additionalInfo[1]);
            int storageSize = stoi(additionalInfo[2]);
            return new Laptop(name, price, available, screenSize, ramSize, storageSize);
        }
    }
    else if (type == "Headphone")
    {
        if (additionalInfo.size() == 2)
        {
            string wirelessType = additionalInfo[0];
            string brand = additionalInfo[1];
            return new Headphone(name, price, available, wirelessType, brand);
        }
    }
    else if (type == "Keyboard")
    {
        if (additionalInfo.size() == 2)
        {
            string keyboardType = additionalInfo[0];
            string brand = additionalInfo[1];
            return new Keyboard(name, price, available, keyboardType, brand);
        }
    }
    else if (type == "Mouse")
    {
        if (additionalInfo.size() == 2)
        {
            string mouseType = additionalInfo[0];
            string brand = additionalInfo[1];
            return new Mouse(name, price, available, mouseType, brand);
        }
    }
    else if (type == "Monitor")
    {
        if (additionalInfo.size() == 2)
        {
            int screenSize = stoi(additionalInfo[0]);
            string resolution = additionalInfo[1];
            return new Monitor(name, price, available, screenSize, resolution);
        }
    }

    // If the type is not recognized or the additionalInfo is incorrect, create a base Product
    return new Product(name, price, available);
}