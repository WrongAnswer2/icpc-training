#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define all(s) (s).begin(), (s).end()

void inline work(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> busy(n+1);
    for(int i = 0; i < k; i++){
        int x;
        cin >> x;
        busy[x] = 1;
    }

    vector<vector<int>>g(n+1);
    
    for(int i = 0; i < m ; i++){
        int u, v;
        cin >> u >> v;
        if(busy[u] && busy[v]) continue;
        if(busy[u]) g[v].eb(u);
        else if(busy[v]) g[u].eb(v);
        else {g[v].eb(u); g[u].eb(v);}
    }
    
    int root = -1;
    
    for(int i = 1; i <= n ; i++) {if(busy[i]) continue; root=i; break;}
    if(root==-1) {cout << "No" << endl; return;}
    vector<bool> vis(n+1);
    queue<int> que; que.push(root); vis[root] = true;
    vector<pair<int, vector<int>>> ans;
    while(!que.empty())  {
        int u = que.front(); que.pop();
        vector<int> tmp;
        for(auto v:g[u]) if(!vis[v]) {tmp.eb(v); vis[v] = true; if(!busy[v]) que.push(v);}
        sort(all(tmp));
        if(!tmp.empty()) ans.eb(u, tmp);
    }
    for(int i = 1 ; i<=n ; i++) if(!vis[i]) { cout << "No" << endl; return; }
    cout << "Yes" << endl;
    cout << ans.size() << endl;
    for(auto &[u, s] : ans) {
        cout << u << " " << s.size();
        for(auto x : s) cout << " " << x;
        cout << endl;
    }
    return;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    work();
}