
# include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 77;
struct Tree {
   int n , tim = 1 , d[N] , up[N] , par[N] , sz[N] , st[N] , en[N] , who[N];
   vector < int > adj[N];
   void dfsSz(int v) {
      sz[v] = 1;
      for(int u : adj[v]) {
         if(find(adj[u].begin() , adj[u].end() , v) != adj[u].end())
            adj[u].erase(find(adj[u].begin() , adj[u].end() , v));
         d[u] = d[v] + 1;
         par[u] = v;
         dfsSz(u);
         sz[v] += sz[u];
      }
   }
   void dfsHv(int v) {
      who[tim] = v;
      st[v] = tim ++;
      sort(adj[v].begin() , adj[v].end() , [&](int x , int y) { return sz[x] > sz[y];});
      int cnt = 0;
      for(int u : adj[v]) {
         up[u] = u;
         if(cnt ++ == 0)
            up[u] = up[v];
         dfsHv(u);
      }
      en[v] = tim;
   }
   inline int getLca(int v , int u) {
      while(up[v] != up[u]) {
         if(d[up[v]] < d[up[u]])
            swap(v , u);
         v = par[up[v]];
      }
      if(d[v] > d[u])
         swap(v , u);
      return v;
   }
   inline int getPar(int v , int k) {
      while(d[v] - d[up[v]] < k)
         k -= d[v] - d[up[v]] + 1 , v = par[up[v]];
      return who[st[v] - k];
   }
   inline int getKth(int v , int u , int k) {
      int lca = getLca(v , u);
      if(k <= d[v] - d[lca] + 1)
         return getPar(v , k - 1);
      k -= d[v] - d[lca] + 1;
      return getPar(u , d[u] - d[lca] - k);
   }
   inline int getDistance(int v , int u) {
      return d[v] + d[u] - (d[getLca(v , u)] << 1);
   }
   void buildHLD(int root) {
      for(int i = 0;i < N;++ i)
         d[i] = st[i] = en[i] = sz[i] = par[i] = up[i] = who[i] = 0;
      tim = 1;
      up[root] = root;
      dfsSz(root);
      dfsHv(root);
   }
} Tree;

int main() {

   return 0;
}
