#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

class GraphMatrix {
private:
	int vertexCount;          
	vector<vector<int>> matrix; 
	vector<string> vertexNames; 
	
public:
	GraphMatrix(int n) : vertexCount(n) {
		matrix.resize(n, vector<int>(n, 0));
		vertexNames.resize(n);
		
		for (int i = 0; i < n; i++) {
			vertexNames[i] = "V" + to_string(i);
		}
	}
	
	void setVertexName(int vertex, const string& name) {
		if (vertex >= 0 && vertex < vertexCount) {
			vertexNames[vertex] = name;
		}
	}
	
	void addEdge(int v1, int v2) {
		if (v1 >= 0 && v1 < vertexCount && v2 >= 0 && v2 < vertexCount) {
			matrix[v1][v2] = 1;
			matrix[v2][v1] = 1; 
		}
	}
	
	void addEdge(int v1, int v2, int weight) {
		if (v1 >= 0 && v1 < vertexCount && v2 >= 0 && v2 < vertexCount) {
			matrix[v1][v2] = weight;
			matrix[v2][v1] = weight;  
		}
	}
	
	void removeEdge(int v1, int v2) {
		if (v1 >= 0 && v1 < vertexCount && v2 >= 0 && v2 < vertexCount) {
			matrix[v1][v2] = 0;
			matrix[v2][v1] = 0;
		}
	}
	
	void printMatrix() {
		cout << "邻接矩阵:" << endl;
		cout << "   ";
		for (int i = 0; i < vertexCount; i++) {
			cout << setw(4) << vertexNames[i];
		}
		cout << endl;
		
		for (int i = 0; i < vertexCount; i++) {
			cout << setw(3) << vertexNames[i];
			for (int j = 0; j < vertexCount; j++) {
				cout << setw(4) << matrix[i][j];
			}
			cout << endl;
		}
	}
	
	void BFS(int startVertex) {
		vector<bool> visited(vertexCount, false);
		queue<int> q;
		
		cout << "BFS遍历(从" << vertexNames[startVertex] << "开始): ";
		
		visited[startVertex] = true;
		q.push(startVertex);
		
		while (!q.empty()) {
			int current = q.front();
			q.pop();
			cout << vertexNames[current] << " ";
			
			for (int i = 0; i < vertexCount; i++) {
				if (matrix[current][i] != 0 && !visited[i]) {
					visited[i] = true;
					q.push(i);
				}
			}
		}
		cout << endl;
	}
	
	void DFSUtil(int vertex, vector<bool>& visited) {
		visited[vertex] = true;
		cout << vertexNames[vertex] << " ";
		
		for (int i = 0; i < vertexCount; i++) {
			if (matrix[vertex][i] != 0 && !visited[i]) {
				DFSUtil(i, visited);
			}
		}
	}
	
	void DFS(int startVertex) {
		vector<bool> visited(vertexCount, false);
		cout << "DFS遍历(从" << vertexNames[startVertex] << "开始): ";
		DFSUtil(startVertex, visited);
		cout << endl;
	}
	
	int getVertexCount() const {
		return vertexCount;
	}
	
	const vector<vector<int>>& getMatrix() const {
		return matrix;
	}
};

struct AdjListNode {
	int dest;         
	int weight;        
	AdjListNode* next;  
	
	AdjListNode(int d, int w = 1) : dest(d), weight(w), next(nullptr) {}
};

class GraphList {
private:
	int vertexCount;              
	vector<AdjListNode*> adjList;  
	vector<string> vertexNames;  
	
public:
	GraphList(int n) : vertexCount(n) {
		adjList.resize(n, nullptr);
		vertexNames.resize(n);
		
		for (int i = 0; i < n; i++) {
			vertexNames[i] = "V" + to_string(i);
		}
	}
	
	~GraphList() {
		for (int i = 0; i < vertexCount; i++) {
			AdjListNode* current = adjList[i];
			while (current != nullptr) {
				AdjListNode* temp = current;
				current = current->next;
				delete temp;
			}
		}
	}
	
	void setVertexName(int vertex, const string& name) {
		if (vertex >= 0 && vertex < vertexCount) {
			vertexNames[vertex] = name;
		}
	}
	
	void addEdge(int v1, int v2) {
		addEdge(v1, v2, 1);
	}
	
	void addEdge(int v1, int v2, int weight) {
		if (v1 >= 0 && v1 < vertexCount && v2 >= 0 && v2 < vertexCount) {
			AdjListNode* newNode = new AdjListNode(v2, weight);
			newNode->next = adjList[v1];
			adjList[v1] = newNode;
			
			newNode = new AdjListNode(v1, weight);
			newNode->next = adjList[v2];
			adjList[v2] = newNode;
		}
	}
	
