#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct tree {
    map<string, vector<string>> nodes;
};

void insertnode(tree& pohon, const string& parent, const string& child) {
    pohon.nodes[parent].push_back(child);
}

void cetaktree(tree& pohon, const string& nama, const string& prefix, bool islast, bool isroot = false) {
    if(isroot)
        cout << nama << endl;
    else
        cout << prefix << (islast ? "|___ " : "|-- ") << nama << endl;

    auto it = pohon.nodes.find(nama);
    if(it == pohon.nodes.end() || it->second.empty())
        return;

    string newprefix = prefix;
    if(!isroot)
        newprefix += (islast ? "    " : "|   ");

    auto& children = it->second;
    for(size_t i = 0; i < children.size(); i++) {
        bool last = (i == children.size() - 1);
        cetaktree(pohon, children[i], newprefix, last);
    }
}

int main() {
    tree folder;

    insertnode(folder, "Root", "Dokumen");
    insertnode(folder, "Root", "Gambar");
    insertnode(folder, "Dokumen", "Tugas");
    insertnode(folder, "Dokumen", "Skripsi");
    insertnode(folder, "Gambar", "Foto");
    insertnode(folder, "Gambar", "Logo");

    cout << "Struktur Folder:" << endl;
    cetaktree(folder, "Root", "", true, true);

    return 0;
}
