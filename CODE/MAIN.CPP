#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>  
#include <string>
#include <unordered_map>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj; 
    vector<bool> flooded;
public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
        flooded.resize(V, false);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void markFlooded(int node) {
        flooded[node] = true;
    }

    void simulateFloodBFS(int start) {
        queue<int> q;
        q.push(start);
        flooded[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &edge : adj[u]) {
                int v = edge.first;
                if (!flooded[v]) {
                    flooded[v] = true;
                    q.push(v);
                }
            }
        }
    }

    bool isSafe(int node) {
        return !flooded[node];
    }

    void displayFloodStatus(const vector<string>& names) {
        cout << "\n--- FLOOD STATUS ---\n";
        for (int i = 0; i < V; i++) {
            cout << names[i] << ": " << (flooded[i] ? "FLOODED" : "SAFE") << endl;
        }
    }

    void dijkstra(int start, int end, const vector<string>& names) {
        vector<int> dist(V, INT_MAX);
        vector<int> prev(V, -1);
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u] || flooded[u]) continue;
            visited[u] = true;

            for (auto &edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!visited[v] && !flooded[v] && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[end] == INT_MAX) {
            cout << "\nNO SAFE PATH FOUND from " << names[start] << " to " << names[end] << ".\n";
            return;
        }

        cout << "\nSAFE EVACUATION PATH FOUND!\nDistance: " << dist[end] << "\nPath: ";
        vector<int> path;
        for (int at = end; at != -1; at = prev[at])
            path.push_back(at);

        for (size_t i = path.size() - 1; i > 0; i--)
            cout << names[path[i]] << " -> ";
        cout << names[path[0]] << "\n";
    }

    void resetFlood() {
        fill(flooded.begin(), flooded.end(), false);
    }
};

int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid integer.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    vector<string> names = {"Barangay A", "Barangay B", "Barangay C", "Barangay D",
                            "Barangay E", "Barangay F", "Barangay G", "Barangay H"};

    unordered_map<string, int> nameToNode;
    for (int i = 0; i < names.size(); i++) nameToNode[names[i]] = i;

    Graph g(8);

    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(1, 4, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(5, 6, 1);
    g.addEdge(6, 7, 7);

    queue<string> alertQueue;

    int choice;
    while (true) {
        cout << "\n===== FLOOD MONITORING SYSTEM =====\n";
        cout << "1. Mark flooded area\n";
        cout << "2. View flood status\n"; 
        cout << "3. Find evacuation route (Dijkstra)\n";
        cout << "4. View emergency alerts\n";
        cout << "5. Clear alerts\n";
        cout << "6. Reset flood status\n";
        cout << "7. Exit\n";

        choice = readInt("Enter choice: ");

        if (choice == 1) {
            string area;
            cout << "Enter area that is flooded: ";
            getline(cin, area);
            if (nameToNode.find(area) != nameToNode.end()) {
                g.markFlooded(nameToNode[area]);
                alertQueue.push(area + " is FLOODED.");
            } else {
                cout << "Invalid area name.\n";
            }

        } else if (choice == 2) {
            g.displayFloodStatus(names);

        } else if (choice == 3) {
            string startArea, endArea;
            cout << "Enter start area: ";
            getline(cin, startArea);
            cout << "Enter destination area: ";
            getline(cin, endArea);

            if (nameToNode.find(startArea) != nameToNode.end() &&
                nameToNode.find(endArea) != nameToNode.end()) {
                g.dijkstra(nameToNode[startArea], nameToNode[endArea], names);
            } else {
                cout << "Invalid area name.\n";
            }

        } else if (choice == 4) {
            cout << "\n--- EMERGENCY ALERTS ---\n";
            if (alertQueue.empty()) {
                cout << "No alerts.\n";
            } else {
                queue<string> temp = alertQueue;
                while (!temp.empty()) {
                    cout << "⚠️ " << temp.front() << "\n";
                    temp.pop();
                }
            }

        } else if (choice == 5) {
            while (!alertQueue.empty()) alertQueue.pop();
            cout << "Alerts cleared.\n";

        } else if (choice == 6) {
            g.resetFlood();
            cout << "Flood status reset.\n";

        } else if (choice == 7) {
            break;

        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}


