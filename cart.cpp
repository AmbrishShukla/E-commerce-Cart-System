// Cart Class
class Cart
{
public:
    Cart() {}

    // add item
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

    //  add item to cart with specified quantity
    void AddItem(Product *product, int quantity)
    {
        // using try catch block to handle the edge cases when the quantity is less than 0
        try
        {
            if (quantity <= 0)
            {
                throw std::invalid_argument("Quantity cannot be negative or zero");
            }

            if (product->IsAvailable() == false)
            {
                throw std::invalid_argument("Product not available");
            }

            if (this->cartItems.find(product) != this->cartItems.end())
            {
                this->cartItems[product] += quantity;
            }
            else
            {
                this->cartItems.insert({product, quantity});
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }

    void RemoveItem(Product *product)
    {
        // to handle the case when the product to remove is not present in the cart
        try
        {
            auto it = cartItems.find(product);
            if (it != cartItems.end())
            {
                cout << product->GetName() << " is removed from the cart " << endl;
                cartItems.erase(it); // Product found, remove it
            }
            else
            {
                throw std::runtime_error("Product not found in the cart.");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }

    void UpdateQuantity(Product *product, int quantity)
    {
        // edge case : when quantity < 0  || product not in cart
        try
        {
            if (quantity <= 0)
            {
                throw std::invalid_argument("Quantity cannot be negative or zero.");
            }

            auto it = cartItems.find(product);
            if (it != cartItems.end())
            {
                cout << "The quantity of " << product->GetName() << " is updated to " << quantity << endl;
                it->second = quantity; // Update the quantity for the product
            }
            else
            {
                throw std::runtime_error("Product not found in the cart.");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
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
            cout << "You Have " << item.second << " " << item.first->GetName() << " In Your Cart "
                 << "each cost $" << item.first->GetPrice() << endl;
        }
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Total Bill                  --> $" << GetTotalPrice() << endl;
        if (total_price > 0)
        {
            cout << "-------------------------------------------------------------------" << endl;
            cout << "Total Bill after discount's --> $" << total_price << endl;
        }
        cout << "-------------------------------------------------------------------" << endl;
        cout << endl;
    }

public:
    map<Product *, int> cartItems;
    double total_price = 0; // Add a total_price member variable
};