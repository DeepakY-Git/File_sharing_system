#include<iostream> 
#include<climits>
#include<vector>
using namespace std;

int isSearching(vector<int> v, int s, int e, int key){
    //  Base Case
    //  case 1 -> Key Not Found
    if(s>e){
        return -1;
    }
    int mid = s + (e-s)/2;
    if(v[mid]==key){
        return mid;
    }
    // arr[mid] < key -> right search needed
    if(v[mid] < key){
        return isSearching(v, mid+1, e, key);
    }
    else{
        return isSearching(v, s, mid-1, key);
    }
}

int main(){
    vector<int> v{10,20,40,60,70,90,99};
    int key = 99;
    int s = 0;
    int e = v.size() - 1;
    int ans = isSearching(v, s, e, key);

    cout << "Answer is : "<<ans<<endl;

    return 0;
}