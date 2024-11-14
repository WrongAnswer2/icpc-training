#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int C(int n, int k) {
    double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return (int)(res + 0.01);
}

//Pascal's triangle: nCk = (n-1)C(k-1) + (n-1)Ck

inline void work(){
    //pre-compute binomial
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
    return 0;
}