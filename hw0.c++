////////////////////////////////////////////////////////////////////////////////////////////
//5/10
#include<iostream>
#include<algorithm>

using namespace std;

struct treasure{
    int V;
    int W;
    double D;
};              // 需要分號

bool cmp1 (treasure i, treasure j){ //需要在treasure 後面
    if(i.D==j.D){
        return (i.V > j.V);
    }
    return (i.D > j.D);
};

bool cmp2 (treasure i, treasure j){ //需要在treasure 後面
    if(i.V==j.V){
        return (i.W < j.W);
    }
    return (i.V > j.V);
};


int main(){
    int N, K;
    treasure t[100];
    treasure t1[100]; //density decending
    treasure t2[100]; //value decending
    treasure record1;
    record1.V=0;
    record1.W=0;
    treasure record2;
    record2.V=0;
    record2.W=0;
    
    cin >> N >> K;
  
    int temp = 0;
    while(temp < N){
        cin >> t[temp].V >> t[temp].W;
        t[temp].D = t[temp].V/t[temp].W;
        t1[temp]=t[temp];
        t2[temp]=t[temp];
        temp++;
    }
    
    sort(t1, t1+N, cmp1);
    sort(t2, t2+N, cmp2);
    
    //test
    //for(int i=0; i<N; i++){
    //    cout << t[i].V << " " << t[i].W << endl;
    //}
    
    for(int i=0; i<N; i++){
            if(record1.W+t1[i].W <= K){
                record1.V = record1.V+t1[i].V;
                record1.W = record1.W+t1[i].W;
            }
    }
    
    for(int i=0; i<N; i++){
            if(record2.W+t2[i].W <= K){
                record2.V = record2.V+t2[i].V;
                record2.W = record2.W+t2[i].W;
            }
    }
   
    
    if(record1.V > record2.V){
        cout << record1.V << endl;
    }
    else{
        cout << record2.V << endl;
    }
    
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
//4/10
#include<iostream>
#include<algorithm>

using namespace std;

struct treasure{
    int V;
    int W;
};              // 需要分號

bool cmp2 (treasure i, treasure j){ //需要在treasure 後面
    if(i.V==j.V){
        return (i.W < j.W);
    }
    return (i.V > j.V);
};


int main(){
    int N, K;
    treasure t[100];
    treasure record;
    record.V=0;
    record.W=0;
    int ans=0;
    
    cin >> N >> K;
  
    int temp = 0;
    while(temp < N){
        cin >> t[temp].V >> t[temp].W;
        temp++;
    }
  
    sort(t, t+N, cmp2);
    
    //test
    //for(int i=0; i<N; i++){
    //    cout << t[i].V << " " << t[i].W << endl;
    //}
    
    for(int a=0; a<N; a++){
        record.V =0;
        record.W =0;
        for(int i=a; i<N; i++){
            if(record.W+t[i].W <= K){
                record.V = record.V+t[i].V;
                record.W = record.W+t[i].W;
            }
            if(i==N-1){
                if(ans < record.V){
                    //cout << record.V << " " << record.W << endl;
                    ans = record.V;
                }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}






//複數次sort: https://hackmd.io/@sa072686/cp/%2F%40sa072686%2FB1Zg7tI5U
/*
Steal the most value
------------------
Description
You are a theif sneaking into a house that contains N items. You carry a bag and want to steal some valuable items from the house. 
Unfortunately, your bag can hold at most K kilograms. As a smart theif, you know exactly the value Vi and the weight Wi of each item.
Since your bag is not strong enough to carry over the limit of K (the sum of weight Wi you carry must be less then K).
What is the highest value you can carry out from this house?

Input
The first line contains two integers N and K, representing the number of items in the house and how much can the bag hold.
Each of the following N lines contain two integers Vi and Wi, describing the value and weight of the i-th item.

It is guaranteed that :
0≤ Vi, Wi ≤103
For test case #1~9: 1≤N≤20, 0≤K≤103
For test case #10: 1≤N≤100, 0≤K≤103

Output
Print the most value the thief can get.
(you need to print a newline '\n' right following your answer)
For the sample test case, we can choose the third item (6,3) and the fifth (5,4) item. The maximum value the thief can get would be 11.
*/



//複數次sort: https://hackmd.io/@sa072686/cp/%2F%40sa072686%2FB1Zg7tI5U
/*
Steal the most value
------------------
Description
You are a theif sneaking into a house that contains N items. You carry a bag and want to steal some valuable items from the house. 
Unfortunately, your bag can hold at most K kilograms. As a smart theif, you know exactly the value Vi and the weight Wi of each item.
Since your bag is not strong enough to carry over the limit of K (the sum of weight Wi you carry must be less then K).
What is the highest value you can carry out from this house?

Input
The first line contains two integers N and K, representing the number of items in the house and how much can the bag hold.
Each of the following N lines contain two integers Vi and Wi, describing the value and weight of the i-th item.

It is guaranteed that :
0≤ Vi, Wi ≤103
For test case #1~9: 1≤N≤20, 0≤K≤103
For test case #10: 1≤N≤100, 0≤K≤103

Output
Print the most value the thief can get.
(you need to print a newline '\n' right following your answer)
For the sample test case, we can choose the third item (6,3) and the fifth (5,4) item. The maximum value the thief can get would be 11.
*/
