#include "bits/stdc++.h"
#define MAX  256
#define CMAP map<char,int>
#define IMAP map<int ,int>
using namespace std;

IMAP good;
CMAP bad;
IMAP cmt;

void setbad(string& s )
{
    for(int i = 0 ; i< s.length(); i++)
    {
        bad[s[i]] = i;
    }
}

void setCurrentMatchTail(string& s)
{
    int m = s.length();
    cmt[m-1] = m;
    for(int i = m - 2;i>=0;i--)
    {
        int q = i;
        while(s[i-(i-q)]==s[m-1-(i-q)])
            q--;
        cmt[i] = i-q;
    }
}

void setgood(string& s)
{
     setCurrentMatchTail(s);
    //第三种情况
    for(int i = 0 ; i<s.length(); i++ )
            good[i] = s.length();
    //第二种情况
    for(int i = s.length()-1; i>=0;i--)
    {
        if(cmt[i] == i+1)
        {
           for(int j=i;j<s.length()-cmt[i];j++)
           {
                if(good[j]==s.length())
                    good[j] = s.length()-1-i;
           }   
        }
    }
    //第三种情况
    for(int i = 0 ; i< s.length();i++)
        good[s.length()-1-cmt[i]] = s.length()-1-i;
}

int BMFind(string& src,string& match)
{
    setgood(match);
   setbad(match);
    int i = 0;
    int cnt = 0;
    while(src.length()>i)
    {
        int j = match.length()-1;
        while(src[i+j]==match[j])
            j--;
        //if(j<0)break;
        if(j<0)
        {
        	cout<<"第"<<(cnt+1)<<"个位置在: "<<i<<endl;
        	i++;
        	cnt++;
        	continue;
        }
        int l1 = good[j];
        int l2 = j-bad[src[i+j]];
        if(l1>l2)
            i=i+l1;
        else
            i=i+l2;
    }
    return cnt;
}
int main()
{
    cout<<"请输入源字符串："<<endl;
    string src;
    cin>>src;
    cout<<"请输入要匹配的字符串："<<endl;
    string match;
    cin>>match;
    if(src.length()<match.length())
    {
        cout<< "长度都不够，好意思来匹配啊"<<endl;
        return 0;
    }
    int flag = BMFind(src,match);
    if(flag>0)
        cout<<"一共找到了"<<flag<<"个。"<<endl;
    else
        cout<<"木有 木有 ～～"<<endl;
    return 0;
}
