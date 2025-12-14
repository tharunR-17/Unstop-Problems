#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void process_food_preferences(const string &menu) {
    if (menu.empty()) {
        cout << "EMPTY";
        return;
    }

    vector<int> dish_count(26, 0);
    for (char c : menu) {
        dish_count[c - 'a']++;
    }

    vector<pair<char, int>> vegetarian_dishes;
    vector<pair<char, int>> non_vegetarian_dishes;
    string vowels = "aeiou";

    for (int i = 0; i < 26; i++) {
        if (dish_count[i] > 0) {
            char dish = 'a' + i;
            if (vowels.find(dish) != string::npos) {
                vegetarian_dishes.push_back({dish, dish_count[i]});
            } else {
                non_vegetarian_dishes.push_back({dish, dish_count[i]});
            }
        }
    }

    sort(vegetarian_dishes.begin(), vegetarian_dishes.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        if (a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    });

    sort(non_vegetarian_dishes.begin(), non_vegetarian_dishes.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        if (a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    });

    string result;
    for (const auto &dish : vegetarian_dishes) {
        result += dish.first;
        result += to_string(dish.second);
    }
    for (const auto &dish : non_vegetarian_dishes) {
        result += dish.first;
        result += to_string(dish.second);
    }

    cout << (result.empty() ? "EMPTY" : result);
}

int main() {
    string menu;
    getline(cin, menu);

    process_food_preferences(menu);
    return 0;
}
