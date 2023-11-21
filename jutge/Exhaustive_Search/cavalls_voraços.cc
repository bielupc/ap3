#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> dirs = {{-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};


bool check_valid(int i, int j, const vector<vector<int>>& T){
  int n = int(T.size());
  int m = int(T[0].size());
  return 0 <= i and i < n and 0 <= j and j < m; 
}


//taules, comptador de monedes, i, j, solucio parcial
int monedes(const vector<vector<int>>& T,
            vector<vector<bool>>& sol,
            int i, int j, int monedes_actuals){


  if(j == int(T[0].size())){
    j = 0;
    i++;
  }
  
  if (i == int(T.size())){
    return monedes_actuals;
  }
  else{
    // no posem el cavall
    sol[i][j] = false;
    int cas1 = monedes(T, sol, i, j+1, monedes_actuals);

    // posem el cavall

    bool valid = true;
     
    // comprovar que sigui un cavall vàlid
    for (pair<int, int>& dir: dirs) {
      int n_i = i + dir.first;
      int n_j = j + dir.second;

      if(check_valid(n_i, n_j, T) and sol[n_i][n_j]) valid = false;
    }

    int cas2 = 0;

    if (valid){
      sol[i][j] = true;
      cas2 = monedes(T, sol, i, j+1, monedes_actuals + T[i][j]);
    }
    
    return max(cas1, cas2);

  }
}

int main () {
  int n, m;

  while (cin >> n >> m) {       
    vector<vector<int>> T(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++){
        cin >> T[i][j];
      }
    }

    vector<vector<bool>> sol(n, vector<bool>(m));
    cout << monedes(T, sol, 0, 0, 0) << endl;
  }

  return 0;
}
