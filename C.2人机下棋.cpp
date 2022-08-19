#include<iostream>
#include<vector>
#include <windows.h>
#include<cstdlib>
using namespace std;
class com_player{
public:
    char x;//棋子
public:
    void judge(vector<vector<char>> &table);//根据棋盘布局进行判断下子位置
    void run(vector<vector<char>> &table,int count,int &flag);//电脑下棋
};
void com_player::judge(vector<vector<char>> &t){
//    cout<<"judge被调用"<<endl;
    int n=t.size();
    int score[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            score[i][j]=0;
        }
    }
    int sum_c=0,sum_m=0,sum_x=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(t[i][j]=='*'){
                for(int k=0;k<n;k++){//统计行的情况
                    if(t[i][k]==this->x)sum_c++;
                    else if(t[i][k]=='*')sum_x++;
                    else sum_m++;
                }
                if(n==3){
                    if(sum_c==2)score[i][j]+=50;
                    else if(sum_m==2)score[i][j]+=25;
                    else if(sum_c==1)score[i][j]+=10;
                    else if(sum_m==1)score[i][j]+=8;
                    else if(sum_x==2)score[i][j]+=4;
                }
                else if(n==4){
                    if(sum_c==3)score[i][j]+=50;
                    else if(sum_c==2)score[i][j]+=40;
                    else if(sum_m==3)score[i][j]+=25;
                    else if(sum_m==2)score[i][j]+=20;
                    else if(sum_c==1)score[i][j]+=10;
                    else if(sum_m==1)score[i][j]+=8;
                    else if(sum_x==2)score[i][j]+=4;
                    else if(sum_x==1)score[i][j]+=2;
                }
                else if(n==5){
                    if(sum_c==4)score[i][j]+=50;
                    else if(sum_c==3)score[i][j]+=40;
                    else if(sum_c==2)score[i][j]+=35;
                    else if(sum_c==1)score[i][j]+=25;
                    else if(sum_c==1)score[i][j]+=10;

                    else if(sum_m==4)score[i][j]+=48;
                    else if(sum_m==3)score[i][j]+=30;
                    else if(sum_m==2)score[i][j]+=15;
                    else if(sum_m==1)score[i][j]+=10;

                    else if(sum_x==4)score[i][j]+=7;
                    else if(sum_x==3)score[i][j]+=6;
                    else if(sum_x==2)score[i][j]+=4;
                    else if(sum_x==1)score[i][j]+=1;
                }
                sum_c=0;sum_m=0;sum_x=0;//清零
                for(int k=0;k<n;k++){//统计列的情况
                    if(t[k][j]==this->x)sum_c++;
                    else if(t[k][j]=='*')sum_x++;
                    else sum_m++;
                }
                if(n==3){
                    if(sum_c==2)score[i][j]+=50;
                    else if(sum_m==2)score[i][j]+=25;
                    else if(sum_c==1)score[i][j]+=10;
                    else if(sum_m==1)score[i][j]+=8;
                    else if(sum_x==2)score[i][j]+=4;
                }
                else if(n==4){
                    if(sum_c==3)score[i][j]+=50;
                    else if(sum_c==2)score[i][j]+=40;
                    else if(sum_m==3)score[i][j]+=25;
                    else if(sum_m==2)score[i][j]+=20;
                    else if(sum_c==1)score[i][j]+=10;
                    else if(sum_m==1)score[i][j]+=8;
                    else if(sum_x==2)score[i][j]+=4;
                    else if(sum_x==1)score[i][j]+=2;
                }
                else if(n==5){
                    if(sum_c==4)score[i][j]+=50;
                    else if(sum_c==3)score[i][j]+=40;
                    else if(sum_c==2)score[i][j]+=35;
                    else if(sum_c==1)score[i][j]+=25;
                    else if(sum_c==1)score[i][j]+=10;

                    else if(sum_m==4)score[i][j]+=48;
                    else if(sum_m==3)score[i][j]+=30;
                    else if(sum_m==2)score[i][j]+=15;
                    else if(sum_m==1)score[i][j]+=10;

                    else if(sum_x==4)score[i][j]+=7;
                    else if(sum_x==3)score[i][j]+=6;
                    else if(sum_x==2)score[i][j]+=4;
                    else if(sum_x==1)score[i][j]+=1;
                }
                sum_c=0;sum_m=0;sum_x=0;//清零
                if(i==j){
                      for(int k=0;k<n;k++){
                        if(t[k][k]==this->x)sum_c++;
                        else if(t[k][k]=='*')sum_x++;
                        else sum_m++;
                      }
                      if(n==3){
                        if(sum_c==2)score[i][j]+=50;
                        else if(sum_m==2)score[i][j]+=25;
                        else if(sum_c==1)score[i][j]+=10;
                        else if(sum_m==1)score[i][j]+=8;
                        else if(sum_x==2)score[i][j]+=4;
                    }
                    else if(n==4){
                        if(sum_c==3)score[i][j]+=50;
                        else if(sum_c==2)score[i][j]+=40;
                        else if(sum_m==3)score[i][j]+=25;
                        else if(sum_m==2)score[i][j]+=20;
                        else if(sum_c==1)score[i][j]+=10;
                        else if(sum_m==1)score[i][j]+=8;
                        else if(sum_x==2)score[i][j]+=4;
                        else if(sum_x==1)score[i][j]+=2;
                    }
                    else if(n==5){
                        if(sum_c==4)score[i][j]+=50;
                        else if(sum_c==3)score[i][j]+=40;
                        else if(sum_c==2)score[i][j]+=35;
                        else if(sum_c==1)score[i][j]+=25;
                        else if(sum_c==1)score[i][j]+=10;

                        else if(sum_m==4)score[i][j]+=48;
                        else if(sum_m==3)score[i][j]+=30;
                        else if(sum_m==2)score[i][j]+=15;
                        else if(sum_m==1)score[i][j]+=10;

                        else if(sum_x==4)score[i][j]+=7;
                        else if(sum_x==3)score[i][j]+=6;
                        else if(sum_x==2)score[i][j]+=4;
                        else if(sum_x==1)score[i][j]+=1;
                    }
                }
                sum_c=0;sum_m=0;sum_x=0;//清零
                if(i+j==n-1){
                    for(int k=0;k<n;k++){
                        if(t[n-k-1][k]==this->x)sum_c++;
                        else if(t[n-k-1][k]=='*')sum_x++;
                        else sum_m++;
                    }
                    if(n==3){
                        if(sum_c==2)score[i][j]+=50;
                        else if(sum_m==2)score[i][j]+=25;
                        else if(sum_c==1)score[i][j]+=10;
                        else if(sum_m==1)score[i][j]+=8;
                        else if(sum_x==2)score[i][j]+=4;
                    }
                    else if(n==4){
                        if(sum_c==3)score[i][j]+=50;
                        else if(sum_c==2)score[i][j]+=40;
                        else if(sum_m==3)score[i][j]+=25;
                        else if(sum_m==2)score[i][j]+=20;
                        else if(sum_c==1)score[i][j]+=10;
                        else if(sum_m==1)score[i][j]+=8;
                        else if(sum_x==2)score[i][j]+=4;
                        else if(sum_x==1)score[i][j]+=2;
                    }
                     else if(n==5){
                        if(sum_c==4)score[i][j]+=50;
                        else if(sum_c==3)score[i][j]+=40;
                        else if(sum_c==2)score[i][j]+=35;
                        else if(sum_c==1)score[i][j]+=25;
                        else if(sum_c==1)score[i][j]+=10;

                        else if(sum_m==4)score[i][j]+=48;
                        else if(sum_m==3)score[i][j]+=30;
                        else if(sum_m==2)score[i][j]+=15;
                        else if(sum_m==1)score[i][j]+=10;

                        else if(sum_x==4)score[i][j]+=7;
                        else if(sum_x==3)score[i][j]+=6;
                        else if(sum_x==2)score[i][j]+=4;
                        else if(sum_x==1)score[i][j]+=1;
                    }
                }
                sum_c=0;sum_m=0;sum_x=0;//清零
            }
        }
    }
    int max_x=0,max_y=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(score[max_x][max_y]<score[i][j]){
                max_x=i;
                max_y=j;
            }
        }
    }
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            cout<<score[i][j]<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<max_x<<" "<<max_y<<endl;
    t[max_x][max_y]=this->x;
}
void com_player::run(vector<vector<char>> &table,int count,int &flag){
    if(!flag){
        int i=table.size()/2;
        int j=table[0].size()/2;
        table[i][j]=this->x;
        flag=2;
    }
    else{
        judge(table);
    }
}
class mu_complayer{
public:
    char x;//棋子
public:
    void run(vector<vector<char>> &table,int n);//玩家下棋
};
void mu_complayer::run(vector<vector<char>> &table,int n){
    cout<<"请输入你下棋的坐标（左上角为（1,1）其余坐标都为正）";
    int x,y;
    while(1){
        cin>>x>>y;
        if(x>0&&x<=n&&y>0&&y<=n)break;
        cout<<"输入非法"<<endl;
    }
    while(1){
        if(table[x-1][y-1]=='*')break;
        cout<<"该位置不能放子"<<endl;
        while(1){
            cin>>x>>y;
            if(x>0&&x<=n&&y>0&&y<=n)break;
            cout<<"输入非法"<<endl;
        }
    }
    table[x-1][y-1]=this->x;
//    cout<<table[x-1][y-1];

}
class Manager{
private:
    com_player p1;//电脑玩家
    mu_complayer p2;//人类玩家
    int n;//棋盘的行列数
    vector<vector<char>> table;//棋盘
    int count1;//记录电脑下棋的步数
    int count2;//记录玩家下棋的步数
public:
    Manager();//重写构造函数
    int judge();//判断是否有获胜方
    void run();//井字棋程序的运行
    void show();//展示棋盘
};
Manager::Manager(){
    count1=0;
    count2=0;
    cout<<"欢迎来到井字棋进阶版小游戏"<<endl;
    cout<<"游戏规则：选择棋盘大小n，将n子连接成一条直线者获胜"<<endl;
    while(1){
        cout<<"请选择棋盘大小:(3<=n<=5)"<<endl;
        cin>>n;
        if(n>=0&&n<=5)break;
        cout<<"输入非法"<<endl;
    }

    for(int i=0;i<n;i++){
        vector<char>vec1;
        for(int j=0;j<n;j++){
            vec1.push_back('*');
        }
        table.push_back(vec1);
        vec1.clear();
    }
    cout<<"请选择你要使用的棋子（X O）大写";
    char x;
    cin>>x;
    p2.x=x;
//    cout<<p2.x;
    if(x=='X') p1.x='O';
    else p1.x='X';
//    cout<<p1.x;
}
void Manager::show(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<"—";
        }
        cout<<endl;
        for(int j=0;j<n;j++){
            cout<<table[i][j];
            cout<<" ";
        }
        cout<<endl;
    }
    for(int j=0;j<n;j++){
        cout<<"—";
    }
    cout<<endl;
}
int Manager::judge(){
    //返回0 代表电脑获胜 1代表玩家获胜 2代表未结束 3代表平局
    int sum_c=0,sum_m=0,sum_x=0,count=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){//统计行的情况
                if(table[i][k]==p1.x)sum_c++;
                else if(table[i][k]=='*')sum_x++;
                else sum_m++;
            }
