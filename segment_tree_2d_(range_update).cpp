#include <bits/stdc++.h>

using namespace std;

const int MAX = 506;
const int INF = 1 << 30;
int P[MAX][MAX]; // container for 2D grid

/* 2D Segment Tree node */
struct Point {
   int x, y, mx;
   Point() {}
   Point(int x, int y, int mx) : x(x), y(y), mx(mx) {}
   bool operator < (const Point& other) const{
      return mx < other.mx;
   }
};

struct Segtree2d{
   Point T[2 * MAX * MAX]; // TODO: calculate the accurate space needed
   int n, m;

   // initialize and construct segment tree
   void init(int n, int m){
      this -> n = n;
      this -> m = m;
      build(1, 1, 1, n, m);
   }
   // build a 2D segment tree from data [ (a1, b1), (a2, b2) ]
   // Time: O(n logn)
   Point build(int node, int a1, int b1, int a2, int b2) {
      // out of range
      if(a1 > a2 or b1 > b2){
         return def();
		}
      // if it is only a single index, assign value to node
      if(a1 == a2 and b1 == b2){
         return T[node] = Point(a1, b1, P[a1][b1]);
		}
      // split the tree into four segments
      T[node] = def();
      T[node] = maxNode(T[node], build(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2 ) );
      T[node] = maxNode(T[node], build(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2 ));
      T[node] = maxNode(T[node], build(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2) );
      T[node] = maxNode(T[node], build(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2) );
      return T[node];
   }
   // helper function for query(int, int, int, int);
   Point query(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2) {
      // if we out of range, return dummy
      if(x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2){
         return def();
		}
      // if it is within range, return the node
      if(x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2){
         return T[node];
		}
      // split into four segments
      Point mx = def();
      mx = maxNode(mx, query(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2) );
      mx = maxNode(mx, query(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2));
      mx = maxNode(mx, query(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2));
      mx = maxNode(mx, query(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2));
      // return the maximum value
      return mx;
   }
   // query from range [ (x1, y1), (x2, y2) ]
   // Time: O(log n)
   Point query(int x1, int y1, int x2, int y2){
      return query(1, 1, 1, n, m, x1, y1, x2, y2);
   }
   // helper function for update(int, int, int);
   Point update(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2, int value){
      if(a1 > a2 or b1 > b2){
         return def();
		}
		if(x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1){
         return T[node];
		}
      if(a1 == a2 and b1 == b2){
         return T[node] = Point(a1, a2, value);
		}
      Point mx = def();
      mx = maxNode(mx, update(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2, value));
      mx = maxNode(mx, update(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2, value));
      mx = maxNode(mx, update(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2, value));
      mx = maxNode(mx, update(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2, value));
      return T[node] = mx;
   }
   // update from range [ (x1, y1), (x2, y2) ] to 'value'
   // Time: O(log n)
   Point update(int x1, int y1, int x2, int y2, int value){
      return update(1, 1, 1, n, m, x1, y1, x2, y2, value);
   }
   // utility functions; these functions are virtual because they will be overridden in child class
   virtual Point maxNode(Point a, Point b){
      return max(a, b);
   }
   // dummy node
   virtual Point def(){
      return Point(0, 0, -INF);
   }
};

Segtree2d Tmax;

/* Drier program */
int main()
{
   int n, m;
   // input
   scanf("%d %d", &n, &m);
   for(int i = 1; i <= n; i++){
       for(int j = 1; j <= m; j++){
           scanf("%d", &P[i][j]);
       }
   }
   // initialize
   Tmax.init(n, m);
   // query
   int qq, op;
   scanf("%d", &qq);
   while(qq--){
   	scanf("%d", &op);
   	if(op == 1){
         int x1, y1, x2, y2;
         scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
         int vmax = Tmax.query(x1, y1, x2, y2).mx;
      	cout << "query: " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
         cout << "max_value: " << vmax << endl << endl;
		}
		else{
         int x1, y1, x2, y2, val;
         scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &val);
         Tmax.update(x1, y1, x2, y2, val);
      	cout << "update: " << x1 << " " << y1 << " " << x2 << " " << y2 << " val: " << val << endl << endl;
   	}
	}

   return 0;
}