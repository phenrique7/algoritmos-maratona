#include <bits/stdc++.h>

using namespace std;

const int MAX = 101000;

struct ponto{
	long long axis[2];
};

ponto P[MAX], PNode[MAX], Q[MAX];

int esq[2 * MAX], dir[2 * MAX], at;
long long minDist;

bool cmpX(ponto p1, ponto p2){
   if(p1.axis[0] != p2.axis[0]){
   	return p1.axis[0] < p2.axis[0];
   }
   return p1.axis[1] < p2.axis[1];
}

bool cmpY(ponto p1, ponto p2){
   if(p1.axis[1] != p2.axis[1]){
	   return p1.axis[1] < p2.axis[1];
   }
   return p1.axis[0] < p2.axis[0];
}

int make_tree(int ini, int fim, int axis){
   //f o l h a
   if(ini + 1 == fim){
      int root = at++;
      PNode[root] = P[ini];
      esq[root] = dir[root] = -1;
      return root;
   }
   else if(ini + 1 > fim){
	   return -1;
   }
   int root = at++;
   int meio = (ini + fim) / 2;
   if(!axis){
   	nth_element(P + ini, P + meio, P + fim, cmpX);
   }
   else{
	   nth_element(P + ini, P + meio, P + fim, cmpY);
   }
   PNode[root] = P[meio];
   esq[root] = make_tree(ini, meio, 1 - axis);
   dir[root] = make_tree(meio + 1, fim, 1 - axis);
   return root;
}

// -1 distancia normal (Euclidiana) ao quadrado, 0 distancia em relacao a x,
// 1 dist em relacao a y
long long dist(ponto p1, ponto p2, int axis = -1){
   if(axis == -1){
      return (p1.axis [0] - p2.axis[0]) * (p1.axis [0] - p2.axis[0]) +
             (p1.axis [1] - p2.axis[1]) * (p1.axis [1] - p2.axis[1]);
   }
   else{
   	return (p1.axis[axis] - p2.axis[axis]) * (p1.axis[axis] - p2.axis[axis]);
   }
}

void query(ponto p, int root, int axis){
   if(root == -1){
   	return;
   }
   long long d = dist(p, PNode[root]);
   if(d != 0LL){
   	minDist = (minDist != -1LL) ? min(minDist, d) : d;
   }
   if(p.axis[axis] < PNode[root].axis[axis]){
      query(p, esq[root], 1 - axis);
      if(dist(p, PNode[root], axis) <= minDist){
   	   query(p, dir[root], 1 - axis);
      }
   }
   else{
      query(p, dir[root], 1 - axis);
      if(dist(p, PNode[root], axis) <= minDist){
	      query(p, esq[root], 1 - axis);
      }
   }
}

int main()
{
   int tt, nn;

   scanf("%d", &tt);
   for(int qq = 1; qq <= tt; qq++){
      scanf("%d", &nn);
      for(int i = 0; i < nn; i++){
         scanf("%lld %lld ", &P[i].axis[0], &P[i].axis[1]);
         Q[i] = P[i];
      }
      at = 0;
      int root = make_tree(0, nn, 0);
      printf("root: %d\n", root);
      printf("root_x: %lld | root_y: %lld\n", P[root].axis[0], P[root].axis[1]);
      for(int i = 0; i < nn; i++){
         minDist = -1LL;
         query(Q[i], root, 0);
         printf("%lld\n", minDist);
      }
   }

   return 0;
}