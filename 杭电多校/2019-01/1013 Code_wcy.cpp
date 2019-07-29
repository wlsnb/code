#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 220;
struct Point{
    ll x,y;
    Point(ll _x=0.0,ll _y=0.0){
        x=_x; y=_y;
    };
};
int sgn(ll x){
    if(x==0) return 0;
    else if(x>0) return 1;
    else return -1;
}
Point operator + (Point a, Point b) { return Point(a.x+b.x,a.y+b.y); }
Point operator - (Point a, Point b) { return Point(a.x-b.x,a.y-b.y); }
bool operator < (const Point &a, const Point &b) { return a.x<b.x||(a.x==b.x&&a.y<b.y); }
bool operator == (const Point &a, const Point &b) { return a.x==b.x&&a.y==b.y; }
ll Dot(Point a, Point b) { return a.x*b.x+a.y*b.y; }
ll Cross(Point a, Point b) { return a.x*b.y-a.y*b.x; }
ll Area2(Point a, Point b, Point c) { return Cross(b-a,c-a); }

bool OnSegment(Point p,Point a,Point b){
    return sgn(Cross(a-p,b-p))==0 && sgn(Dot(a-p,b-p))<0;
}

bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
    ll c1=Cross(a2-a1,b1-a1), c2=Cross(a2-a1,b2-a1), c3=Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
    return sgn(c1)*sgn(c2)<0 && sgn(c3)*sgn(c4)<0;
}

bool SegmentIntersection(Point a1,Point a2,Point b1,Point b2){
    if(a1==b1||a1==b2||a2==b1||a2==b2) return true;
    if(SegmentProperIntersection(a1,a2,b1,b2)) return true;
    if(OnSegment(a1,b1,b2)||OnSegment(a2,b1,b2)||OnSegment(b1,a1,a2)||OnSegment(b2,a1,a2)) return true;
    return false;
}

int getConvex(Point *p,int n,Point *cvx){
    int m=0; sort(p,p+n);
    for(int i=0;i<n;++i){
        while(m>=2&&sgn(Cross(cvx[m-1]-cvx[m-2],p[i]-cvx[m-2]))>0) m--;
        cvx[m++]=p[i];
    }
    for(int i=n-2;i>=0;--i){
        while(m>=2&&sgn(Cross(cvx[m-1]-cvx[m-2],p[i]-cvx[m-2]))>0) m--;
        cvx[m++]=p[i];
    }
    return m;
}

bool IsConvex(Point *p, int n){
    for(int i=2;i<n;++i)
        if(Area2(p[0],p[i],p[i-1])!=0) return true;
    return false;
}

bool ConvexIntersection(Point *p,int n,Point *q,int m){
    for(int i=1;i<n;++i)
        for(int j=1;j<m;++j)
            if(SegmentIntersection(p[i-1],p[i],q[j-1],q[j])) return true;
    if(IsConvex(p,n)){
        for(int i=1;i<n;++i){
            for(int j=1;j<m;++j){
                if(sgn(Cross(p[i]-p[i-1],q[j]-p[i-1]))>0) return false;
            }
        }
        return true;
    }
    if(IsConvex(q,m)){
        for(int i=1;i<n;++i){
            for(int j=1;j<m;++j){
                if(sgn(Cross(q[j]-q[j-1],p[i]-q[j-1]))>0) return false;
            }
        }
        return true;
    }
    return false;
}

Point up[maxn],down[maxn],c1[maxn],c2[maxn];
int n,m;

int main(){
    int t,v,d;ll x,y; scanf("%d",&t);
    while(t--){
        scanf("%d",&v); n=m=0;
        while(v--){
            scanf("%lld %lld %d",&x,&y,&d);
            if(d>0){
                up[n].x=x; up[n].y=y; n++;
            }
            else{
                down[m].x=x; down[m].y=y; m++;
            }
        }
        n=getConvex(up,n,c1); m=getConvex(down,m,c2);
        if(ConvexIntersection(c1,n,c2,m)) printf("Infinite loop!\n");
        else printf("Successful!\n");
    }
}