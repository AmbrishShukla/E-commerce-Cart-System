// laptop class
class Laptop : public Product
{
public:
    Laptop(string name, double price, bool availability_status, int screen_size, int ram, int storage) : Product(name, price, availability_status)
    {
        this->screen_size = screen_size;
        this->ram = ram;
        this->storage = storage;
    }

    int GetScreenSize() { return this->screen_size; }
    int GetRam() { return this->ram; }
    int GetStorage() { return this->storage; }

private:
    int screen_size;
    int ram;
    int storage;
};