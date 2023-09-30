
// Product Class
class Product
{
public:
    Product(string name, double price, bool availability_status)
    {
        this->name = name;
        this->price = price;
        this->availability_status = availability_status;
    }

    string GetName() { return this->name; }
    double GetPrice() { return this->price; }
    bool IsAvailable() { return this->availability_status; }

private:
    string name;
    double price;
    bool availability_status;
};