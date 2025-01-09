#include<iostream> 
using namespace std;

int fibonacci(int n){
    if(n == 1){
        return 0; 
    }
    if(n == 2){
        return 1;
    }
    int nth_term = fibonacci(n-1) + fibonacci(n-2);
    return nth_term;
}

int main(){
    int n;
    cout<<"Enter the value of n "<<endl;
    cin >> n;

    int ans = fibonacci(n);
    cout <<n <<"th term of the fibonacci series is : "<<ans<<endl;
}