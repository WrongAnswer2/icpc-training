#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void work(){
    //beat 2 -> 16
    //beat 6 -> 8
    //beat 13 -> 4
    //beat 27 -> 2
    int a;
    cin >> a;
    int i = 31;
    int n;
    int bt = 0;
    while(i--) {cin >> n; if(a>n)bt++;}
    if(bt>=31){cout << "1" << endl; return;} 
    else if(bt>=27){cout << "2" << endl; return;} 
    else if(bt>=13){cout << "4" << endl; return;} 
    else if(bt>= 6){cout << "8" << endl; return;} 
    else if(bt>= 2){cout <<"16" << endl; return;} 
    else {cout << "32" << endl; return;}
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) work();
    return 0;
}