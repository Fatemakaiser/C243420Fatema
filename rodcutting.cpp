#include<iostream>
using namespace std;

int main()
{
    int n;

    cout<<"Enter rod length: ";
    cin>>n;

    int price[n];

    cout<<"Enter prices:\n";
    for(int i=0;i<n;i++)
        cin>>price[i];

    int dp[n+1];
    dp[0]=0;

    for(int i=1;i<=n;i++)
    {
        int mx=-1;

        for(int j=0;j<i;j++)
        {
            mx=max(mx,price[j]+dp[i-j-1]);
        }

        dp[i]=mx;
    }

    cout<<"Maximum Profit = "<<dp[n];

    return 0;
}
