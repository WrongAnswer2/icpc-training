#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
inline void work(){
    ll b;
    cin >> b;
    if(b==2) {cout << 3 << endl; return;}
    if(b==1) {cout << 1 << endl; return;}
    vector<ll> factors;
    for (ll i = 2; i <= sqrt(b); i++) {
        if (b % i == 0) {factors.eb(i); if(i!=b/i && i >= 2){factors.eb(b/i);}}
    }
    factors.eb(b);
    sort(factors.begin(), factors.end());
    ll total = 0;
    ll prev = 1;
    for (ll x : factors) {
        total += (x - prev) * (b / prev);
        prev = x;
    }
    total += 1;
    cout << total << endl;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
}