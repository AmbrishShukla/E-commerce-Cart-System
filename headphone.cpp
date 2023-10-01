// headphones class
class Headphone : public Product
{
public:
    Headphone(string name, double price, bool availability_status, string type, string brand)
        : Product(name, price, availability_status)
    {
        this->type = type;
        this->brand = brand;
    }

    string GetType() { return this->type; }
    string GetBrand() { return this->brand; }

private:
    string type;
    string brand;
};