#include<iostream>
using namespace std;

//-------------------------------------------------------------------
string map[100][100]; //(c,l)   *string array
int col_top[100]= {0};
string dig = "DIG";
string use = "USE";
string backpack[10000]={" "};
string inventory[10000]={" "};
int backpack_top = 0; //0表示沒東西
int inv_top = 0;
int inv_use=0; //quene
int R=-1; //column
int L=-1; //level


//-------------------------------------------------------------------
void Finish( int dig_position ){  //填滿（似乎可以用成函示）
    map[dig_position][col_top[dig_position]] = "_";
    col_top[dig_position]--;
}

int High_level(){
    int l=-1;
    for(int i=0; i<R; i++){
        l=max(col_top[i], l);
        //cout << l << endl;
    }
    return l+1;
}

void Col_top(){
    for(int i=0; i<R; i++){ //column
        for(int j=L-1; j>=0; j--){ //level
            if(map[i][j] != "_"){
                col_top[i] = j;
                //cout << "col_top" << i << "=" << col_top[i] << endl;
                break;
            }
            else{
                if(j==0){
                    col_top[i] = -1;
                    //cout << "col_top" << i << "=" << col_top[i] << endl;
                }
            }
        }
    }
}


//-------------------------------------------------------------------
//連鎖反應未解決
void Bomb( int x, int y){
    //cout << "Bomb" <<endl;
    //map[x][y]="-"; //已使用
    
    for(int i=max(y-1, 0); i<= min(y+1, L-1); i++){
        for(int j=max(x-1, 0); j<= min(x+1, R-1); j++){
            map[j][i] = "_";
        }
    }
    
}


void Clover(int p){
    //cout << "Clover" <<endl;
    
    //cout << p << endl;
    string t=backpack[backpack_top];
    if(t != " "){
        //確認最上層
        L=3+High_level();
        for(int i=max(p-2, 0); i<=min(p+2,R-1); i++){
            map[i][L-1] = t;
            map[i][L-2] = t;
            map[i][L-3] = t;
        }
    }
    else{
        return;
    }
}


void Pig(){
    //cout << "Pig" <<endl;
    while(backpack_top>0){
        if(backpack[backpack_top]=="G"){
            backpack[backpack_top]=" ";
            backpack_top--;
        }
        else{
            break;
        }
    }
    
    //cout << "bag top " << backpack_top << endl;
}



//-------------------------------------------------------------------
void Dig( int dig_position ){
    if(map[dig_position][col_top[dig_position]] == "G" || map[dig_position][col_top[dig_position]] == "D"){
        backpack_top++;
        backpack[backpack_top] = map[dig_position][col_top[dig_position]];
        Finish( dig_position);
        
        //cout << "backpack " << backpack_top << ": " << backpack[backpack_top] << endl;

    }
    else if(map[dig_position][col_top[dig_position]] == "B"){
        Bomb(dig_position, col_top[dig_position]);
        Col_top();
        Finish( dig_position);
    }
    else if(map[dig_position][col_top[dig_position]] == "C"){
        Finish( dig_position);
        Clover( dig_position);
        Col_top();
    }
    else if(map[dig_position][col_top[dig_position]] == "P"){
        Pig();
        Finish( dig_position);
    }
    else if(map[dig_position][col_top[dig_position]] == "M" || map[dig_position][col_top[dig_position]] == "F"){
        inv_top++;
        inventory[inv_top] = map[dig_position][col_top[dig_position]];
        Finish( dig_position);
        //cout << "inventory " << inv_top << ": " << inventory[inv_top] << endl;
    }
    else{
        return;
    }
    
     
}

//-------------------------------------------------------------------
void Flashlight(){
    int lev=High_level()-1;
    if(lev>=0){
        cout << "MINE LEVEL:" << lev+1 << endl;
        for(int i=0; i<R; i++){
            cout << map[i][lev] << " ";
        }
    }
    else{
        cout << "MINE LEVEL:1" << endl;
        for(int i=0; i<R; i++){
            cout << map[i][0] << " ";
        }
    }
    cout << endl;
};

void Magnet(){
    for(int i=0; i<R; i++){
        Dig(i);
    }
}

//-------------------------------------------------------------------
void Use(){
    if(inv_top > inv_use){
        inv_use++;
        string use = inventory[inv_use];
        inventory[inv_use] = " ";
        if(use == "F"){
            Flashlight();
        }
        else{
            Magnet();
        }
    }
    else{
        return;
    }
}
//-------------------------------------------------------------------

int main(){
    
    //initialize map
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            map[i][j]="_";
        }
    }
    
    
    int N; //action
    
    cin >> R >> L >> N;
    
    //filling map
    for(int i=L-1; i>=0; i--){
        for(int j=0; j<R; j++){
            cin >> map[j][i];
            
        }
    }
    
    /*test
    for(int i=L-1; i>=0; i--){
        for(int j=0; j<R; j++){
            cout << map[j][i] << " ";
        }
        cout << endl;
    }
     */
    
    Col_top();
    
    
    int x=0;
    while(x<N){
        string action;
        cin >> action;
        if(action == dig){
            int dig_position;
            cin >> dig_position;
            Dig(dig_position);
            
            
        }else if (action == use){
            Use();
        }
        
        Col_top();
        L=High_level();
        
        /*
        //test map condi
        for(int i=L-1; i>=0; i--){
            for(int j=0; j<R; j++){
                cout << map[j][i] << " ";
            }
            cout << endl;
        }
     
        */
        
        x++;
    }
    
    
    
    //cout bag
    cout << "FINAL BAG:" << endl;
    for(int i=1; i<=backpack_top; i++){
        cout << backpack[i] << " ";
    }
    cout << endl;
    
    
    //檢測地圖是否空
    int flag=1;
    if(L<=0){
        flag=0;
    }
    
    //cout map
    cout << "FINAL MAP:" << endl;
    if(flag==1){
        for(int i=L-1; i>=0; i--){
            for(int j=0; j<R; j++){
                cout << map[j][i] << " ";
            }
            cout << endl;
        }
    }
    
    
    
    
    
    return 0;
}
