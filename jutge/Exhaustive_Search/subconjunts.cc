#include <asm-generic/errno.h>
#include <iostream>
#include <vector>

using namespace std;


void subconjunts(const vector<string>& paraules, vector<bool>& escollit, int idx, int mida, const int m){

  if (mida > m) return;
  if (mida + (int(escollit.size()) - idx)  < m) return;

  if (idx == int(escollit.size())){
    cout << "{";
    bool primer = true;

    for (uint i = 0; i < escollit.size(); ++i){
      if (escollit[i]) {
        if(not primer) cout << ",";
        else primer = false;
        cout << paraules[i];
      }
    }
    cout << "}" << endl;
  }
  else {

    escollit[idx] = false;
    subconjunts(paraules,escollit,idx+1,mida,m);

    escollit[idx] = true;
    subconjunts(paraules,escollit,idx+1,mida+1,m);
  }
}

int main () {
  int m, n;
  cin >> m >> n;

  vector<string> paraules(n);

  vector<bool> escollit(n, false);

  for (int i = 0; i < n; ++i) {
    cin >> paraules[i];
  }

  subconjunts(paraules, escollit, 0, 0, m);
  
  return 0;
}
