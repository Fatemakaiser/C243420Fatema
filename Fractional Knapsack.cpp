#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    string id;
    double weight;
    double value;
    double ratio;
};

bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

void fractionalKnapsack(double capacity, vector<Item>& items) {
    
    for (auto &item : items) {
        item.ratio = item.value / item.weight;
    }

    sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    cout << fixed << setprecision(2);
    cout << "\nItems taken: "<< endl;

    for (auto &item : items) {
        if (capacity == 0) break;

        if (item.weight <= capacity) {
            capacity -= item.weight;
            totalValue += item.value;
            cout << item.id << " (Full) - Value: " << item.value << endl;
        } else {
            double fraction = capacity / item.weight;
            totalValue += (item.value * fraction);
            cout << item.id << " (Fraction: " << fraction 
                 << ") - Value: " << item.value * fraction << endl;
            capacity = 0;
        }
    }

    cout << "Maximum Profit: " << totalValue << endl;
}

int main() {
    int n;
    double maxCapacity;

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> maxCapacity;

    vector<Item> items(n);

    cout << "Enter item ID, weight, and value:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].id >> items[i].weight >> items[i].value;
    }

    fractionalKnapsack(maxCapacity, items);

    return 0;
}