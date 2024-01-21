#include <iostream>
#include <vector>

using namespace std;



int main () {
  int m, n;

  while (cin >> m >> n) {
    vector<vector<int>> M(n+1, vector<int>(n+1));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++){
        cin >> M[i][j];
      }
    }

    int premi = 0;


    cout << digit() << endl;
  }
  
  return 0;
}
