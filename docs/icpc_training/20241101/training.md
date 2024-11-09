# The 3rd Universal Cup. Stage 14: Harbin

Virtual Contest: [The 3rd Universal Cup. Stage 14: Harbin](https://qoj.ac/contest/1817)

Solutions: [https://qoj.ac/download.php?type=attachments&id=1817&r=2](https://qoj.ac/download.php?type=attachments&id=1817&r=2)

# Submissions

## Problem M. Weird Ceiling

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

## Problem G. Welcome to Join the Online Meeting! (Reference: SGColin)

```cpp
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
```

## Problem C. Giving Directions in Harbin

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

## Problem K: Farm Management (Reference: SGColin)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll rd() {
    ll x = 0;
    bool f = false;
    char c = getchar();
    while (!isdigit(c) && c != '-' && c != EOF) c = getchar();
    if (c == '-') { f = true; c = getchar(); }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + (c - '0');
    }
    return f ? -x : x;
}

#define eb emplace_back
#define all(s) (s).begin(), (s).end()

const int N = 1000007;

struct segtree {
    ll cnt[4*N] = {0}, sum[4*N] = {0};
    void pushup(int rt) {
        cnt[rt] = cnt[rt<<1] + cnt[rt<<1|1];
        sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    }
    void upd(int rt, int l, int r, int p, ll num) {
        if (l == r) {
            cnt[rt] += num;
            sum[rt] += num * l;
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid) 
            upd(rt<<1, l, mid, p, num);
        else 
            upd(rt<<1|1, mid+1, r, p, num);
        pushup(rt);
    }
    ll ksum(int rt, int l, int r, ll k) {
        if (l == r) return l * k;
        int mid = (l + r) / 2;
        if (cnt[rt<<1|1] >= k) 
            return ksum(rt<<1|1, mid+1, r, k);
        else 
            return sum[rt<<1|1] + ksum(rt<<1, l, mid, k - cnt[rt<<1|1]);
    }
} tr;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll m;
    n = rd();
    m = rd();
    
    vector<tuple<ll, ll, ll>> s;
    s.reserve(n);
    ll totalL = 0;
    
    for(int i = 0; i < n; i++){
        ll w = rd(), l = rd(), r = rd();
        s.emplace_back(w, l, r);
        totalL += w * l;
        m -= l;
    }
    sort(all(s), [&](const tuple<ll, ll, ll> &a, const tuple<ll, ll, ll> &b) -> bool {
        return get<0>(a) > get<0>(b);
    });
    
    ll ans = totalL + m * get<0>(s.front());
    
    for(auto &[w, l, r] : s){
        ll tmp = m + l;
        ll tmptot = totalL - w * l;
        if (tr.cnt[1] < tmp) {
            tmptot += tr.sum[1] + w * (tmp - tr.cnt[1]);
        }
        else {
            tmptot += tr.ksum(1, 1, N-1, tmp);
        }
        ans = max(ans, tmptot);
        tr.upd(1, 1, N-1, w, r - l);
    }
    
    printf("%lld\n", ans);
}
```

## Problem B: Farm Management (Reference: SGColin + ChatGPT)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Structure to represent a point
struct P {
    ll x, y;
    P(ll x_=0, ll y_=0) : x(x_), y(y_) {}
    
    // Operator for sorting
    bool operator<(const P& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    
    // Subtraction operator
    P operator - (const P& other) const {
        return P(x - other.x, y - other.y);
    }
};

// Cross product of OA and OB vectors
ll cross(const P& O, const P& A, const P& B) {
    ll dx1 = A.x - O.x;
    ll dy1 = A.y - O.y;
    ll dx2 = B.x - O.x;
    ll dy2 = B.y - O.y;
    return dx1 * dy2 - dx2 * dy1;
}

// Function to compute the convex hull using Andrew's algorithm
vector<P> convex_hull(vector<P> pts) {
    int n = pts.size();
    if(n == 0) return {};
    sort(pts.begin(), pts.end());
    
    vector<P> hull;
    // Lower hull
    for(int i = 0; i < n; ++i){
        while(hull.size() >=2 && cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0){
            hull.pop_back();
        }
        hull.emplace_back(pts[i]);
    }
    // Upper hull
    int lower_size = hull.size();
    for(int i = n-2; i >=0 ; --i){
        while(hull.size() > lower_size && cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0){
            hull.pop_back();
        }
        hull.emplace_back(pts[i]);
    }
    // Remove the last point because it's the same as the first one
    if(hull.size() >1) hull.pop_back();
    return hull;
}

// Function to compute twice the area of a polygon
ll polygon_area_twice(const vector<P>& poly){
    ll area = 0;
    int n = poly.size();
    for(int i=0;i<n;i++){
        int j = (i+1)%n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return abs(area);
}

inline void work(){
    int n;
    scanf("%d", &n);
    vector<P> points(n);
    for(int i=0;i<n;i++) scanf("%lld %lld", &points[i].x, &points[i].y);
    
    // Compute Convex Hull CH1
    vector<P> CH1 = convex_hull(points);
    if((int)CH1.size() == n){
        // All points are on convex hull, cannot form concave polygon
        printf("-1\n");
        return;
    }
    
    // Sort CH1 and points to collect interior points using two pointers
    vector<P> sorted_CH1 = CH1;
    sort(sorted_CH1.begin(), sorted_CH1.end());
    sort(points.begin(), points.end());
    
    vector<P> interior;
    int ptr1 = 0, ptr2 = 0;
    int m = sorted_CH1.size();
    int total = points.size();
    while(ptr1 < m && ptr2 < n){
        if(points[ptr2].x < sorted_CH1[ptr1].x || 
           (points[ptr2].x == sorted_CH1[ptr1].x && points[ptr2].y < sorted_CH1[ptr1].y)){
            interior.emplace_back(points[ptr2++]);
        }
        else if(points[ptr2].x == sorted_CH1[ptr1].x && points[ptr2].y == sorted_CH1[ptr1].y){
            ++ptr1; ++ptr2;
        }
        else{
            ++ptr1;
        }
    }
    // Add any remaining points
    while(ptr2 < n){
        interior.emplace_back(points[ptr2++]);
    }
    
    if(interior.empty()){
        // No interior points, cannot form concave polygon
        printf("-1\n");
        return;
    }
    
    // Compute Convex Hull of interior points (CH2)
    vector<P> CH2 = convex_hull(interior);
    
    // Compute twice the area of CH1
    ll CH1_area_twice = polygon_area_twice(CH1);
    
    // Initialize minimum decrease in area
    ll min_decrease = LLONG_MAX;
    
    // Rotating Calipers to find the minimum decrease
    int m1 = CH1.size();
    int m2 = CH2.size();
    if(m2 ==0){
        // No interior convex hull, cannot form concave polygon
        printf("-1\n");
        return;
    }
    int j = 0;
    for(int i =0; i<m1; ++i){
        P a = CH1[i];
        P b = CH1[(i+1)%m1];
        P ab = b - a;
        
        // Move pointer j to minimize |ab cross (CH2[j] - a)|
        while(true){
            int jp = (j +1) % m2;
            P current = CH2[j] - a;
            P next_p = CH2[jp] - a;
            ll cross1 = abs(ab.x * current.y - ab.y * current.x);
            ll cross2 = abs(ab.x * next_p.y - ab.y * next_p.x);
            if(cross2 < cross1){
                j = jp;
            }
            else{
                break;
            }
        }
        // Update minimum decrease
        P x = CH2[j] - a;
        ll cross_val = abs(ab.x * x.y - ab.y * x.x);
        if(cross_val < min_decrease){
            min_decrease = cross_val;
            // Early exit if the minimal possible value is found
            if(min_decrease ==1) break;
        }
    }
    
    // Now, the maximum area of concave polygon is CH1_area_twice - min_decrease
    ll result = CH1_area_twice - min_decrease;
    // Ensure the result is positive
    if(result >0){
        printf("%lld\n", result);
    }
    else{
        printf("-1\n");
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--) work();
    return 0;
}
```

