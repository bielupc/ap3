#include <iostream>
#include <vector>

using namespace std;

int millor (const vector<vector<int>>& M,
	    int nombre, int digits,
	    vector<bool>& used, int premi, int m){
  int n = M.size() - 1;
  if (digits == n) return premi;
  else {
    int maxim = 0;
    for (int d = 1; d <= n; ++d) {
      if (not used[d] and (nombre*10 + d)%m != 0) {
	used[d] = true;
	maxim = max(maxim,millor(M,10*nombre+d,digits+1,used,premi + M[nombre%10][d],m)); // nota: funciona quan nomes tenim un digit perque hem inicialitat la matriu M a zero
	used[d] = false;
      }
    }
    return maxim;
  }
}

int millor (const vector<vector<int>>& M, int m) {
  int nombre = 0;
  int digits = 0;
  int premi = 0;
  int n = M.size() - 1;
  vector<bool> used(n+1,false);
  return millor(M,nombre,digits,used,premi,m);
}

int main () {
  int m, n;
  while (cin >> m >> n) {
    vector<vector<int>> M(n+1,vector<int>(n+1,0));
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
	cin >> M[i][j];
    cout << millor(M,m) << endl;
  }
}