	void removeEdge(int v1, int v2) {
		if (v1 >= 0 && v1 < vertexCount && v2 >= 0 && v2 < vertexCount) {
			AdjListNode* current = adjList[v1];
			AdjListNode* prev = nullptr;
			
			while (current != nullptr && current->dest != v2) {
				prev = current;
				current = current->next;
			}
			
			if (current != nullptr) {
				if (prev == nullptr) {
					adjList[v1] = current->next;
				} else {
					prev->next = current->next;
				}
				delete current;
			}
			
			current = adjList[v2];
			prev = nullptr;
			
			while (current != nullptr && current->dest != v1) {
				prev = current;
				current = current->next;
			}
			
			if (current != nullptr) {
				if (prev == nullptr) {
					adjList[v2] = current->next;
				} else {
					prev->next = current->next;
				}
				delete current;
			}
		}
	}
	
	void printList() {
		cout << "邻接表:" << endl;
		for (int i = 0; i < vertexCount; i++) {
			cout << vertexNames[i] << " -> ";
			AdjListNode* current = adjList[i];
			while (current != nullptr) {
				cout << vertexNames[current->dest] << "(" << current->weight << ")";
				if (current->next != nullptr) {
					cout << " -> ";
				}
				current = current->next;
			}
			cout << endl;
		}
	}
	
	void BFS(int startVertex) {
		vector<bool> visited(vertexCount, false);
		queue<int> q;
		
		cout << "BFS遍历(从" << vertexNames[startVertex] << "开始): ";
		
		visited[startVertex] = true;
		q.push(startVertex);
		
		while (!q.empty()) {
			int current = q.front();
			q.pop();
			cout << vertexNames[current] << " ";
			
			AdjListNode* temp = adjList[current];
			while (temp != nullptr) {
				if (!visited[temp->dest]) {
					visited[temp->dest] = true;
					q.push(temp->dest);
				}
				temp = temp->next;
			}
		}
		cout << endl;
	}
	
	void DFSUtil(int vertex, vector<bool>& visited) {
		visited[vertex] = true;
		cout << vertexNames[vertex] << " ";
		
		AdjListNode* temp = adjList[vertex];
		while (temp != nullptr) {
			if (!visited[temp->dest]) {
				DFSUtil(temp->dest, visited);
			}
			temp = temp->next;
		}
	}
	
	void DFS(int startVertex) {
		vector<bool> visited(vertexCount, false);
		cout << "DFS遍历(从" << vertexNames[startVertex] << "开始): ";
		DFSUtil(startVertex, visited);
		cout << endl;
	}
	
	int getVertexCount() const {
		return vertexCount;
	}
	
	const vector<AdjListNode*>& getAdjList() const {
		return adjList;
	}
};

int main() {
	cout << "=== 无向图实现示例 ===" << endl << endl;
	
	const int VERTEX_COUNT = 5;
	
	cout << "1. 邻接矩阵实现:" << endl;
	GraphMatrix graphMatrix(VERTEX_COUNT);
	
	graphMatrix.setVertexName(0, "A");
	graphMatrix.setVertexName(1, "B");
	graphMatrix.setVertexName(2, "C");
	graphMatrix.setVertexName(3, "D");
	graphMatrix.setVertexName(4, "E");
	
	graphMatrix.addEdge(0, 1);
	graphMatrix.addEdge(0, 2);
	graphMatrix.addEdge(1, 3);
	graphMatrix.addEdge(2, 3);
	graphMatrix.addEdge(3, 4);
	graphMatrix.addEdge(1, 4, 2); 
	
	graphMatrix.printMatrix();
	graphMatrix.BFS(0);
	graphMatrix.DFS(0);
	
	cout << endl << "2. 邻接表实现:" << endl;
	GraphList graphList(VERTEX_COUNT);
	
	graphList.setVertexName(0, "A");
	graphList.setVertexName(1, "B");
	graphList.setVertexName(2, "C");
	graphList.setVertexName(3, "D");
	graphList.setVertexName(4, "E");
	
	graphList.addEdge(0, 1);
	graphList.addEdge(0, 2);
	graphList.addEdge(1, 3);
	graphList.addEdge(2, 3);
	graphList.addEdge(3, 4);
	graphList.addEdge(1, 4, 2); 
	
	graphList.printList();
	graphList.BFS(0);
	graphList.DFS(0);
	
	return 0;
}
