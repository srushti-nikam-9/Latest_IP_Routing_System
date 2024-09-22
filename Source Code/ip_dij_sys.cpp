#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX_ROUTERS = 100;
const int INF = numeric_limits<int>::max();
int n;
int adj[MAX_ROUTERS][MAX_ROUTERS];
int dist[MAX_ROUTERS];
int prev_router[MAX_ROUTERS];

void dijkstra(int source) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev_router[i] = -1;
    }
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (int v = 0; v < n; v++) {
            if (adj[u][v] != 0) {  // Check if there is a connection
                int alt = dist[u] + adj[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev_router[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
}

void print_path(int source, int dest) {
    if (prev_router[dest] == -1) {
        cout << "\nNo path from " << source << " to " << dest << endl;
        return;
    }
    
    vector<int> path;
    int cur = dest;
    
    while (cur != source) {
        path.push_back(cur);
        cur = prev_router[cur];
    }
    
    path.push_back(source);
    reverse(path.begin(), path.end());
    
    cout << "\nShortest path from " << source << " to " << dest << ": ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << "\nTotal cost: " << dist[dest] << endl;
}

bool check_subnet(const string& sourceIP, const string& destinationIP, const string& subnet) {
    string subnetPart = subnet.substr(0, subnet.rfind('.'));
    string srcPart = sourceIP.substr(0, sourceIP.rfind('.'));
    string destPart = destinationIP.substr(0, destinationIP.rfind('.'));
    return (srcPart == subnetPart && destPart == subnetPart);
}

int main() {
    cout << "\nEnter the number of routers: ";
    cin >> n;
    
    cout << "\nEnter the adjacency matrix (" << n << " X " << n << "): \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }
    
    string subnet, sourceIP, destinationIP;
    int source, dest;

    cout << "\nEnter the subnet address (e.g., '192.168.1.0'): ";
    cin >> subnet;
    cout << "\nEnter the source IP: ";
    cin >> sourceIP;
    cout << "\nEnter the destination IP: ";
    cin >> destinationIP;

    cout << "\nEnter the source router: ";
    cin >> source;
    cout << "\nEnter the destination router: ";
    cin >> dest;

    // Check if source and destination IPs are in the same subnet
    if (check_subnet(sourceIP, destinationIP, subnet)) {
        cout << "\nSource and Destination are in the same subnet." << endl;
        cout << "\nNo routing required." << endl;
    } else {
        cout << "\nSource and Destination are in different subnets." << endl;
        cout << "\nRouting required." << endl;

        dijkstra(source);
        print_path(source, dest);
    }
    
    return 0;
}
