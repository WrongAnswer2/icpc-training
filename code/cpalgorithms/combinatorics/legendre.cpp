#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int fact_pow (int n, int k) { 
    //n = 5, k = 2 --> 3. 6! = 1*2*3*4*5 = 1*2*2*2*3*5 = 120, 120 / 2^3
    //n = 6, k = 2 --> 6! = 1 * (2) * 3 * [(2 * 2)] * 5 * (2 * 3)
    //n = 14, k = 3 --> 1 * 2 * 3 * 4 * 5 * 6(3*2) * 7 * 8 * [9(3*3)] * 10 * 11 * 12(3*4) * 13 * 14
    int res = 0;
    while (n) {
        // 6/2 = 3/2 = 1/2 = 0, 0+3+1 = 4
        //14/3 = 4/3 = 1/3 = 0, 4 + 1 = 5
        n /= k;
        res += n;
    }
    return res;
}

inline void work(){
    // Given n and k, find the largest power of k x such that n! is divisible by k^x.
    cout << fact_pow(6, 2) << endl;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
    return 0;
}