## Problem B Explanation (ChatGPT):

Certainly! Let's delve into the detailed step-by-step explanation of the provided C++ code. The code is designed to solve the problem of finding the maximum possible area of a *concave polygon* that can be formed from a given set of points, ensuring that the polygon has a strictly positive area. If such a polygon cannot be formed, the code outputs -1.

Here's a structured breakdown of the algorithm and its implementation:

---

### *1. Overview of the Problem*

Given \( n \) distinct points in a 2D plane (with no three points collinear), the task is to select a subset of these points (possibly all) and connect them to form a *concave polygon* with a positive area. The goal is to determine the *maximum possible area* of such a polygon. If forming a concave polygon is impossible, the output should be -1.

---

### *2. Key Concepts and Terminology*

Before diving into the code, it's essential to understand some fundamental concepts:

- *Convex Polygon*: A polygon where any line segment connecting two points inside the polygon lies entirely within the polygon. All internal angles are less than 180°.

- *Concave Polygon*: A simple polygon that is not convex. It has at least one internal angle greater than 180°, creating a "dent."

- *Convex Hull*: The smallest convex polygon that encloses all the given points. It can be visualized as the shape formed by a tight elastic band stretched around the outermost points.

- *Cross Product*: A mathematical operation on two vectors in 2D space that provides information about their relative orientation. It helps determine whether a sequence of three points makes a left turn, right turn, or are collinear.

