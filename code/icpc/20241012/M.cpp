#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void work(){
    int n; cin >> n;
    set<string> names[26];
    for(int i = 0; i < n; i++){
        string tname, prob, res;
        cin >> tname >> prob >> res;
        if(res!="accepted") continue;
        names[prob[0]-'A'].insert(tname);
    }
    int ans = 0;
    for(int i = 0; i < 26; i++){if(names[i].size() > names[ans].size()) ans = i;}
    cout << (char)('A' + ans) << endl;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
    return 0;
}