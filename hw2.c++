/*
命令：

插入int1 int2 int3字串：插入具有int1口袋妖怪值、int2傷害值、int3生命值和字串姿態的口袋妖怪。 如果列表中存在多個寶可夢，請將寶可夢插入當前目標的左側。 如果列表中存在兩個以上的寶可夢，則在當前目標寶可夢和目標左側的寶可夢之間插入具有int值的寶可夢。 插入寶可夢時，它們將採取以下三種姿態，進化、攻擊或中立。

- 進化姿態，如果插入的寶可夢相鄰的寶可夢屬於同一型別（Pokédex值），那麼它們可以進化（合併成一個，並將其新的生命值和攻擊值設定為其中的當前最高值）。 然而，每個寶可夢只能進化2次，即如果其中一個相鄰的寶可夢已經進化到“3”級，那麼插入的寶可夢就無法進化（合併），在進化時採取具有最高進化等級的寶可夢並從中增加。 進化的寶可夢成為當前的目標。 初始插入時，預設情況下基本進化級別為1。 如果不符合任何要求，請正常插入口袋妖怪。

-攻擊姿勢，插入的寶可夢將以int2傷害點攻擊其相鄰的鄰居。 如果相鄰的寶可夢健康點降低到<= 0，它們被視為“進入睡眠”，並將被拖出競技場（移除它們，如果被移除的寶可夢是當前目標，請將當前目標交給插入的寶可夢）。 如果圈子裡只有另一個寶可夢，只攻擊一次，雙重攻擊是不公平的，被認為是犯規。

-中立的姿態，什麼都不會發生，寶可夢將正常插入。 在所有必要的操作完成後，插入的口袋妖怪將恢復“中立”的姿態。

在所有必要的操作完成後，插入的口袋妖怪將恢復“中立”的姿態。

刪除：刪除當前目標寶可夢。 如果列表中有不止一個寶可夢，請將順時針方向的下一個寶可夢分配為下一個目標寶可夢。

隨機播放char int：從當前目標以順時針（char == 'c'）或逆時針（char == 'a'）方向開始，在列表int時間中穿越到相鄰的寶可夢。 完成後，將該寶可夢的位置與當前的目標寶可夢互換。

檢查int：從目標寶可夢開始，順時針方向搜尋，刪除下一個int-1寶可夢中發現的任何重複物（具有相同寶可夢值的寶可夢）。 如果當前目標被移除，請沿順時針方向分配最近的未移除的寶可夢作為新目標寶可夢。

反向int：從目標寶可夢開始，順時針方向計數。 對於每個int寶可夢，將建立一個群組。 然後在每個小組中，顛倒他們的立場。 將當前目標寶可夢更改為取代其位置的寶可夢。
*/

#include<iostream>
#include<vector>
using namespace std;

class List; //先宣告



class Poke{
public:
    int cat;
    int dam;
    int hel;
    int lev;
    string state;
    Poke* rnext; //順時針（右）
    Poke* lnext; //逆時針(左)
    
    Poke(int cat, int dam, int hel, string state): //initialize
    cat(cat), dam(dam), hel(hel), state(state), lev(1), rnext(nullptr),lnext(nullptr){}
    
    friend class List; //使list 可以造訪（修改） poke 的 private and public
};



class List{
private:
    Poke* cur; //==current:在沒有額外行為時，是起始點

public:
    List(): cur(nullptr){} //initialize
    
    //根據不同state做出不同插入行為
    void Insert(int icat, int idam, int ihel, string istate);
    
    //三種型態
    void Neutral(int icat, int idam, int ihel, string istate);
    void Evolve(int icat, int idam, int ihel, string istate);
    void Attack(int icat, int idam, int ihel, string istate);
    
    //delete
    void Delete();
    void SDelete( Poke* a);
    
    //shuffle:swap the node with int in couter or clockwise order
    void Shuffle(char direct, int order);
    void TShuffle(Poke *a, Poke *b);
    
    //Check: 在order之內 刪除與current 相同的物
    void Check(int order);
    
    //reverse: 順序調換
    void Reverse(int order);
    
    void Print();
    
    int Size();
};



