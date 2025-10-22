#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
public:
    Rectangle(double l=0, double w=0):length(l),width(w){}
    double area()const{
        return length * width;
    }
    void display()const{
        cout<<"长："<<length<<"宽："<<width<<"面积："<<area()<<endl;
    }
    Rectangle operator>(const Rectangle&other)const{
        if (this->area()>other.area()){
            return *this;
        }else{
            return other;
        }
    }
};

int main(){
    double l1, w1, l2, w2;
    cin>>l1>>w1>>l2>>w2;
    Rectangle r1(l1,w1);
    Rectangle r2(l2,w2);
    Rectangle larger=r1>r2;
    cout<<larger.area()<<endl;
    larger.display();
    return 0;
}