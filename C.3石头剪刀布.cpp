#include<iostream>
#include<map>
#include <ctime>
#include<string>
using namespace std;

class com_player{
private:
    char value;//计算机出的值
public:
    void guess(map<int,string>);//根据每次猜拳结果进行分析该出的拳
    void set_value(map<int,string>);//设定出的拳
    char get_value();//获取出的拳
};
void com_player::guess(map<int,string>m){
    int n=m.size();
    string s1,s2;
    string s3;
    int num[3]={0,0,0};
    for(int i=1;i<n+1;i++){
        s1=m[i].substr(0,1);
//        s2=m[i].substr(2,1);
        s3=m[i].substr(4,1);
//        cout<<s3<<endl;
        if(!s1.compare("1")){
            if(!s3.compare("0")){
                num[0]+=2;
            }
            else if(!s3.compare("1")){
                num[1]+=2;
            }
            else{
                num[2]+=2;
            }
        }
        else if(!s1.compare("2")){
            if(!s3.compare("0")){
                num[0]++;
            }
            else if(!s3.compare("1")){
                num[1]++;
            }
            else{
                num[2]++;
            }
        }
        else{
            if(!s3.compare("0")){
                num[0]--;
            }
            else if(!s3.compare("1")){
                num[1]--;
            }
            else{
                num[2]--;
            }
        }
//        cout<<n<<endl;
//        cout<<m[i]<<endl;
    }
    int max=0;
    if(max<num[1])max=1;
    if(max<num[2])max=2;
//    cout<<"max="<<max<<endl;
    switch(max){
        case 0:value='2';break;
        case 1:value='0';break;
        case 2:value='1';break;
    }
}
void com_player::set_value(map<int,string>m){
    if(m.empty()){
        srand((unsigned)time(NULL));
        int a=rand()%3;
        switch(a){
            case 0:value='0';break;
            case 1:value='1';break;
            case 2:value='2';break;
        }
    }
    else{
        guess(m);
    }
}
char com_player::get_value(){
    return value;
}
class hum_player{
private:
    char value;//人类玩家出的拳
public:
    void set_value();//设置出的拳
    char get_value();//获取出的拳
};
void hum_player::set_value(){
    while(1){
        cout<<"请输入你要出的拳:";
        cin>>value;
        if(value=='0'||value=='1'||value=='2')break;
        else cout<<"输入有误，请重新输入"<<endl;
    }
//        cout<<a<<endl;
//        value=a;
}
char hum_player::get_value(){
    return value;
}
class Manager{
private:
    com_player p1;//电脑玩家
    hum_player p2;//人类玩家
    map<int,string>reme;//每次输赢对应的值
    int n;              //记录玩的次数
    int f0;             //记录电脑获胜次数
    int f1;             //记录玩家获胜次数
    int f2;             //记录平局次数
public:
    void init();//初始化猜拳程序
    void run();//运行猜拳程序
    void play();//判断电脑和玩家出的拳压制关系
};
void Manager::init(){
    n=0;f0=0;f1=0;f2=0;
    cout<<"欢迎来到石头剪刀布游戏"<<endl;
    cout << "0代表石头" << endl;
    cout << "1代表剪刀" << endl;
    cout << "2代表布" << endl;
    cout<<"比赛开始"<<endl;
}
void Manager::run(){
    char flag='n';
//    cout<<"输入测试因子"<<endl;
    while(1){
//        if(n==10000)break;
        n++;
        play();
        while(1){
            cout<<"还要再来一把吗?y/n"<<endl;
            cin>>flag;
            if(flag=='n'||flag=='y')break;
            else cout<<"输入有误，请重新输入"<<endl;
        }
        if(flag=='n') break;
    }
    cout<<"感谢游玩"<<endl;
}
void Manager::play(){
    p1.set_value(reme);
    cout<<"我已经完成了出拳,到你了"<<endl;
    p2.set_value();
    int flag;//0代表p1赢，1代表p2赢，2代表平局
    if(p1.get_value()==p2.get_value()){
        flag=2;
    }
    else{
        if(p1.get_value()=='2'&&p2.get_value()=='0'){
        flag=0;
        }
        else if(p2.get_value()=='2'&&p1.get_value()=='0'){
            flag=1;
        }
        else if(p1.get_value()<p2.get_value()){
            flag=0;
        }
        else{
            flag=1;
        }
    }
    if(flag==1){
        cout<<"你获胜了，电脑玩家出的是";
        if(p1.get_value()=='0')cout<<"石头";
        if(p1.get_value()=='1')cout<<"剪刀";
        if(p1.get_value()=='2')cout<<"布";
        cout<<"，你出的是";
        if(p2.get_value()=='0')cout<<"石头";
        if(p2.get_value()=='1')cout<<"剪刀";
        if(p2.get_value()=='2')cout<<"布";
        cout<<endl;
        f1++;
    }
    else if(flag==2){
        cout<<"平局，电脑玩家出的是";
        if(p1.get_value()=='0')cout<<"石头";
        if(p1.get_value()=='1')cout<<"剪刀";
        if(p1.get_value()=='2')cout<<"布";
        cout<<"，你出的是";
        if(p2.get_value()=='0')cout<<"石头";
        if(p2.get_value()=='1')cout<<"剪刀";
        if(p2.get_value()=='2')cout<<"布";
        cout<<endl;
        f2++;
    }
    else{
        cout<<"你输了，电脑玩家出的是";
        if(p1.get_value()=='0')cout<<"石头";
        if(p1.get_value()=='1')cout<<"剪刀";
        if(p1.get_value()=='2')cout<<"布";
        cout<<"，你出的是";
        if(p2.get_value()=='0')cout<<"石头";
        if(p2.get_value()=='1')cout<<"剪刀";
        if(p2.get_value()=='2')cout<<"布";
        cout<<endl;
        f0++;
    }
    string str=to_string(flag)+","+p1.get_value()+","+p2.get_value();
    reme.insert(pair<int,string>(n,str));
    cout<<"一共进行了"<<n<<"局,电脑获胜"<<f0<<"局,你获胜"<<f1<<"局,平局"<<f2<<"局"<<endl;
}
int main(){
    Manager magr;
    magr.init();
    magr.run();
    return 0;
}
