#include <iostream>
#include<ctime>
#include <iomanip>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
class Ticket{
public:
    string Tno;//车次号
    string Time;//发车时间
    string source;//始发站
    string destination;//终点站
    float run_time;//运行时间
    int capacity;//载客量
    int soldTicket;//已售车票
};
class SystemManager{
private:
    Ticket tickets[1000];//定义车次类
    int total;//现有车次总数
public:
    SystemManager();//重写构造函数，对各个变量进行初始化
    void showMenu();//展示系统菜单
    void add_ticket();//添加车次信息
    void show_all();//浏览车次信息
    void title();//用于展示表头
    void show_ticket(Ticket);//展示车次信息
    void find_ticket();//查询车票信息
    void sell_ticket();//售票
    void return_ticket();//退票
    void file_in();//文件的导入
    void file_out();//文件导出
};
SystemManager::SystemManager(){
    total=0;
}
//判断是否超时
bool is_time_out(string tim){
        time_t rawtime;
        struct tm *ptminfo;
        time(&rawtime);
        ptminfo = localtime(&rawtime);
//        ptminfo->tm_hour, ptminfo->tm_min;
        int pos=tim.find(":");
        string H=tim.substr(0,pos);
        string M=tim.substr(pos+1);
        int h=atoi(H.c_str());
        int m=atoi(M.c_str());
        if(h>ptminfo->tm_hour) return false;
        else if(h==ptminfo->tm_hour){
            if(m>=ptminfo->tm_min)return false;
            else return true;
        }
        else return true;
}

