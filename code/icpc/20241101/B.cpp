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