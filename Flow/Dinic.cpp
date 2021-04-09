#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 4004;
struct Edge {int to, flow;};
struct Dinic
{
    int s, t, D[N], qu[N], P[N];
    vector < int > Adj[N];
    vector < Edge > E;
    inline void Add(int v, int u, int w1, int w2 = 0)
    {
        Adj[v].pb(E.size());
        E.pb({u, w1});
        Adj[u].pb(E.size());
        E.pb({v, w2});
    }
    inline bool BFS()
    {
        int l = 0, r = 0;
        memset(D, -1, sizeof(D));
        qu[r ++] = s; D[s] = 0;
        while (r - l)
        {
            int v = qu[l ++];
            if (v == t)
                return 1;
            for (int &id : Adj[v])
                if (E[id].flow && D[E[id].to] == -1)
                    D[E[id].to] = D[v] + 1, qu[r ++] = E[id].to;
        }
        return 0;
    }
    int DFS(int v, int flow)
    {
        if (v == t)
            return (flow);
        int Flow = 0;
        for (int i = P[v]; i < Adj[v].size(); i++)
        {
            int id = Adj[v][i];
            if (E[id].flow && D[E[id].to] == D[v] + 1)
            {
                int sub = DFS(E[id].to, min(flow, E[id].flow));
                if (!sub)
                {
                    swap(Adj[v][P[v]], Adj[v][i]);
                    P[v] ++; continue;
                }
                E[id].flow -= sub;
                E[id^1].flow += sub;
                Flow += sub; flow -= sub;
                if (!flow) return Flow;
            }
            else
                swap(Adj[v][P[v]], Adj[v][i]), P[v] ++;
        }
        return Flow;
    }
    inline int MaxFlow(int _s, int _t)
    {
        s = _s; t = _t;
        int Flow = 0;
        while (BFS())
            memset(P, 0, sizeof(P)),
            Flow += DFS(s, INT_MAX);
        return Flow;
    }
};
int main()
{
    Dinic G;

    G.Add(0, 1, 10);
    G.Add(1, 2, 3);
    G.Add(0, 2, 4);

    printf("%d", G.MaxFlow(0, 2));
    return (0);
}
