#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void suma(const vector<int> &nombres, vector<bool> &usats, int suma_actual,
          int idx, const int &s) {

  // cas base
  if (suma_actual == s) {
    cout << "{";
    bool first = true;
    for (int i = 0; i < int(usats.size()); ++i) {
      if (usats[i] == true) {
        if (first == true) {
          first = false;
          cout << nombres[i];
        } else {
          cout << "," << nombres[i];
        }
      }
    }
    cout << "}" << endl;
    return;
  }

  if (idx == int(nombres.size()))
    return;

  // cas recursiu
  usats[idx] = true;
  suma(nombres, usats, suma_actual + nombres[idx], idx + 1, s);

  usats[idx] = false;
  suma(nombres, usats, suma_actual, idx + 1, s);
}

int main() {
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
