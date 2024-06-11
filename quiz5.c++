#include<iostream>
#include<vector>

using namespace std;

long long Merge(vector<int>& arr, int left, int mid, int right){
    int leftsize = mid-left+1;
    int rightsize = right - mid;
    
    vector<int> Left(leftsize);
    vector<int> Right(rightsize);
    
    //partition
    for(int i=0; i<leftsize; i++){
        Left[i] = arr[left+i];
    }
    
    for(int i=0; i<rightsize; i++){
        Right[i]=arr[right+i];
    }
    
    
    int leftcur=0;
    int rightcur=0;
    int k=left; //從left開始重貼
    int swaptime=0;
    
    //merge
    while(leftcur<leftsize && rightcur<rightsize){
        if(Left[leftcur]<= Right[rightcur]){
            arr[k]=Left[leftcur]; //將原本順序開始重貼
            leftcur++;
        }else{
            arr[k]=Right[rightcur];
            rightcur++;
            swaptime=swaptime+(leftsize-leftcur);
            
        }
        k++;
    }
    
    
    while(leftcur < leftsize){
        arr[k]=Left[leftcur]; //將原本順序開始重貼
        leftcur++;
    }
    while(rightcur < rightsize){
        arr[k]=Right[rightcur];
        rightcur++;
    }
    
    return swaptime;
}

long long MergeSort(vector<int>& arr, int left, int right){
    long long swaptime=0;
    if(left < right){
        int mid = left +(right-left)/2;
        
        swaptime = swaptime + MergeSort(arr, left, mid);
        swaptime = swaptime + MergeSort(arr, mid+1, right);
        swaptime = swaptime + Merge(arr, left, mid, right);
    }
    
    return swaptime;
}

int main(){
    long long n;
    cin >> n;
    vector<int> list(n);
    
    for(int i=0; i<n; i++){
        cin >> list[i];
    }
    
    long long ans = MergeSort(list, 0, n-1);
    cout << ans << endl;
}




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
