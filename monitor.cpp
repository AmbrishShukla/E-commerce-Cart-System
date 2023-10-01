// monitor class
class Monitor : public Product
{
public:
    Monitor(string name, double price, bool availability_status, int size, string resolution)
        : Product(name, price, availability_status)
    {
        this->size = size;
        this->resolution = resolution;
    }

    int GetSize() { return this->size; }
    string GetResolution() { return this->resolution; }

private:
    int size;
    string resolution;
};