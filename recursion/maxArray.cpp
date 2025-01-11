#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

int maxArray(int arr[], int n, int i, int maxi){
    if(i>=n){
        return maxi;
    }
    
    maxi = max(maxi, arr[i]);
    
    // cout << arr[i]<< " ";
    return maxArray(arr, n, i+1, maxi);
    

}

int main(){
    
    int arr[5] = {10, 20, 30, 40 ,50};
    int n =5;
    int i = 0;
    int maxi = INT_MIN;
    int ans = maxArray(arr, n, i, maxi);
    cout << "Maximum value in array is : "<<ans<<endl;
    


    return 0;
}