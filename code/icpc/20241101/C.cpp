#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;



inline void work(){
    int n;
    cin >> n;
    char d;
    int x;
    char prev;
    vector<pair<char, int>> instructions(n);
    vector<pair<char, int>> harbin;
    cin >> d >> x;
    instructions[0] = make_pair(d, x);
    harbin.eb(make_pair(d, 0));
    harbin.eb(make_pair('Z', x));
    prev = d;
    for(int i = 1; i < n; i++){
        cin >> d >> x;
        if(prev=='S' && d=='E') {harbin.eb(make_pair('L', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='S' && d=='W') {harbin.eb(make_pair('R', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='N' && d=='E') {harbin.eb(make_pair('R', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='N' && d=='W') {harbin.eb(make_pair('L', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='E' && d=='N') {harbin.eb(make_pair('L', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='E' && d=='S') {harbin.eb(make_pair('R', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='W' && d=='N') {harbin.eb(make_pair('R', 0)); harbin.eb(make_pair('Z', x));}
        else if(prev=='W' && d=='S') {harbin.eb(make_pair('L', 0)); harbin.eb(make_pair('Z', x));}
        prev = d;
    }
    cout << (harbin.size() - 1) << " ";
    for(auto i: harbin){
        if(i.second==0) cout << i.first << endl;
        else cout << "Z " << i.second << endl;
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
}