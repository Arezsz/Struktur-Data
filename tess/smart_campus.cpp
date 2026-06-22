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
    int id;
    string nim;
    string nama;
    string dosen;
    string waktu;
};

queue<konsultasi> antriankonsultasi;

// Tree (Struktur Organisasi)
struct tree {
    string root;
    unordered_map<string, vector<string>> nodes;
};

tree strukturorganisasi;

// Graph (Navigasi Kampus)
unordered_map<string, vector<pair<string,int>>> graphkampus;

// Stack (Undo KRS)
stack<string> stackkrs;

// Priority Queue
struct layanan{
    int prioritas;
    string nama;
    bool operator<(const layanan& other) const{
        return prioritas < other.prioritas;
    }
};

priority_queue<layanan> layananprioritas;

// Login State
bool sudahlogin = false;
mahasiswa mahasiswaaktif;

// Helper Tree
bool nodeada(tree& pohon, const string& nama){
    if(pohon.root == nama) return true;
    if(pohon.nodes.find(nama) != pohon.nodes.end()) return true;
    for(auto& p : pohon.nodes)
        for(auto& c : p.second)
            if(c == nama) return true;
    return false;
}

void hapussubtree(tree& pohon, const string& nama){
    if(pohon.nodes.find(nama) != pohon.nodes.end()){
        vector<string> anak = pohon.nodes[nama];
        for(auto& c : anak) hapussubtree(pohon, c);
        pohon.nodes.erase(nama);
    }
}

void cetaktree(tree& pohon, const string& nama, const string& prefix, bool islast, bool isroot = false){
    if(isroot) cout << nama << endl;
    else cout << prefix << (islast ? "|___ " : "|-- ") << nama << endl;
    auto it = pohon.nodes.find(nama);
    if(it == pohon.nodes.end() || it->second.empty()) return;
    string newprefix = prefix;
    if(!isroot) newprefix += (islast ? "    " : "|   ");
    auto& children = it->second;
    for(size_t i = 0; i < children.size(); i++){
        bool last = (i == children.size() - 1);
        cetaktree(pohon, children[i], newprefix, last);
    }
}

// Mock Data
void mockdata(){
    akunmahasiswa["hilmy052"] = {"5025251052", "Hilmy Fausta Pratama", "Teknik Informatika", 2, "hilmy123"};
    akunmahasiswa["reza014"] = {"5022251014", "Reza Ferdian", "Teknik Elektro", 2, "reza123"};
    akunmahasiswa["kenzy063"] = {"5010251063", "Kenzy Viriyananda", "Teknik Industri", 2, "kenzy123"};

    graphkampus["Gerbang Utama"] = {{"Fakultas Teknik", 2}, {"Rektorat", 3}};
    graphkampus["Fakultas Teknik"] = {{"Gerbang Utama", 2}, {"Perpustakaan", 1}, {"Kantin", 3}};
    graphkampus["Perpustakaan"] = {{"Fakultas Teknik", 1}, {"Rektorat", 2}, {"Lab Komputer", 3}};
    graphkampus["Kantin"] = {{"Fakultas Teknik", 3}, {"Lab Komputer", 1}};
    graphkampus["Rektorat"] = {{"Gerbang Utama", 3}, {"Perpustakaan", 2}};
    graphkampus["Lab Komputer"] = {{"Perpustakaan", 3}, {"Kantin", 1}};

    strukturorganisasi.root = "Rektor";

    strukturorganisasi.nodes["Rektor"].push_back("WR Akademik");
    strukturorganisasi.nodes["Rektor"].push_back("WR Kemahasiswaan");

    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Teknologi Elektro dan Informatika Cerdas");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Sains dan Analitika Dat");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Teknologi Industri dan Rekayasa Sistem");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Teknik Sipil, Perencanaan, dan Kebumian");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Teknologi Kelautan");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Desain Kreatif dan Bisnis Digital");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Vokasi");
    strukturorganisasi.nodes["WR Akademik"].push_back("Fakultas Kedokteran dan Kesehatan");
}

// Tampil Konsultasi
void tampilkonsultasi(konsultasi k){
    cout << endl;
    cout << "ID    : " << k.id << endl;
    cout << "Nama  : " << k.nama << endl;
    cout << "NIM   : " << k.nim << endl;
    cout << "Dosen : " << k.dosen << endl;
    cout << "Waktu : " << k.waktu << endl;
    cout << endl;
}

