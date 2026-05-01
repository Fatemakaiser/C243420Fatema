#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    double value, weight;
};

bool compare(Item a, Item b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2;
}

int main() {
    int n;
    double W;
    cin >> n >> W;

    Item items[100];

    for(int i=0;i<n;i++)
        cin >> items[i].value >> items[i].weight;

    sort(items, items+n, compare);

    double totalValue = 0.0;

    for(int i=0;i<n;i++){
        if(items[i].weight <= W){
            W -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * (W / items[i].weight);
            break; // Knapsack full
        }
    }

    cout << "Maximum value: " << totalValue;
}
