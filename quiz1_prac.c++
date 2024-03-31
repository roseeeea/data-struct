#include<iostream>
#include<vector>
#include<algorithm> //reverse 出處
//#include<cstring> //strlen 出處
using namespace std;

vector< vector<char> > matrix;  //matrix[row][col]
int mcol=0;
//int mrow=0;
//int flag=1;



void Print(){
    //cout << "6" << endl;
    for(const auto& row : matrix){ //直接調用matrix （不複製），避免對直接調動運算->const
        for(char c:row){ //c是row的每個元素
            cout << c << " ";
        }
        cout << endl;
    }
}



void Insert(){
    //cout << "2" << endl;
    vector<char> row;
    char c;
    
    while(cin.get(c)){ //不能用cin
        if(c == '\n'){ //不能雙點
            break;
        }
        
        if(c != ' '){ //空格不讀
            row.push_back(c);
            //cout << "3" << endl;
        }
    }
    //cout << "4" << endl;
    
    matrix.push_back(row); //binding放入
    //cout << "5" << endl;
    
    //test
    //Print();
    //cout << "7" << endl;
    
    
}


void Shift(int index, char c){ //index==row
    matrix[index].erase(matrix[index].begin());
    matrix[index].push_back(c);
}



void Reverse(int index){
    reverse(matrix[index].begin(), matrix[index].end());
}


void Transpose(){
    int col=matrix[0].size();
    int row=matrix.size();
    for(int i=0; i<col; ++i){
        for(int j=0; j<row; j++){
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }
}







int main(){
    string action;
    
    int flag=1;
    while(flag==1){
        cin >> action;
        
        if(action == "Insert"){
            //cout << "1" << endl;
            Insert();
        }
        else if(action == "Print"){
            Print();
            flag=0;
        }
        else if(action == "Shift"){
            int index;
            char c;
            cin >> index >> c;
            Shift(index, c);
        }
        else if(action == "Transpose"){
            Transpose();
            flag=0;
        }
        else if(action == "Reverse"){
            int index;
            cin >> index;
            Reverse(index);
            
        }
    
    }
            
    return 0;
}

/*
 1.列印的其他方法(但需要知道i j )
 for (size_t i = 0; i < matrix.size(); ++i) {
 for (size_t j = 0; j < matrix[i].size(); ++j) {
     std::cout << matrix[i][j] << " ";
 }
 std::cout << std::endl;
}
 2. 這樣輸入會讀取空格
 // getline(cin, temp)
 //for(char c : temp){ //c為字元，以temp字串分解 ！！！會讀到空格
 //    row.push_back(c);
 //}
 
 3. cin.get() 一個個字符讀
 
 
 
 
 */
