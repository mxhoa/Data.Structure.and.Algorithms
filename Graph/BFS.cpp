#include <iostream>
#include <list>

using namespace std;

class Graph
{
private:
    int V;               // Number of vertices
    std::list<int> *adj; // adjacency lists

public:
    Graph(int v);
    void addEdge(int v, int w); // Add w to v's list
    void BFS(int s);            // BFS traversal from a given source 's'
};

Graph::Graph(int v)
{
    V = v;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::BFS(int s)
{
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

    std::list<int> queue;

    visited[s] = true;
    queue.push_back(s);

    std::list<int>::iterator it;
    while (!queue.empty())
    {
        int currentVertex = queue.front();
        std::cout << "Visited: " << currentVertex << " -> ";
        queue.pop_front();

        for (it = adj[currentVertex].begin(); it != adj[currentVertex].end(); ++it)
        {
            int adjVertex = *it;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
}

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 1);
    g.addEdge(2, 4);
    g.addEdge(3, 0);

    g.BFS(0);

    return 0;
}