#include <iostream>
#include <iterator>
#include <vector>

using namespace std;


void suma(const vector<int>& nombres, vector<bool>& usats, int suma_actual, int i, const int& s){

  // cas base
  if (i  == int(usats.size())){

    if (suma_actual == s){
      cout << "{";
      bool first = true;
      for (int i = 0; i < int(usats.size()); ++i) {
        if (usats[i] == true){
          if (first == true){
            first = false;
            cout << nombres[i];
          }
          else{
            cout << "," << nombres[i];
          }
        }
      }
      cout << "}" << endl;
    }
    return;
  }

  // cas recursiu
  usats[i] = true;
  suma(nombres, usats, suma_actual + nombres[i], i+1, s);

  usats[i] = false;
  suma(nombres, usats, suma_actual, i+1, s);
  
}


int main () {
  int s, n;

  cin >> s >> n;
  vector<int> nombres(n);

  for (int i = 0; i < n; ++i) {
    cin >> nombres[i];
  }

  vector<bool> usats(n, false);
  int suma_actual = 0;
  int i = 0;


  suma(nombres, usats, suma_actual, i, s);

  return 0;
}
