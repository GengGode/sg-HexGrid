#include<iostream>
using namespace std;
class Map
{
    public:

};
class point2d
{
    public:
    int x;
    int y;
    point2d(){}
    point2d(int a,int b):x(a),y(b){}

    point2d operator+(point2d& p)
    {
        x=this->x+p.x;
        y=this->y+p.y;
        return *this;
    }
    //virtual void out()
    void out()
    {
        cout<<"| "<<x<<" , "<<y<<" |"<<endl;
    }
};
class pointhex
{
    public:
    point2d corner[6];
    public:
    void setCenter(point2d p,double r)
    {
        double xCos[] = { 0.866025, 0., -0.866025, -0.866025, 0., 0.866025 };
	    double ySin[] = { 0.5, 1., 0.5, -0.5, -1., -0.5 };
        for (int i=0;i<6;i++)
            corner[i]=point2d(ceil(r*xCos[i]), ceil(r*ySin[i]));
    }
    void out()
    {
        for (int i=0;i<6;i++)
            cout<<"    | "<<corner[i].x<<" , "<<corner[i].y<<" | <<"<<i<<endl;
    }
    private:
    int ceil(double In)
    {
        int Out=(int)In;
        //if (Out-In>=0.5)Out+=1;
        if (In>=0)
        {
            if(Out-In>=0.5)Out+=1;
        }
        else
        {
            if (In-Out>=0.5)Out-=1;
        }
        return Out;
    }
};
class Hex
{
    public:
    point2d center;//中心坐标
    pointhex corner;//顶点集
    point2d Connect[6];//相接中心坐标
    public:
    Hex(point2d p,double r)
    {
        center=p;
        corner.setCenter(p,r);
    }
    void out()
    {
        center.out();
        corner.out();
    }
    protected:
   
    

};
