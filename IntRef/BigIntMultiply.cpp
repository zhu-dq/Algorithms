/*
 *  题目：大整数相乘
 *  思路：分解成我们最原始的手算过程
 */

#include <iostream>
#include <cstring>
using namespace std;
/*
 *  大数结构
 */
typedef struct {
    int nums[3000];
    int length;
}BigInt;

/*
 * 功能：把一个整数转换成大数结构
 */
BigInt  Int2BigInt(int num)
{
    BigInt big ;
    memset(big.nums,0,sizeof(big.nums));
    big.length = 0;
    while (num)
    {
        big.nums[big.length++]=num%10;
        num = num/10;
    }
    return big;
}

/*
 * 功能：大数相乘
 */
BigInt BigIntMultiply(BigInt big1,BigInt big2)
{
    BigInt result;
    memset(result.nums,0,sizeof(result.length));
    result.length=0;
    for(int i=0;i<big1.length;++i)
        for(int j=0;j<big2.length;++j)
            result.nums[i+j]+=big1.nums[i]*big2.nums[j];//核心，先不考虑进位此位结果是多少就保存多少
    //考虑进位问题
    for(int i=0;i<big1.length+big2.length;++i)
    {
        int pos = result.nums[i]/10;
        result.nums[i]=result.nums[i]%10;
        result.nums[i+1]+=pos;
    }
    //求length
    int pos = big1.length+big2.length;
    while (pos>=0 && result.nums[pos]==0)pos--;
    result.length=pos+1;
    return result;
}

/*
 * 功能：输出大数
 */
void showBigInt(BigInt result)
{
    int pos = result.length-1;
    cout<<endl;
    while (pos>=0)cout<<result.nums[pos--];
    cout<<endl;
}


int main() {
    int num1,num2;
    BigInt big1 ,big2,result;
    cout<<"please input num1 :"<<endl;
    cin>>num1;
    cout<<"please input num2 :"<<endl;
    cin>>num2;
    big1 = Int2BigInt(num1);
    big2 = Int2BigInt(num2);
    result = BigIntMultiply(big1,big2);
    showBigInt(result);
    cout<<"ending...."<<endl;
    getchar();
    return 0;
}