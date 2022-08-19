#include<iostream>
#include <ctime>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;
class dot{
public:
    float x1;//横坐标
    float x2;//纵坐标
    int y;//判断值
    dot(float x1=0,float x2=0,int y=0):x1(x1),x2(x2),y(y){};//重写构造函数
};
class NetWork{
public:
    int epoches;//训练次数
    float learning_rate;//学习率
    float w1,w2,w3,w4,w5,w6;//各个权重
    float b1,b2,b3;//b1 b2为隐含层结点，b3为输出层结点
public:
    NetWork();//重写构造函数
    float sigmoid();//激活函数
    float deriv_sigmoid();//激活函数求导
    float loss(vector<dot>A,vector<dot>B);//损失函数
    void forward(float x1,float x2);//前向传播函数
    void train(vector<dot>A);//训练函数
    int predict(float,float);//预测函数
    void add(float pre,float now);//向后调整权重
    void sub(float pre,float now);//向前调整权重
};
NetWork::NetWork(){
    cout<<"请输入训练次数:";
    cin>>epoches;
    cout<<"请输入学习率：";
    cin>>learning_rate;
    srand((unsigned)time(NULL));
    w1=rand()%1000*0.01;
    w2=rand()%1000*0.01;
    w3=rand()%1000*0.01;
    w4=rand()%1000*0.01;
    w5=rand()%1000*0.01;
    w6=rand()%1000*0.01;
}
float NetWork::sigmoid(){
    if(b3>=0)return 1;
    else return 0;
}
float NetWork::deriv_sigmoid(){
    return 0;
}
void NetWork::forward(float x1,float x2){
    b1=w1*x1+w2*x2;
    b2=w3*x1+w4*x2;
    b3=b1*w5+b2*w6;
}
float NetWork::loss(vector<dot>A,vector<dot>B){
    int n=A.size();
    float m=0;
    for(int i=0;i<n;i++){
        if(A[i].y!=B[i].y){
            m++;
        }
    }
//    cout<<"m/n="<<m/n<<endl;
    return m/n;
}
void NetWork::add(float pre,float now){
    float x=(now-pre)/0.001;
    w1-=learning_rate*x;
    w2-=learning_rate*x;
    w3-=learning_rate*x;
    w4-=learning_rate*x;
    w5-=learning_rate*x;
    w6-=learning_rate*x;
}
void NetWork::sub(float pre,float now){
    float x=(now-pre)/0.001;
    w1+=learning_rate*x;
    w2+=learning_rate*x;
    w3+=learning_rate*x;
    w4+=learning_rate*x;
    w5+=learning_rate*x;
    w6+=learning_rate*x;
}
void NetWork::train(vector<dot>A){
    int n=A.size();
    float pre=1;
    float now;
    for(int j=0;j<epoches;j++){
        vector<dot>B;
       for(int i=0;i<n;i++){
        forward(A[i].x1,A[i].x2);
        int y=sigmoid();
//        cout<<y<<endl;
        dot c(A[i].x1,A[i].x2,y);
        B.push_back(c);
        }
        now=loss(A,B);
//        cout<<"loss:"<<now<<endl;
        if(pre<=now)break;
        add(pre,now);
        pre=now;
    }
    sub(pre,now);
    cout<<"loss:"<<now<<endl;
}
int NetWork::predict(float x1,float x2){
    forward(x1,x2);
    return sigmoid();
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
    vector<dot> A;
    ifstream ifs;
    ifs.open("B2.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return 0;
	}
    string buf;
	while (getline(ifs, buf))
	{
		vector<string> data;
        Stringsplit(buf,',', data);
        dot c(atof(data[0].c_str()),atof(data[1].c_str()),atoi(data[2].c_str()));
        A.push_back(c);
    }
//    for(int i=0;i<A.size();i++){
//        cout<<A[i].y<<endl;
//    }
    NetWork nw;
    cout<<"初始权重w1:"<<nw.w1<<" w2:"<<nw.w2<<" w3:"<<nw.w3<<" w4:"<<nw.w4<<" w5:"<<nw.w5<<" w6:"<<nw.w6<<endl;
    nw.train(A);
    cout<<"学习后权重w1:"<<nw.w1<<" w2:"<<nw.w2<<" w3:"<<nw.w3<<" w4:"<<nw.w4<<" w5:"<<nw.w5<<" w6:"<<nw.w6<<endl;
    while(1){
         cout<<"输入想要预测的点"<<endl;
        float a,b;
        char c;
        cin>>a>>c>>b;
        cout<<"预测值为"<<nw.predict(a,b);
        cout<<"是否要继续预测？y/n";
        cin>>c;
        if(c=='n')break;
    }

    return 0;
}
