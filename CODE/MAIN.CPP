#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;
    vector< vector< pair<int, int> > > adj;
    vector<bool> flooded;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
        flooded.resize(V, false);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    void markFlooded(int node) {
        flooded[node] = true;
    }

    void resetFlood() {
        for (int i = 0; i < flooded.size(); i++)
            flooded[i] = false;
    }

    void displayFloodStatus(const vector<string>& names) {
        cout << "\n--- FLOOD STATUS ---\n";
        for (int i = 0; i < V; i++) {
            cout << names[i] << ": " 
                 << (flooded[i] ? "FLOODED" : "SAFE") << endl;
        }
    }

    int shortestDistance(int start, int end) {
        vector<int> dist(V, INT_MAX);
        priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > pq;

        dist[start] = 0;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            pair<int,int> top = pq.top();
            pq.pop();

            int d = top.first;
            int u = top.second;

            if (u == end) return d;

            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return INT_MAX;
    }
};

struct EvacCenter {
    int node;
    int capacity;
    int currentPeople;
    string name;
};

int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(99999, '\n');
            cout << "Invalid input. Enter a number.\n";
        } else {
            cin.ignore(99999, '\n');
            return value;
        }
    }
}

int main() {

    vector<string> names;
    names.push_back("Barangay A");
    names.push_back("Barangay B");
    names.push_back("Barangay C");
    names.push_back("Barangay D");
    names.push_back("Barangay E");
    names.push_back("Barangay F");
    names.push_back("Barangay G");
    names.push_back("Barangay H");

    unordered_map<string, int> nameToNode;
    for (int i = 0; i < names.size(); i++) {
        nameToNode[names[i]] = i;
    }

    Graph g(8);

    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(1, 4, 6);
    g.addEdge(4, 5, 5);
    g.addEdge(5, 6, 1);
    g.addEdge(6, 7, 7);

    vector<EvacCenter> evacCenters;

    EvacCenter e1;
    e1.node = 3;
    e1.capacity = 2;
    e1.currentPeople = 0;
    e1.name = "Evacuation Center 1 (Barangay D)";
    evacCenters.push_back(e1);

    EvacCenter e2;
    e2.node = 5;
    e2.capacity = 3;
    e2.currentPeople = 0;
    e2.name = "Evacuation Center 2 (Barangay F)";
    evacCenters.push_back(e2);

    EvacCenter e3;
    e3.node = 7;
    e3.capacity = 4;
    e3.currentPeople = 0;
    e3.name = "Evacuate Center 3 (Barangay H)";
    evacCenters.push_back(e3);

    queue<string> alertQueue;

    int choice = 0;

    while (true) {
        cout << "\n===== FLOOD MONITORING SYSTEM =====\n";
        cout << "1. Mark flooded area\n";
        cout << "2. View flood status\n";
        cout << "3. Evacuation recommendation\n";
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
        }

        else if (choice == 2) {
            g.displayFloodStatus(names);
        }

        else if (choice == 3) {
            string userArea;
            cout << "Enter your barangay location: ";
            getline(cin, userArea);

            if (nameToNode.find(userArea) == nameToNode.end()) {
                cout << "Invalid area name.\n";
                continue;
            }

            int userNode = nameToNode[userArea];

            vector< pair<int,int> > ranked; 
            for (int i = 0; i < evacCenters.size(); i++) {
                int d = g.shortestDistance(userNode, evacCenters[i].node);
                ranked.push_back(make_pair(d, i));
            }

            sort(ranked.begin(), ranked.end());

            cout << "\n=== RECOMMENDED EVACUATION CENTERS ===\n";

            bool recommended = false;

            for (int i = 0; i < ranked.size(); i++) {
                int dist = ranked[i].first;
                int idx = ranked[i].second;

                EvacCenter &e = evacCenters[idx];

                if (dist == INT_MAX) {
                    cout << e.name << ": NO SAFE PATH\n";
                    continue;
                }

                cout << e.name 
                     << " | Distance: " << dist
                     << " | Family Size: " << e.currentPeople 
                     << "/" << e.capacity;

                if (e.currentPeople < e.capacity) {
                    cout << "  <-- Recommended!\n";
                    e.currentPeople++;
                    recommended = true;
                    break;
                } else {
                    cout << "  (FULL)\n";
                }
            }

            if (!recommended) {
                cout << "\n⚠ ALL evacuation centers are FULL.\n";
            }
        }

        else if (choice == 4) {
            cout << "\n--- EMERGENCY ALERTS ---\n";
            if (alertQueue.empty()) {
                cout << "No alerts.\n";
            } else {
                queue<string> temp = alertQueue;
                while (!temp.empty()) {
                    cout << "⚠ " << temp.front() << endl;
                    temp.pop();
                }
            }
        }

        else if (choice == 5) {
            while (!alertQueue.empty()) alertQueue.pop();
            cout << "Alerts cleared.\n";
        }

        else if (choice == 6) {
            g.resetFlood();
            cout << "Flood status reset.\n";
        }

        else if (choice == 7) {
            break;
        }

        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
