#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<bits/stdc++.h>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<bitset>
// #include < unordered_map > 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #include "boost/algorithm/string.hpp"
#define fio ios_base::sync_with_stdio(false)
#define mod 1000000007
#define mod1 mod
#define mod2 100000009
#define li long long int
#define ll li
#define readi(x) scanf("%d",&x)
#define  reads(x)  scanf("%s", x)
#define readl(x) scanf("%I64d",&x)
#define rep(i,n) for(i=0;i<n;i++)
#define revp(i,n) for(i=(n-1);i>=0;i--)
#define myrep1(i,a,b) for(i=a;i<=b;i++)
#define myrep2(i,a,b) for(i=b;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define sec second
#define MAXN 1000000000000000000
#define MINN -1000000000000000000
#define pii pair<ll,ll> 
#define pdd pair<double,double>
#define pic pair<int,char>
#define N 50050
#define lgn 20
#define ddouble long double
#define minus minu
#define PI 3.1415926535
#define lgn 20


// #define INTMAX 200000000

// using namespace boost;
// #define si short int

using namespace std;
using namespace __gnu_pbds;             
typedef priority_queue<ll, vector<ll> > max_pq;
typedef priority_queue<pii, vector<pii> , greater<pii >  > min_pq;
ll toint(const string &s) {stringstream ss; ss << s; ll x; ss >> x; return x;}
string tostring ( ll number ){stringstream ss; ss<< number; return ss.str();}

// typedef priority_queue<pair < ll , pair < pii , ll > >  , vector<pair < ll , pair < pii , ll > >  > ,greater<pair < ll , pair < pii , ll > >  > > min_pq;

typedef tree< ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update > OST;
typedef priority_queue< char , vector<char> > max_pqc;
// typedef priority_queue<ll, vector<ll > , greater < ll >  > min_pq;
struct entry{
    ll ar[2];
    ll p;
}L[N],temp[N]   ;

ll t;
ll P[lgn][N],freq[N];
ll n;

bool comp ( entry x , entry y )
{
    if ( x.ar[0] == y.ar[0] )
        return x.ar[1]<y.ar[1];
    else
        return x.ar[0] < y.ar[0];
}

ll findlcp(ll x , ll y )
{
    ll ret = 0;
    while ( x < n and y < n )
    {
        bool flg = 0;
        ll k;
        for ( k = lgn - 1 ; k >= 0 ; k --)
        {
            if ( (P[k][x] == P[k][y]) and (P[k][x] != -1) and ((1<<k)<=min(n-x,n-y)))
            {
                flg = 1;
                ret += ( 1 << k );
                break;
            }
            
        }
        if ( !flg )
            break;
        // cout <<"x=" << x <<" " << "y = " << y <<" ";
        x += ( 1 << k );
        y += ( 1 << k );
        
     }
    // cout <<"ret= " << ret << e;
    return ret;
}

void radix_sort ( ll n , ll kitna)
{
    if ( kitna == -1)
        return;
    memset ( freq, 0 , sizeof freq );
    //L.ar[0]
    for ( ll i = 0 ; i < n ; i ++ )
        freq[L[i].ar[kitna]+1]++;
    for ( ll i = 1; i < max(n+1,30LL) ; i ++)
        freq[i] = freq[i-1] + freq[i];
    for ( ll i = n-1 ; i >=0   ; i -- )
    {
       
        temp[freq[L[i].ar[kitna]+1]-1] = L[i];
        freq[L[i].ar[kitna]+1]--;    
        
    }

    for ( ll i = 0 ; i < n ; i ++)
        L[i] = temp[i];
    radix_sort(n,kitna-1);


}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt","r",stdin);
    //     freopen("output.txt","w",stdout);
    // #endif

    cin >> t;
    while ( t -- )
    {
        memset ( P , -1 , sizeof P );
        string s;
        cin >> s;
        for ( ll i = 0 ; i < s.size() ; i ++)
            P[0][i] = s[i]-'A';
        n = s.size();
        ll step=0, cnt;
        for ( step=1 , cnt = 1 ; cnt < n  ; step++,cnt*=2)
        {
            for ( ll i = 0 ; i < n ; i ++)
            {
                L[i].ar[0] = P[step-1][i];
                L[i].ar[1] = (i+cnt < n)?P[step-1][i+cnt]:-1;//empty is smaller than something so -1 for empty position
                L[i].p = i;//which suffix
            }
            radix_sort(n,1);
            for ( ll i = 0 ; i < n ; i ++)
                P[step][L[i].p]= (( i > 0 ) and ( L[i].ar[0] == L[i-1].ar[0] ) and ( L[i].ar[1] == L[i-1].ar[1]) ) ? P[step][L[i-1].p] : i;
        }
        if ( n == 1)
            cout <<"1" << endl;
        else
        {
            step--;
            li ans = (n - L[0].p);
            // for ( ll i = 0 ; i < n ; i ++)
            // {
            //     cout <<"L=" << L[i].p << endl;
            // }
            // cout << "P=" << P[step][0] << endl;
            for ( ll i = 1 ; i < n ; i ++)
            { 
                // cout <<"P=" << P[step][i] << endl; 
                ans += ( n - L[i].p - findlcp(L[i-1].p,L[i].p));
            }
            cout << ans << endl;
        }
    }






}   


