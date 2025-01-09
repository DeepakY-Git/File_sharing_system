#include<iostream> 
using namespace std;

int factorial(int n){
    cout<<"The value of n is : "<<n<<endl;
    if(n==1){
        return 1;
    }
    int ans =  n*factorial(n-1);
    return ans;
}

int main(){
    int n;
    cout<<"Enter the value of n "<<endl;
    cin >> n;

    int ans = factorial(n);

    cout << "The facorial of " << n <<" is "<<ans<<endl;
}