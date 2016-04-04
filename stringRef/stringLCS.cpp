/*
 * 题意：寻找两个字符串的最长公共子序列。
 * 例如：s1 : 2 5 7 9 1 2
 *      s2 : 3 5 3 2 8
 *      LCS: 5 3 2
 *  思路： 动态规划，分割字符串
 *      s1 : |....sub1....|e1|
 *      s2 : |....sub2....|e2|
 *      分四种情况：
 *      1.e1是LCS的一部分，e2不是
 *      2.e1不是，e2是
 *      3.e1 e2都不是
 *      4.e1 e2 都是 => e1==e2
 *      (x-1,y-1)|(x,y-1)
 *        (x-1,y)|(x,y)
 *
 *                      |   LCS(sub1,s2)orLCS(s1,sub2)orLCS(sub1,sub2)    e1!=e2
 *      LCS(s1,s2) =    |
 *                      |   LCS(sub1,sub2)+e1                             e1==e2
 *
 *      即：
 *                      |   max(LCS(sub1,s2),LCS(s1,sub2))                  e1!=e2
 *      LCS(s1,s2) =    |
 *                      |    LCS(sub1,sub2)+e1                             e1==e2
 */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main() {

    string s1;
    cout<<"please input s1 : "<<endl;
    cin>>s1;

    cout<<"please input s2 : "<<endl;
    string s2;
    cin>>s2;

    //创建并初始化 matrix_dp
    map<int,vector<int>> matrix_dp;
    vector<int> v2(s2.size()+1,0);
    for(size_t i = 0;i<s1.size()+1;++i)
    {
        matrix_dp.insert(std::pair<int,vector<int>>(i,v2));
    }

    //动态规划
    for(size_t i = 1;i<s1.size()+1;++i)
        for(size_t j = 1;j<s2.size()+1;++j)
        {
            if(s1[i-1] ==s2[j-1])
            {
                matrix_dp[i][j]  = matrix_dp[i-1][j-1]+1;//e1 == e2
            }
            else
            {
                 matrix_dp[i][j] = max(matrix_dp[i-1][j],matrix_dp[i][j-1]);//e1!=e2
            }
        }

    cout << "LCS length : " << matrix_dp[s1.size()][s2.size()]<<endl;
    return 0;
}