void List :: Insert(int icat, int idam, int ihel, string istate){
    if(cur==nullptr){
        Neutral(icat, idam, ihel, istate);
        return;
    }
    
    if(istate == "Neutral"){
        Neutral(icat, idam, ihel, istate);
    }
    else if (istate == "Evolve"){
        Evolve(icat, idam, ihel, istate);
        
    }
    else if(istate == "Attack"){
        Attack(icat, idam, ihel, istate);
    }
    
}


void List :: Neutral(int icat, int idam, int ihel, string istate){
    Poke* newPoke = new Poke(icat, idam, ihel, istate); //new是返回對象的"指針" -> Poke*
    if(cur==nullptr){
        cur=newPoke;
        newPoke->rnext=newPoke;
        newPoke->lnext=newPoke;
    }
    else{
        newPoke->rnext=cur;
        newPoke->lnext=cur->lnext;
        cur->lnext->rnext=newPoke;
        cur->lnext=newPoke;
        
    }
    
}

void List :: Evolve(int icat, int idam, int ihel, string istate){
    
    //數量
    if(cur->lnext!=cur){
        if(cur->cat == icat && cur->lnext->cat == icat){
            if(cur->lev<3 && cur->lnext->lev<3){
                cur->lev=max(cur->lnext->lev, cur->lev)+1;
                
                cur->hel=max(ihel, cur->hel);
                cur->hel=max(cur->hel, cur->lnext->hel);
                
                cur->dam=max(idam, cur->dam);
                cur->dam=max(cur->dam, cur->lnext->dam);
                
                SDelete(cur->lnext); //delete cur->lnext
            }
            else{
                Neutral(icat, idam, ihel, istate);
            }
        }
        else{
            Neutral(icat, idam, ihel, istate);
        }
    }
    else{
        Neutral(icat, idam, ihel, istate);
    }
    //Poke* newPoke = new Poke(icat, idam, ihel, istate); //new是返回對象的"指針" -> Poke*
    
}

void List :: Attack(int icat, int idam, int ihel, string istate){
    
    if(cur==nullptr){
        Neutral(icat, idam, ihel, istate);
        return;
    }
    
    cur->hel= cur->hel - idam;
    
    if(cur->lnext != cur){
        cur->lnext->hel =  cur->lnext->hel -idam;
        if(cur->lnext->hel <=0){
            SDelete(cur->lnext);
        }
    }
    
    if(cur->hel <=0){
        Poke* newPoke = new Poke(icat, idam, ihel, istate);
        
        newPoke->lnext = cur->lnext;
        cur->lnext->rnext=newPoke;
        
        newPoke->rnext = cur->rnext;
        cur->rnext->lnext=newPoke;
        
        delete cur;
        cur=newPoke;
        
    }
    else{
        Neutral(icat, idam, ihel, istate);
    }
    
    
    
   
}


void List :: Delete(){
    
    if(cur==nullptr){
        return;
    }
    
    if(cur->rnext==cur){
        delete cur;
        cur = nullptr;
    }
    else{
        cur->lnext->rnext=cur->rnext;
        cur->rnext->lnext=cur->lnext;
        Poke* temp = cur->rnext;
        delete cur;
        cur = temp;
        
    }
     
}
 

void List :: SDelete(Poke *a){
    if(cur==nullptr){
        return;
    }
    
    if(cur->rnext==cur){
        delete cur;
        cur = nullptr;
    }
    else{
        if(a!=cur){
            a->lnext->rnext=a->rnext;
            a->rnext->lnext=a->lnext;
            delete a;
        }
        else{
            //順時針
            Poke* temp=a->rnext;
            a->lnext->rnext=a->rnext;
            a->rnext->lnext=a->lnext;
            delete a;
            cur=temp;
        }
        
    }
}

