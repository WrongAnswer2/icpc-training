# The 2024 ICPC Asia East Continent Online Contest (I)

Virtual Contest: [The 2024 ICPC Asia East Continent Online Contest (I)](https://qoj.ac/contest/1794)

Solutions: [https://qoj.ac/blog/bulijiojiodibuliduo/blog/994](https://qoj.ac/blog/bulijiojiodibuliduo/blog/994)

# Submissions

## Problem A. World Cup

```cpp
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
```

## Problem M. Find the Easiest Problem

```cpp
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
```

## Problem C. Permutation Counting 4
Todo:Understand https://qoj.ac/submission/567854 

## F. Make Max 
Todo: Understand https://qoj.ac/submission/565950

## G. The Median of the Median of the Median
Todo: Understand https://qoj.ac/submission/565952