#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 500 + 5;
const int inf = 1e9;

int adj[maxn][maxn], deg[maxn];
bool bin[maxn], visited[maxn];

int minimumCutPhase(int n, int &s, int &t) {
	int start = 0;
	for (int i = 0; i < n; i++)
		if (!bin[i])
			deg[i] = 0, visited[i] = false, start = i;
	for (int i = 0; i < n; i++){
		int z = -1;
		for (int j = 0; j < n; j++)
			if (!bin[j] and !visited[j] and (z == -1 or deg[z] < deg[j]))
				z = j;
		if (z == -1)
			break;
		visited[z] = true;
		s = t;
		t = z;
		for (int j = 0; j < n; j++)
			if (!bin[j] and !visited[j])
				deg[j] += adj[z][j];
	}
	return deg[t];
}

int StoerWagner(int n) {
	int minimumCut = inf;
	for (int i = 0; i < n - 1; i++) {
		int s, t;
		minimumCut = min(minimumCut, minimumCutPhase(n, s, t));

		bin[t] = 1;
		for (int v = 0; v < n; v++)
			if (!bin[v])
				adj[v][s] += adj[v][t], adj[s][v] += adj[t][v];
	}
	return minimumCut;
}

int main(){
	ios_base::sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i][j] = 0;
	for (int i = 0; i < m; i++) {
		int v, u, w;
		cin >> v >> u >> w;
		v--, u--;
		adj[v][u] = adj[u][v] += w;
	}
	cout << StoerWagner(n) << '\n';
}
