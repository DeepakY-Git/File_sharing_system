#include<iostream> 
using namespace std;

void printCount(int n){
    if(n == 0){
        return;
    }
    cout << n << " ";
    printCount(n-1);
}

int main(){
    int n;
    cout<<"Enter the value of n "<<endl;
    cin >> n;

    printCount(n);
}