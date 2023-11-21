#include <vector>
#include <iostream>

using namespace std;


void escriu(const vector<char>& voc, const vector<char>& con, vector<char>& sol, vector<bool>& usedCon, vector<bool>& usedVoc, int idx){

  if (idx == int(sol.size())){
    for (char c : sol) cout << c;
    cout << endl;
  }
  
  else{
    const vector<char>& lletres = (idx%2 == 0 ? con : voc);
    vector<bool>& used = (idx%2 == 0 ? usedCon: usedVoc);

    for (uint i = 0; i < lletres.size() ; ++i) {
      if ( not used[i]) {
        sol[idx] = lletres[i];
        used[i] = true;
        escriu(voc, con, sol, usedCon, usedVoc, idx+1);
        used[i] = false;
      }
    }
  }
  
}


int main () {
  int n;
  cin >> n;

  vector<char> voc(n), con(n);
  for (int i = 0; i < n; ++i) cin >> con[i];
  for (int i = 0; i < n; ++i) cin >> voc[i];

  vector<char> sol(2*n);
  vector<bool> usedCon(n, false);
  vector<bool> usedVoc(n, false);
  int idx = 0;

  escriu(voc, con, sol, usedCon, usedVoc, idx);
  
  return 0;
}
