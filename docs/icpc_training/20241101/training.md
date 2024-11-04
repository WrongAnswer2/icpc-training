# The 3rd Universal Cup. Stage 14: Harbin

Virtual Contest: [The 3rd Universal Cup. Stage 14: Harbin](https://qoj.ac/contest/1817)

Solutions: [https://qoj.ac/download.php?type=attachments&id=1817&r=2](https://qoj.ac/download.php?type=attachments&id=1817&r=2)

# Submissions

Problem M. Weird Ceiling (Submitted by Kenny)

```cpp
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
```

Problem G. Welcome to Join the Online Meeting! (Submitted by Jun)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t{};
int n{}, m{}, k{};

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> k;
    vector<int> adj[n + 1];
    unordered_set<int> excluded(k);

    while(k--) {
        int temp;
        cin >> temp;
        excluded.insert(temp);
    }
    
    while(m--) {
        int u, v;
        cin >> u >> v;
        if (excluded.find(u) == excluded.end()) {
            adj[u].push_back(v);
        }
        if (excluded.find(v) == excluded.end()) {
            adj[v].push_back(u);
        }
    }


    int startPoint = 1;
    for (int i = 1; i <= n; i++) {
        if (excluded.find(i) == excluded.end()) {
            startPoint = i;
            break;
        }
    }

    vector<int> answer[n + 1];
    int answerSize = 0;
    bool visited[n + 1] = { false };
    int visitedCnt = 0;
    stack<int> stk;
    stk.push(startPoint);
    visited[startPoint] = true;
    visitedCnt++;

    while(!stk.empty()) {
        int cur = stk.top(); stk.pop();
        int cnt = 0;
        for (auto nxt : adj[cur]) {
            if (!visited[nxt]) {
                if (cnt == 0) answer[answerSize].push_back(cur);
                visited[nxt] = true;
                visitedCnt++;
                stk.push(nxt);
                answer[answerSize].push_back(nxt);
                cnt++;
            }
        }
        if (cnt > 0) answerSize++;
    }

    if (visitedCnt < n) {
        cout << "No" << '\n';
    } else {
        cout << "Yes" << '\n';
        cout << answerSize << '\n';
        for (int i = 0; i < answerSize; i++) {
            cout << answer[i][0] << ' ' << answer[i].size() - 1 << ' ';
            for (int j = 1; j < answer[i].size(); j++) {
                cout << answer[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}
```

Problem C. Giving Directions in Harbin (Submitted by Jun)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t{};
int n{}, x{};
char d{};

int getDir(char c) {
    if (c == 'N') {
        return 0;
    } else if (c == 'E') {
        return 1;
    } else if (c == 'S') {
        return 2;        
    } else {
        return 3;
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        int prevDir, curDir;

        for (int i = 0; i < n; i++) {
            cin >> d >> x;
            curDir = getDir(d);
            if (i == 0) {
                cout << (n - 1) * 2 + 1 << ' ' << d << '\n';
                cout << 'Z' << ' ' << x << '\n';
            } else {
                if (curDir == (prevDir + 1) % 4) {
                    cout << 'R' << '\n';
                    cout << 'Z' << ' ' << x << '\n';
                } else {
                    cout << 'L' << '\n';
                    cout << 'Z' << ' ' << x << '\n';
                }
            }
            prevDir = curDir;
        }
    }
}
```