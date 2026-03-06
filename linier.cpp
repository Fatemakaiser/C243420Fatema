#include <iostream>
using namespace std;

int main() {
    int n , key;
    cout << "Enter number of elements: " << endl ;
    cin >> n;

    int arr[n];
    cout << "Enter elements:" << endl ;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter element to search: " << endl ;
    cin >> key;

    int position = -1;

    for(int i = 0; i < n; i++) {
        if(arr[i] == key) {
            position = i;
            break;
        }
    }

    if(position != -1)
        cout << "Element found at index " << position << endl ;
    else
        cout << "Element not found" << endl ;

    return 0;
}