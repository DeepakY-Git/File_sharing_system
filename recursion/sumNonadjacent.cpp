#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

void maxSum(vector<int>& arr, int sum, int i, int& maxi){
    // Base case
    if(i >= arr.size()){
        maxi = max(maxi, sum); //maxi update
        return;
    }

    // exclude
    maxSum(arr, sum, i+1, maxi);

    //incldue
    maxSum(arr, sum + arr[i] ,i+2, maxi);
    
}

int main(){
    
    vector<int> arr{2, 1, 4, 9};

    int sum = 0;
    int i = 0;
    int maxi = INT_MIN;

    maxSum(arr, sum, i, maxi);
    cout << "Maximum Sum of the subsequence : "<<maxi<<endl;

    return 0;
}