#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Fast input function
inline ll rd() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    while (!isdigit(c) && c != '-' && c != EOF) c = getchar();
    if (c == '-') { f = true; c = getchar(); }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + (c - '0');
    }
    return f ? -x : x;
}

#define eb emplace_back
#define all(s) (s).begin(), (s).end()

const int N = 1000007;

struct segtree {
    ll cnt[4*N] = {0}, sum[4*N] = {0};
    void pushup(int rt) {
        cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
        sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    }
    void upd(int rt, int l, int r, int p, ll num) {
        if (l == r) {
            cnt[rt] += num;
            sum[rt] += num * l;
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid) 
            upd(rt<<1, l, mid, p, num);
        else 
            upd(rt<<1|1, mid+1, r, p, num);
        pushup(rt);
    }
    ll ksum(int rt, int l, int r, ll k) {
        if (l == r) return l * k;
        int mid = (l + r) / 2;
        if (cnt[rt<<1|1] >= k) 
            return ksum(rt<<1|1, mid+1, r, k);
        else 
            return sum[rt<<1|1] + ksum(rt<<1, l, mid, k - cnt[rt<<1|1]);
    }
} tr;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll m;
    n = rd();
    m = rd();
    
    vector<tuple<ll, ll, ll>> s;
    s.reserve(n);
    ll totalL = 0;
    
    for(int i = 0; i < n; i++){
        ll w = rd(), l = rd(), r = rd();
        s.emplace_back(w, l, r);
        totalL += w * l;
        m -= l;
    }
    sort(all(s), [&](const tuple<ll, ll, ll> &a, const tuple<ll, ll, ll> &b) -> bool {
        return get<0>(a) > get<0>(b);
    });
    
    ll ans = totalL + m * get<0>(s.front());
    
    for(auto &[w, l, r] : s){
        ll tmp = m + l;
        ll tmptot = totalL - w * l;
        if (tr.cnt[1] < tmp) {
            tmptot += tr.sum[1] + w * (tmp - tr.cnt[1]);
        }
        else {
            tmptot += tr.ksum(1, 1, N-1, tmp);
        }
        ans = max(ans, tmptot);
        tr.upd(1, 1, N-1, w, r - l);
    }
    
    printf("%lld\n", ans);
}