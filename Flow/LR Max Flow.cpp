#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 404, INF = INT_MAX;
struct Edge {int from, to, cost, flow;};
struct LRMaxFlow // 0-Based
{
    int n, m = 0, L_sum = 0;
    vector < int > F;
    LRMaxFlow(int _n = 0) : n(_n) {m = L_sum = 0;}
    struct MinCostMaxFlow
    {
        int D[N], P[N];
        bool M[N];
        vector < int > Adj[N];
        vector < Edge > E;
        inline void Add(int v, int u, int c, int w1, int w2 = 0)
        {
            Adj[v].pb(E.size());
            E.pb({v, u, c, w1});
            Adj[u].pb(E.size());
            E.pb({u, v, -c, w2});
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
                int flow = INF, v = t;
                while (v != s)
                    flow = min(flow, E[P[v]].flow), v = E[P[v]].from;
                v = t;
                while (v != s)
                {
                    E[P[v]].flow -= flow,
                    E[P[v]^1].flow += flow,
                    v = E[P[v]].from;
                }
                Flow += flow;
                Cost += D[t] * flow;
            }
            return make_pair(Flow, Cost);
        }
    };
    MinCostMaxFlow G;
    inline void Add(int v, int u, int c, int l, int r)
    {
        L_sum += l;
        int e1 = n + 2 + F.size() * 2, e2 = e1 + 1;
        G.Add(0, e2, 0, l);
        G.Add(e1, 1, c, l);
        G.Add(e1, e2, c, r - l);
        G.Add(u + 2, e1, 0, INF);
        G.Add(e2, v + 2, 0, INF);
        F.pb(l); m ++;
    }
    inline int MinCost()
    {
        pair < int , int > R = G.MaxFlow(0, 1);
        if (R.first < L_sum)
            return (INF); // It's not possible.
        for (int i = 0; i < F.size(); i++)
            F[i] += G.E[i * 10 + 2 * 2 + 1].flow;
        return (R.second);
    }
};
int main()
{
    LRMaxFlow G(5);

    //G.Add(0, 1, 5, 2, 5);
    //G.Add(1, 0, 1, 4, 10);
    G.Add(1, 2, 0, 1, 3);
    G.Add(2, 3, 0, 1, 3);
    G.Add(3, 4, 0, 1, 3);
    G.Add(4, 1, 0, 1, 3);
    G.Add(1, 3, 0, 1, 3);
    G.Add(4, 2, 0, 1, 3);


    int Cost = G.MinCost();
    if (Cost == INF)
        puts("It's not possible.");
    else
    {
        printf("%d\n", Cost);
        for (int &f : G.F)
            printf("%d ", f);
    }
    return (0);
}
