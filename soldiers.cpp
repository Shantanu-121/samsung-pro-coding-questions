/*
    each node of the tree represents a military unit. We are given the no. of soldiers in each     unit.
    we need to balance the tree such that
        all nodes belonging to the same parent node have the same subtree sum
        we can only balance by deleting some soldiers from a node 
        we should remove the minimum no. of soldiers(total)
    return the no. of soldiers total after balancing

    constraints:
        1<=N<=500
        0<=node.val<=100
        1<=depth<=100
    input form:(for each of the n nodes)
        parent index, soldiers in that unit
*/
#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define int long long
#define INT_MAX LLONG_MAX
#define INT_MIN LLONG_MIN
#define ll long long
#define F first
#define S second
#define vi vector<int>
#define pii pair<int, int>
#define getset __builtin_popcountll
#define vec vector
#define input(a)                       \
    for (int i = 0; i < a.size(); i++) \
    cin >> a[i]
#define print(a)     \
    for (auto i : a) \
    cout << i << ' '
#define all(a) a.begin(), a.end()

void f(int c,int p,vec<vi>&adj,vec<vec<bool>>&dp,vi&v)
{
    vi cld; 
    for(auto&x:adj[c])
    {
        if(x!=p)
        {
            cld.push_back(x); 
            f(x,c,adj,dp,v); 
        }
    }
    if(cld.empty())
    {
        for(int sm=0;sm<=v[c];sm++)
        {
            dp[c][sm]=1;
        }
        return;
    }
    for(int sm=0;sm<=50000;sm++)
    {
        bool flag=0; 
        for(auto&c:cld)
        {
            if(!dp[c][sm]){flag=1;break;}
        }
        if(!flag)
        {
            for(int smm=0;smm<=v[c];smm++)
            {
                dp[c][smm+sm*cld.size()]=1;
            }
        }
    }
}

void solve()
{
    int n;
    cin>>n; 
    vec<pii> a(n);
    //int res=0;
    int rt=-1;
    vec<vec<bool>>dp(n+1,vec<bool>(50001,0));

    vi v(n);
    for(int i=0;i<n;i++)
        {auto &x= a[i]; cin>>x.first>>x.second;if(x.first==-1)rt=i;v[i]=x.second;} 
    vec<vi>adj(n); 
    for(int i=0;i<n;i++)
    {
        auto x=a[i];
        if(x.first==-1)continue; 
        adj[x.first].push_back(i);
        adj[i].push_back(x.first); 
    }
    //f(rt,-1,adj,res,v); 
    int res =0 ;
    f(rt,-1,adj,dp,v); 
    for(int sm=50000;sm>=0;sm--)
    {
        if(dp[rt][sm]){res=sm;break;}
    }
    cout<<res<<'\n'; 
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //n >> t;
    for(int i=1;i<=t;i++)
        solve();
    return 0;
}
