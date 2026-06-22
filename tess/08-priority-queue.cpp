#include <iostream>
#include <queue>
using namespace std;

struct pasien {
    string nama;
    int prioritas;

    bool operator<(const pasien& p) const {
        return prioritas > p.prioritas;
    }
};

int main() {

    priority_queue<pasien> pq;

    pq.push({"A",3});
    pq.push({"B",1});
    pq.push({"C",2});

    while(!pq.empty()) {
        cout << pq.top().nama << endl;
        pq.pop();
    }

    return 0;
}