// Riwayat
void riwayat(){
    int opsi = 0;
    while(opsi != 4){
        cout << "=================" << endl;
        cout << "Riwayat Aktivitas" << endl;
        cout << "=================" << endl << endl;
        cout << "1. Hapus riwayat terakhir" << endl;
        cout << "2. Hapus semua riwayat" << endl;
        cout << "3. Tampilkan semua riwayat" << endl;
        cout << "4. Kembali" << endl << endl;
        cout << "Pilih Opsi: ";
        cout << endl;
        cin >> opsi;
        if(opsi == 1){
            if(!riwayataktivitas.empty()){
                riwayataktivitas.pop_back();
                cout << "Riwayat berhasil dihapus!" << endl;
            }else cout << "Riwayat sudah kosong!" << endl;
        }else if(opsi == 2){
            riwayataktivitas.clear();
            cout << "Riwayat berhasil dihapus!" << endl;
        }else if(opsi == 3){
            if(riwayataktivitas.empty()) cout << "(Belum ada riwayat aktivitas)" << endl;
            else{
                for(const auto& x : riwayataktivitas) cout << x << " -> ";
                cout << "End of List" << endl;
            }
        }
    }
}

// Antrian Konsultasi
void antrian(){
    cout << "===================================" << endl;
    cout << "\tAntrian Konsultasi" << endl;
    cout << "===================================" << endl << endl;
    int opsi;
    while(true){
        cout << "1. Tambahkan Jadwal Konsultasi" << endl;
        cout << "2. Layani Antrian (Hapus paling depan)" << endl;
        cout << "3. Lihat Antrian depan" << endl;
        cout << "4. Kembali" << endl << endl;
        cout << "Pilih Opsi: ";
        cin >> opsi;
        cout << endl;
        if(opsi == 4){
            return;
        }else if(opsi == 3){
            if(!antriankonsultasi.empty()) tampilkonsultasi(antriankonsultasi.front());
            else cout << "Antrian konsultasi kosong!" << endl;
        }else if(opsi == 2){
            if(!antriankonsultasi.empty()){
                cout << "Melayani antrian paling depan";
                tampilkonsultasi(antriankonsultasi.front());
                riwayataktivitas.push_back("Melayani Konsultasi: " + antriankonsultasi.front().nama + " (NIM: " + antriankonsultasi.front().nim + ")");
                antriankonsultasi.pop();
                cout << "Penghapusan berhasil!" << endl;
            }else cout << "Antrian konsultasi kosong!" << endl;
        }else if(opsi == 1){
            konsultasi k;
            k.id = antriankonsultasi.size() + 1;
            cin.ignore();
            cout << "Masukkan nama: ";
            getline(cin, k.nama);
            cout << "Masukkan NIM: ";
            cin >> k.nim;
            cin.ignore();
            cout << "Masukkan nama dosen: ";
            getline(cin, k.dosen);
            cout << "Masukkan waktu (misal: 12:00 WIB): ";
            getline(cin, k.waktu);
            antriankonsultasi.push(k);
            riwayataktivitas.push_back("Menambahkan Konsultasi: " + k.nama + " (NIM: " + k.nim + ")");
            cout << "Konsultasi berhasil ditambahkan!" << endl << endl;
        }else cout << "Opsi tidak ditemukan!" << endl;
    }
}

// Struktur Organisasi
void struktur(){
    cout << "===================================" << endl;
    cout << "\tStruktur Organisasi Kampus" << endl;
    cout << "===================================" << endl << endl;
    int opsi;
    while(true){
        cout << "1. Tambahkan Jabatan" << endl;
        cout << "2. Hapus Jabatan" << endl;
        cout << "3. Tampilkan Struktur" << endl;
        cout << "4. Kembali" << endl << endl;
        cout << "Pilih Opsi: ";
        cin >> opsi;
        if(opsi == 4){
            return;
        }else if(opsi == 3){
            if(strukturorganisasi.root.empty()) cout << ">> Struktur masih kosong, root belum diset." << endl << endl;
            else{
                cout << endl;
                cetaktree(strukturorganisasi, strukturorganisasi.root, "", true, true);
                cout << endl;
            }
        }else if(opsi == 2){
            string nama;
            cout << "Masukkan nama jabatan yang akan dihapus: ";
            cin.ignore();
            getline(cin, nama);
            if(nama == strukturorganisasi.root) strukturorganisasi.root.clear();
            for(auto& p : strukturorganisasi.nodes){
                auto& children = p.second;
                for(size_t i = 0; i < children.size(); i++){
                    if(children[i] == nama){
                        children.erase(children.begin() + i);
                        break;
                    }
                }
            }
            hapussubtree(strukturorganisasi, nama);
            cout << "Berhasil menghapus \"" << nama << "\" beserta seluruh bawahannya (jika ada)." << endl << endl;
            riwayataktivitas.push_back("Menghapus Jabatan " + nama);
        }else if(opsi == 1){
            if(strukturorganisasi.root.empty()){
                string jabatan;
                cout << "Tree masih kosong. Masukkan nama jabatan tertinggi (root): ";
                cin.ignore();
                getline(cin, jabatan);
                strukturorganisasi.root = jabatan;
                cout << "Root berhasil diset ke " << strukturorganisasi.root << endl << endl;
                riwayataktivitas.push_back("Menambahkan Jabatan " + jabatan);
            }else{
                string parent, jabatanbaru;
                cout << "Masukkan nama atasan (parent): ";
                cin.ignore();
                getline(cin, parent);
                cout << "Masukkan nama jabatan baru: ";
                getline(cin, jabatanbaru);
                strukturorganisasi.nodes[parent].push_back(jabatanbaru);
                cout << "Berhasil menambahkan \"" << jabatanbaru << "\" di bawah \"" << parent << "\"." << endl << endl;
                riwayataktivitas.push_back("Menambahkan Jabatan " + jabatanbaru);
            }
        }else cout << "Opsi tidak ditemukan!" << endl;
    }
}

