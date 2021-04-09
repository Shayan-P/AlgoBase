#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 404;
struct Edge {int to, flow, cost;};
struct MinCostMaxFlow
{
    int D[N], P[N];
    bool M[N];
    vector < int > Adj[N];
    vector < Edge > E;
    inline void Add(int v, int u, int w, int c)
    {
        Adj[v].pb(E.size());
        E.pb({u, w, c});
        Adj[u].pb(E.size());
        E.pb({v, 0, -c});
    }
    inline bool SPFA(int s, int t)
    {
        queue < int > qu;
        memset(D, 63, sizeof(D));
        memset(P, -1, sizeof(P));
        memset(M, 0, sizeof(M));
        D[s] = 0; qu.push(s);
        while (qu.size())
        {
            int v = qu.front();
            qu.pop(); M[v] = 0;
            for (int &id : Adj[v])
                if (E[id].flow && D[E[id].to] > D[v] + E[id].cost)
                {
                    P[E[id].to] = id;
                    D[E[id].to] = D[v] + E[id].cost;
                    if (!M[E[id].to])
                        qu.push(E[id].to), M[E[id].to] = 1;
                }
        }
        return (P[t] != -1);
    }
    inline pair < int , int > MaxFlow(int s, int t)
    {
        int Flow = 0, Cost = 0;
        while (SPFA(s, t))
        {
            int flow = INT_MAX, v = t;
            while (v != s)
                flow = min(flow, E[P[v]].flow), v = E[P[v]^1].to;
            v = t;
            while (v != s)
            {
                E[P[v]].flow -= flow,
                E[P[v]^1].flow += flow,
                v = E[P[v]^1].to;
            }
            Flow += flow;
            Cost += D[t] * flow;
        }
        return make_pair(Flow, Cost);
    }
};
int main()
{
    MinCostMaxFlow G;

    G.Add(0, 1, 10, 5);
    G.Add(1, 2, 10, 2);
    G.Add(2, 3, 19, 14);
    G.Add(0, 2, 10, 5);

    pair < int , int > X = G.MaxFlow(0, 3);
    printf("%d , %d\n", X.first, X.second);
    return (0);
}
