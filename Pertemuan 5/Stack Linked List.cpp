#include <bits/stdc++.h>
#define MAX 5
using namespace std;
struct Node {
  int data;
  Node *next;
};

class Stack {
private:
  Node *top;

public:
  Stack() { top = NULL; }

  bool isEmpty() { return (top == NULL); }

  void push(int x) {
    Node *newNode = new Node();
    newNode->data = x;
    newNode->next = top;
    top = newNode;

    cout << x << " ditambahkan ke stack\n";
  }

  void pop() {
    if (isEmpty()) {
      cout << "Stack Underflow\n";
      return;
    }

    Node *temp = top;
    cout << temp->data << " dihapus dari stack\n";
    top = top->next;
    delete temp;
  }

  void peek() {
    if (isEmpty()) {
      cout << "Stack kosong\n";
    } else {
      cout << "Elemen teratas: " << top->data << endl;
    }
  }
};

int main() {
  Stack s;

  s.push(10);
  s.push(20);
  s.push(30);

  s.peek();

  s.pop();
  s.peek();

  return 0;
}