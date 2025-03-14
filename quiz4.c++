#include<iostream>
#include<vector>
using namespace std;

const long long None = 99999999999;
const int Size = 100000;

class Point{
public:
    int id;
    Point * parent;
    vector<pair<Point*, long long>> children;
    
    Point(int id): id(id){};
};

vector<Point*> points;
long long DistfromA[Size];
long long DistfromB[Size];

void FindDistA(int id){
    
    long long childsize = points[id]->children.size();
    
    for(int i=0; i<childsize; i++){
        
        int tempid = points[id]->children[i].first->id;
        
        if(DistfromA[tempid] > DistfromA[id] + points[id]->children[i].second){
            DistfromA[tempid] = DistfromA[id] + points[id]->children[i].second;
            FindDistA(tempid);
        }
    }
}

void FindDistB(int id){
    long long childsize = points[id]->children.size();
    
    for(int i=0; i<childsize; i++){
        
        int tempid = points[id]->children[i].first->id;
        
        if(DistfromB[tempid] > DistfromB[id] + points[id]->children[i].second){
            DistfromB[tempid] = DistfromB[id] + points[id]->children[i].second;
            FindDistB(tempid);
        }
    }
    
}

int main(){
    int n, m;
    cin >> n >> m;
    
    for (int i=0; i<n; i++){
        Point* newPoint = new Point(i);
        points.push_back(newPoint);
        DistfromA[i]=None;
        DistfromB[i]=None;
    }
    
    for(int i=0; i<m; i++){
        int parent, child, dist;
        cin >> parent >> child >> dist;
        points[parent]->children.push_back({points[child], dist});
    }
    
    int type;
    cin >> type;
    
    if(type == 1){
        int A, center;
        cin >> A >> center;
        
        DistfromA[A]=0;
        FindDistA(A);
        
        if(DistfromA[center]==None){
            cout << "-1" << endl;
        }else{
            cout << DistfromA[center] << endl;
        }
        
        
    }else if(type == 2){
        int A, B, center;
        cin >> A >> B >> center;
        
        DistfromA[A]=0;
        FindDistA(A);
        
        DistfromB[B]=0;
        FindDistB(B);
        
        if(DistfromA[center]==None || DistfromB[center]==None){
            cout << "-1" << endl;
        }else{
            long long ans1 =DistfromA[center] + DistfromB[center];
            long long ans2 = DistfromA[B] + DistfromB[center];
            long long ans3 =DistfromB[A] + DistfromA[center];
            
            long long ans = min(ans1, ans2);
            ans = min(ans, ans3);
            
            cout << ans << endl;
        }
        
    }
    
    
    
    
    
    return 0;
}



/////////////////////old
#include<iostream>
#include<vector>
#include<queue>
#include<list>
using namespace std;

long long vertex; //n
long long edge; //m
long long travtime[10000][10000];
vector<long long> path[10000];


long long A;
long long B;
long long dest;
long long distfromA[10000];
long long distfromB[10000];
int ifAB[10000]={0};


long long findpathA(){
    for(long long i=0; i<10000; i++){
        distfromA[i]=10000;
    }
    distfromA[A]=0;
    
    queue<long long> visit;
    long long check[10000]={0};
    visit.push(A);
    
    int k=0;
    while(visit.empty()!=1){
        
        //cout << "in while " << k << endl;
        long long cur = visit.front();
        
        int flag=0;
        while(check[cur]==1){
            visit.pop();
            if(visit.empty()!=1){
                cur=visit.front();
            }
            else{
                flag=1;
                break;
            }
        }
        
        if(flag==1){
            break;
        }
        
        check[cur]=1;
        //cout << "cur " << cur << endl;
        //cout << "A" << A << endl;
        //cout << "distfromA[A]" << distfromA[A] << endl;
        
        for(auto i=path[cur].begin(); i!=path[cur].end(); i++){
            //cout <<"*i " <<*i << endl;
            if(*i != A){
                visit.push(*i);
                
                //cout << "cur2 " << cur << endl;
                
                //cout << "distfromA[*i]" << distfromA[*i] << endl;
                //cout << "distfromA[cur]" << distfromA[cur] << endl;
                //cout << "travtime[cur][*i]" << travtime[cur][*i] << endl;
                
                
                if(distfromA[*i] > distfromA[cur]+travtime[cur][*i]){
                    distfromA[*i] = distfromA[cur]+travtime[cur][*i];
                }
                
            }
        }
        k++;
        visit.pop();
    }
    
    if(distfromA[dest]!=10000){
        return distfromA[dest];
    }else{
        return -1;
    }
    

}


long long findpathB(){
    for(long long i=0; i<10000; i++){
        distfromB[i]=10000;
    }
    distfromB[B]=0;
    
    
    
    queue<long long> visit;
    int check[10000]={0};
    visit.push(B);
    
    
    while(visit.empty()!=1){
        //cout << "in while" << endl;
        long long cur = visit.front();
        
        int flag=0;
        while(check[cur]==1){
            visit.pop();
            if(visit.empty()!=1){
                cur=visit.front();
            }
            else{
                flag=1;
                break;
            }
        }
        
        if(flag==1){
            break;
        }
        
        check[cur]=1;
        //cout << "cur" << cur << endl;
        
        for(auto i=path[cur].begin(); i!=path[cur].end(); i++){
            if(*i != B){
                visit.push(*i);
                if(distfromB[*i] > distfromB[cur]+travtime[cur][*i]){
                    distfromB[*i] = distfromB[cur]+travtime[cur][*i];
                }
                
            }
        }
        
        visit.pop();
    }
    
    if(distfromB[dest]!=10000){
        return distfromB[dest];
    }else{
        return -1;
    }
    

}


int main(){
    for(long long i=0; i<10000; i++){
        distfromA[i]=10000;
        distfromB[i]=10000;
    }
    
    
    
    cin >> vertex >> edge;
    
    for(long long i=0; i<edge; i++){
        long long from;
        long long to;
        long long ti;
        cin >> from >> to >> ti;
        travtime[from][to]=ti;
        path[from].push_back(to);
    }
    
    int choice;
    
    cin >> choice;
    
    
    
    if(choice==1){
        distfromA[A]=0;
        
        cin >> A;
        cin >> dest;
        long long ans=findpathA();
        
        if(ans==10000){ ans=-1;}
        cout << ans << endl;
    }
    else if(choice==2){
        distfromA[A]=0;
        distfromB[B]=0;
        
        cin >> A;
        cin >> B;
        cin >> dest;
        
        long long ans1=findpathA();
        long long ans2=findpathB();
        
        //cout << ans1 << " " << ans2 << endl;
        
        long long ans;
        if((ans1==-1) || (ans1==10000)){ ans=-1;}
        else if((ans2==-1) || (ans2==10000)){ ans=-1;}
        else{
            ans=ans1+ans2;}
        
        
        cout << ans << endl;
        
    }
    
    
    
    
    
    return 0;
}
