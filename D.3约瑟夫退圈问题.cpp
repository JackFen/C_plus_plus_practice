#include<iostream>
using namespace std;
//整数循环链表
class Node {
public:
    /* 用于链表节点的定义 */
    int data; // 表示id
    Node *next;  // 表示指针域，存储下一个节点的位置
};
class LinkList : public Node{
public:
    /* 用于链表的定义 */
    Node *head; // 头节点
public:
    /* 成员函数的声明 */
    LinkList(); // 重写默认的构造函数
    bool Empty(); // 判断链表是否为空
    int GetLen(); // 获取链表的长度
    void insert(int elem); // 默认插入链表的尾部
    bool insert(int idx, int elem); // 在链表的指定位置插入元素
    int remove(); // 默认删除链表的最后一个元素，并返回该元素
    bool remove(int idx, int &elem); // 删除并指定位置的元素
    bool index(int idx, int &elem); // 找出并返回指定位置的元素
    int index(int elem); // 找到并返回传入元素的位置
    void traverse(); // 用于遍历整个链表
};

inline LinkList::LinkList() {
    this -> head = new Node;
    if (!this -> head) {
        cerr << "申请空间不足" << endl;
    }
    this->head->data=-1;
    this -> head -> next = this->head;
}


inline bool LinkList::Empty() {
    if (this -> head->next == this->head) {
        return true;
    }
    return false;
}


int LinkList::GetLen() {
    Node *tmp = this -> head -> next;
    int counter = 0;
    while (tmp!=this->head) {
        counter++;
        tmp = tmp -> next;
    }
    return counter;
}


inline void LinkList::insert(int elem) {
    Node *r=this->head;
    while(r->next!=this->head){
        r=r->next;
    }
    Node *newnode = new Node;
    newnode -> data = elem;
    newnode -> next = this->head;
    r->next=newnode;
}


bool LinkList::insert(int idx, int elem) {
    if (idx < 1 || idx > this -> GetLen() + 1) {
        cerr << "插入位置越界" << endl;
        return false;
    }
    int counter = 0;
    Node *newnode = this -> head, *tmp = new Node;
    while (counter < idx - 1 && newnode -> next != nullptr) {
        counter++;
        newnode = newnode -> next;
    }
    tmp -> data = elem;
    tmp -> next = newnode -> next;
    newnode -> next = tmp;
    return true;
}


int LinkList::remove() {
    Node *tmp = this -> head -> next;
    while(tmp->next->next!=this->head){
        tmp=tmp->next;
    }
    Node *q=tmp->next;
    tmp->next=this->head;
    int elem = q-> data;
    free(q);
    return elem;
}


bool LinkList::remove(int idx, int &elem) {
    if (idx < 1 || idx > this -> GetLen()) {
        cerr << "删除位置越界" << endl;
        return false;
    }
    Node *newnode = this -> head, *tmp;
    int counter = 0;
    while (counter < idx - 1 && newnode -> next != nullptr) {
        newnode = newnode -> next;
        counter++;
    }
    tmp = newnode -> next;
    elem = tmp -> data;
    newnode -> next = tmp -> next;
    free(tmp);
    return true;
}


bool LinkList::index(int idx, int &elem) {
    if (idx < 1 || idx > this -> GetLen()) {
        cerr << "查询位置越界" << endl;
        return false;
    }
    Node *newnode = this -> head -> next;
    int counter = 1;
    while (counter < idx) {
        counter++;
        newnode = newnode -> next;
    }
    elem = newnode -> data;
    return true;
}


int LinkList::index(int elem) {
    Node *newnode = this -> head;
    int counter = 0;
    while (newnode -> next != this->head) {
        newnode = newnode -> next;
        counter++;
        if (newnode->data==elem) {
            return counter;
        }
    }
    return -1;
}

void LinkList::traverse() {
    Node *tmp = this -> head -> next;
    while (tmp!=this->head) {
        cout<<tmp->data<<" ";
        tmp = tmp -> next;
    }
    cout << endl;
}

int main(){
    LinkList L,queue1;
    cout<<"请输入人数n:";
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        L.insert(i+1);
    }
    int standId;
    while(1){
        cout<<"请输入standId：(范围是1到n)"<<endl;
        cin>>standId;
        if(standId<=n&&standId>0)break;
        else cout<<"standId不能大于n且为正数"<<endl;
    }
    int pos=L.index(standId);//定位standId
    Node *pre=L.head;//满足要求要退圈的那个人的前一个人
    for(int i=1;i<pos;i++){
        pre=pre->next;
    }
    int m;
    cout<<"请输入报数的上限m（m为正数）"<<endl;
    cin>>m;
    int x;
    while(!L.Empty()){
        for(int i=pos;i<m+pos-1;i++){
            pre=pre->next;
            if(pre->next==L.head)pre=pre->next;//如果遇到头结点，就跳过
        }
        Node *q=pre->next; //q为要退圈的那个人
        pre->next=q->next;
        x=q->data;        //要退圈的那个人的Id
        delete(q);        //退圈
        if(pre->next==L.head)pre=pre->next;//如果遇到头结点，就跳过
        queue1.insert(x);//加入到退圈队列
    }
    cout<<"出列次序为:";
    queue1.traverse();//遍历输出退圈队列
    return 0;
}