//            cout<<"f1 sum_c"<<sum_c<<" sum_m"<<sum_m<<endl;
            if(sum_c==n) return 0;
            else if(sum_m==n)return 1;
            sum_c=0;sum_m=0;sum_x=0;//清零
            for(int k=0;k<n;k++){//统计列的情况
                if(table[k][j]==p1.x)sum_c++;
                else if(table[k][j]=='*')sum_x++;
                else sum_m++;
            }
//            cout<<"f2 sum_c"<<sum_c<<" sum_m"<<sum_m<<endl;
            if(sum_c==n) return 0;
            else if(sum_m==n)return 1;
            sum_c=0;sum_m=0;sum_x=0;//清零
            if(i==j){
                for(int k=0;k<n;k++){
                    if(table[k][k]==p1.x)sum_c++;
                    else if(table[k][k]=='*')sum_x++;
                    else sum_m++;
                }
//                cout<<"f3 sum_c"<<sum_c<<" sum_m"<<sum_m<<endl;
                if(sum_c==n) return 0;
                else if(sum_m==n)return 1;
            }
            sum_c=0;sum_m=0;sum_x=0;//清零
            if(i+j==n-1){
                for(int k=0;k<n;k++){
                    if(table[n-k-1][k]==p1.x)sum_c++;
                    else if(table[n-k-1][k]=='*')sum_x++;
                    else sum_m++;
                }
//                cout<<"f4 sum_c"<<sum_c<<" sum_m"<<sum_m<<endl;
                if(sum_c==n) return 0;
                else if(sum_m==n)return 1;
            }
            sum_c=0;sum_m=0;sum_x=0;//清零
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(table[i][j]!='*')count++;
//            else cout<<i<<","<<j<<endl;
        }
    }
//    cout<<count<<endl;
    if(count==n*n)return 3;
    return 2;
}
void Manager::run(){
    cout<<"请选择电脑先走还是玩家先走（电脑：0 || 玩家：1）";
    int flag,mark;
    cin>>flag;
//    show();
    if(flag){
        show();
        p2.run(table,n);
        count2++;
    }
    while(1){
            system("cls");
            p1.run(table,count1,flag);
            count1++;
            cout<<"电脑已走完"<<endl;
            show();
            mark=judge();
            if(mark==0||mark==1||mark==3)break;
            p2.run(table,n);
            system("cls");
            show();
            count2++;
            mark=judge();
            if(mark==0||mark==1||mark==3)break;
        }
    if(mark==0){
        cout<<"电脑共用"<<count1<<"步打败了你"<<endl;
    }
    else if(mark==1){
        cout<<"你共用"<<count2<<"步打败了电脑"<<endl;
    }
    else{
        cout<<"平局"<<endl;
    }
}
int main(){
    system("mode con cols=55 lines=30");
    Manager magr;
    magr.run();
    return 0;
}
