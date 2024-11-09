#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
#define all(s) (s).begin(), (s).end()
const int N = 1000007;

struct segtree {

#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid ((l + r) >> 1)

    ll cnt[N << 2], sum[N << 2];
    void pushup(int rt) {
        cnt[rt] = cnt[ls] + cnt[rs];
        sum[rt] = sum[ls] + sum[rs];
    }
    void upd(int rt, int l, int r, int p, ll num) {
        if (l == r) {
            cnt[rt] += num;
            sum[rt] += 1ll * num * l;
            return;
        }
        p <= mid ? upd(ls, l, mid, p, num) : upd(rs, mid + 1, r, p, num);
        pushup(rt);
    }
    ll ksum(int rt, int l, int r, ll k) {
        if (l == r) {return 1ll * l * k;}
        if (cnt[rs] >= k) return ksum(rs, mid + 1, r, k);
        return sum[rs] + ksum(ls, l, mid, k - cnt[rs]);
    }
} tr;

int main(){
    
}