#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
using namespace std;

vector< queue<char> > map;
list<char> bag;
stack<char> inv;
int R; //col
int L; //row
int N; //action
int coin=0;
int pastp=-1;
int flag=1;
int depth[100]={0};


void PrintMap(){
    cout << "Map:" << endl;
    for(int i=0; i<L; ++i){
        for(int k=0; k<depth[i]; k++){
            cout << "_ ";
        }
        while(map[i].empty() != 1){
            cout << map[i].front() << " ";
            map[i].pop();
        }
        cout << endl;
    }
}



void PrintBag(){
    cout << "Backpack:";
    int size = bag.size();
    for(auto i=0; i<size; ++i){
        char c = bag.front();
        bag.pop_front();
        cout << " " << c ;
    }
    cout << endl;
}

void PrintInv(){
    cout << "Inventory:";
    int size=inv.size();
    for(int i=0; i<size; i++){
        char top=inv.top();
        cout << " " << top ;
        inv.pop();
    }
    cout << endl;
    
}


void Pig(){
    bag.remove('G');
}



void Dig(int row){
    char p = map[row].front();
    //cout << "test front " << p << endl;
    pastp=row;
    
    if(map[row].empty()){
        return;
    }
    
    depth[row]++;
    map[row].pop();
    
    if(p =='D' || p=='G'){
        bag.push_back(p);
    }
    else if(p == 'S' || p=='X'){
        inv.push(p);
    }
    else if(p == 'C'){
        coin = 1;
    }
    else if(p == 'P'){
        if(coin == 1){
            cout << "Ding!" << endl;
            coin=coin-1;
            return;
        }
        else{
            Pig();
        }
    }
    else if(p == 'V'){
        cout << "Game Over!" << endl;
        flag=0;
        return;
    }
    else{
        return;
    }
}


void Shovel(){
    if(pastp != -1){
        Dig(pastp);
        Dig(pastp);
    }
    else{
        return;
    }
}

void SButton(){
    R++;
    for(int i=0; i < L; i++){
        if(i%2==0){
            map[i].push('D');
        }
        else{
            map[i].push('G');
            
        }
    }
}



void Use(){
    char item = inv.top();
    inv.pop();
    if(item == 'S'){
        Shovel();
    }
    else{
        SButton();
    }
    
}





int main(){
    cin >> R >> L >> N;
    
    int r=0;
    while(r < L){
        queue<char> temp;
        for(int i=0; i<R; i++){
            char c;
            cin >> c;
            temp.push(c);
        }
        map.push_back(temp);
        
        r++;
    }
    
    int time=0;
    while(time<N && flag==1){
        string action;
        cin >> action;
        if(action == "DIG"){
            int row;
            cin >> row;
            //cout << row << endl;
            
            if(row < L){
                Dig(row);
            }
            
        }
        else if(action == "USE"){
            Use();
        }
        
        //cout << "time" << time << endl;
        time++;
    }
    
    //cout << 'e' << endl;
    
    PrintBag();
    PrintInv();
    PrintMap();
    
    
    
    return 0;
}
