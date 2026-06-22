#include <bits/stdc++.h>
#define ll long long
using namespace std;

// Hash Table (Login)
struct mahasiswa{
    string nim;
    string nama;
    string prodi;
    int semester;
    string password;
};

unordered_map<string, mahasiswa> akunmahasiswa;

// Linked List (Riwayat)
list<string> riwayataktivitas;

// Queue (Antrian Konsultasi)
struct konsultasi {
    string nim;
    string nama;
    string dosen;
};

queue<konsultasi> antriankonsultasi;

// Tree (Struktur Organisasi)
struct treenode{
    string nama;
    vector<treenode*> child;
    treenode(string n){
        nama = n;
    }
};

void tampiltree(treenode* root, int level = 0){
    for(int i = 0; i < level; i++) cout << "   ";
    cout << "- " << root->nama << endl;
    for(auto c : root->child) tampiltree(c, level + 1);
}

// Graph (Navigasi Kampus)
const int V = 5;
string lokasikampus[V] = {"Gerbang Utama", "Fakultas Teknik", "Perpustakaan", "Kantin", "Rektorat"};
vector<pair<int,int>> graphkampus[V];

void tambahjalan(int u, int v, int w){
    graphkampus[u].push_back({v,w});
    graphkampus[v].push_back({u,w});
}

