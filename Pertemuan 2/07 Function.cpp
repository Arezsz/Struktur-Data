#include <bits/stdc++.h>
using namespace std;


void vowelorconsonant(char x){

if(x == 'a' || x == 'i' || x == 'u' || x == 'e' ||
   x == 'o' || x == 'A' || x == 'I' || x == 'U' ||
   x == 'E' || x == 'O'){
    cout << "VOWEL" << endl;
   }
   else{
    cout << "CONSONANT" << endl;
   }


}


int main(){

    vowelorconsonant('c');
    vowelorconsonant('E');
    return 0;


}
