#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int inf = 1000000000;

int main(){
    vector<string> waypoints = {
        "Base Station",
        "Titik A",
        "Titik B",
        "Titik C",
        "Titik D",
        "Titik E",
        "Target Operasi"
    };

    int total_node = 7;
    vector<pair<int, int>> graph[7];

    auto addedge = [&](int u, int v, int w){
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    };

    addedge(0, 1, 12);
    addedge(0, 2, 15);
    addedge(1, 3, 10);
    addedge(2, 3, 5);
    addedge(2, 4, 8);
    addedge(3, 5, 6);
    addedge(4, 5, 4);
    addedge(4, 6, 14);
    addedge(5, 6, 9);

    vector<int> dist(total_node, inf);
    vector<int> parent(total_node, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int start = 0;
    int goal = 6;
    dist[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(d > dist[u]) continue;
        for(auto edge : graph[u]){
            int v = edge.first;
            int w = edge.second;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    for(int v = goal; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "===== SISTEM NAVIGASI DRONE =====\n\n";
    cout << "Rute Penerbangan Optimal : \n";

    for(size_t i = 0; i < path.size(); i++){
        cout << waypoints[path[i]];
        if(i < path.size() - 1) cout << " -> ";
    }

    cout << "\n\n";
    cout << "Total Jarak Tempuh : " << dist[goal] << " meter\n";
    return 0;
}
