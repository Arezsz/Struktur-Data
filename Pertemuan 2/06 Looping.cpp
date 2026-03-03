#include <bits/stdc++.h>
using namespace std;

int main(){

    int rows, columns, number = 1, i;

    cin >> i;
    for(rows = 0; rows <= i;rows++){
        for(columns = 0; columns < rows; columns++){
        cout << number << " ";
        number++;

        }
        cout << "\n";
    }
    return 0;


}
