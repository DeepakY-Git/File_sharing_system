#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// pair<int, int> findArray(int arr[], int n, int i, int maxi, int mini) {
//     if (i >= n) {
//         return {maxi, mini}; // Return a pair of maximum and minimum values.
//     }
    
//     maxi = max(maxi, arr[i]);
//     mini = min(mini, arr[i]);
//     return findArray(arr, n, i + 1, maxi, mini); // Recursive call.
// }

void findArray(int arr[], int n, int i, int &maxi, int &mini) {
    if (i >= n) {
        return; // Base case.
    }
    
    maxi = max(maxi, arr[i]);
    mini = min(mini, arr[i]);
    findArray(arr, n, i + 1, maxi, mini); // Recursive call.
}


int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int n = 5;
    int i = 0;
    int maxi = INT_MIN;
    int mini = INT_MAX;
    
    findArray(arr, n, 0, maxi, mini);
    // pair<int, int> ans = findArray(arr, n, i, maxi, mini);
    cout << "Maximum value in array is: " << maxi << endl;
    cout << "Minimum value in array is: " << mini << endl;

    return 0;
}
