#include<iostream>
#include<string>
#include <iomanip>
#include<vector>
#include<fstream>
using namespace std;
class Node {
public:
    /* 用于错题节点的定义 */
    int No;           //题目编号
    string title;     // 题目
    string er_msg;    //错误信息
    string answer;    //答案分析
    string experience;//心得体会
    string source;   //错题来源
    string reason;   //错题原因
    string rank;        //难易程度
    int type;     //题目类型 选择题：2 判断题：1 填空：0
    string point;    //知识点
    Node *next;      // 表示指针域，存储下一个节点的位置
};

class Manager : public Node{
private:

    Node *head2; // 难题头节点
    Node *head1; // 适中题头节点
    Node *head0; // 简单题头节点
public:
    /* 成员函数的声明 */
    Manager(); // 重写默认的构造函数
    void Menu();//显示菜单
    void add();//添加错题
    void show(Node *head,int flag);//flag传给to_string方法
    void traverse();//遍历错题
    void find(int);//查找错题
    void update();//修改错题
    void remove();//删除错题
    void file_in();//文件的导入
    void file_out();//文件导出
    void to_string(Node *p,int flag=0);//0表示展示题目类型，不展示知识点；1表示展示知识点，不展示题目类型
};
Manager::Manager(){
    head2=new Node;
    head2->next=nullptr;
    head1=new Node;
    head1->next=nullptr;
    head0=new Node;
    head0->next=nullptr;
    No=1;
}
void Manager::add(){
    Node *r2=this->head2;
    while(r2->next){
        r2=r2->next;
    }
    Node *r1=this->head1;
    while(r1->next){
        r1=r1->next;
    }
    Node *r0=this->head0;
    while(r0->next){
        r0=r0->next;
    }
    while(1){
        Node *p=new Node;
        p->No=this->No;
        No++;
        cout<<"请输入题目:"<<endl;;
        cin>>p->title;
        cout<<"请输入错误信息"<<endl;
        cin>>p->er_msg;
        cout<<"请输入答案分析"<<endl;
        cin>>p->answer;
        cout<<"请输入心得体会"<<endl;
        cin>>p->experience;
        cout<<"请输入错题来源"<<endl;
        cin>>p->source;
        cout<<"请输入错题原因"<<endl;
        cin>>p->reason;
        cout<<"请选择难易程度"<<endl;
        cin>>p->rank;
        cout<<"请输入题目类型（选择题：2 判断题：1 填空：0）"<<endl;
        cin>>p->type;
        cout<<"请输入知识点"<<endl;
        cin>>p->point;
        if(p->type==2){
//            cout<<"flag";
            r2->next=p;
            p->next=nullptr;
            r2=p;
//            cout<<"flag2";
        }
        else if(p->type==1){
            r1->next=p;
            p->next=nullptr;
            r1=p;
        }
        else{
            r0->next=p;
            p->next=nullptr;
            r0=p;
        }
        char flag='n';
        cout<<"添加成功\n是否还要继续添加?y/n"<<endl;
        cin>>flag;
        if(flag=='n')break;
    }

}
void Manager::to_string(Node *p,int flag){
    cout<<"\n题目编号:"<<p->No<<endl;
    cout<<"题目:\n"<<p->title<<endl;
    cout<<"错误信息\n"<<p->er_msg<<endl;
    cout<<"答案分析\n"<<p->answer<<endl;
    cout<<"心得体会\n"<<p->experience<<endl;
    cout<<"错题来源\n"<<p->source<<endl;
    cout<<"错题原因\n"<<p->reason<<endl;
    cout<<"难易程度\n"<<p->rank<<endl;
    if(flag==0){
        cout<<"题目类型\n";
        if(p->type==2)cout<<"选择题"<<endl;
        else if(p->type==1)cout<<"判断题"<<endl;
        else cout<<"填空题"<<endl;
    }
    else cout<<"知识点\n"<<p->point<<endl;
    cout<<endl;
}
void Manager::show(Node *head,int flag){
    Node *p=head->next;
    if(!p){
        cout<<"无"<<endl;
    }
    else{
        while(p){
        to_string(p,flag);
        p=p->next;
        }
    }
}
void Manager::traverse(){
    cout<<"全部错题如下:"<<endl;

    cout<<"选择题："<<endl;
    show(head2,1);

    cout<<"判断题："<<endl;
    show(head1,1);

    cout<<"填空题："<<endl;
    show(head0,1);
}
void Manager::find(int G=0){
    int flag;
    cout<<"请";
    if(G)cout<<"先";
    cout<<"选择查询方式(0:按知识点查询 1:按题目类型查询)"<<endl;
    cin>>flag;
    //按题目类型查询
    if(flag){
        int flag2;
        cout<<"请输入题目类型（选择题：2 判断题：1 填空题：0）"<<endl;
        cin>>flag2;
        if(flag2==2){
            cout<<"选择题"<<endl;
            show(head2,1);
        }
        else if(flag2==1){
            cout<<"判断题"<<endl;
            show(head1,1);
        }
        else{
            cout<<"填空题"<<endl;
            show(head0,1);
        }
    }
    else{
        string str;
        cout<<"请输入知识点:"<<endl;
        cin>>str;
        Node *p=head2->next;
        while(p){
            if(!p->point.compare(str)) to_string(p,0);
            p=p->next;
        }
        p=head1->next;
        while(p){
            if(!p->point.compare(str)) to_string(p,0);
            p=p->next;
        }
        p=head0->next;
        while(p){
            if(!p->point.compare(str)) to_string(p,0);
            p=p->next;
        }
    }
    if(!G){
        char mark;
        cout<<"是否要进行修改?y/n"<<endl;
        cin>>mark;
        if(mark=='y') update();
    }
}
void Manager::update(){
    int no;
    while(1){
        cout<<"请输入要修改题目的题目编号"<<endl;
        cin>>no;
        Node *pre=head2;
        int a=0;
        while(pre->next){
            if(pre->next->No==no){
                a=1;
                break;
            }
            pre=pre->next;
        }
        if(a==0){
            pre=head1;
            while(pre->next){
                if(pre->next->No==no){
                    a=1;
                    break;
                }
//                cout<<pre->next->No<<endl;
                pre=pre->next;
            }
        }
        if(a==0){
            pre=head0;
            while(pre->next){
                if(pre->next->No==no){
                    a=1;
                    break;
                }
                pre=pre->next;
            }
        }
        if(pre->next){
            Node *p=pre->next;
            while(1){
                int flag;
                cout<<"请输入要修改的部分(题目:1 ||错误信息:2 ||答案分析:3 ||心得体会:4 ||错题来源:5 ||错题原因:6 ||难易程度:7 ||题目类型:8 ||知识点:9)"<<endl;
                cin>>flag;
                if(flag==1){
                    cout<<"请输入修改后的题目"<<endl;
                    cin>>p->title;
                }
                else if(flag==2){
                    cout<<"请输入修改后的错误信息"<<endl;
                    cin>>p->er_msg;
                }
                else if(flag==3){
                    cout<<"请输入修改后的答案分析"<<endl;
                    cin>>p->answer;
                }
                else if(flag==4){
                    cout<<"请输入修改后的心得体会"<<endl;
                    cin>>p->experience;
                }
                else if(flag==5){
                    cout<<"请输入修改后的错题来源"<<endl;
                    cin>>p->source;
                }
                else if(flag==6){
                    cout<<"请输入修改后的错题原因"<<endl;
                    cin>>p->reason;
                }
                else if(flag==7){
                    cout<<"请输入修改后的难易程度"<<endl;
                    cin>>p->rank;
                }
                else if(flag==8){
                    cout<<"请输入修改后的题目类型（选择题：2 判断题：1 填空题：0）"<<endl;
                    cin>>p->type;
                    if(p->type==2){
                        pre->next=p->next;
                        p->next=nullptr;
                        Node *r=head2->next;
                        while(r->next) r=r->next;
                        r->next=p;
                    }
                    else if(p->type==1){
                        pre->next=p->next;
                        p->next=nullptr;
                        Node *r=head1->next;
                        while(r->next) r=r->next;
                        r->next=p;
                    }
                    else{
                        pre->next=p->next;
                        p->next=nullptr;
                        Node *r=head0->next;
                        while(r->next) r=r->next;
                        r->next=p;
                    }
                }
                else{
                    cout<<"请输入修改后的知识点"<<endl;
                    cin>>p->point;
                }
                char M;
                cout<<"修改成功,还要继续修改题目编号为"<<no<<"的信息吗？y/n"<<endl;
                cin>>M;
                if(M=='n')break;
            }
        }
        else{
            cout<<"无此题，请检查题目编号"<<endl;
        }
        cout<<"是否还要继续修改其他题目?y/n"<<endl;
        char N;
        cin>>N;
        if(N=='n')break;
    }
}
void Manager::remove(){
    find(1);
    cout<<"请输入要删除题的题目编号"<<endl;
    int no;
    cin>>no;
    Node *pre=head2;
        int a=0;
        while(pre->next){
            if(pre->next->No==no){
                a=1;
                break;
            }
            pre=pre->next;
        }
        if(a==0){
            pre=head1;
            while(pre->next){
                if(pre->next->No==no){
                    a=1;
                    break;
                }
                pre=pre->next;
            }
        }
        if(a==0){
            pre=head0;
            while(pre->next){
                if(pre->next->No==no){
                    a=1;
                    break;
                }
                pre=pre->next;
            }
        }
        if(pre->next){
            Node *q=pre->next;
            pre->next=q->next;
            delete q;
            cout<<"删除成功"<<endl;
        }
        else{
            cout<<"无此题，请检查题目编号"<<endl;
        }
}
void Manager::file_in(){
    void Stringsplit(const string& str, const char split, vector<string>& res);
    ifstream ifs;
    ifs.open("D2.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	Node *r2=this->head2;
    while(r2->next){
        r2=r2->next;
    }
    Node *r1=this->head1;
    while(r1->next){
        r1=r1->next;
    }
    Node *r0=this->head0;
    while(r0->next){
        r0=r0->next;
    }
    string buf;
	while (getline(ifs, buf)){
		vector<string> data;
        Stringsplit(buf,'#', data);
        Node *p=new Node;
        p->No=atoi(data[0].c_str());
        p->title=data[1];
        p->er_msg=data[2];
        p->answer=data[3];
        p->experience=data[4];
        p->source=data[5];
        p->reason=data[6];
        p->rank=data[7];
        p->type=atoi(data[8].c_str());
        p->point=data[9];
        if(p->type==2){
            r2->next=p;
            p->next=nullptr;
            r2=p;
        }
        else if(p->type==1){
            r1->next=p;
            p->next=nullptr;
            r1=p;
        }
        else{
            r0->next=p;
            p->next=nullptr;
            r0=p;
        }
    }
    cout<<"文件导入成功"<<endl;
}
void Manager::file_out(){
    ofstream ofs;
    ofs.open("D2.txt", ios::out);
    Node *p=head2->next;
    while(p){
        ofs<<p->No<<"#"<<p->title<<"#"<<p->er_msg<<"#"<<p->answer<<"#"<<p->experience<<"#"<<p->source<<"#"<<p->reason<<"#"<<p->rank<<"#"<<p->type<<"#"<<p->point<<endl;
        p=p->next;
    }
    p=head1->next;
    while(p){
        ofs<<p->No<<"#"<<p->title<<"#"<<p->er_msg<<"#"<<p->answer<<"#"<<p->experience<<"#"<<p->source<<"#"<<p->reason<<"#"<<p->rank<<"#"<<p->type<<"#"<<p->point<<endl;
        p=p->next;
    }
    p=head0->next;
    while(p){
        ofs<<p->No<<"#"<<p->title<<"#"<<p->er_msg<<"#"<<p->answer<<"#"<<p->experience<<"#"<<p->source<<"#"<<p->reason<<"#"<<p->rank<<"#"<<p->type<<"#"<<p->point<<endl;
        p=p->next;
    }
    ofs.close();
    cout<<"文件导出成功"<<endl;
}
void Manager::Menu(){
    cout<<"错题本管理程序"<<endl;
    cout<<"   1添加错题信息"<<endl;
    cout<<"   2浏览错题信息"<<endl;
    cout<<"   3查询错题信息"<<endl;
    cout<<"   4删除错题信息"<<endl;
    cout<<"   5文件导入"<<endl;
    cout<<"   6文件导出"<<endl;
    cout<<"   7退出"<<endl;
    cout<<" 请选择功能"<<endl;
}
// 使用字符分割
void Stringsplit(const string& str, const char split, vector<string>& res)
{
	if (str == "")		return;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + split;
	size_t pos = strs.find(split);

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

int main(){
    Manager mgr;
    int k;
    while(1){
       mgr.Menu();
       cin>>k;
       switch(k){
           case 1:mgr.add();break;
           case 2:mgr.traverse();break;
           case 3:mgr.find();break;
           case 4:mgr.remove();break;
           case 5:mgr.file_in();break;
           case 6:mgr.file_out();break;
           default:cout<<"再见";mgr.file_out();exit(0);break;
       }
    }
    return 0;
}
