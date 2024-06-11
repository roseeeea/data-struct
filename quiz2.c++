///網址https://acm.cs.nthu.edu.tw/problem/14294/
#include<iostream>
#include<algorithm>
#include<list>
#include<iterator>
using namespace std;

class Poke{
public:
    int id;
    int lv;
    
    Poke(): id(0), lv(0){}
    Poke(int id, int lv): id(id), lv(lv){}
};

list<Poke> a[10];

void Print(int index){
    cout << "List " << index<<endl;
    
    if(a[index].empty()){
        cout << "Empty" << endl;
        return;
    }
    
    for(auto i=a[index].begin(); i!=a[index].end(); i++){
        Poke temp=*i;
        cout << "ID: " << temp.id << " Level: " << temp.lv << endl;
    }
}



int main(){
    int n;
    cin >> n;
    
    
    int action;
    cin >> action;
    
    while(action--){
        string order;
        cin >> order;
        
        if(order=="Insert"){ //1 2 3 4 5

            int index;
            int id;
            int lv;
            cin >> index >> id >> lv;
            
            Poke temp(id, lv);
            a[index].push_back(temp);
            
            
        }else if(order=="Remove"){ //1 4 5
            int index;
            int id;
            cin >> index >> id;
            
            a[index].remove_if([id](const Poke& item){
                return item.id==id;
            });
            
            
        }else if(order=="Rotate"){ //2 4 5
            int index;
            int rotate;
            cin >> index >> rotate;
            
            for(int i=0; i<rotate; i++){
                Poke tempPoke=a[index].back();
                a[index].pop_back();
                a[index].push_front(tempPoke);
            }
            
        }else if(order=="Reorder"){ //3 4 5
            int index;
            cin >> index;
            list<Poke> odd;
            list<Poke> even;
            int evennum=0;
            int oddnum=0;
            
            int size = a[index].size();
            int k=1;
            while(k<size+1){
                Poke temp=a[index].front();
                a[index].pop_front(); //記得要pop
                
                //cout << temp.id << " " << temp.lv << endl;
                
                if(k%2==0){
                    even.push_back(temp);
                    evennum++;
                    //cout << "in even" << endl;
                }else{
                    odd.push_back(temp);
                    oddnum++;
                    //cout << "in odd" << endl;
                }
                k++;
            }
            
            //a[index].clear();
            //a[index].splice(a[index].end(), odd);
            //a[index].splice(a[index].end(), even);
            
            for(int i=0; i<oddnum; i++){
                Poke temp = odd.front();
                odd.pop_front();
                a[index].push_back(temp);
                
            }
            for(int i=0; i<evennum; i++){
                Poke temp = even.front();
                even.pop_front();
                a[index].push_back(temp);
                
            }
            
        }else if(order=="Reverse"){ //4 5
            int index;
            int start;
            int end;
            cin >> index >> start >> end;
            
            auto S=a[index].begin();
            auto E=a[index].begin();
            advance(S, start);
            advance(E, end+1);
            
            reverse(S, E);
            
        }else if(order=="MergeListsPreserveOrder"){ //5
            int aindex;
            int bindex;
            cin >> aindex >> bindex;
            
            list<Poke> temp;
            
            //int size=a[aindex].size()+a[bindex].size();
            
            while(!a[aindex].empty() && !a[bindex].empty()){ //從size改成這個，兩者都不empty，要考慮有個已經空一個沒有
                Poke x=a[aindex].front();
                Poke y=a[bindex].front();
                //cout << x.id << " " << y.id << endl;
                
                if(x.lv < y.lv){
                    //cout << "1" << endl;
                    temp.push_back(x);
                    a[aindex].pop_front();
                    
                }else if(x.lv > y.lv){
                    //cout << "2" << endl;
                    temp.push_back(y);
                    a[bindex].pop_front();
                    
                }else{
                    if(x.id < y.id){
                        //cout << "3" << endl;
                        temp.push_back(x);
                        a[aindex].pop_front();
                        
                    }else{
                        //cout << "4" << endl;
                        temp.push_back(y);
                        a[bindex].pop_front();
                    }
                }
        
            }
            
            while (!a[aindex].empty()) {
                    temp.push_back(a[aindex].front());
                    a[aindex].pop_front();
            }
            while (!a[bindex].empty()) {
                    temp.push_back(a[bindex].front());
                    a[bindex].pop_front();
            }
            
            
            
            a[aindex]=temp;
            a[bindex].clear();
            
        }else{
            for(int i=0; i<n; i++){
                Print(i);
            }
        }
        
        
    }
    
    for(int i=0; i<n; i++){
        Print(i);
    }
    

    
    return 0;
}

/*
3
16
Insert 0 1 1
Insert 0 1 1
Insert 0 1 1
Insert 1 3 2
Insert 1 2 1
Insert 1 2 2
Insert 1 1 2
Insert 2 1 1
Insert 2 1 1
Insert 1 1 1

MergeListsPreserveOrder 0 1
*/
