#include<vector>
#include<iostream>
#include<list>
#include<queue>
using namespace std;

const int NV = -1000001;
const int NP = -2;

int rootip=-1;
int parentip[500000]={NP}; //[ip] parent=-1~ root
int value[500000]={NV};
list<int> chlip[500000];
list<int> existip;
long long maxmap[500000];



void setNode(int par, int ip, int val){
    parentip[ip]=par;
    value[ip]=val;
    chlip[par].push_back(ip);
    
    existip.push_back(ip);

}


void Delete(int ip){
    
    //for ip that not exist
    if(value[ip]==NV) return;
    
    value[ip]=NV;
    int par = parentip[ip];
    chlip[par].remove(ip);
    
    
    if(chlip[ip].empty()!=1){
        for(auto i=chlip[ip].begin(); i!=chlip[ip].end(); i++){
            int child= *i;
            parentip[child]=par;
            chlip[par].push_back(child);
        }
        
    }
    
    chlip[ip].clear();
    
    parentip[ip]=NP;
    existip.remove(ip);
}


void Print(){
    queue<int> q;
    q.push(rootip);
    
    while(1){
        int curip=q.front();
        
        for(auto i=chlip[curip].begin(); i!=chlip[curip].end(); i++){
            q.push(*i);
        }
        

        cout << "par=" << parentip[curip] << " ip= " << curip <<" val= "<< value[curip] << endl;
        q.pop();
        if(q.empty()) break;
        
    }
    
}

long long FindSum(int curip){

    if(chlip[curip].empty()){
        maxmap[curip]=value[curip];
        return value[curip];
    }
    
    long long max1=0;
    long long max2=0;
    
    
    for(auto i=chlip[curip].begin(); i!=chlip[curip].end(); i++){
            
        long long childmax=FindSum(*i);
        if(max1<=childmax){
            max2=max1;
            max1=childmax;
        }
            
    }
   
    maxmap[curip]=value[curip]+max1+max2;
    return max1+value[curip]; //return 單向
    
}


vector<long long> Check() {
    vector<long long> a;
    long long Max=NV;
    int Maxip=NP;
    
    FindSum(rootip);
    
    for(auto i=existip.begin(); i!=existip.end(); i++){
        if(Max < maxmap[*i]){
            Max=maxmap[*i];
            Maxip=*i;
        }
    }
    
    a.push_back(Max);
    a.push_back(Maxip);
    
    return a;
}



int main(){
    int N; //the size of the tree = N+1
    int action;
    
    cin >> N >> action;
    
    //set root
    cin >> rootip;
    cin >> value[rootip];
    parentip[rootip]=-1;
    
    int n=0;
    while(n<N){
        int par;
        int ip;
        int val;
        
        cin >> par >> ip >> val;
        setNode(par, ip, val);
        
        n++;
    }
    
    int cur=0;
    while(cur < action){
        string state;
        cin >> state;
        if(state == "Add"){
            int par;
            int ip;
            int val;
            
            cin >> par >> ip >> val;
            setNode(par, ip, val);
            
            
        }else if(state == "Delete"){
            int ip;
            cin >> ip;
            Delete(ip);
        }
        else if(state == "Check"){
            vector<long long> ans2 = Check();
            cout << "Maximum Value: " << ans2[0] << endl;
            cout << "Root of the Path: " << ans2[1] << endl;
        }
        else if(state == "Print"){ //for testing
            Print();
        }
        
        cur++;
    }
    
    vector<long long> ans2 = Check();
    
    cout << "Final Root: " << ans2[1] << endl;
    
    
    
    return 0;
}

/*
 class Node;
 class Tree;

 class Node{
 public:
     int lev;
     int ip;
     int val;
     Node* parent;
     vector<Node*> children;
     
     
     Node(Node* parent, int ip, int val):
     parent(parent), ip(ip), val(val), lev(parent->lev+1){}
     
     friend Tree;
     
 };

 class Tree{
 private:
     Node* root;
     int size;
 public:
     Tree():root(nullptr){};
 };
 
 
 //int lev[10001]={-1}; //-1~the node do not exist; 0~the node is root
 //insert 不規律～要找lev要loop


 
 */

/*
4 10
0 -30
0 1 7
2 3 2
2 4 13
0 2 19
Check
Add 0 5 10
Delete 2
 
Maximum Value: 34
Root of the Path: 2
Final Root: 4
 */
