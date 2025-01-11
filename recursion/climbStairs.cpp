#include<iostream> 
using namespace std;

int climbStairs(int n){
    if(n == 0 || n == 1){ 
        // 0th stair we r already standing so it will be wrong if we return 0 bcz it means that 0th stair is not accessible which is wrong since we are already there
        return 1; 
    }
    int nth_term = climbStairs(n-1) + climbStairs(n-2); // Exponential time complexity
    return nth_term;
}

int main(){
    int n;
    cout<<"Enter the value of n "<<endl;
    cin >> n;

    int ans = climbStairs(n);
    cout <<"Ans is : "<<ans<<endl;
}