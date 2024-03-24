#include<bits/stdc++.h>

using namespace std;

struct Edge {int from, to, flow, gross;};
template<int N, int INF> struct Dinic
{
    int s, t, D[N], qu[N], P[N];
    vector < int > Adj[N];
    vector < Edge > E;
    inline void Add(int v, int u, int w1)
    {
        Adj[v].push_back(E.size());
        E.push_back({v, u, w1, 1});
        Adj[u].push_back(E.size());
        E.push_back({u, v, 0, 0});
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
        for (int i = P[v]; i < int(Adj[v].size()); i++)
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

    void relax_path(vector<int> eids) {
        int mn = INF;
        for(int &id: eids) {
            mn = min(mn, E[id].gross);
        }
        for(int &id: eids) {
            E[id].gross -= mn;
        }
    }

    void find_path(int u, vector<bool> &seen, vector<int> &eids) {
        int out_id = -1;
        for(int &id: Adj[u]) {
            if(E[id].gross > 0)
                out_id = id;
        }
        if(out_id == -1)
            return;
        int nxt = E[out_id].to;
        if(seen[nxt]) {
            vector<int> extra_edges;
            extra_edges.push_back(out_id);
            while(true) {
                int tp = eids.back();
                eids.pop_back();
                extra_edges.push_back(tp);
                seen[E[tp].to] = false;
                if(E[tp].from == nxt)
                    break;
            }
            reverse(extra_edges.begin(), extra_edges.end());
            relax_path(extra_edges);
            find_path(nxt, seen, eids);
            return;
        }
        eids.push_back(out_id);
        seen[nxt] = true;
        find_path(nxt, seen, eids);
    }

    vector<vector<int>> FlowPaths(int _s, int _t) {
        vector<bool> seen(N);
        seen[_s] = true;
        vector<vector<int>> result;
        for(int id = 0; id < int(E.size()); id++) {
            if(E[id].gross == 1) {
                E[id].gross = E[id^1].flow;
            } else {
                E[id].gross = 0;
            }
        }
        while(true) {
            vector<int> path;
            find_path(_s, seen, path);
            if(path.empty())
                break;
            assert(E[path.back()].to == _t);
            relax_path(path);
            for(int id: path) {
                seen[E[id].to] = false;
            }
            result.push_back(path);
        }
        return result;
    }
};
