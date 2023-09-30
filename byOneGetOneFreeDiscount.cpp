class BuyOneGetOneFreeDiscountStrategy : public DiscountStrategy
{
public:
    double GetDiscountAmount(const Cart *cart) override
    {
        double discount_amount = 0;
        for (pair<Product *, int> item : cart->cartItems)
        {
            if (item.second >= 2)
            {
                // Calculate the number of products eligible for the discount
                int eligible_count = item.second / 2;
                // Subtract the price of every second product
                discount_amount += item.first->GetPrice() * eligible_count;
            }
        }
        return discount_amount;
    }
};