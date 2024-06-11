



//////////////////////////////////old
#include<iostream>
using namespace std;

int a[200001]={0};
int smaller[2000001]={0};

int main(){
    int num;
    int ans=0;
    cin >> num;
    
    int x=1;
    while(x<num+1){
        cin >> a[x];
        
        for(int i=1; i<x; i++){
            if(a[i]>a[x]){
                smaller[i]++;
                //cout << x <<" smaller " << i << ":"  << smaller[i] << endl;
            }
        }
        
        x++;
    }
    
    x=1;
    while(x<num+1){
        ans=ans+smaller[x];
        x++;
    }
    
    cout << ans << endl;
    
    return 0;
    
}
