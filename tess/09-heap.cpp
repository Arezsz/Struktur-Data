#include <iostream>
#include <queue>
using namespace std;

int main() {

    priority_queue<int> maxheap;

    maxheap.push(1000);
    maxheap.push(800);
    maxheap.push(600);
    maxheap.push(500);

    cout << "Produk terlaris: "
         << maxheap.top() << endl;

    return 0;
}
