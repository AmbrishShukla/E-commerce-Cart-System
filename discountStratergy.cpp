// Discount Strategy Pattern
class DiscountStrategy
{
public:
    virtual double GetDiscountAmount(const Cart *cart) = 0;
};