//for stack queue list
#include<iostream>
#include<stack>
#include<queue>
#include<list>
#include<any> //允許不同型態的融合 ex:多型態stack
using namespace std;


int main(){
    //stack---------------------------------------------------------------------------------
    stack<int> s; //不能直接允值
    s.push(3); //put sth in the stack
    s.pop(); //pop the top and NO return value
    s.empty(); //if empty-> return 1
    int size_s=s.size(); //return the size of the stack
    int top =s.top(); //return(report) the top value (but the stack order do not change)
    
    
    
    //queue---------------------------------------------------------------------------------
    queue<string> q;
    q.push("HI"); //put sth in the queue
    q.pop(); //pop the "front"(old) and NO return value
    q.empty(); //if empty -> return 1
    int size_q = q.size();
    string front = q.front(); //report front(the old one)
    string back = q.back(); //report back(the new one)
    

    
    //list---------------------------------------------------------------------------------
    list<double> l ={0.1, 0.9, 0.7};
    l.push_front(0.3); //put sth from the front
    l.push_back(0.5); //put sth from the back
    l.empty(); //if empty -> return 1
    int size_l = l.size();
    double front_l = l.front();
    double back_l = l.back();
    cout << front_l << " " << back_l << endl;
    
    //目前 0.3 0.1 0.9 0.7 0.5
    
    //下列功能輸入值可以想成「位子」（auto t）
    auto it_1 = next(l.begin(), 2); // 获取 it 位置(迭代器)，指向第三个元素(0.9)
    l.insert(it_1, 0.5); //在it 「之前」 插入值=0.5
    //0.3 0.1 "0.5" 0.9 0.7 0.5
    l.insert(it_1, 3, 0.8); //在it(第四位：0.9) 「之前」 插入 3個 值=0.8
    //0.3 0.1 0.5 "0.8 0.8 0.8" 0.9 0.7 0.5
    
    //erase
    auto it_2 = next(l.begin(), 3); //erase 第四個位置(0.8)
    l.erase(it_2); //erase 單個
    
    auto first = l.begin();
    auto last = next(l.begin(), 5);
    l.erase(first, last); //[1, 6) 不包含尾
    
    l.remove(0.5); //remove所有0.5的值
    
    //列印值
    for (auto i = l.begin(); i != l.end(); ++i) { //位置(i)無大小 不能用 > <
        cout << *i << " "; //取位置(i)的值
    }


    l.sort();     // 使用默認排序（升序）
    l.sort([](int a, int b) { return a > b; }); //降序

    //多型態--------------------------------------------------------------------
    stack<any> s2; //不能直接允值
    s2.push("hi");
    s2.push(3);
    int size_s2=s2.size();
    any top_s2 = s2.top();
    cout << size_s2 << endl;
    //cout << top_s2 << endl; 不能直接輸出any，要用top_s2.type() == typeid(int) 判斷式判斷
    //在轉換形態輸出： any_cast<int>(top_s2)
    //if(top_s2.type() == typeid(int))
    cout << any_cast<int>(top_s2)<<endl;
    
    
    return 0;
}
