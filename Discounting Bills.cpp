#include<bits/stdc++.h>
#define ll long long int 

using namespace std;

class Cashier {
public:
    Cashier(ll n, ll discount, vector<ll>& products, vector<ll>& prices) {
        this->n = n;
        this->discount = discount;
        this->productPrices = unordered_map<ll, ll>();
        for (ll i = 0; i < products.size(); ++i) {
            productPrices[products[i]] = prices[i];
        }
        this->customerCount = 0;
    }

    double getBill(vector<ll>& product, vector<ll>& amount) {
        double subtotal = 0;
        for (ll i = 0; i < product.size(); ++i) {
            subtotal += productPrices[product[i]] * amount[i];
        }
        customerCount++;
        if (customerCount % n == 0) {
            subtotal *= (100 - discount) / 100.0;
        }
        return subtotal;
    }

private:
    ll n;
    ll discount;
    unordered_map<ll, ll> productPrices;
    ll customerCount;
};

int main() {
    ll n, discount;
    cin >> n >> discount;

    ll z;
    cin >> z;

    vector<ll> products(z);
    vector<ll> prices(z);

    for (ll i = 0; i < z; ++i) {
        cin >> products[i];
    }

    for (ll i = 0; i < z; ++i) {
        cin >> prices[i];
    }

    Cashier cashier(n, discount, products, prices);

    ll q;
    cin >> q;

    while (q--) {
        ll y;
        cin >> y;

        vector<ll> product(y);
        vector<ll> amount(y);

        for (ll i = 0; i < y; ++i) {
            cin >> product[i];
        }

        for (ll i = 0; i < y; ++i) {
            cin >> amount[i];
        }

        double bill = cashier.getBill(product, amount);
        cout << bill << endl;
    }

    return 0;
}
