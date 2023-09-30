
class PercentageDiscountStrategy : public DiscountStrategy
{
public:
    PercentageDiscountStrategy(double percentage)
    {
        this->percentage = percentage;
    }

    double GetDiscountAmount(const Cart *cart) override
    {
        return cart->GetTotalPrice() * (this->percentage / 100);
    }

private:
    double percentage;
};