void List :: Shuffle(char direct, int order){
    
    order=order % Size();
    if(cur==nullptr){
        return;
    }
    
    Poke* temp = cur;
    if(direct == 'a'){
        for(int i=0; i<order; i++){
            temp = temp->lnext;
        }
    }
    else if(direct == 'c'){
        for(int i=0; i<order; i++){
            temp = temp->rnext;
            //cout << "temp cat: " << temp->cat << endl;
        }
    }
    
    if(cur->rnext->rnext==cur){
        return;
    }
    
    //要temp移之後才能確定
    if(cur->lnext == temp){
        Poke* a=cur->lnext;
        Poke* b=cur;
        Poke* br=b->rnext;
        Poke* al=a->lnext;
        
        a->rnext=br;
        a->lnext=b;
        b->rnext=a;
        b->lnext=al;
        
        al->rnext=b;
        br->lnext=a;
        return;
    }
    
    if(cur->rnext==temp){
        Poke* a=cur;
        Poke* b=cur->rnext;
        Poke* br=b->rnext;
        Poke* al=a->lnext;
        
        a->rnext=br;
        a->lnext=b;
        b->rnext=a;
        b->lnext=al;
        
        al->rnext=b;
        br->lnext=a;
        
        return;
    }
    
    
    
    
    //將各自接線交換(如何ip不變)
    //先記錄個接頭地址
    //相鄰接法不同！！！######################
    
    Poke *tr = temp->rnext;
    Poke *tl = temp->lnext;
    Poke *cr =cur->rnext;
    Poke *cl = cur->lnext;
    
    
    cl->rnext=temp;
    cr->lnext=temp;
    tr->lnext=cur;
    tl->rnext=cur;
    
    cur->rnext=tr;
    cur->lnext=tl;
    temp->rnext=cr;
    temp->lnext=cl;
    
    
    //cout << cur->rnext->cat << " " << cur->lnext->cat << endl;
    //cout << temp->rnext->cat << " " << temp->lnext->cat << endl;
     
    
}

void List :: TShuffle(Poke *a, Poke *b){
    Poke *ar = a->rnext;
    Poke *al = a->lnext;
    Poke *br =b->rnext;
    Poke *bl = b->lnext;

    
    if(a==b){
        //cout << "same" << endl;
        return;
    }
    
    if(a==cur){
        //cout << "cur change a" << endl;
        cur=b;
    }
    else if(b==cur){
        //cout << "cur change b" << endl;
        cur=a;
    }
    
    if(a->rnext==b && a->rnext->rnext==a){
        //cout << "only two" << endl;
        return;
    }
    
    if(a->rnext==b){ //右相鄰
        //cout << "right next" << endl;
        a->rnext=br;
        a->lnext=b;
        b->rnext=a;
        b->lnext=al;
        
        al->rnext=b;
        br->lnext=a;
        
        
        return;
    }
    
    if(a->lnext==b){
        //cout << "left next" << endl;
        a->rnext=b;
        a->lnext=bl;
        b->rnext=ar;
        b->lnext=a;
        
        ar->lnext=b;
        bl->rnext=a;
        return;
    }
    
    
    //cout << "suppose" << endl;
    al->rnext=b;
    ar->lnext=b;
    br->lnext=a;
    bl->rnext=a;
    
    a->rnext=br;
    a->lnext=bl;
    b->rnext=ar;
    b->lnext=al;
}

void List :: Check(int order){
    
    if(cur==nullptr){
        return;
    }
    
    int flag=0;
    int a[110]={0};
    Poke* end =cur;
    for(int i=0; i<order; i++){
        a[end->cat]++;
        //cout << end->cat << " " << a[end->cat]<<endl;
        if(end->rnext==cur){
            flag=1;
            break;
        }
        end=end->rnext;
        
    }
    //end=end->rnext;
    
    Poke* temp=cur;
    while(temp != end){
        if(a[temp->cat]>1){
            temp=temp->rnext;
            SDelete(temp->lnext);
        }
        else{
            temp=temp->rnext;
        }
    }
    
    if(flag==1){
        if(a[end->cat]>1){
            SDelete(end);
        }
    }
    
    
}


