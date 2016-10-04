/*
 * 表达式求值
 * 核心思想：
 *      严蔚敏《数据结构》P52
 *      利用两个栈结构:
 *              1. OPTR:寄存运算符
 *              2. OPND:寄存操作数
 *      遍历表达式:
 *              1. 如果是操作数，直接入栈(OPND)
 *              2. 如果是运算符，就要与栈顶元素（OPTR）做比较：
 *                                          1）  栈顶运算符>当前运算符:计算
 *                                          2）  栈顶运算符<当前运算符:当前运算符压栈
 *                                          3)   栈顶运算符=当前运算符:脱括号
 *
 */

#include <iostream>
#include <unordered_map>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

void initOptTable(unordered_map<char,unordered_map<char,char> > & optTable)
{
    optTable['+']['+'] = '>';
    optTable['+']['-'] = '>';
    optTable['+']['*'] = '<';
    optTable['+']['/'] = '<';
    optTable['+']['('] = '<';
    optTable['+'][')'] = '>';
    optTable['+']['#'] = '>';


    optTable['-']['+'] = '>';
    optTable['-']['-'] = '>';
    optTable['-']['*'] = '<';
    optTable['-']['/'] = '<';
    optTable['-']['('] = '<';
    optTable['-'][')'] = '>';
    optTable['-']['#'] = '>';


    optTable['*']['+'] = '>';
    optTable['*']['-'] = '>';
    optTable['*']['*'] = '>';
    optTable['*']['/'] = '>';
    optTable['*']['('] = '<';
    optTable['*'][')'] = '>';
    optTable['*']['#'] = '>';


    optTable['/']['+'] = '>';
    optTable['/']['-'] = '>';
    optTable['/']['*'] = '>';
    optTable['/']['/'] = '>';
    optTable['/']['('] = '<';
    optTable['/'][')'] = '>';
    optTable['/']['#'] = '>';


    optTable['(']['+'] = '<';
    optTable['(']['-'] = '<';
    optTable['(']['*'] = '<';
    optTable['(']['/'] = '<';
    optTable['(']['('] = '<';
    optTable['('][')'] = '=';
    //optTable['(']['#'] = '>';//错误情况


    optTable[')']['+'] = '>';
    optTable[')']['-'] = '>';
    optTable[')']['*'] = '>';
    optTable[')']['/'] = '>';
    //optTable[')']['('] = '<';//错误情况
    optTable[')'][')'] = '>';
    optTable[')']['#'] = '>';


    optTable['#']['+'] = '<';
    optTable['#']['-'] = '<';
    optTable['#']['*'] = '<';
    optTable['#']['/'] = '<';
    optTable['#']['('] = '<';
    //optTable['#'][')'] = '<';//错误情况
    optTable['#']['#'] = '=';
}

int operate(char opt,int a,int b)
{
    int ans = 0;
    switch (opt)
    {
        case '+':
            ans = a+b;
            break;
        case '-':
            ans =a-b;
            break;
        case '*':
            ans =a*b;
            break;
        case '/':
            ans =a/b;
            break;
     //   case '(':
     //       break;
     //   case ')':
     //       break;
     //   case '#':
     //       break;
    }
    return ans;
}

int EvaluateExpression(vector<string> & expr,unordered_map<char,unordered_map<char,char> > & optTable)
{
    expr.push_back("#");
    stack<char> OPTR;//存放算符
    OPTR.push('#');
    stack<int> OPND;//存放操作数
    for(int i =0;i<expr.size();)
    {
        stringstream ss(expr[i]);
        if(expr[i].size()>1)//一定是操作数
        {
            int data;
            ss>>data;
            OPND.push(data);
            ++i;
            continue;
        }
        char OP;
        ss>>OP;
        if(!optTable.count(OP))//操作数
        {
            OPND.push(OP-'0');
            ++i;
            continue;
        }
        //算符
        assert(OPTR.size()>=1);
        assert(optTable[OPTR.top()].count(OP));
        int a,b;
        switch (optTable[OPTR.top()][OP])
        {
            case '>'://退栈并将运算结果入栈
                assert(OPND.size()>=2);
                b = OPND.top();
                OPND.pop();
                a = OPND.top();
                OPND.pop();
                OPND.push(operate(OPTR.top(),a,b));
                OPTR.pop();
                //++i;//这里不能++i
                break;
            case '<'://栈顶元素优先级低
                OPTR.push(OP);
                ++i;
                break;
            case '='://脱括号并接受下一个字符
                OPTR.pop();
                ++i;
                break;
        }
    }
    assert(OPND.size()==1);
    return OPND.top();
}

int main() {
    //输入请以空格隔开 例如： 3 * ( 7 - 2 )
    unordered_map<char,unordered_map<char,char> > optTable;//存放算符优先级关系
    initOptTable(optTable);
    vector<string> expr;
    string str_line;
    getline(cin,str_line);
    stringstream ss0(str_line);
    while(ss0>>str_line) expr.push_back(str_line);
    int result = EvaluateExpression(expr,optTable);
    cout<<result<<endl;
    return 0;
}