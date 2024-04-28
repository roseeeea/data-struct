#include<iostream>
#include<vector>
#include<algorithm>
#include<functional> //包含greater() ～升冪; less() ~降冪
using namespace std;

bool cmp(int a, int b){
  return a>b; //由大到小 
  //還可以根據第二特徵進行排序
}


int main(){
  sort(a.begin(), a.end(), cmp); //a是位子
  reverse();
  distance(a.begin(), it); //返回int 兩個pointer 距離
  reverse(v.begin() + 1, v.begin() + 4);//partial reverse 也看以整個reverse

  
  //heap
  vector<int> heap; //需要是vector
  make_heap(heap.begin(), heap.end()); //maxheap，將vector排序成heap O(n)
  make_heap(heap.begin(), heap.end(), greater()); //以下操作，如果是mini heap 都要加greater函式

  heap.push_back(20); //vector放入
  push_heap(heap.begin(), heap.end()); //重新排列

  //if insert 
  heap.insert(heap.begin()+5, 10);
  make_heap(heap.begin(), heap.end());

  pop_heap(heap.begin(), heap.end()); //pop~將root放到尾巴
  heap.pop_back();
  
  
  

  
  return 0;
}
