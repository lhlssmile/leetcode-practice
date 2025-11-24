//
// Created by 24276 on 2025/11/24.
//
#include<bits/stdc++.h>
using namespace std;
#define V vector;
#define For(i, n) for (int i = 0; i < (n); i++)
using vi = vector<int>;
#define pb push_back
#define FOR(i,a,b) for (int i = (a); i < (b);i++)
#define fi first
#define EACH(x, y) for(auto& x : (y))
#define se second
using vpii = vector<pair<int,int>>;
signed main() {
    int t;cin>>t;while(t--) {
        int n,k,q;cin>>n>>k>>q;
        vpii c1, c2;vi a(n + 1, k + 1),inC1(n + 1,0),inC2(n+1,0);
        For(i, q) {
            int op,l,r;cin>>op>>l>>r;if(op == 1) {
                c1.pb({l, r});
            }else {
                c2.pb({l,r});
            }
        }
        //op1:(l,r)出现k,op2:(l,r)不允许出现k但要有0~k-1
        EACH(x, c1) FOR(i, x.fi, x.se+1) inC1[i]=1;
        EACH(x, c2) FOR(i, x.fi, x.se+1) inC2[i]=1;
        vi p;
        FOR(i, 1, n + 1) if (!inC1[i]) p.pb(i);
        For(i, p.size()) a[p[i]] = i % k;
        EACH(seg, c1) {
            int l = seg.fi, r = seg.se;
            int pos = -1;
            FOR(i,l,r+1) if (!inC2[i]) {pos=i;break;}
            a[pos] = k;
        }

        FOR(i, 1,n+1) cout<<a[i]<<" ";cout<<"\n";
    }
}