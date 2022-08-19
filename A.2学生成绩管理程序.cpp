#include<iostream>
#include<string>
#include <iomanip>
#include<vector>
#include<fstream>
using namespace std;
class Student{
public:
    string Sno;//学号
    string Sname;//姓名
    int Math_Score;//数学成绩
    int Chinese_Score;//语文成绩
    int English_Score;//英语成绩
    int sum;//总分
public:
    Student(string Sno,string Sname,int Math_Score=0,int Chinese_Score=0,int English_Score=0){
        this->Sno=Sno;
        this->Sname=Sname;
        this->Math_Score=Math_Score;
        this->Chinese_Score=Chinese_Score;
        this->English_Score=English_Score;
        this->sum=Math_Score+Chinese_Score+English_Score;
        }
};
class Manager{
private:
    vector<Student> stus;//定义全体学生
public:
    Manager(vector<Student> stu);//重写构造函数
    void showMenu(); //显示输出菜单
    void create_stu();//1.创建
    void addGrade(); //2.添加
    void average_sumary(); //3.汇总
    void orderBySum();  //4.排序
    void findStu();     //5.查询
    void show_all();    //6.显示
    void file_in();   //7.文件导入
    void file_out();  //8.文件导出
};
Manager::Manager(vector<Student> stu):stus(stu){};
void Manager::showMenu(){
    printf("学生成绩管理系统：\n");
    printf("       1创建\n");
    printf("       2添加\n");
    printf("       3汇总\n");
    printf("       4排序\n");
    printf("       5查询\n");
    printf("       6显示\n");
    printf("       7文件导入\n");
    printf("       8文件导出\n");
    printf("       9退出\n");
}
void Manager::create_stu(){
    while(true){
            string Sno,Sname;
            int Math,Chinese,English;
            int n=stus.size();
        while(true){
            cout<<"请输入要添加的学生学号，姓名，数学成绩，语文成绩，英语成绩"<<endl;
            cin>>Sno>>Sname>>Math>>Chinese>>English;
            if(Math>=0&&Math<=100&&Chinese>=0&&Chinese<=100&&English>=0&&English<=100){
                //    cout<<Sno<<" "<<Sname<<" "<<Math<<" "<<Chinese<<" "<<English<<endl;
                int flag=0;
                for(int i=0;i<n;i++){
                    if(!stus[i].Sno.compare(Sno)){
                        flag=1;
                        cout<<"该学生已经存在"<<endl;
                        break;
                    }
                }
                if(!flag) break;
            }
            else{
                cout<<"成绩要位与0到100之间"<<endl;
            }

        }
        Student stu(Sno,Sname,Math,Chinese,English);
        cout<<"选择插入位置（指定位置插入：1 ||插入到最后：0）"<<endl;
        int mark;
        cin>>mark;
        if(mark==0)stus.push_back(stu);
        else{
            int pos;
            while(1){
                cout<<"请输入插入位置（从0开始）"<<endl;
                cin>>pos;
                if(pos>=0&&pos<=stus.size())break;
            }
            stus.insert(stus.begin()+pos,stu);
        }
        cout<<"结果为"<<endl;
        printf("学号   姓名    数学成绩    语文成绩    英语成绩\n");
        cout<<stu.Sno<<setw(8)<<stu.Sname<<setw(9)<<stu.Math_Score<<setw(12)<<stu.Chinese_Score<<setw(12)<<stu.English_Score<<endl;
        cout<<"是否还要继续添加？y/n"<<endl;
        char flag='n';
        cin>>flag;
        if(flag=='n'){
            break;
        }
    }

}
void Manager::addGrade(){
    if(stus.empty()){
        cout<<"无数据"<<endl;
    }
    else{
        while (1){
        int pos;
        while(1){
            string sno;
            cout<<"输入要添加成绩的学生学号"<<endl;
            cin>>sno;
            int n=stus.size(),flag=0;
            for(int i=0;i<n;i++){
                if(!sno.compare(stus[i].Sno)){
                        pos=i;
                        flag=1;
                        break;
                }
            }
            if(!flag){
                cout<<"未找到该学生,请检查输入的学号"<<endl;
            }
            else{
                break;
            }
        }
        cout<<"请输入数学成绩：";
        cin>>stus[pos].Math_Score;
        cout<<"请输入语文成绩：";
        cin>>stus[pos].Chinese_Score;
        cout<<"请输入英语成绩：";
        cin>>stus[pos].English_Score;
        cout<<"结果为"<<endl;
        printf("学号   姓名    数学成绩    语文成绩    英语成绩\n");
        cout<<stus[pos].Sno<<setw(8)<<stus[pos].Sname<<setw(9)<<stus[pos].Math_Score<<setw(12)<<stus[pos].Chinese_Score<<setw(12)<<stus[pos].English_Score<<endl;
        stus[pos].sum=stus[pos].Math_Score+stus[pos].Chinese_Score+stus[pos].English_Score;
        cout<<"是否要继续添加学生成绩？y/n"<<endl;
        char flag2='n';
        cin>>flag2;
        if(flag2=='n'){
            break;
        }
      }
    }
}
void Manager::average_sumary(){
    if(stus.empty()){
        cout<<"无数据"<<endl;
    }
    else{
        int sum=0;
        float average=0.0;
        int n=stus.size();
        printf("学号   姓名    总分    平均分\n");
        for(int i=0;i<n;i++){
            sum=stus[i].Math_Score+stus[i].Chinese_Score+stus[i].English_Score;
            average=sum/3;
            cout<<stus[i].Sno<<setw(8)<<stus[i].Sname<<setw(7)<<sum<<setw(10)<<fixed<<setprecision(2)<<average<<endl;
        }
    }
}
void Manager::orderBySum(){
     if(stus.empty()){
        cout<<"无数据"<<endl;
    }
    else{
        int n=stus.size();
        int sum[n];
        for(int i=0;i<n;i++){
            stus[i].sum=stus[i].Math_Score+stus[i].Chinese_Score+stus[i].English_Score;
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<n-i;j++){
                if(stus[j].sum<stus[j+1].sum){
                    swap(stus[j],stus[j+1]);
                }
            }
        }
        cout<<"按成绩降序排列如下"<<endl;
        show_all();
    }
}
void Manager::findStu(){
     if(stus.empty()){
        cout<<"无数据"<<endl;
    }
    else{
        while(1){
                string sno;
                int pos;
                cout<<"请输入要查询的学生学号"<<endl;
                cin>>sno;
                int n=stus.size(),flag=0;
                for(int i=0;i<n;i++){
                    if(!sno.compare(stus[i].Sno)){
                            pos=i;
                            flag=1;
                            break;
                    }
                }
                if(!flag){
                    cout<<"未找到该学生,请检查输入的学号"<<endl;
                }
                else{
                    cout<<"结果为"<<endl;
                    printf("学号   姓名    数学成绩    语文成绩    英语成绩\n");
                    cout<<stus[pos].Sno<<setw(8)<<stus[pos].Sname<<setw(9)<<stus[pos].Math_Score<<setw(12)<<stus[pos].Chinese_Score<<setw(12)<<stus[pos].English_Score<<endl;
                }
                cout<<"是否要继续查找？y/n"<<endl;
                char flag2='n';
                cin>>flag2;
                if(flag2=='n'){
                    break;
                }
            }
    }
}
void Manager::show_all(){
    if(stus.empty()){
        cout<<"还未导入数据"<<endl;
    }
    else{
        printf("学号   姓名    数学成绩    语文成绩    英语成绩\n");
        int n=stus.size();
    //    cout<<stus[0].Sname;
        for(int i=0;i<n;i++){
            cout<<stus[i].Sno<<setw(8)<<stus[i].Sname<<setw(9)<<stus[i].Math_Score<<setw(12)<<stus[i].Chinese_Score<<setw(12)<<stus[i].English_Score<<endl;
        }
    }
}
void Manager::file_in(){
    void Stringsplit(const string& str, const char split, vector<string>& res);
    ifstream ifs;
    ifs.open("A2.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
    string buf;
	while (getline(ifs, buf))
	{
		vector<string> data;
        Stringsplit(buf,' ', data);
        Student stu(data[0],data[1],atoi(data[2].c_str()),atoi(data[3].c_str()),atoi(data[4].c_str()));
        stus.push_back(stu);
    }
    cout<<"文件导入成功"<<endl;
}
void Manager::file_out(){
    ofstream ofs;
    ofs.open("A2.txt", ios::out);
    int n=stus.size();
    for(int i=0;i<n;i++){
        ofs<<stus[i].Sno<<" "<<stus[i].Sname<<" "<<stus[i].Math_Score<<" "<<stus[i].Chinese_Score<<" "<<stus[i].English_Score<<endl;
    }
    ofs.close();
    cout<<"文件导出成功"<<endl;
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
//    Student stu1("123","张三",1,80,90);
//    Student stu2("124","李四",80,80,100);
//    Student stu3("125","王五",80,80,90);
//    vector<Student> stus={stu1,stu2,stu3};
vector<Student> stus;
    Manager magr(stus);
//    cout<<magr.stus[0].Sname;
    char choice;
    while(1){
        magr.showMenu();
        cout<<"主菜单:请选择"<<endl;
        cin>>choice;
        if(choice=='1'){
            magr.create_stu();
        }
        else if(choice=='2'){
            magr.addGrade();
        }
        else if(choice=='3'){
            magr.average_sumary();
        }
        else if(choice=='4'){
            magr.orderBySum();
        }
        else if(choice=='5'){
            magr.findStu();
        }
        else if(choice=='6'){
            magr.show_all();
        }
        else if(choice=='7'){
            magr.file_in();
        }
        else if(choice=='8'){
            magr.file_out();
        }
        else if(choice=='9'){
            cout<<"已退出";
            break;
        }
        else{
            cout<<"输入有误，请重新输入"<<endl;
        }
    }
    return 0;
}