void SystemManager::showMenu(){
    cout<<"~~~~~欢迎使用车票管理系统！~~~~~"<<endl;
    cout<<"    ====================="<<endl;
    cout<<"        1.录入车票信息"<<endl;
    cout<<"        2.浏览车票信息"<<endl;
    cout<<"        3.查询车票信息"<<endl;
    cout<<"        4.售票"<<endl;
    cout<<"        5.退票"<<endl;
    cout<<"        6.退出系统"<<endl;
    cout<<"     请选择";
}
void SystemManager::add_ticket(){
    cout<<"请选择录入方式(文件导入：0 || 手动输入：1)"<<endl;
    int type;
    cin>>type;
    if(type==1){
        while(1){
            cout<<"请输入车次号:";
            cin>>tickets[total].Tno;
            cout<<"请输入发车时间:";
            cin>>tickets[total].Time;
            cout<<"请输入起始站:";
            cin>>tickets[total].source;
            cout<<"请输入终点站:";
            cin>>tickets[total].destination;
            cout<<"请输入行车时间:";
            cin>>tickets[total].run_time;
            cout<<"请输入载客量:";
            cin>>tickets[total].capacity;
            cout<<"请输入已售车票:";
            cin>>tickets[total].soldTicket;
            total++;
            cout<<"添加成功\n是否还要添加？y/n：";
            char flag;
            cin>>flag;
            if(flag=='n') break;
        }
        file_out();
    }
    else{
        file_in();
    }

}
void SystemManager::title(){
    cout<<"车次号  发车时间      起始站  终点站  行车时间  载客量  已售车票"<<endl;
}
void SystemManager::show_ticket(Ticket t){
    cout<<setw(4)<<t.Tno;
        if(is_time_out(t.Time)){
            cout<<setw(14)<<"此班已发出";
            cout<<setw(10)<<t.source;
        }
        else{
            cout<<setw(10)<<t.Time;
            cout<<setw(14)<<t.source;
        }
        cout<<setw(8)<<t.destination<<setw(8)<<t.run_time<<setw(10)<<t.capacity<<setw(10)<<t.soldTicket<<endl;
}
void SystemManager::show_all(){
    title();
    for(int i=0;i<total;i++){
        show_ticket(tickets[i]);
    }
}
void SystemManager::find_ticket(){
    cout<<"请选择查询方式（按车次号：0 ||按终点站：1）"<<endl;
    int flag;
    cin>>flag;
    while(1){
         if(flag){
            cout<<"请输入终点站:";
            string desti;
            cin>>desti;
            title();
            for(int i=0;i<total;i++){
                if(!tickets[i].destination.compare(desti)){
                    show_ticket(tickets[i]);
                }
            }
        }
        else{
            cout<<"请输入车次号：";
            string no;
            cin>>no;
            title();
            for(int i=0;i<total;i++){
                if(!tickets[i].Tno.compare(no)){
                    show_ticket(tickets[i]);
                }
            }
        }
        cout<<"是否还要继续查询？y/n:";
        char mark;
        cin>>mark;
        if(mark=='n')break;
    }

}
void SystemManager::sell_ticket(){
    title();
    for(int i=0;i<total;i++){
        if(!is_time_out(tickets[i].Time)){
            show_ticket(tickets[i]);
        }
    }
    while(1){
        cout<<"请选择要买票的车次:";
        int flag=0;
        string no;
        cin>>no;
        int i;
        for(i=0;i<total;i++){
            if(!tickets[i].Tno.compare(no)){
                flag=1;
                break;
            }
        }
        if(!flag){
            cout<<"请输入正确的车次"<<endl;
        }
        else{
            if(is_time_out(tickets[i].Time)){
                cout<<"该车已出发，无法购票"<<endl;
            }
            else{
                if(tickets[i].capacity>tickets[i].soldTicket){
                    tickets[i].soldTicket++;
                    cout<<"购票成功\n结果如下"<<endl;
                    title();
                    show_ticket(tickets[i]);
                }
                else{
                    cout<<"该车次已经满员，无法购票"<<endl;
                }
            }
        }
        cout<<"是否还要继续购票？y/n：";
        char mark;
        cin>>mark;
        if(mark=='n')break;
    }
}
void SystemManager::return_ticket(){
    title();
    for(int i=0;i<total;i++){
        if(!is_time_out(tickets[i].Time)){
            show_ticket(tickets[i]);
        }
    }
    while(1){
        cout<<"请选择要退票的车次:";
        int flag=0;
        string no;
        cin>>no;
        int i;
        for(i=0;i<total;i++){
            if(!tickets[i].Tno.compare(no)){
                flag=1;
                break;
            }
        }
        if(!flag){
            cout<<"请输入正确的车次"<<endl;
        }
        else{
            if(is_time_out(tickets[i].Time)){
                cout<<"该车已出发，无法退票"<<endl;
            }
            else{
                if(tickets[i].soldTicket>0){
                    tickets[i].soldTicket--;
                    cout<<"退票成功\n结果如下"<<endl;
                    title();
                    show_ticket(tickets[i]);
                }
                else{
                    cout<<"操作错误，该车次已售车票为0"<<endl;
                }
            }
        }
        cout<<"是否还要继续购票？y/n：";
        char mark;
        cin>>mark;
        if(mark=='n')break;
    }
}
void SystemManager::file_in(){
    void Stringsplit(const string& str, const char split, vector<string>& res);
    ifstream ifs;
    ifs.open("A1.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
    string buf;
	while (getline(ifs, buf))
	{
		vector<string> data;
        Stringsplit(buf,'#', data);
        tickets[total].Tno=data[0];
        tickets[total].Time=data[1];
        tickets[total].source=data[2];
        tickets[total].destination=data[3];
        tickets[total].run_time=atof(data[4].c_str());
        tickets[total].capacity=atoi(data[5].c_str());
        tickets[total].soldTicket=atoi(data[6].c_str());
        total++;
    }
    cout<<"文件导入成功"<<endl;
}
void SystemManager::file_out(){
    ofstream ofs;
    ofs.open("A1.txt", ios::out);
    for(int i=0;i<total;i++){
        ofs<<tickets[i].Tno<<"#"<<tickets[i].Time<<"#"<<tickets[i].source<<"#"<<tickets[i].destination<<"#"<<tickets[i].run_time<<"#"<<tickets[i].capacity<<"#"<<tickets[i].soldTicket<<endl;
    }
    ofs.close();
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
    SystemManager magr;
    int k;
    while(1){
        magr.showMenu();
        cin>>k;
        switch(k){
            case 1:magr.add_ticket();break;
            case 2:magr.show_all();break;
            case 3:magr.find_ticket();break;
            case 4:magr.sell_ticket();break;
            case 5:magr.return_ticket();break;
            default:magr.file_out();cout<<"再见";exit(0);
        }
    }
    return 0;
}
