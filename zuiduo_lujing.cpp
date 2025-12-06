#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class Graph {
private:
	int V; // 顶点数量
	vector<vector<pair<int, int>>> adj; // 邻接表：pair<邻接顶点, 权重>
	
public:
	Graph(int vertices) : V(vertices) {
		adj.resize(V);
	}
	
	void addEdge(int u, int v, int weight) {
		adj[u].push_back({v, weight});
	}
	
	void dijkstra(int src) {
		vector<int> dist(V, INT_MAX);
		vector<int> parent(V, -1);
		vector<bool> visited(V, false);
		
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		
		dist[src] = 0;
		pq.push({0, src});
		
		while (!pq.empty()) {
			int u = pq.top().second;
			pq.pop();
			
			if (visited[u]) continue;
			visited[u] = true;
			
			for (auto &neighbor : adj[u]) {
				int v = neighbor.first;
				int weight = neighbor.second;
				
				if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
					parent[v] = u;
					pq.push({dist[v], v});
				}
			}
		}
		
		printSolution(src, dist, parent);
	}
	
private:
	void printSolution(int src, const vector<int>& dist, const vector<int>& parent) {
		cout << "从顶点 " << src << " 到其他顶点的最短路径:\n";
		cout << "顶点\t距离\t路径\n";
		
		for (int i = 0; i < V; i++) {
			if (i != src) {
				cout << src << " -> " << i << "\t";
				if (dist[i] == INT_MAX) {
					cout << "不可达\t无路径";
				} else {
					cout << dist[i] << "\t";
					printPath(i, parent);
				}
				cout << endl;
			}
		}
	}
	
	void printPath(int current, const vector<int>& parent) {
		if (current == -1) return;
		printPath(parent[current], parent);
		cout << current;
		if (parent[current] != -1) cout << " -> ";
	}
};

int main() {
	Graph g(6);
	
	g.addEdge(0, 1, 4);
	g.addEdge(0, 2, 2);
	g.addEdge(1, 2, 1);
	g.addEdge(1, 3, 5);
	g.addEdge(2, 3, 8);
	g.addEdge(2, 4, 10);
	g.addEdge(3, 4, 2);
	g.addEdge(3, 5, 6);
	g.addEdge(4, 5, 3);
	
	g.dijkstra(0);
	
	return 0;
}