void dijkstra(int start){
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[start] = 0;
    pq.push({0,start});

    while(!pq.empty()){
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(d > dist[u]) continue;

        for(auto edge : graphkampus[u]){
            int v = edge.first;
            int w = edge.second;

            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << endl << "Rute dari " << lokasikampus[start] << endl;

    for(int i = 0; i < V; i++){
        cout << lokasikampus[i] << " = ";
        cout << dist[i] << endl;
    }
}

// Stack (Undo KRS)
struct matakuliah{
    string kode;
    string nama;
};

stack<matakuliah> stackkrs;

void tampilkrs(){
    stack<matakuliah> temp = stackkrs;
    vector<matakuliah> data;

    while(!temp.empty()){
        data.push_back(temp.top());
        temp.pop();
    }

    cout << endl << "Daftar Mata Kuliah:" << endl;

    for(int i = data.size() - 1; i >= 0; i--) cout << data[i].kode << " - " << data[i].nama << endl;
}

// Priority Queue
struct layanan{
    int prioritas;
    string nama;

    bool operator<(const layanan& other) const{
        return prioritas > other.prioritas;
    }
};

priority_queue<layanan> layananprioritas;

// Menu

void registrasi(){
    mahasiswa m;

    cout << "NIM      : ";
    cin >> m.nim;
    cin.ignore();

    cout << "Nama     : ";
    getline(cin,m.nama);

    cout << "Prodi    : ";
    getline(cin,m.prodi);

    cout << "Semester : ";
    cin >> m.semester;

    cout << "Password : ";
    cin >> m.password;

    akunmahasiswa[m.nim] = m;

    cout << endl << "Registrasi berhasil!" << endl;
}

void login(){
    string nim, pw;

    cout << "NIM      : ";
    cin >> nim;

    cout << "Password : ";
    cin >> pw;

    if(akunmahasiswa.count(nim) && akunmahasiswa[nim].password == pw){
        cout << endl << "Login berhasil" << endl;
        riwayataktivitas.push_back("Login oleh " + akunmahasiswa[nim].nama);
    }else cout << endl << "Login gagal" << endl;
}

void cariakun(){
    string nim;

    cout << "Masukkan NIM : ";
    cin >> nim;

    if(akunmahasiswa.count(nim)){
        cout << endl << "Nama : " << akunmahasiswa[nim].nama << endl;
        cout << "Prodi : " << akunmahasiswa[nim].prodi << endl;
    }else cout << "Data tidak ditemukan" << endl;
}

void tambahriwayat(){
    string aktivitas;

    cin.ignore();

    cout << "Aktivitas : ";
    getline(cin, aktivitas);

    riwayataktivitas.push_back(aktivitas);
}

void tampilriwayat(){
    cout << endl << "=== RIWAYAT ===" << endl;

    for(auto x : riwayataktivitas) cout << x << endl;
}

void ambilantrian(){
    konsultasi k;

    cin.ignore();

    cout << "Nama  : ";
    getline(cin, k.nama);

    cout << "NIM   : ";
    getline(cin, k.nim);

    cout << "Dosen : ";
    getline(cin, k.dosen);

    antriankonsultasi.push(k);

    cout << "Berhasil masuk antrian" << endl;
}

void layaniantrian(){
    if(antriankonsultasi.empty()){
        cout << "Tidak ada antrian\n";
        return;
    }

    konsultasi k = antriankonsultasi.front();
    antriankonsultasi.pop();

    cout << endl << "Dilayani:" << endl;
    cout << k.nama << " - " << k.dosen << endl;
}

void tambahmk(){
    matakuliah mk;

    cin.ignore();

    cout << "Kode MK : ";
    getline(cin, mk.kode);

    cout << "Nama MK : ";
    getline(cin, mk.nama);

    stackkrs.push(mk);

    cout << "Mata kuliah ditambahkan" << endl;
}

void undomk(){
    if(stackkrs.empty()){
        cout << "Tidak ada data" << endl;
        return;
    }

    cout << "Undo: " << stackkrs.top().kode << " - " << stackkrs.top().nama << endl;

    stackkrs.pop();
}

void tambahprioritas(){
    layanan l;

    cin.ignore();

    cout << "Nama Mahasiswa : ";
    getline(cin, l.nama);

    cout << "Prioritas (1 tertinggi): ";
    cin >> l.prioritas;

    layananprioritas.push(l);
}

void layaniprioritas(){
    if(layananprioritas.empty()){
        cout << "Tidak ada layanan\n";
        return;
    }

    auto x = layananprioritas.top();
    layananprioritas.pop();

    cout << endl << "Dilayani : " << x.nama << " (Prioritas " << x.prioritas << ")" << endl;
}

int main(){
    // Struktur Organisasi ITS
    treenode* rektor = new treenode("Rektor");
    treenode* wrakademik = new treenode("WR Akademik");
    treenode* wrkemahasiswaan = new treenode("WR Kemahasiswaan");

    // Fakultas
    treenode* fteic = new treenode("Fakultas Teknologi Elektro dan Informatika Cerdas");
    treenode* fsad = new treenode("Fakultas Sains dan Analitika Data");
    treenode* ftirs = new treenode("Fakultas Teknologi Industri dan Rekayasa Sistem");
    treenode* ftspk = new treenode("Fakultas Teknik Sipil, Perencanaan, dan Kebumian");
    treenode* ftk = new treenode("Fakultas Teknologi Kelautan");
    treenode* fkbd = new treenode("Fakultas Desain Kreatif dan Bisnis Digital");
    treenode* vokasi = new treenode("Fakultas Vokasi");
    treenode* fkk = new treenode("Fakultas Kedokteran dan Kesehatan");

    // Hubungan Tree
    rektor->child.push_back(wrakademik);
    rektor->child.push_back(wrkemahasiswaan);

    wrakademik->child.push_back(fteic);
    wrakademik->child.push_back(fsad);
    wrakademik->child.push_back(ftirs);
    wrakademik->child.push_back(ftspk);
    wrakademik->child.push_back(ftk);
    wrakademik->child.push_back(fkbd);
    wrakademik->child.push_back(vokasi);
    wrakademik->child.push_back(fkk);

    // Graph Kampus
    tambahjalan(0,1,2);
    tambahjalan(0,2,4);
    tambahjalan(1,2,1);
    tambahjalan(1,3,7);
    tambahjalan(2,4,3);
    tambahjalan(4,3,2);

    int pilih;

    do{
        cout << endl << "=================================" << endl;
        cout << "SMART CAMPUS NAVIGATION SYSTEM" << endl;
        cout << "=================================" << endl;
        cout << "1. Registrasi" << endl;
        cout << "2. Login" << endl;
        cout << "3. Cari Akun" << endl;
        cout << "4. Tambah Riwayat" << endl;
        cout << "5. Tampil Riwayat" << endl;
        cout << "6. Ambil Antrian Konsultasi" << endl;
        cout << "7. Layani Antrian" << endl;
        cout << "8. Tampil Struktur Organisasi" << endl;
        cout << "9. Navigasi Kampus (Dijkstra)" << endl;
        cout << "10. Tambah KRS" << endl;
        cout << "11. Undo KRS" << endl;
        cout << "12. Tampil KRS" << endl;
        cout << "13. Tambah Prioritas Layanan" << endl;
        cout << "14. Layani Prioritas" << endl;
        cout << "0. Keluar" << endl;
        cout << endl << "Pilih : ";

        cin >> pilih;

        switch(pilih){
        case 1:
            registrasi();
            break;

        case 2:
            login();
            break;

        case 3:
            cariakun();
            break;

        case 4:
            tambahriwayat();
            break;

        case 5:
            tampilriwayat();
            break;

        case 6:
            ambilantrian();
            break;

        case 7:
            layaniantrian();
            break;

        case 8:
            cout << endl << "=== STRUKTUR ORGANISASI ===" << endl;
            tampiltree(rektor);
            break;

        case 9:
            dijkstra(0);
            break;

        case 10:
            tambahmk();
            break;

        case 11:
            undomk();
            break;

        case 12:
            tampilkrs();
            break;

        case 13:
            tambahprioritas();
            break;

        case 14:
            layaniprioritas();
            break;
        }

    }while(pilih != 0);
    return 0;
}
