#include <iostream>
#include <unordered_map>
using namespace std;

struct user {
    string password;
};

int main() {
    unordered_map<string, user> akun;

    akun["fajar"] = {"12345"};
    akun["andi"] = {"abcde"};

    string username, password;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if(akun.count(username) && akun[username].password == password)
        cout << "Login berhasil";
    else
        cout << "Login gagal";

    return 0;
}
