#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> tumpukanundo;
    stack<string> tumpukanredo;

    tumpukanundo.push("Tambah A");
    tumpukanundo.push("Tambah B");
    tumpukanundo.push("Tambah C");

    cout << "Undo: " << tumpukanundo.top() << endl;
    tumpukanredo.push(tumpukanundo.top());
    tumpukanundo.pop();

    cout << "Setelah Undo, aksi terakhir: "
         << tumpukanundo.top() << endl;

    return 0;
}
