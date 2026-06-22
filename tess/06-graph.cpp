#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 1e9;

int main() {
    int v = 4;
    vector<pair<int,int>> graph[4];

    graph[0].push_back({1,4});
    graph[0].push_back({2,2});
    graph[1].push_back({3,5});
    graph[2].push_back({3,1});

    vector<int> dist(v, inf);
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[0] = 0;
    pq.push({0,0});

    while(!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int d = cur.first;
        int u = cur.second;

        for(auto edge : graph[u]) {
            int ver = edge.first;
            int w = edge.second;

            if(dist[ver] > d + w) {
                dist[ver] = d + w;
                pq.push({dist[ver], ver});
            }
        }
    }

    cout << "Jarak ke node 3 = " << dist[3];

    return 0;
}
