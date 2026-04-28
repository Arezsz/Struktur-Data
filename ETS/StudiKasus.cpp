#include <iostream>
#include <string>

using namespace std;

// Struktur Node untuk menampung data mahasiswa secara dinamis
struct Node {
    string nama;
    Node* next;
};

class AntrianAkademik {
private:
    Node* front;
    Node* rear;

public:
    // Constructor: Kondisi awal antrian kosong
    AntrianAkademik() {
        front = NULL;
        rear = NULL;
    }

    // Fungsi Enqueue (Tambah ke antrian)
    void enqueue(string nama) {
        Node* nodeBaru = new Node();
        nodeBaru->nama = nama;
        nodeBaru->next = NULL;

        if (front == NULL) {
            front = nodeBaru;
            rear = nodeBaru;
        } else {
            rear->next = nodeBaru;
            rear = nodeBaru;
        }
        cout << "[+] Mahasiswa '" << nama << "' berhasil masuk ke antrian.\n";
    }

    // Fungsi Dequeue (Panggil dari antrian)
    void dequeue() {
        if (front == NULL) {
            cout << "[!] Tidak ada antrian mahasiswa saat ini.\n";
            return;
        }

        Node* temp = front;
        cout << "[LOKET] Memanggil mahasiswa: '" << front->nama << "' ke loket.\n";
        
        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;
    }

    // Fungsi menampilkan status antrian
    void tampilkanAntrian() {
        cout << "\n--- STATUS ANTRIAN SAAT INI ---\n";
        
        if (front == NULL) {
            cout << "Kondisi: KOSONG\n";
        } else {
            cout << "Front (Depan)   : " << front->nama << "\n";
            cout << "Rear (Belakang) : " << rear->nama << "\n";
            cout << "Daftar Tunggu   : ";
            
            Node* bantu = front;
            while (bantu != NULL) {
                cout << "[" << bantu->nama << "] ";
                bantu = bantu->next;
            }
            cout << "\n";
        }
        cout << "-------------------------------\n";
    }
};

int main() {
    AntrianAkademik loket;
    int pilihan;
    string nama;

    do {
        cout << "=== MENU LAYANAN AKADEMIK ===\n";
        cout << "1. Ambil Antrian (Tambah Mahasiswa)\n";
        cout << "2. Panggil Loket (Layani Mahasiswa)\n";
        cout << "3. Tampilkan Status Antrian\n";
        cout << "4. Keluar Program\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;
        
        // Membersihkan karakter newline (\n) dari buffer setelah input angka
        // agar fungsi getline di bawahnya bisa berjalan normal
        cin.ignore(); 

        cout << "\n";
        switch (pilihan) {
            case 1:
                cout << "Masukkan nama mahasiswa: ";
                getline(cin, nama); // Menggunakan getline agar bisa input nama dengan spasi
                loket.enqueue(nama);
                break;
            case 2:
                loket.dequeue();
                break;
            case 3:
                loket.tampilkanAntrian();
                break;
            case 4:
                cout << "Menutup sistem antrian. Terima kasih!\n";
                break;
            default:
                cout << "[!] Pilihan tidak valid. Silakan masukkan angka 1-4.\n";
        }
        cout << "\n";

    } while (pilihan != 4);

    return 0;
}