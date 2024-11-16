# Codeforces Round 987 (Div. 2)

Contest: [Codeforces Round 987 (Div. 2)](https://codeforces.com/contest/2031)

Author: Eric

Solved: 2/6

Upsolved: 3/6

# Submissions

## A. Penchick and Modern Monument

Solution: Greedy, replace all non most frequent elements.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> v(n);
        for(int i=0; i<n; i++) {
            cin>>v[i];
        }
        map<int,int> mp;
        for(int i=0; i<n; i++) {
            mp[v[i]]++;
        }
        int ans = INT_MAX;
        for(auto& p: mp) {
            ans = min(ans, n-p.second);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

## B. Penchick and Satay Sticks

Observation 1: You can only sort an array segment when it is in the order of x+1 x x+3 x+2 ...

e.g. 2 1 4 3 6 5

Observation 2: There will be multiple unsorted segment

e.g. 1 2 3 (5 4 7 6) 8 9 (11 10) 12 13

Solution: Loop from left to right, check each elemnt is sorted or not, if unsorted, check whether it can be sorted based on observation 1.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<int> v(n);
        for(int i=0; i<n; i++) {
            cin>>v[i];
        }
        bool ans = true;
        int l = 0;
        int r = 0;
        while(r<n) {
            while(r<n && v[r]!=r+1) {
                r++;
            }
            int x = l+1;
            while(l<r && l+1<n) {
                if(v[l]!=x && v[l]!=x+1) {
                    ans = false;
                }
                if(v[l+1]!=x && v[l+1]!=x+1) {
                    ans = false;
                }
                x += 2;
                l += 2;
            }
            while(r<n && v[r]==r+1) {
                r++;
            }
            l = r;
        }
        (ans)  ? cout<<"YES"<<endl : cout<<"NO"<<endl;
    }
    return 0;
}
```

## C. Penchick and BBQ Buns

Observation 1: Since 1 is a perfect square, if n is even, we can form a sequence of 

1 1 2 2 ...

Observation 2: If n is odd, we need 1 element that occurs 3 times. Since 3^2+4^2=5^2, we can form a sequence of 

1 (8 elements) 1 (12 elements) 2 (2 elements) 1 2 (even number of elements)

so that it has an odd length of at least 27.

We can fill in those even sequences using observation 1, and fill even number of elements at the back.

Therefore, there exist solution for any odd n of n>=27.

```cpp
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        if(n%2==0) {
            int x = 1;
            for(int i=0; i<n; i+=2) {
                cout<<x<<" "<<x<<" ";
                x++;
            }
            cout<<endl;
        } else if(n>=27) {
            cout<<"1 3 3 4 4 5 5 6 6 1 7 7 8 8 9 9 10 10 11 11 12 12 2 13 13 1 2 ";
            int x = 14;
            for(int i=28; i<=n; i+=2) {
                cout<<x<<" "<<x<<" ";
                x++;
            }
            cout<<endl;
        } else {
            cout<<-1<<endl;
        }
    }
    return 0;
}
```