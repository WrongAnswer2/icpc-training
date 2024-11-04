# The 2nd Universal Cup. Stage 22: Hangzhou

Virtual Contest: [The 2nd Universal Cup. Stage 22: Hangzhou](https://qoj.ac/contest/1516)

Solutions: [https://qoj.ac/download.php?type=attachments&id=1516&r=1](https://qoj.ac/download.php?type=attachments&id=1516&r=1)

# Submissions

Problem M. V-Diagram (Submitted by Jun)

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int t, n, center;
ll a[300005];
ll temp, minA;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        minA = 1000000005;
        for (int i = 0; i < n; i++) {
            cin >> temp;
            a[i] = temp;
            if (a[i] < minA) {
                minA = a[i];
                center = i;
            }
        }

        ll leftSum = a[center + 1];
        ll rightSum = a[center - 1];

        for (int i = center; i >= 0; i--) {
            leftSum += a[i];
        }
        
        for (int i = center; i < n; i++) {
            rightSum += a[i];
        }

        double leftAvg =  1.0 * leftSum / (center + 2);
        double rightAvg = 1.0 * rightSum / (n - center + 1);

        if (leftAvg > rightAvg) {
            ll tempSum = leftSum;
            ll cnt = center + 2;
            double tempAvg = 0;

            for (int i = center + 2; i < n; i++) {
                tempSum += a[i];
                cnt++;
                tempAvg = 1.0 * tempSum / cnt;
                if (tempAvg > leftAvg) {
                    leftAvg = tempAvg;
                }    
            }

            cout << fixed;
            cout.precision(10);
            cout << leftAvg << "\n";
        } else { 
            ll tempSum = rightSum;
            ll cnt = n - center + 1;
            double tempAvg = 0;

            for (int i = center - 2; i >= 0; i--) {
                tempSum += a[i];
                cnt++;
                tempAvg = 1.0 * tempSum / cnt;
                if (tempAvg > rightAvg) {
                    rightAvg = tempAvg;
                }    
            }

            cout << fixed;
            cout.precision(10);
            cout << rightAvg << "\n";
        }
    }

    return 0;
}
```

Problem J. Mysterious Tree (Submitted by )

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int t, n, res, u, v, x, y;
bool flag;
string q;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    
    while(t--) {
        cin >> n;
        flag = false;

        for (int i = 1; i <= n; i += 2) {
            if (i == n) {
                q = "? " + to_string(i - 1) + " " + to_string(i) + "\n";
            } else {
                q = "? " + to_string(i) + " " + to_string(i + 1) + "\n";
            }
            cout << q;
            cout.flush();

            cin >> res;

            if (res == 1) {
                if (i == n) {
                    u = i - 1;
                    v = i;
                } else {
                    u = i;
                    v = i + 1;
                }

                if (i == 1) {
                    x = n - 1;
                    y = n;
                } else {
                    x = 1;
                    y = 2;
                }
                flag = true;
                break;
            }
        }

        if (!flag) {
            cout << "! 1" << "\n";
            cout.flush();
        } else {
            q = "? " + to_string(u) + " " + to_string(x) + "\n";
            cout << q;
            cout.flush();
            cin >> res;
            if (res == 0) {
                q = "? " + to_string(v) + " " + to_string(x) + "\n";
                cout << q;
                cout.flush();
                cin >> res;
                if (res == 0) {
                    cout << "! 1" << "\n";
                    cout.flush();
                } else {
                    q = "? " + to_string(v) + " " + to_string(y) + "\n";
                    cout << q;
                    cout.flush();
                    cin >> res;

                    if (res == 1) {
                        cout << "! 2" << "\n";
                        cout.flush();
                    } else {
                        cout << "! 1" << "\n";
                        cout.flush();
                    }
                }
            } else {
                q = "? " + to_string(u) + " " + to_string(y) + "\n";
                cout << q;
                cout.flush();
                cin >> res;
                if (res == 0) {
                    q = "? " + to_string(v) + " " + to_string(x) + "\n";
                    cout << q;
                    cout.flush();
                    cin >> res;
                    if (res == 0) {
                        cout << "! 1" << "\n";
                        cout.flush();
                    } else {
                        q = "? " + to_string(v) + " " + to_string(y) + "\n";
                        cout << q;
                        cout.flush();
                        cin >> res;

                        if (res == 1) {
                            cout << "! 2" << "\n";
                            cout.flush();
                        } else {
                            cout << "! 1" << "\n";
                            cout.flush();
                        }
                    }
                } else {
                    cout << "! 2" << "\n";
                    cout.flush();
                }
            }
        }
    }

    cout.flush();
    return 0;
}
```