- *Rotating Calipers*: An algorithmic technique used to solve various computational geometry problems, especially those involving polygons and their properties.

---

### *3. Detailed Breakdown of the Code*

#### *a. Including Libraries and Defining Basic Structures*

cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


- *#include <bits/stdc++.h>*: Includes almost all C++ standard libraries, which is convenient for competitive programming.

- *typedef long long ll;*: Defines ll as an alias for long long to handle large integer values.

#### *b. Defining the P Structure*

cpp
// Structure to represent a point
struct P {
    ll x, y;
    P(ll x_=0, ll y_=0) : x(x_), y(y_) {}
    
    // Operator for sorting
    bool operator<(const P& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    
    // Subtraction operator
    P operator - (const P& other) const {
        return P(x - other.x, y - other.y);
    }
};


- *struct P*: Represents a point in 2D space with coordinates \( x \) and \( y \).

- *Constructors and Operators*:
  - *P(ll x_=0, ll y_=0)*: Initializes a point with given \( x \) and \( y \) coordinates. Default values are \( 0 \).
  - *operator<*: Allows points to be sorted first by \( x \)-coordinate and then by \( y \)-coordinate. This is crucial for algorithms like convex hull construction.
  - *operator-*: Defines the subtraction of two points, resulting in a vector. This is used in vector operations like cross products.

#### *c. Cross Product Function*

cpp
// Cross product of OA and OB vectors
ll cross(const P& O, const P& A, const P& B) {
    ll dx1 = A.x - O.x;
    ll dy1 = A.y - O.y;
    ll dx2 = B.x - O.x;
    ll dy2 = B.y - O.y;
    return dx1 * dy2 - dx2 * dy1;
}


- *Purpose: Computes the cross product of vectors **OA* and *OB*, where \( O \), \( A \), and \( B \) are points.

- *Formula*:
  \[
  \text{Cross Product} = (A_x - O_x) \times (B_y - O_y) - (A_y - O_y) \times (B_x - O_x)
  \]

- *Interpretation*:
  - If the result is *positive, the sequence \( O \rightarrow A \rightarrow B \) makes a **left turn* (counter-clockwise).
  - If it's *negative, it's a **right turn* (clockwise).
  - If the result is *zero, the points are **collinear*.

- *Application*: Used in constructing the convex hull and determining the orientation of three points.

#### *d. Convex Hull Function*

cpp
// Function to compute the convex hull using Andrew's algorithm
vector<P> convex_hull(vector<P> pts) {
    int n = pts.size();
    if(n == 0) return {};
    sort(pts.begin(), pts.end());
    
    vector<P> hull;
    // Lower hull
    for(int i = 0; i < n; ++i){
        while(hull.size() >=2 && cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0){
            hull.pop_back();
        }
        hull.emplace_back(pts[i]);
    }
    // Upper hull
    int lower_size = hull.size();
    for(int i = n-2; i >=0 ; --i){
        while(hull.size() > lower_size && cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0){
            hull.pop_back();
        }
        hull.emplace_back(pts[i]);
    }
    // Remove the last point because it's the same as the first one
    if(hull.size() >1) hull.pop_back();
    return hull;
}


- *Purpose: Computes the **convex hull* of a given set of points using *Andrew's Monotone Chain Algorithm*, which is an efficient \( O(n \log n) \) method.

- *Steps*:
  
  1. *Sorting*:
     - The points are first sorted based on their \( x \)-coordinates. If two points have the same \( x \)-coordinate, they're sorted by their \( y \)-coordinates.
  
  2. *Building the Lower Hull*:
     - Iteratively adds points to the hull vector.
     - Ensures that the sequence of points in the hull makes a *left turn* (counter-clockwise). If a *right turn* or *collinear* points are detected, the last point is removed from the hull.

  3. *Building the Upper Hull*:
     - Similar to the lower hull but iterates from the end towards the beginning.
     - This ensures that the upper boundary of the convex hull is constructed.

