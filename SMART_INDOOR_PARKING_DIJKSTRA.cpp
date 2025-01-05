#include <iostream>
#include <limits.h>
using namespace std;
#define V 6 // Number of vertices in the graph
const int INF = INT_MAX;
// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[])
 {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function that implements Dijkstra's single source shortest path algorithm
void dijkstra(int graph[V][V], int src, int dist[], int parent[])
 {
    bool sptSet[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

// Function to print the shortest path from the source to the given vertex
void printPath(int parent[], int j)
 {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << j << " ";
}

// Function to find and print the nearest parking lot
void findNearestParking(int graph[V][V], int entrance, int parkingLots[], int numParkingLots)
 {
    int dist[V];
    int parent[V];
    dijkstra(graph, entrance, dist, parent);
    int nearestParking = -1;
    int minDistance = INF;
    for (int i = 0; i < numParkingLots; i++) {
        if (dist[parkingLots[i]] < minDistance) {
            minDistance = dist[parkingLots[i]];
            nearestParking = parkingLots[i];
        }
    }

    if (nearestParking != -1) {
        cout << "Nearest parking lot is at node " << nearestParking << " with a distance of " << minDistance << endl;
        cout << "Path: " << entrance << " ";
        printPath(parent, nearestParking);
        cout << endl;
    } else {
        cout << "No parking lot available." << endl;
    }
}

int main()
{
    int graph[V][V] = { { 0, 2, 0, 0, 0, 0 },
                        { 2, 0, 3, 0, 0, 0 },
                        { 0, 3, 0, 7, 0, 0 },
                        { 0, 0, 7, 0, 2, 6 },
                        { 0, 0, 0, 2, 0, 4 },
                        { 0, 0, 0, 6, 4, 0 } };

    int entrance = 0;
    int parkingLots[] = {2, 4, 5};
    int numParkingLots = sizeof(parkingLots) / sizeof(parkingLots[0]);
    findNearestParking(graph, entrance, parkingLots, numParkingLots);
    return 0;
}
