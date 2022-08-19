#include<iostream>
#include<cmath>
using namespace std;
class dot{
public:
    float x;//横坐标
    float y;//纵坐标
    float z;//竖坐标
    dot(float x=0,float y=0,float z=0):x(x),y(y),z(z){};//重写构造函数
    void to_string(){//将点转换为字符串输出
        cout<<"("<<x<<","<<y<<","<<z<<")";
    };
};
class Vector{
public:
    float xx;//横坐标
    float yy;//纵坐标
    float zz;//竖坐标
    Vector(float x=0,float y=0,float z=0):xx(x),yy(y),zz(z){};//重写构造函数
    void to_string(){
        cout<<"("<<xx<<","<<yy<<","<<zz<<")";
    };
};
class plane{//采用一般式表示 Ax+By+Cz+D=0
public:
    float a;
    float b;
    float c;
    float d;
    void to_string();//将平面转换为字符串输出
    plane(float a,float b,float c,float d):a(a),b(b),c(c),d(d){};//直接传参构造
    plane(dot a,dot b,dot c);//三个不共线的点构造一个平面
    plane(dot a,Vector n);//一个点和法向量构造一个平面
    Vector vec();//求单位法向量
};
Vector plane::vec(){
    Vector n;
    float sum=sqrt(pow(a,2)+pow(b,2)+pow(c,2));
    n.xx=a/sum;
    n.yy=b/sum;
    n.zz=c/sum;
    return n;
}
void plane::to_string(){
    cout<<"("<<a<<")x+("<<b<<")y+("<<c<<")z+("<<d<<")=0";
}
plane::plane(dot A,dot B,dot C){
    int judge(dot,dot,dot);
    if(!judge(A,B,C)){
        Vector AB,AC,n;
        AB.xx=B.x-A.x;
        AB.yy=B.y-A.y;
        AB.zz=B.z-A.z;
        AC.xx=C.x-A.x;
        AC.yy=C.y-A.y;
        AC.zz=C.z-A.z;
        n.xx=AB.yy*AC.zz-AC.yy*AB.zz;
        n.yy=AC.xx*AB.zz-AB.xx*AC.zz;
        n.zz=AB.xx*AC.yy-AC.xx*AB.yy;
        a=n.xx;
        b=n.yy;
        c=n.zz;
        d=-(A.x*a+A.y*b+A.z*c);
        if(d==-0) d=0;
    }
    else{
        cout<<"三点中至少有两点共线";
    }
}
plane::plane(dot A,Vector n){
    a=n.xx;
    b=n.yy;
    c=n.zz;
    d=-(A.x*a+A.y*b+A.z*c);
    if(d==-0) d=0;
}
class line{//采用点向式表示 (x-x0)/m=(y-y0)/n=(z-z0)/p
public:
    float a;//m
    float b;//n
    float c;//p
    dot X;//(x0,y0,z0)
public:
    line(float a,float b,float c,dot X):a(a),b(b),c(c),X(X){};//直接传参构造
    line(dot A,dot B);//两点构造一条直线
    line(plane A,plane B);//两平面构造一条直线
    void to_string();//将直线转换为字符串输出
    Vector vec();//求单位方向向量
};
Vector line::vec(){
    Vector n;
    float sum=sqrt(pow(a,2)+pow(b,2)+pow(c,2));
    n.xx=a/sum;
    n.yy=b/sum;
    n.zz=c/sum;
    return n;
}
void line::to_string(){
    if(X.x>=0)cout<<"(x-"<<X.x<<")/"<<a;
    else if(X.x<0)cout<<"(x+"<<-X.x<<")/"<<a;;

    if(X.y>=0)cout<<"=(y-"<<X.y<<")/"<<b;
    else if(X.y<0)cout<<"=(y+"<<-X.y<<")/"<<b;

    if(X.z>=0)cout<<"=(z-"<<X.z<<")/"<<c;
    else if(X.z<0)cout<<"=(z+"<<-X.z<<")/"<<c;
}
line::line(dot A,dot B){
    a=B.x-A.x;
    b=B.y-A.y;
    c=B.z-A.z;
    X=A;
}
line::line(plane A,plane B){
    int judge(plane,plane);
    if(!judge(A,B)){
        a=A.b*B.c-B.b*A.c;
        b=A.c*B.a-B.c*A.a;
        c=A.a*B.b-B.a*A.b;
        float x,y,z;
        int flag[3];
        if(a==0){
            x=0;
            flag[0]=1;
        }
        if(b==0){
            y=0;
            flag[1]=1;
        }
        if(c==0){
            z=0;
            flag[2]=1;
        }
        if(flag[0]!=1){
            if(A.a==0) x=1;
            else x=-(A.d/(A.a+A.b*b/a+A.c*c/a));
        }
        if(flag[1]!=1){
            if(A.b==0) y=1;
            else y=-(A.d/(A.a*a/b+A.b+A.c*b/c));
        }
        if(flag[2]!=1){
            if(A.c==0) z=1;
            else z=-(A.d/(A.a*c/a+A.b*c/b+A.c));
        }
        X.x=x;
        X.y=y;
        X.z=z;
    }
    else{
        cout<<"两平面无交线";
    }
}
float distance(dot a,dot b){
    float d;
    d=sqrt(pow((a.x-b.x),2)+pow((a.y-b.y),2)+pow((a.z-b.z),2));
    return d;
}
float distance(dot A,line L){
    float x,y,z;
    if(L.a!=0){
        x=A.x;
        y=(x-L.X.x)/L.a*L.b+L.X.y;
        z=(x-L.X.x)/L.a*L.c+L.X.z;
    }
    else if(L.b!=0){
        y=A.y;
        x=L.X.x;
        z=(y-L.X.y)/L.b*L.c+L.X.z;
    }
    else{
        x=L.X.x;
        y=L.X.y;
        z=A.z;
    }
    float d1=sqrt(pow(x-A.x,2)+pow(y-A.y,2)+pow(z-A.z,2));
    float d2=sqrt(pow(x-L.X.x,2)+pow(y-L.X.y,2)+pow(z-L.X.z,2));
    Vector n,m;
    n.xx=A.x-x;
    n.yy=A.y-y;
    n.zz=A.z-z;
    m.xx=L.X.x-x;
    m.yy=L.X.y-y;
    m.zz=L.X.z-z;
    float sum=n.xx*m.xx+n.yy*m.yy+n.zz*m.zz;
    float cos=sum/(d1*d2);
    float d3=d1*sqrt(1-pow(cos,2));
    return d3;
}
float distance(dot A,plane P){
    float d=abs(P.a*A.x+P.b*A.y+P.c*A.z+P.d)/sqrt(pow(P.a,2)+pow(P.b,2)+pow(P.c,2));
    return d;
}
//1表示三点共线，0表示不共线
int judge(dot A,dot B,dot C){
    float a1=B.x-A.x;
    float b1=B.y-A.y;
    float c1=B.z-A.z;
    float a2=C.x-B.x;
    float b2=C.y-B.y;
    float c2=C.z-B.z;
    if(a1/a2==b1/b2&&b1/b2==c1/c2) return 1;
    else return 0;
}
//1代表点在线上，0代表点在线外
int judge(dot A,line L){
    float p[3];
    int flag[3];
    if(L.a!=0){
        p[0]=(A.x-L.X.x)/L.a;
        flag[0]=1;
    }
    if(L.b!=0){
        p[1]=(A.y-L.X.y)/L.b;
        flag[1]=1;
    }
    if(L.c!=0){
        p[2]=(A.z-L.X.z)/L.c;
        flag[2]=1;
    }
    float k;
    for(int i=0;i<3;i++){
        if(flag[i]==1){
            k=p[i];
            break;
        }
    }
    if(flag[0]!=1){
        if(A.x==0)p[0]=k;
        else return 0;
    }
    if(flag[1]!=1){
        if(A.y==0)p[1]=k;
        else return 0;
    }
    if(flag[2]!=1){
        if(A.z==0)p[2]=k;
        else return 0;
    }
    if(p[0]==p[1]&&p[1]==p[2])return 1;
    else return 0;
}
//1代表两直线平行，0代表两直线相交
int judge(line A,line B){
    if(A.a/B.a==A.b/B.b&&A.b/B.b==A.c/B.c) return 1;
    else return 0;
}
//1代表点在面上 0代表点在面外
int judge(dot A,plane P){
    if(A.x*P.a+A.y*P.b+A.z*P.c+P.d==0) return 1;
    else return 0;
}
//1代表线和面平行，0代表线和面相交
int judge(line L,plane P){
    if(L.a*P.a+L.b*P.b+L.c*P.c==0)return 1;
    else return 0;
}
//1代表两平面平行，0代表两平面相交
int judge(plane P1,plane P2){
    if(P1.a/P2.a==P1.b/P2.b&&P1.b/P2.b==P1.c/P2.c) return 1;
    else return 0;
}
int main(){
    //线
    cout<<"创建两个点"<<endl;
    dot A(1,0,0),B(0,1,0);
    A.to_string();
    B.to_string();
    cout<<endl;
    cout<<"由这两个点构成的线为";
    line L1(A,B);
    L1.to_string();
    cout<<endl;
    cout<<"其方向向量为";
    L1.vec().to_string();
    cout<<endl;
    cout<<"点";
    dot C(0,0,1);
    C.to_string();
    cout<<"到该线的距离为"<<distance(C,L1)<<endl;
    cout<<"由两个面";
    plane P2(0,0,1,0),P3(0,1,0,0);
    P2.to_string();
    cout<<",";
    P3.to_string();
    cout<<"确定的直线为";
    line L2(P2,P3);
    L2.to_string();
    cout<<endl;
    //面
    cout<<"由点";
    A.to_string();
    B.to_string();
    C.to_string();
    cout<<"确定的面为";
    plane P1(A,B,C);
    P1.to_string();
    cout<<endl;
    cout<<"其法向量为";
    P1.vec().to_string();
    cout<<endl;
    cout<<"由点";
    A.to_string();
    cout<<"和法向量";
    Vector m(0,0,1);
    m.to_string();
    cout<<"确定的面为";
    plane P4(A,m);
    P4.to_string();
    cout<<"\n点";
    C.to_string();
    cout<<"到面";
    P4.to_string();
    cout<<"的距离为"<<distance(C,P4);

    return 0;
}
