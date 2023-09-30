// Cart Class
class Cart
{
public:
    map<Product *, int> cartItems;
    double total_price = 0; // Add a total_price member variable

public:
    Cart() {}

    // my create function with single parameter
    void AddItem(Product *product)
    {
        if (this->cartItems.find(product) != this->cartItems.end())
        {
            this->cartItems[product] += 1;
        }
        else
        {
            this->cartItems.insert({product, 1});
        }
    }

    void AddItem(Product *product, int quantity)
    {
        if (this->cartItems.find(product) != this->cartItems.end())
        {
            this->cartItems[product] += quantity;
        }
        else
        {
            this->cartItems.insert({product, quantity});
        }
    }

    void RemoveItem(Product *product)
    {
        this->cartItems.erase(product);
    }

    void UpdateQuantity(Product *product, int quantity)
    {
        this->cartItems[product] = quantity;
    }

    double GetTotalPrice() const
    {
        double total_price = 0;
        for (pair<Product *, int> item : this->cartItems)
        {
            total_price += item.first->GetPrice() * item.second;
        }
        return total_price;
    }

    void SetTotalPrice(double total_price)
    {
        this->total_price = total_price; // Add a total_price member variable
    }

    void Print()
    {
        cout << "Cart Items:" << endl;
        for (pair<Product *, int> item : this->cartItems)
        {
            cout << "You Have " << item.second << " " << item.first->GetName() << " In Your Cart" << endl;
        }
        cout << "Total Bill: $" << GetTotalPrice() << endl;
        cout << "Total Bill discouted : $" << total_price << endl;
        cout << endl;
    }
};