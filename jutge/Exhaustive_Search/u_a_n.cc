#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void print(const int n, vector<int> &v) {
  cout << "(";
  bool first = true;
  for (int i = 0; i < n; ++i) {
    if (first == true) {
      first = false;
      cout << v[i];
    } else {
      cout << "," << v[i];
    }
  }
  cout << ")" << endl;
};

void generar(const int &n, vector<bool> &visited, const vector<int> &numbers,
             vector<int> &sol, int idx) {

  if (!visited[idx]) {
    visited[idx] = true;
    sol.push_back(numbers[idx]);
    for (int i = idx + 1; i <= n; ++i) {
      generar(n, visited, numbers, sol, i);
      sol.push_back(1);
      print(n, sol);
    }
  } else { // cas base
    return;
  }
}

int main() {
  int n;
  cin >> n;

  vector<bool> visited(n + 1, false);
  vector<int> numbers(n + 1);
  iota(numbers.begin(), numbers.end(), 0);

  vector<int> sol;

  generar(n, visited, numbers, sol, 2);

  return 0;
}
