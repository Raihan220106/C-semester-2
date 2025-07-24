### Struktur Class `Graph`

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <map> // Untuk representasi adjacency list dengan nama node

class Graph {
private:
    int numVertices; // Jumlah node/vertex dalam graf

    // Representasi Adjacency Matrix
    std::vector<std::vector<int>> adjMatrix;

    // Representasi Adjacency List
    // Menggunakan map untuk memetakan nama node ke daftar tetangga
    std::map<std::string, std::list<std::string>> adjList;

    // Helper untuk DFS
    void DFSUtil(std::string vertex, std::map<std::string, bool>& visited, std::vector<std::string>& result);

public:
    // Konstruktor
    Graph(int V); // Untuk adjacency matrix
    Graph(); // Untuk adjacency list (tanpa batasan jumlah vertex awal)

    // Fungsi addEdge()
    void addEdgeMatrix(int src, int dest);
    void addEdgeList(std::string src, std::string dest);

    // Fungsi Traversal
    std::vector<int> BFSMatrix(int startVertex);
    std::vector<std::string> BFSList(std::string startVertex);
    std::vector<std::string> DFSList(std::string startVertex);

    // Fungsi pembantu untuk menampilkan
    void printAdjMatrix();
    void printAdjList();
};
