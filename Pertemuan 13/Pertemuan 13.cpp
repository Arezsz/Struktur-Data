#include <bits/stdc++.h>
using namespace std;

struct Node {
    int bookId;
    Node* left;
    Node* right;
};

Node* createNode(int bookId) {
    Node* newNode = new Node();
    newNode->bookId = bookId;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert(Node* root, int bookId) {
    if (root == NULL) {
        return createNode(bookId);
    }

    if (bookId < root->bookId) root->left = insert(root->left, bookId);
    else if (bookId > root->bookId) root->right = insert(root->right, bookId);

    return root;
}

void descending(Node* root) {
    if (root != NULL) {
        descending(root->right);
        cout << "ID Buku: " << root->bookId << endl;
        descending(root->left);
    }
}

bool search(Node* root, int bookId) {
    if (root == NULL)
        return false;

    if (root->bookId == bookId)
        return true;

    if (bookId < root->bookId)
        return search(root->left, bookId);
    else
        return search(root->right, bookId);
}

int main() {
    Node* root = NULL;

    // Memasukkan data ID Buku ke dalam sistem katalog BST
    root = insert(root, 500);
    insert(root, 300);
    insert(root, 700);
    insert(root, 200);
    insert(root, 400);
    insert(root, 600);
    insert(root, 800);

    cout << "Katalog Buku (Urutan ID Terbesar):" << endl;
    descending(root);

    int targetId = 600;
    cout << "\nPencarian Buku dengan ID " << targetId << ":" << endl;
    if (search(root, targetId)) cout << "Buku ditemukan di dalam katalog." << endl;
    else cout << "Buku tidak ditemukan." << endl;

    return 0;
}