void List :: Reverse(int order){
    
    if(cur==nullptr){
        return;
    }
    
    //int flag=1;
    Poke *mark=cur; //mark tail
    Poke *firstend=nullptr;
    Poke *firsthead=cur; //cur後面會換值 要先記錄值
    Poke *head=cur;
    Poke *tail=cur;
    int size=Size();
    //cout << size << endl;
    
    int k=min((size-1),(order-1));
    
    while(head!=firstend){
        int flag=-1;
        tail=head;
        //cout <<"min " << k << endl;
        for(int i=0; i<k; i++){
            if(tail->rnext==firstend){
                //cout << "i= " << i << " tail->rnext = firstend" <<endl;
                flag=i;
                break;
            }
            tail=tail->rnext;
        }
        
        //cout << "head= " << head->cat << " tail= " << tail->cat << endl;
        
        if(firstend==nullptr){
            firstend=tail;
        }
        
        if(flag!=-1){
            //cout << "k= " << k << endl;
            k=flag;
        }

        mark=tail->rnext;//下一個開始
        //cout << "mark= " << mark->cat << endl;
        
        int t=0;
        while(t<((k+1)/2)){
            Poke* Nxhead=head->rnext;
            Poke* Nxtail=tail->lnext;
            TShuffle(head, tail);
            
            
            if((t+1) >= (order/2)){
                break;
            }
            else{
                head=Nxhead;
                tail=Nxtail;
                t++;
            }
            
            
        }
        
        
        if(mark==firsthead){ //reverse 整個長度會出現
            //cout << "mark = firsthead" << endl;
            break;
        }
        else{
            head=mark;
        }
        
    
    }
    
    
}


void List :: Print(){
    if(cur==nullptr){
        cout << "no Poke Poke ;-;" << endl;
        return;
    }
    cout << "ID: " << cur->cat <<" HP: " << cur->hel <<" LVL: " << cur->lev << endl;
    
    Poke* t = cur->rnext;
    while(t != cur){
        cout << "ID: " << t->cat <<" HP: " << t->hel <<" LVL: " << t->lev << endl;
        t = t->rnext;
    }
    
    
}

int List::Size(){
    if(cur==nullptr){
        return 0;
    }
    
    int size=1;
    
    Poke* temp=cur->rnext;
    while(temp!=cur){
        temp=temp->rnext;
        size++;
        
    }
    
    return size;
    
}







int main(){
    int action;
    cin >> action;
    
    List pokelist; //記得宣告！！！
    
    
    while(action > 0){
        string type;
        cin >> type;
        
        if(type == "Insert"){
            int icat;
            int idam;
            int ihel;
            string istate;
            
            cin >> icat >> idam >> ihel >> istate;
            
            pokelist.Insert(icat, idam, ihel, istate);
            
        }
        else if(type == "Delete"){
            pokelist.Delete();
            
        }
        else if(type == "Shuffle"){
            char dir;
            int ord;
            cin >> dir >> ord;
            pokelist.Shuffle(dir, ord);
        }
        else if(type == "Check"){
            int ord;
            cin >> ord;
            pokelist.Check(ord);
        }
        else if(type == "Reverse"){
            int ord;
            cin >> ord;
            pokelist.Reverse(ord);
        }
        //else if (type == "Size"){
        //    int size=pokelist.Size();
        //    cout << size << endl;
        //}
        
        
        
        //pokelist.Print();
        
        
        action--;
    }
    
    pokelist.Print();
    
 
    return 0;
}


/*
 1. 沒有dummyhead 情況下
 if(head == nullptr){
     head = newPoke; //把head和tail（頭尾“指針”） 想成地址的紀錄通常不會直接operate他
     tail = newPoke;
     newPoke->rnext = newPoke;
     newPoke->lnext = newPoke;
 }
 else{
     
 }
 
 2. 雙頭
 Poke* head;
 Poke* tail; //==current in general
 
 List(){
     Poke* dummy = new Poke(-1, -1, -1, "dummy");
     head = dummy; //把head和tail（頭尾“指針”） 想成地址的紀錄通常不會直接operate他
     tail = dummy;
     dummy->rnext = dummy;
     dummy->lnext = dummy;
 } //initialize
 
 
19
Insert 1 1 1 Neutral
Insert 2 1 1 Neutral
Insert 3 1 1 Neutral
Insert 3 1 1 Neutral
Delete
Insert 4 1 1 Neutral
Insert 5 1 1 Neutral
Insert 5 1 1 Neutral
Shuffle c 4
Insert 3 1 1 Neutral
Insert 4 1 1 Neutral
Shuffle a 5
Check 4
Insert 6 1 1 Neutral
Check 6
Reverse 2
Insert 3 1 1 Evolve
Insert 3 1 2 Evolve
Insert 5 1 1 Attack

 */
