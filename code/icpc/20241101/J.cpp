#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;

typedef long long ll;


inline void work(){
    int n, m;
    cin >> n >> m;
    vector<ll> capacities(n);
    vector<pair<ll, ll>> stations(m);
    for(int i = 0; i < n; i++) cin >> capacities[i];
    for(int i = 0; i < m; i++) {ll x,t; cin >> x >> t; stations[i] = make_pair(x,t);}
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
}