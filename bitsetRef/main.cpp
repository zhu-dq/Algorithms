#include <iostream>
#include <bitset>
#include <string>
using namespace std;
/*
 *  学成成绩小例子
 */
void demo1()
{
    //假设班级30个学生  用位控制学生的成绩是通过还是不通过
    unsigned  long result = 0;
    //第27位同学通过
    result  |= 1UL <<27;
    //发现第27位没有通过，修改：
    result  &= ~(1UL<<27);
    //检查27最终是否通过了
    bool status = result&(1UL<<27);
}
/*
 * bitset学习
 */
void demo2()
{
    bitset<13> b1(0xbeef);//高位被丢弃
    bitset<20> b2(0Xbeef);//高位补0
    bitset<32> b3("1100");//2 3 位为1
    string str("111000");
    bitset<32> b4(str,1,4);
    cout<<b4<<endl;
    bitset<4> b;
    b.any();//是否存在1
    b.all();//是否所有位都为1
    b.none();//是否都为0
    b.count();//1的个数
    b.size();//位长度
    b.set();//全置1
    b.reset();//全置0
    b.flip();//改变所有位的状态
}
/*
 * 二进制加减
 */
int add(int a ,int b)
{
    int pos = (a&b)<<1;
    int temp_result = a^b;
    if(pos)
        return add(temp_result,pos);
    return temp_result;
}

int sub(int a ,int b)
{
    return add(a,add(~b,1));
}
 void demo3()
 {
     int a = 5;
     int b = 3;
     int result;
     //+
     result = add(a,b);
     cout<<"a+b : "<<result<<endl;
     //-
     result = sub(a,b);
     cout<<"a-b : "<<result<<endl;


 }

int main()
{
    demo1();
    demo2();
    demo3();
    return 0;
}