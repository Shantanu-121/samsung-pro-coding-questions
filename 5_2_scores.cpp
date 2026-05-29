/*
Q2. 
2 arrays given
a = [1, 2, 3, 4, 5]
b = [6, 7, 8, 9, 10]
Value of an array is the total score of elements, 
and score of element is 1 if it is less than or equal to D and 2 if it is greater than D, 
Find D such that A_score - B_Score is maximum
 
constraints -
0 <= D <= 1e9
1 <= a[i] <= 1e8
1 <= b[i] <= 1e8
1 <= a.size(), b.size() <= 1e5

*/

#include <bits/stdc++.h>
using namespace std;
int maxDiffD(const vector<int> &a, const vector<int> &b)
{
    vector<int> sa = a, sb = b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());

    set<int> s;
    for (int x : sa)s.insert(x);
    for (int x : sb)s.insert(x);

    vector<int> c;
    c.push_back(*s.begin() - 1);
    for (int x : s)
        c.push_back(x);
    c.push_back(*s.rbegin() + 1);

    int mx = INT_MIN, bestD = 0;
    for (int d : c)
    {
        int ca = upper_bound(sa.begin(), sa.end(), d) - sa.begin();
        int cb = upper_bound(sb.begin(), sb.end(), d) - sb.begin();

        int as = ca + (sa.size() - ca) * 2;
        int bs = cb + (sb.size() - cb) * 2;

        int diff = as - bs;
        if (diff > mx)
        {
            mx = diff;
            bestD = d;
        }
    }
    return bestD;
}
int main()
{
    int t;cin >> t;
    while (t--){
        int n, m;cin >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++)cin >> a[i];
        for (int i = 0; i < m; i++)cin >> b[i];
        cout << "Optimal D: " << maxDiffD(a, b) << endl;
    }
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n; 
    
    vector<int> a(n), b(n), all;
    
    for(int i = 0; i<n; i++) cin>>a[i], all.push_back(a[i]);
    for(int i = 0; i<n; i++) cin>>b[i], all.push_back(b[i]);
    
    int m = all.size();
    
    int ans = 0;
    
    for(int i = 0; i<m; i++){
        int x, y;
        int val1 = upper_bound(a.begin(), a.end(), all[i]) - a.begin();
        int val2 = upper_bound(b.begin(), b.end(), all[i]) - b.begin();
        
        if(val1 == n) x = 0;
        else x = n + 1 - val1;
        
        if(val2 == n) y = 0;
        else y = n + 1 - val2;
        
        // cout<<all[i]<<" : "<<x<<" "<<y<<endl;
        
        ans = max(ans, x - y);
    }
    cout<<ans<<endl;
    return 0;
}
*/





/*
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


void solve(){
    int n;
    cin>>n;
    vi a(n),b(n); 
    input(a);input(b);
    {
        map<int,int>m1,m2;
        for(auto&x:a)m1[x]++; 
        vi tmpa,tmpb;
        for(auto&x:b)m2[x]++; 
        for(auto&it:m1)
        {
            if(m2.count(it.first))
            {
                int &x=m2[it.first]; 
                if(x==it.second)
                {
                    m2.erase(it.first); 
                    continue; 
                }
                if(x>it.second)
                {
                    x-=it.second; 
                    continue; 
                }
                it.second-=x; 
                m2.erase(it.first); 
                while(it.second--) tmpa.push_back(it.first); 
            }
            else {while(it.second--)tmpa.push_back(it.first); }
        }
        for(auto&it:m2)
        {
            while(it.second--)tmpb.push_back(it.first); 
        }
        a=tmpa;
        b=tmpb;
        n=a.size(); 
    }
    if(n==0)
    {
        cout<<0<<'\n'; 
        return; 
    }
    // for(auto&x:a)cout<<x<<' '; 
    // cout<<'\n'; 
    // for(auto&x:b)cout<<x<<' '; 
    int res=0; 
    int ans= 0; 
    vec<pii> v; 
    sort(all(a)); 
    sort(all(b)); 
    for(int i=0;i<n;i++)
    {
        if(a[i]==b[i])continue; 
        if(b[i]>a[i])
        {
            v.push_back({0,max(0LL,a[i]-1)});
            v.push_back({b[i],1e9});
        }
        else {
            v.push_back({b[i],a[i]-1}) ; 
        }
    }
    sort(all(v),[&](const pii&aa, const pii &bb){
        if(aa.second==bb.second)return aa.first<bb.first;
       return aa.second<bb.second;  
    });
    //for(auto&xx:v)cout<<xx.first<<' '<<xx.second<<'\n'; 
    vec<pii>z; 
    pii p=v.front(); 
    for(int i=1;i<v.size();i++)
    {
        //overlapping ?? 
        pii c=v[i]; 
        if(c.first>=p.first&&c.first<=p.second)
        {
            p={max(p.first,c.first),min(p.second,c.second)}; 
        }
        else {
            z.push_back(p); 
            //cout<<"Hello\n"<<z.back().first<<' '<<z.back().second<<'\n'; 
            p=c; 
        }
    }
    z.push_back(p);
    //1 9 10
    //4 5 6 
    for(auto[l,r]:z)
    {
        int i = lower_bound(all(a),l)-a.begin(); 
        int j = upper_bound(all(a),l)-a.begin();
        if(i==n||a[i]>l)i--; 
        // if(l==6){
        //     cout<<i<<' '<<j<<'\n'; 
        // }
        int aa=2*(min(n-j,n))+min(i+1,n); 
        i=lower_bound(all(b),l)-b.begin(); 
        j=upper_bound(all(b),l)-b.begin();
        if(i==n||b[i]>l)i--; 
        // if(l==6){
        //     cout<<i<<' '<<j<<'\n'; 
        // }
        int ba=2*(min(n-j,n))+min(i+1,n); 
        int xx=aa-ba; 
        //cout<<l<<' '<<r<<' '<<xx<<'\n';
        res=max(res,aa-ba); 
    }
    cout<<res<<'\n'; 
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin >> t;
    for(int i=1;i<=t;i++)
        solve();
    return 0;
}
*/
