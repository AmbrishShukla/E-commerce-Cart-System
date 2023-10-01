
class PercentageDiscountStrategy : public DiscountStrategy
{
public:
    PercentageDiscountStrategy(double percentage)
    {
        if (percentage < 0 || percentage > 100)
        {
            throw std::invalid_argument("Invalid discount percentage.");
        }
        this->percentage = percentage;
    }

    double GetDiscountAmount(const Cart *cart) override
    {
        return cart->GetTotalPrice() * (this->percentage / 100);
    }

private:
    double percentage;
};