// Navigasi Kampus
void navigasi(){
    cout << "===================================" << endl;
    cout << "\tNavigasi Kampus (Graph)" << endl;
    cout << "===================================" << endl << endl;
    int opsi;
    while(true){
        cout << "1. Cari Rute Terpendek (Dijkstra)" << endl;
        cout << "2. Tampilkan Semua Lokasi & Jalur" << endl;
        cout << "3. Tambah Lokasi Baru (Vertex)" << endl;
        cout << "4. Tambah Jalur Baru (Edge)" << endl;
        cout << "5. Kembali" << endl << endl;
        cout << "Pilih Opsi: ";
        cin >> opsi;
        cout << endl;
        if(opsi == 5) return;
        else if(opsi == 2){
            cout << "--- Daftar Gedung dan Koneksi Jalan ---" << endl;
            for(auto const& [asal, listtujuan] : graphkampus){
                cout << asal << " terhubung ke:" << endl;
                for(auto const& tetangga : listtujuan) cout << "  -> " << tetangga.first << " (Jarak: " << tetangga.second << ")" << endl;
            }
            cout << endl;
        }else if(opsi == 3){
            string newvertex;
            cout << "Masukkan nama lokasi baru: ";
            cin.ignore();
            getline(cin, newvertex);
            if(graphkampus.find(newvertex) == graphkampus.end()){
                graphkampus[newvertex] = vector<pair<string,int>>();
                cout << "Lokasi \"" << newvertex << "\" berhasil ditambahkan!" << endl << endl;
                riwayataktivitas.push_back("Menambahkan Vertex Navigasi: " + newvertex);
            }else cout << "Lokasi sudah terdaftar!" << endl << endl;
        }else if(opsi == 4){
            }else if(opsi == 4){
                string asal, tujuan;
                int bobot;
                cout << "Masukkan Lokasi Asal: ";
                cin.ignore();
                getline(cin, asal);
                cout << "Masukkan Lokasi Tujuan: ";
                getline(cin, tujuan);
                cout << "Masukkan Jarak/Bobot: ";
                cin >> bobot;
            if(graphkampus.find(asal) == graphkampus.end() || graphkampus.find(tujuan) == graphkampus.end()){
                cout << "Error: Salah satu atau kedua lokasi belum terdaftar!" << endl << endl;
                continue;
            }
            graphkampus[asal].push_back({tujuan, bobot});
            graphkampus[tujuan].push_back({asal, bobot});
            cout << "Jalur antara \"" << asal << "\" dan \"" << tujuan << "\" dengan jarak " << bobot << " berhasil ditambahkan!" << endl << endl;
            riwayataktivitas.push_back("Menambahkan Edge Navigasi: " + asal + " - " + tujuan + " (" + to_string(bobot) + ")");
        }else if(opsi == 1){
            string asal, tujuan;
            cout << "Masukkan Lokasi Asal: ";
            cin.ignore();
            getline(cin, asal);
            cout << "Masukkan Lokasi Tujuan: ";
            getline(cin, tujuan);
            if(graphkampus.find(asal) == graphkampus.end() || graphkampus.find(tujuan) == graphkampus.end()){
                cout << "Lokasi asal atau tujuan tidak valid/tidak ditemukan!" << endl << endl;
                continue;
            }
            unordered_map<string,int> dist;
            unordered_map<string,string> parent;
            for(auto const& [key, val] : graphkampus) dist[key] = 1e9;
            priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pq;
            dist[asal] = 0;
            pq.push({0, asal});
            while(!pq.empty()){
                string u = pq.top().second;
                int d = pq.top().first;
                pq.pop();
                if(d > dist[u]) continue;
                for(auto const& edge : graphkampus[u]){
                    string v = edge.first;
                    int weight = edge.second;
                    if(dist[u] + weight < dist[v]){
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
            if(dist[tujuan] == (int)1e9) cout << "Tidak ada rute dari " << asal << " ke " << tujuan << endl << endl;
            else{
                cout << "Rute terpendek ditemukan dengan total jarak: " << dist[tujuan] << endl;
                vector<string> path;
                string curr = tujuan;
                while(curr != asal){
                    path.push_back(curr);
                    curr = parent[curr];
                }
                path.push_back(asal);
                reverse(path.begin(), path.end());
                cout << "Jalur: ";
                for(size_t i = 0; i < path.size(); i++){
                    cout << path[i];
                    if(i < path.size() - 1) cout << " -> ";
                }
                cout << endl << endl;
                riwayataktivitas.push_back("Mencari rute dari " + asal + " ke " + tujuan + " (Jarak: " + to_string(dist[tujuan]) + ")");
            }
        }else cout << "Opsi tidak ditemukan!" << endl;
    }
}

// Operasi KRS
void operasikrs(){
    cout << "===================================" << endl;
    cout << "\tLayanan KRS" << endl;
    cout << "===================================" << endl << endl;
    int opsi;
    while(true){
        cout << "1. Tambahkan KRS" << endl;
        cout << "2. Hapus pilihan terbaru" << endl;
        cout << "3. Lihat pilihan terbaru" << endl;
        cout << "4. Kembali" << endl << endl;
        cout << "Pilih Opsi: ";
        cin >> opsi;
        cout << endl;
        if(opsi == 4) return;
        else if(opsi == 3){
            if(!stackkrs.empty()) cout << "Pilihan terbaru: " << stackkrs.top() << endl << endl;
            else cout << "KRS kosong!" << endl;
        }else if(opsi == 2){
            if(!stackkrs.empty()){
                cout << "Menghapus KRS: " << stackkrs.top() << endl;
                riwayataktivitas.push_back("Menghapus KRS: " + stackkrs.top());
                stackkrs.pop();
                cout << "Penghapusan berhasil!" << endl;
            }else cout << "KRS kosong!" << endl;
        }else if(opsi == 1){
            string pilihan;
            cout << "Masukkan nama mata kuliah: ";
            cin.ignore();
            getline(cin, pilihan);
            cout << endl;
            stackkrs.push(pilihan);
            riwayataktivitas.push_back("Menambahkan KRS: " + pilihan);
            cout << "Pilihan " << pilihan << " berhasil ditambahkan!" << endl << endl;
        }else cout << "Opsi tidak ditemukan!" << endl;
    }
}

// Prioritas Layanan
void prioritas(){
    cout << "===================================" << endl;
    cout << "\tPrioritas Layanan" << endl;
    cout << "===================================" << endl << endl;
    int opsi;
    while(true){
        cout << "1. Tambahkan Layanan" << endl;
        cout << "2. Hapus pilihan terbaru" << endl;
        cout << "3. Lihat pilihan terbaru" << endl;
        cout << "4. Kembali" << endl << endl;
        cout << "Pilih Opsi: ";
        cin >> opsi;
        cout << endl;
        if(opsi == 4) return;
        else if(opsi == 3){
            if(!layananprioritas.empty()) cout << "Mahasiswa prioritas tertinggi: " << layananprioritas.top().nama << endl;
            else cout << "Antrian prioritas kosong!" << endl;
        }else if(opsi == 2){
            if(!layananprioritas.empty()){
                cout << "Mengambil Mahasiswa prioritas tertinggi: " << layananprioritas.top().nama << endl;
                riwayataktivitas.push_back("Melayani Layanan Prioritas: " + layananprioritas.top().nama);
                layananprioritas.pop();
                cout << "Penghapusan berhasil!" << endl;
            }else cout << "Antrian prioritas kosong!" << endl;
        }else if(opsi == 1){
            string nama, prio;
            cout << "Masukkan nama mahasiswa: ";
            cin >> nama;
            cout << "Masukkan prioritas mahasiswa (Beasiswa/Disabilitas/Tingkat Akhir/Lainnya): ";
            cin.ignore();
            getline(cin, prio);
            int pr;
            if(prio == "Beasiswa") pr = 4;
            else if(prio == "Disabilitas") pr = 3;
            else if(prio == "Tingkat Akhir") pr = 2;
            else pr = 1;
            layananprioritas.push({pr, nama});
            riwayataktivitas.push_back("Menambahkan Layanan Prioritas: " + nama + " (" + prio + ")");
            cout << "Pilihan " << nama << " berhasil ditambahkan!" << endl;
        }else cout << "Opsi tidak ditemukan!" << endl;
    }
}

// Cari Akun
void cariakun(){
    string query;
    cout << "===================================" << endl;
    cout << "Cari Akun (ketik exit untuk keluar)" << endl;
    cout << "===================================" << endl << endl;
    while(query != "exit"){
        cout << "Masukkan Username: ";
        cin >> query;
        cout << endl;
        if(query == "exit") break;
        auto findusername = akunmahasiswa.find(query);
        if(findusername != akunmahasiswa.end()){
            cout << "Username : " << query << endl;
            cout << "Nama     : " << akunmahasiswa[query].nama << endl;
            cout << "NIM      : " << akunmahasiswa[query].nim << endl;
            cout << "Prodi    : " << akunmahasiswa[query].prodi << endl;
            cout << "Semester : " << akunmahasiswa[query].semester << endl << endl;
        }else cout << "Username tidak ditemukan!" << endl << endl;
        riwayataktivitas.push_back("Mencari Akun");
    }
}

// Login
void login(){
    string username, pw;
    cout << "Masukkan Username : ";
    cin >> username;
    auto found = akunmahasiswa.find(username);
    if(found == akunmahasiswa.end()){
        cout << "Error: Mahasiswa tidak ditemukan!" << endl << endl;
        return;
    }
    cout << "Masukkan Password : ";
    cin >> pw;
    if(pw != akunmahasiswa[username].password){
        cout << "Error: Password salah!" << endl << endl;
        return;
    }
    sudahlogin = true;
    mahasiswaaktif = akunmahasiswa[username];
    cout << "Selamat Datang " << akunmahasiswa[username].nama << "!" << endl << endl;
    riwayataktivitas.push_back("Login akun " + username);
}

// Buat Akun
void buatakun(){
    mahasiswa m;
    string username;
    cout << "Masukkan username : ";
    cin >> username;
    cout << "Nama              : ";
    cin.ignore();
    getline(cin, m.nama);
    cout << "NIM               : ";
    cin >> m.nim;
    cout << "Prodi             : ";
    cin.ignore();
    getline(cin, m.prodi);
    cout << "Password          : ";
    cin >> m.password;
    cout << "Semester          : ";
    cin >> m.semester;
    akunmahasiswa[username] = m;
    cout << endl << "Akun sudah ditambahkan!" << endl;
    cout << "Silahkan Login!" << endl << endl;
    riwayataktivitas.push_back("Membuat akun " + username);
}

int main(){
    cout << endl << "==================================================" << endl;
    cout << "Selamat Datang di Smart Campus Navigation System!" << endl;
    cout << "==================================================" << endl << endl;
    mockdata();
    while(!sudahlogin){
        cout << "1. Login" << endl;
        cout << "2. Buat Akun" << endl << endl;
        int logorreg;
        cout << "Pilih Opsi: ";
        cin >> logorreg;
        if(logorreg == 1) login();
        else if(logorreg == 2) buatakun();
        else cout << "Opsi tidak ditemukan!" << endl;
    }
    while(true){
        cout << "==============================================" << endl;
        cout << "Daftar layanan Smart Campus Navigation System" << endl;
        cout << "==============================================" << endl;
        cout << "1. Riwayat Aktivitas" << endl;
        cout << "2. Antrian Konsultasi" << endl;
        cout << "3. Struktur Organisasi" << endl;
        cout << "4. Navigasi Kampus" << endl;
        cout << "5. Operasi KRS" << endl;
        cout << "6. Prioritas Layanan" << endl;
        cout << "7. Cari Akun" << endl << endl;
        int layanan;
        cout << "Pilih Layanan: ";
        cin >> layanan;
        cout << endl;
        switch(layanan){
        case 1:
            riwayat();
            break;
        case 2:
            antrian();
            break;
        case 3:
            struktur();
            break;
        case 4:
            navigasi();
            break;
        case 5:
            operasikrs();
            break;
        case 6:
            prioritas();
            break;
        case 7:
            cariakun();
            break;
        default:
            cout << "Layanan tidak ditemukan!" << endl;
        }
        cout << endl;
    }
    return 0;
}
