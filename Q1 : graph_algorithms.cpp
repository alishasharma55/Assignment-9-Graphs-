#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// ---------- Graph Class ----------
class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w = 1) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // BFS
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (auto neighbor : adj[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    // DFS Helper
    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto neighbor : adj[v]) {
            if (!visited[neighbor.first])
                DFSUtil(neighbor.first, visited);
        }
    }

    // DFS
    void DFS(int start) {
        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // Prim's MST
    void primMST() {
        vector<int> key(V, INT_MAX);
        vector<bool> mstSet(V, false);
        vector<int> parent(V, -1);

        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1;

            for (int i = 0; i < V; i++) {
                if (!mstSet[i] &&
                    (u == -1 || key[i] < key[u]))
                    u = i;
            }

            mstSet[u] = true;

            for (auto edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!mstSet[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        cout << "\nPrim's MST:\n";
        int total = 0;

        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - "
                 << i << endl;
            total += key[i];
        }

        cout << "Total Cost = " << total << endl;
    }

    // Dijkstra Algorithm
    void dijkstra(int source) {
        vector<int> dist(V, INT_MAX);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {

            int u = pq.top().second;
            pq.pop();

            for (auto edge : adj[u]) {

                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\nDijkstra Shortest Paths:\n";

        for (int i = 0; i < V; i++)
            cout << "Vertex "
                 << i
                 << " Distance = "
                 << dist[i]
                 << endl;
    }
};

// ---------- Kruskal MST ----------

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DisjointSet {
    vector<int> parent;

public:
    DisjointSet(int n) {
        parent.resize(n);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

void kruskalMST(vector<Edge>& edges, int V) {

    sort(edges.begin(), edges.end(), compare);

    DisjointSet ds(V);

    cout << "\nKruskal MST:\n";

    int total = 0;

    for (auto edge : edges) {

        int u = edge.u;
        int v = edge.v;

        if (ds.find(u) != ds.find(v)) {

            ds.unite(u, v);

            cout << u
                 << " - "
                 << v
                 << " ("
                 << edge.weight
                 << ")\n";

            total += edge.weight;
        }
    }

    cout << "Total Cost = "
         << total
         << endl;
}

// ---------- Main ----------
int main() {

    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    g.BFS(0);
    g.DFS(0);

    g.primMST();

    vector<Edge> edges = {
        {0,1,2},
        {0,3,6},
        {1,2,3},
        {1,3,8},
        {1,4,5},
        {2,4,7},
        {3,4,9}
    };

    kruskalMST(edges, 5);

    g.dijkstra(0);

    return 0;
}
