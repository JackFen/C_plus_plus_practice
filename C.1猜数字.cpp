#include<iostream>
#include <ctime>
#include<vector>
#include <conio.h>
using namespace std;

class Rand_num{
private:
    int rand_num;//随机数
public:
    int create_num();//生成随机数
};
int Rand_num::create_num(){
    srand((unsigned)time(NULL));
//    srand(1);
    rand_num=1;
    while(true){
        rand_num=rand()%10001;
        if(rand_num!=0) break;
    }
    return rand_num;
}
class Manager{
public:
    Rand_num R;//随机数生成对象
    int rand_num;//记录生成的随机数
    time_t t;//记录游戏起始时间
    int interval;//倒计时时间
    vector<int> m;//记录各个位上的数值
public:
    void menu();//显示菜单
    void init();//初始化
    void setTime();//设定倒计时
    void tips(int);//提示
    void guess();//判断是否猜对
    void run();//整个猜数字程序的运行
};
void Manager::menu(){
    cout<<"\t\t欢迎来到猜数小游戏:\n系统将随机产生一个1到10000的整数，如果你在规定的时间内猜出答案便获胜，反之失败"<<endl;
}
void Manager::init(){
    m.clear();
	rand_num=R.create_num();
	int n=rand_num;
    while(n>0)
    {
        m.push_back(n%10);
        n/=10;
    }
	setTime();
}
void Manager::setTime(){
    cout<<"请输入倒计时时间（单位：秒）"<<endl;
    cin>>interval;
    t=time(NULL);
}
void Manager::tips(int count){
    int n=m.size();
    cout<<"该数是一个"<<n<<"位数"<<endl;
    if(count<n){
        cout<<"其"<<count<<"位的值为"<<m[count]<<endl;
    }
}
void Manager::guess(){
    cout<<"初始化完成，即将开始游戏\n还剩"<<interval<<"秒"<<endl;
    int num = 0,count=0,n=0;
    int flag=0;
    tips(count);
    cout<<"请输入你猜到的数字"<<endl;
    while(true){           //the main loop  ||  主循环
        if(kbhit()){       //detect the keyboard  ||  kbhit检测键盘输，如果发现了输入
            cin>>num;
            if(num<rand_num){
                cout<<"小了"<<endl;
                count++;
                tips(count);
                cout<<"请输入你猜到的数字"<<endl;
            }
            else if(num>rand_num){
                cout<<"大了"<<endl;
                count++;
                tips(count);
                cout<<"请输入你猜到的数字"<<endl;
            }
            else{
                cout<<"恭喜！正确猜出数字"<<rand_num<<endl;
                flag=1;
            }
        }
        else if(t+interval-time(0)==3&&n==0){
                cout<<"还剩3秒"<<endl;
                n=1;
        }
        else if(t+interval-time(0)==2&&n==1){
                cout<<"还剩2秒"<<endl;
                n=2;
        }
        else if(t+interval-time(0)==1&&n==2){
                cout<<"还剩1秒"<<endl;
                n=3;
        }
        else if(time(0)-t>interval) {
            cout<<"很遗憾，未能在规定时间内猜出正确数字，该数字为"<<rand_num<<endl;
            flag=1;
        }
        else{

        }
        if(flag) break;
    }
}
void Manager::run(){
    while(1){
        char flag='n';
        init();
        guess();
        cout<<"还要继续游玩吗？y/n"<<endl;
        cin>>flag;
        if(flag=='n'){
            cout<<"感谢游玩"<<endl;
            break;
        }
    }
}
int main(){
    Manager magr;
    magr.menu();
    magr.run();
    return 0;
}
