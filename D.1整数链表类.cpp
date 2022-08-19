#include <iostream>
using namespace std;
template <typename T>
class Node {
public:
    /* 用于链表节点的定义 */
    T data; // 表示数据域
    Node<T> *next;  // 表示指针域，存储下一个节点的位置
};
template <typename T>
class LinkList : public Node<T>{
private:
    /* 用于链表的定义 */
    Node<T> *head; // 头节点
public:
    /* 成员函数的声明 */
    LinkList(); // 重写默认的构造函数
    bool Empty(); // 判断链表是否为空
    int GetLen(); // 获取链表的长度
    void insert(T elem); // 默认插入链表的开头
    bool insert(int idx, T elem); // 在链表的指定位置插入元素
    T remove(); // 默认删除链表的第一个元素，并返回该元素
    bool remove(int idx, T &elem); // 删除并指定位置的元素
    bool index(int idx, T &elem); // 找出并返回指定位置的元素
    int index(T elem); // 找到并返回传入元素的位置
    void traverse(); // 用于遍历整个链表
};


template <typename T>
inline LinkList<T>::LinkList() {
    this -> head = (Node<T> *)malloc(sizeof(Node<T>));
    if (!this -> head) {
        cerr << "申请空间不足" << endl;
    }
    this -> head -> next = nullptr;
}

template <typename T>
inline bool LinkList<T>::Empty() {
    if (this -> head == nullptr) {
        return true;
    }
    return false;
}

template <typename T>
int LinkList<T>::GetLen() {
    Node<T> *tmp = this -> head -> next;
    int counter = 0;
    while (tmp) {
        counter++;
        tmp = tmp -> next;
    }
    return counter;
}

template <typename T>
inline void LinkList<T>::insert(T elem) {
    Node<T> *newnode = (Node<T> *)malloc(sizeof(Node<T>));
    newnode -> data = elem;
    newnode -> next = this -> head -> next;
    this -> head -> next = newnode;
}

template <typename T>
bool LinkList<T>::insert(int idx, T elem) {
    if (idx < 1 || idx > this -> GetLen() + 1) {
        cerr << "插入位置越界" << endl;
        return false;
    }
    int counter = 0;
    Node<T> *newnode = this -> head, *tmp = (Node<T> *)malloc(sizeof(Node<T>));
    while (counter < idx - 1 && newnode -> next != nullptr) {
        counter++;
        newnode = newnode -> next;
    }
    tmp -> data = elem;
    tmp -> next = newnode -> next;
    newnode -> next = tmp;
    return true;
}

template <typename T>
T LinkList<T>::remove() {
    Node<T> *tmp = this -> head -> next;
    this -> head -> next = tmp -> next;
    T elem = tmp -> data;
    free(tmp);
    return elem;
}

template <typename T>
bool LinkList<T>::remove(int idx, T &elem) {
    if (idx < 1 || idx > this -> GetLen()) {
        cerr << "删除位置越界" << endl;
        return false;
    }
    Node<T> *newnode = this -> head, *tmp;
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

template <typename T>
bool LinkList<T>::index(int idx, T &elem) {
    if (idx < 1 || idx > this -> GetLen()) {
        cerr << "查询位置越界" << endl;
        return false;
    }
    Node<T> *newnode = this -> head -> next;
    int counter = 1;
    while (counter < idx) {
        counter++;
        newnode = newnode -> next;
    }
    elem = newnode -> data;
    return true;
}

template <typename T>
int LinkList<T>::index(T elem) {
    Node<T> *newnode = this -> head;
    int counter = 0;
    while (newnode -> next != nullptr) {
        newnode = newnode -> next;
        counter++;
        if (newnode->data==elem) {
            return counter;
        }
    }
    return -1;
}
template <typename T>
void LinkList<T>::traverse() {
    Node<T> *tmp = this -> head -> next;
    while (tmp) {
        cout<<tmp->data<<" ";
        tmp = tmp -> next;
    }
    cout << endl;
}

int main()
{
    LinkList<int> L;
    int data;
    int pos;
    cout<<"列表初始化完成(数据类型为int)"<<endl;
    cout<<"1.插入元素\n2.查询元素\n3.删除元素\n4.遍历输出\n5.查询链表长度\n6.退出"<<endl;
    while(1){
        cout<<"目前位于主菜单："<<endl;
        int k;
        cin>>k;
        if(k==1){
            cout<<"请选择插入方式(1.输入数据直接插入到链表头部 2.插入数据到链表指定位置）"<<endl;
            int i;
            cin>>i;
            if(i==1){
                cout<<"请输入数据"<<endl;
                cin>>data;
                L.insert(data);
                cout<<"插入完成"<<endl;
            }
            else if(i==2){
                cout<<"输入位置和数据（pos data）"<<endl;
                cin>>pos>>data;
                if(L.insert(pos,data))cout<<"插入完成"<<endl;
            }
            else exit(0);
        }
        else if(k==2){
            cout<<"请选择查询方式(1.输入位置查询链表对应位置的元素 2.输入元素查询链表对应元素的位置)"<<endl;
            int i;
            cin>>i;
            if(i==1){
                cout<<"请输入位置"<<endl;
                cin>>pos;
                if(L.index(pos,data))cout<<pos<<"处的元素为"<<data<<endl;
            }
            else if(i==2){
                cout<<"请输入元素"<<endl;
                cin>>data;
                pos=L.index(data);
                if(pos!=-1)cout<<data<<"在链表的"<<pos<<"处"<<endl;
            }
            else exit(0);
        }
        else if(k==3){
            cout<<"请选择删除方式(1.直接删除列表头部的元素 2.删除对应位置上的元素)"<<endl;
            int i;
            cin>>i;
            if(i==1){
                L.remove();
                cout<<"删除成功"<<endl;
            }
            else if(i==2){
                cout<<"请输入位置"<<endl;
                cin>>pos;
                if(L.remove(pos,data))cout<<"删除成功"<<endl;
            }
            else exit(0);
        }
        else if(k==4){
            cout<<"链表元素：";
            L.traverse();
            cout<<endl;
        }
        else if(k==5){
            cout<<"链表长度为:"<<L.GetLen()<<endl;
        }
        else{
            break;
        }
    }
    return 0;
}