  4. *Finalizing the Hull*:
     - The last point is removed to prevent duplication since the first and last points are the same after constructing both lower and upper hulls.

- *Output: A vector of points representing the convex hull in **counter-clockwise* order.

#### *e. Polygon Area Calculation Function*

cpp
// Function to compute twice the area of a polygon
ll polygon_area_twice(const vector<P>& poly){
    ll area = 0;
    int n = poly.size();
    for(int i=0;i<n;i++){
        int j = (i+1)%n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return abs(area);
}


- *Purpose: Calculates **twice the area* of a polygon given its vertices using the *Shoelace Formula*.

- *Shoelace Formula*:
  \[
  \text{Area} = \frac{1}{2} \left| \sum_{i=1}^{n} (x_i \times y_{i+1} - x_{i+1} \times y_i) \right|
  \]
  Since the problem requires *twice the area*, the function directly computes the sum without dividing by 2.

- *Loop Explanation*:
  - Iterates through each vertex \( i \) and its subsequent vertex \( j = (i+1) \% n \), ensuring a wrap-around for the last vertex back to the first.
  - Aggregates the cross products \( (x_i \times y_j - x_j \times y_i) \) to compute the signed area.
  
- *Output*: The absolute value of the accumulated sum, representing twice the positive area of the polygon.

#### *f. Processing Each Test Case (work Function)*

cpp
inline void work(){
    int n;
    scanf("%d", &n);
    vector<P> points(n);
    for(int i=0;i<n;i++) scanf("%lld %lld", &points[i].x, &points[i].y);
    
    // Compute Convex Hull CH1
    vector<P> CH1 = convex_hull(points);
    if((int)CH1.size() == n){
        // All points are on convex hull, cannot form concave polygon
        printf("-1\n");
        return;
    }
    
    // Sort CH1 and points to collect interior points using two pointers
    vector<P> sorted_CH1 = CH1;
    sort(sorted_CH1.begin(), sorted_CH1.end());
    sort(points.begin(), points.end());
    
    vector<P> interior;
    int ptr1 = 0, ptr2 = 0;
    int m = sorted_CH1.size();
    int total = points.size();
    while(ptr1 < m && ptr2 < n){
        if(points[ptr2].x < sorted_CH1[ptr1].x || 
           (points[ptr2].x == sorted_CH1[ptr1].x && points[ptr2].y < sorted_CH1[ptr1].y)){
            interior.emplace_back(points[ptr2++]);
        }
        else if(points[ptr2].x == sorted_CH1[ptr1].x && points[ptr2].y == sorted_CH1[ptr1].y){
            ++ptr1; ++ptr2;
        }
        else{
            ++ptr1;
        }
    }
    // Add any remaining points
    while(ptr2 < n){
        interior.emplace_back(points[ptr2++]);
    }
    
    if(interior.empty()){
        // No interior points, cannot form concave polygon
        printf("-1\n");
        return;
    }
    
    // Compute Convex Hull of interior points (CH2)
    vector<P> CH2 = convex_hull(interior);
    
    // Compute twice the area of CH1
    ll CH1_area_twice = polygon_area_twice(CH1);
    
    // Initialize minimum decrease in area
    ll min_decrease = LLONG_MAX;
    
    // Rotating Calipers to find the minimum decrease
    int m1 = CH1.size();
    int m2 = CH2.size();
    if(m2 ==0){
        // No interior convex hull, cannot form concave polygon
        printf("-1\n");
        return;
    }
    int j = 0;
    for(int i =0; i<m1; ++i){
        P a = CH1[i];
        P b = CH1[(i+1)%m1];
        P ab = b - a;
        
        // Move pointer j to minimize |ab cross (CH2[j] - a)|
        while(true){
            int jp = (j +1) % m2;
            P current = CH2[j] - a;
            P next_p = CH2[jp] - a;
            ll cross1 = abs(ab.x * current.y - ab.y * current.x);
            ll cross2 = abs(ab.x * next_p.y - ab.y * next_p.x);
            if(cross2 < cross1){
                j = jp;
            }
            else{
                break;
            }
        }
        // Update minimum decrease
        P x = CH2[j] - a;
        ll cross_val = abs(ab.x * x.y - ab.y * x.x);
        if(cross_val < min_decrease){
            min_decrease = cross_val;
            // Early exit if the minimal possible value is found
            if(min_decrease ==1) break;
        }
    }
    
    // Now, the maximum area of concave polygon is CH1_area_twice - min_decrease
    ll result = CH1_area_twice - min_decrease;
    // Ensure the result is positive
    if(result >0){
        printf("%lld\n", result);
    }
    else{
        printf("-1\n");
    }
}


Let's break down each part of the work function:

##### *i. Input Handling*

cpp
int n;
scanf("%d", &n);
vector<P> points(n);
for(int i=0;i<n;i++) scanf("%lld %lld", &points[i].x, &points[i].y);


- *Read Input*:
  - *n*: Number of points.
  - *points*: A vector of \( n \) points, each with \( x \) and \( y \) coordinates.

##### *ii. Computing the Initial Convex Hull (CH1)*

cpp
// Compute Convex Hull CH1
vector<P> CH1 = convex_hull(points);
if((int)CH1.size() == n){
    // All points are on convex hull, cannot form concave polygon
    printf("-1\n");
    return;
}


- *Compute Convex Hull (CH1)*:
  - Uses the previously defined convex_hull function.
  - CH1 represents the outer boundary (convex hull) of all points.

- *Check for Convexity*:
  - If *all points* lie on the convex hull (CH1.size() == n), it implies that there are *no interior points*.
  - Without interior points, it's *impossible* to form a concave polygon (since removing any point would maintain convexity or reduce the number of vertices below 3).
  - *Action*: Print -1 and terminate the current test case.

##### *iii. Identifying Interior Points*

cpp
// Sort CH1 and points to collect interior points using two pointers
vector<P> sorted_CH1 = CH1;
sort(sorted_CH1.begin(), sorted_CH1.end());
sort(points.begin(), points.end());

vector<P> interior;
int ptr1 = 0, ptr2 = 0;
int m = sorted_CH1.size();
int total = points.size();
while(ptr1 < m && ptr2 < n){
    if(points[ptr2].x < sorted_CH1[ptr1].x || 
       (points[ptr2].x == sorted_CH1[ptr1].x && points[ptr2].y < sorted_CH1[ptr1].y)){
        interior.emplace_back(points[ptr2++]);
    }
    else if(points[ptr2].x == sorted_CH1[ptr1].x && points[ptr2].y == sorted_CH1[ptr1].y){
        ++ptr1; ++ptr2;
    }
    else{
        ++ptr1;
    }
}
// Add any remaining points
while(ptr2 < n){
    interior.emplace_back(points[ptr2++]);
}

if(interior.empty()){
    // No interior points, cannot form concave polygon
    printf("-1\n");
    return;
}


- *Objective: Extract points **not* on the convex hull (CH1). These are the *interior points* and are crucial for forming a concave polygon.

- *Steps*:
  
  1. *Sorting for Efficient Comparison*:
     - *sorted_CH1: A copy of CH1, sorted using the overloaded < operator. This ensures both CH1 and points are sorted to facilitate a **two-pointer* approach.
     - *points*: All points are also sorted.

  2. *Two-Pointer Technique*:
     - *Pointers*:
       - *ptr1*: Iterates through sorted_CH1.
       - *ptr2*: Iterates through sorted points.
     - *Comparison Logic*:
       - *If* the current point in points is *not* on CH1 (i.e., its \( x \)-coordinate is less or, if equal, its \( y \)-coordinate is less than the current CH1 point), it's an *interior point* and is added to the interior vector.
       - *If* the current point in points *matches* the current CH1 point (x and y both), it's part of CH1, so both pointers are incremented without adding to interior.
       - *Else*, the CH1 pointer (ptr1) is advanced.

  3. *Adding Remaining Points*:
     - After the main loop, any remaining points in points that haven't been compared are considered *interior points* and are added to interior.

  4. *Final Check*:
     - If *no interior points* are found (interior.empty()), it's impossible to form a concave polygon, so the code prints -1 and ends the test case.

##### *iv. Computing the Convex Hull of Interior Points (CH2)*

cpp
// Compute Convex Hull of interior points (CH2)
vector<P> CH2 = convex_hull(interior);


- *Purpose: To construct the convex hull of the **interior points*. This helps in effectively determining how to form a concave polygon by "cutting" into the initial convex hull (CH1).

- *Reasoning*:
  - The second convex hull (CH2) represents the boundary of the inner set of points.
  - The relationship between CH1 and CH2 provides insights into how to adjust the polygon to make it concave while maximizing the area.

##### *v. Calculating the Area of the Initial Convex Hull*

cpp
// Compute twice the area of CH1
ll CH1_area_twice = polygon_area_twice(CH1);


- *Purpose*: Calculates twice the area of the initial convex hull (CH1) using the polygon_area_twice function.

- *Reasoning*:
  - Since the problem requires outputting *twice the area*, this value serves as a starting point to determine the area reduction needed to make the polygon concave.

##### *vi. Initializing the Minimum Decrease in Area*

cpp
// Initialize minimum decrease in area
ll min_decrease = LLONG_MAX;


- *Purpose: Sets a variable min_decrease to the maximum possible value, which will later be updated to store the **minimum possible decrease* in area when transforming the convex hull into a concave polygon.

- *Reasoning*:
  - The goal is to find the *smallest* possible reduction in area that still allows the polygon to become concave.
  - This ensures that the resulting concave polygon has the *maximum possible area*.

##### *vii. Rotating Calipers Technique to Find Minimal Decrease*

cpp
// Rotating Calipers to find the minimum decrease
int m1 = CH1.size();
int m2 = CH2.size();
if(m2 ==0){
    // No interior convex hull, cannot form concave polygon
    printf("-1\n");
    return;
}
int j = 0;
for(int i =0; i<m1; ++i){
    P a = CH1[i];
    P b = CH1[(i+1)%m1];
    P ab = b - a;
    
    // Move pointer j to minimize |ab cross (CH2[j] - a)|
    while(true){
        int jp = (j +1) % m2;
        P current = CH2[j] - a;
        P next_p = CH2[jp] - a;
        ll cross1 = abs(ab.x * current.y - ab.y * current.x);
        ll cross2 = abs(ab.x * next_p.y - ab.y * next_p.x);
        if(cross2 < cross1){
            j = jp;
        }
        else{
            break;
        }
    }
    // Update minimum decrease
    P x = CH2[j] - a;
    ll cross_val = abs(ab.x * x.y - ab.y * x.x);
    if(cross_val < min_decrease){
        min_decrease = cross_val;
        // Early exit if the minimal possible value is found
        if(min_decrease ==1) break;
    }
}


- *Purpose: Determines the **minimum decrease* in area required to turn the convex hull CH1 into a concave polygon by leveraging the *Rotating Calipers* technique.

- *Key Variables*:
  - *m1*: Number of points in CH1.
  - *m2*: Number of points in CH2.
  - *j*: Pointer/index used for iterating through CH2 in conjunction with each edge of CH1.

- *Steps*:

  1. *Handle Edge Cases*:
     - If CH2 is empty (m2 == 0), it means there are *no interior convex hull points, making it **impossible* to form a concave polygon. The code outputs -1 and terminates.

  2. *Iterating Over Each Edge of CH1*:
     - For each edge \( ab \) in CH1 (from point a to point b):
       - *P ab = b - a;*: Computes the vector representation of edge \( ab \).
  
  3. *Finding the Point in CH2 Minimizing the Cross Product with Edge \( ab \)*:
     - The goal is to find a point \( x \) in CH2 such that the absolute value of the cross product \( |ab \times (x - a)| \) is *minimized*.
     - A smaller cross product implies a smaller area reduction when introducing a concave vertex at \( x \), thereby maximizing the remaining area.

  4. *Rotating Calipers Mechanism*:
     - *While Loop*:
       - Continuously evaluates whether moving the pointer j to the next point in CH2 decreases the cross product.
       - *jp = (j + 1) % m2;*: Computes the next index in CH2, ensuring wrap-around using modulo operation.
       - *current* and *next_p*: Vectors from point a to the current and next points in CH2, respectively.
       - *cross1* and *cross2*: Compute the absolute cross products with the current and next points.
       - *Decision*:
         - If moving to next_p results in a *smaller* cross product (cross2 < cross1), update j to jp.
         - Otherwise, stop moving j for the current edge.

  5. *Updating the Minimum Decrease*:
     - After finding the optimal point \( x \) in CH2 for the current edge \( ab \), compute the cross product \( |ab \times (x - a)| \).
     - If this value is *smaller* than the current min_decrease, update min_decrease.
     - *Early Termination*:
       - If min_decrease reaches 1 (the smallest possible positive integer, given that all points are distinct and no three are collinear), break out of the loop early as no smaller value is possible.

##### *viii. Final Computation and Output*

cpp
// Now, the maximum area of concave polygon is CH1_area_twice - min_decrease
ll result = CH1_area_twice - min_decrease;
// Ensure the result is positive
if(result >0){
    printf("%lld\n", result);
}
else{
    printf("-1\n");
}


- *Calculating the Result*:
  - *result = CH1_area_twice - min_decrease;*
    - *CH1_area_twice*: Twice the area of the initial convex hull.
    - *min_decrease*: The minimal area reduction needed to convert the convex hull into a concave polygon.
    - *Interpretation: Subtracting min_decrease from CH1_area_twice yields the **maximum possible area* of a concave polygon that can be formed.

- *Final Check and Output*:
  - If the result is *positive*, it signifies that a valid concave polygon exists, and its twice area is printed.
  - If result is *not positive*, it's impossible to form a concave polygon with positive area under the given constraints, so -1 is printed.

#### *g. The main Function*

cpp
int main(){
    int t;
    scanf("%d", &t);
    while(t--) work();
    return 0;
}


- *Purpose*: Handles multiple test cases.

- *Steps*:
  - *Read Number of Test Cases (t)*: Determines how many times to execute the work function.
  - *Loop Over Test Cases*: For each test case, invoke the work function to process the input and compute the desired output.

---

### *4. Comprehensive Example Walkthrough*

To solidify the understanding, let's walk through an illustrative example.

#### *Example Input*


1
5
0 0
2 0
1 1
2 2
0 2


- *Interpretation*:
  - *1 Test Case*:
    - *5 Points*:
      - \( (0, 0) \)
      - \( (2, 0) \)
      - \( (1, 1) \)
      - \( (2, 2) \)
      - \( (0, 2) \)

#### *Step-by-Step Execution*

1. *Compute Convex Hull (CH1)*:
   - For the given points, the convex hull would include all points except \( (1, 1) \), as it's an interior point.
   - *CH1*: \( [(0, 0), (2, 0), (2, 2), (0, 2)] \)

2. *Check Convexity*:
   - *CH1.size() = 4, *n = 5**: Not all points are on the convex hull. Proceed.

3. *Identify Interior Points*:
   - *Interior Points*: \( [(1, 1)] \)

4. *Compute Convex Hull of Interior Points (CH2)*:
   - Since there's only one interior point, the convex hull is the point itself.
   - *CH2*: \( [(1, 1)] \)

5. *Calculate Twice the Area of CH1*:
   - *Formula*:
     \[
     \text{Area} = \frac{1}{2} \left| \sum_{i=1}^{n} (x_i \times y_{i+1} - x_{i+1} \times y_i) \right|
     \]
   - *Calculation*:
     - \( (0 \times 0 - 2 \times 0) = 0 \)
     - \( (2 \times 2 - 2 \times 0) = 4 \)
     - \( (2 \times 2 - 0 \times 2) = 4 \)
     - \( (0 \times 0 - 0 \times 2) = 0 \)
     - *Sum*: \( 0 + 4 + 4 + 0 = 8 \)
     - *Twice the Area*: \( |8| = 8 \)

6. *Initialize min_decrease*:
   - *min_decrease*: Initially set to \( LLONG\_MAX \)

7. *Applying Rotating Calipers*:

   - *Iterate Over Each Edge of CH1*:

     *First Edge*: \( (0, 0) \rightarrow (2, 0) \)
     - *Vector \( ab \)*: \( (2-0, 0-0) = (2, 0) \)
     - *Special Point from CH2*: \( (1,1) - (0,0) = (1,1) \)
     - *Cross Product*: \( |2 \times 1 - 0 \times 1| = |2| = 2 \)
     - *Update min_decrease*: \( \min(\text{LLONG\_MAX}, 2) = 2 \)

     *Second Edge*: \( (2, 0) \rightarrow (2, 2) \)
     - *Vector \( ab \)*: \( (2-2, 2-0) = (0, 2) \)
     - *Special Point from CH2*: \( (1,1) - (2,0) = (-1,1) \)
     - *Cross Product*: \( |0 \times 1 - 2 \times (-1)| = |2| = 2 \)
     - *Update min_decrease*: \( \min(2, 2) = 2 \)

     *Third Edge*: \( (2, 2) \rightarrow (0, 2) \)
     - *Vector \( ab \)*: \( (0-2, 2-2) = (-2, 0) \)
     - *Special Point from CH2*: \( (1,1) - (2,2) = (-1,-1) \)
     - *Cross Product*: \( |-2 \times (-1) - 0 \times (-1)| = |2| = 2 \)
     - *Update min_decrease*: \( \min(2, 2) = 2 \)

     *Fourth Edge*: \( (0, 2) \rightarrow (0, 0) \)
     - *Vector \( ab \)*: \( (0-0, 0-2) = (0, -2) \)
     - *Special Point from CH2*: \( (1,1) - (0,2) = (1,-1) \)
     - *Cross Product*: \( |0 \times (-1) - (-2) \times 1| = |2| = 2 \)
     - *Update min_decrease*: \( \min(2, 2) = 2 \)

   - *Final min_decrease*: \( 2 \)

8. *Compute the Result*:

   - *Formula*:
     \[
     \text{Result} = \text{CH1\_area\_twice} - \text{min\_decrease} = 8 - 2 = 6
     \]
   - *Check*:
     - Since \( 6 > 0 \), a valid concave polygon exists.
   - *Output*: 6

#### *Final Output for the Example*


6


*Interpretation*: Twice the maximum area of the concave polygon that can be formed with the given points is 6, which corresponds to an area of 3.

---

### *5. Summary of the Algorithm's Workflow*

1. *Input Parsing*:
   - Read all points for each test case.

2. *Initial Convex Hull (CH1) Construction*:
   - Determine the convex hull of all points.
   - If all points lie on CH1, it's impossible to form a concave polygon; output -1.

3. *Identifying Interior Points*:
   - Extract points that are *not* on CH1. These are potential candidates to introduce concavity into the polygon.

4. *Secondary Convex Hull (CH2) Construction*:
   - Compute the convex hull of the interior points.
   - If there are no interior points (CH2 is empty), output -1.

5. *Area Computation*:
   - Calculate twice the area of the initial convex hull (CH1).

6. *Minimal Area Decrease Determination*:
   - For each edge in CH1, find the point in CH2 that, when used to introduce a concave vertex, results in the smallest possible area reduction.
   - Use the *Rotating Calipers* technique to efficiently iterate and find this minimal decrease.

7. *Final Area Calculation*:
   - Subtract the minimal decrease from the area of CH1 to obtain the maximum possible area of a concave polygon.
   - Ensure the result is positive before outputting; otherwise, output -1.

8. *Output the Result*:
   - For each test case, output the computed value or -1 as per the conditions.

---

### *6. Key Optimizations Implemented in the Code*

To ensure that the code runs efficiently within the given constraints (especially with large inputs), several optimizations are employed:

1. *Efficient Convex Hull Construction*:
   - *Andrew's Monotone Chain Algorithm* is used, which runs in \( O(n \log n) \) time and is suitable for large datasets.

2. *Two-Pointer Technique for Identifying Interior Points*:
   - By sorting both CH1 and points, the two-pointer approach reduces the time complexity of identifying interior points from \( O(n \log n) \) (using binary search) to \( O(n) \), which is crucial when \( n \) is large.

3. *Rotating Calipers for Minimal Decrease Calculation*:
   - Instead of naively iterating over all possible point-edge pairs (which would be computationally expensive), the Rotating Calipers technique efficiently traverses points and edges to find the optimal minimal decrease in area.

4. *Early Termination*:
   - If the minimum possible decrease (min_decrease) reaches 1, the algorithm terminates early since this is the smallest possible positive integer value, ensuring no further unnecessary computations.

5. *Fast Input/Output Operations*:
   - The use of scanf and printf (as opposed to cin and cout) significantly speeds up input and output operations, which is beneficial when dealing with a large number of test cases and points.

6. *Avoiding Redundant Calculations*:
   - By pre-sorting and efficiently managing pointers, the code avoids recalculating or re-evaluating points and edges, ensuring optimal runtime performance.

---

### *7. Final Notes and Best Practices*

- *Data Types*: The use of long long (ll) ensures that very large coordinate values and cross products do not cause integer overflow.

- *Edge Case Handling*: The algorithm meticulously handles scenarios where:
  - All points lie on the convex hull.
  - There are no interior points.
  - Reducing the area might lead to invalid (zero or negative) results.

- *Modular Code Design*: Functions like convex_hull and polygon_area_twice encapsulate specific functionalities, promoting code readability and reusability.

- *Algorithm Choice*: Selecting the right algorithms (like Andrew's for convex hull and Rotating Calipers for minimal decrease) is pivotal for achieving the desired time complexity.

- *Performance Considerations*: Given the problem's constraints (up to \( 10^5 \) points per test case and \( 2 \times 10^5 \) across all test cases), ensuring \( O(n \log n) \) or better time complexities is essential to prevent Time Limit Exceeded (TLE) errors.

---

By following this detailed explanation, you should now have a comprehensive understanding of the algorithm and logic underpinning the provided C++ code. This understanding not only aids in grasping how the problem is solved but also equips you with insights into efficient computational geometry techniques essential for similar problems.