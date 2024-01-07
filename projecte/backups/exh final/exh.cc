#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace std::chrono;

class Player {
public:
  int id;
  string name;
  string position;
  int price;
  string club;
  int points;

  Player(int ident, const string &n, const string &pos, int pr, const string &c,
         int p):
         id(ident), name(n), position(pos), price(pr), club(c), points(p) {}
};

class Tactic {
public:
  string por;
  vector<string> def;
  vector<string> mig;
  vector<string> dav;
  int points;
  int price;

  Tactic() : por(""), points(0), price(0) {}
  Tactic(string por, vector<string>& def, vector<string>& mig, vector<string>& dav,
         int points, int price)
      : por(por), def(def), mig(mig), dav(dav), points(points), price(price) {}

  void showTactic() {
    cout << "Por: " << this->por << endl;
    cout << "Def: ";
    for (string p : this->def) {
      cout << p << " ";
    }
    cout << endl;
    cout << "Mig: ";
    for (string p : this->mig) {
      cout << p << " ";
    }
    cout << endl;

    cout << "Dav: ";
    for (string p : this->dav) {
      cout << p << " ";
    }
    cout << endl;
    cout << "Points: " << this->points << endl;
    cout << "Price: " << this->price << endl;
  }
};

using Players = vector<Player>;

// Constants
int N1, N2, N3, T, J;
Players players;
int MAX_POINTS = -1;

string print_players(const string label, const vector<string>& names) {
  stringstream phrase;
  phrase << label << ": ";
  bool first = true;
  for (string name: names) {
    if (first) {
      phrase << name;
      first = false;
    } else {
      phrase << ";";
      phrase << name;
    }
  }
  return phrase.str();
}

void write(Tactic &t, const char *output) {
  ofstream file(output);
  if (file.is_open()) {

    // output << fixed << setprecision(1) << duration.count() << endl;
    file << "2.3" << endl;

    file << "POR: " << t.por<< endl;
    file << print_players("DEF", t.def) << endl;
    file << print_players("MIG", t.mig) << endl;
    file << print_players("DAV", t.dav) << endl;
    file << "Punts: " << t.points << endl;
    file << "Preu: " << t.price << endl;
    file.close();
  } else {
    cout << "Unable to open output file";
    exit(1);
  }
}

void exh(Tactic &t, const char *output, int idx) {

  // cout << "Depth: " << idx << ", Price: " << t.price << ", Points: " << t.points << endl;


  // Main prunings
  if(t.price > T) return;
  
  if (idx > int(players.size() - 1)) return; 

  // if ((not t.por.empty()) and t.def.size() == N1 and t.mig.size() == N2 and t.dav.size() == N3 and t.points > MAX_POINTS) {
  // // if (t.points > MAX_POINTS){
  //   // auto end = high_resolution_clock::now();
  //   // duration<double> duration = end - startTimer;
  //   MAX_POINTS = t.points;
  //   write(t, output);
  //   // t.showTactic();
  //   return;
  // }

  if ((not t.por.empty()) and int(t.def.size()) == N1 and int(t.mig.size()) == N2 and int(t.dav.size()) == N3) {
    // auto end = high_resolution_clock::now();
    // duration<double> duration = end - startTimer;
    if (t.points > MAX_POINTS){
      MAX_POINTS = t.points;
      t.showTactic();
    }
    // write(t, output);
    return;
  }

  if (players[idx].position == "por" and t.por.empty()) {
    t.por = players[idx].name;
    t.price += players[idx].price;
    t.points += players[idx].points;

    // auto startTimer = high_resolution_clock::now();
    exh(t, output, idx+1);

    t.price -= players[idx].price;
    t.points -= players[idx].points;
    t.por = "";
    exh(t, output, idx+1);
  }

  else if (players[idx].position == "def" and int(t.def.size()) < N1) {
    t.def.push_back(players[idx].name);
    t.price += players[idx].price;
    t.points += players[idx].points;
    exh(t, output, idx + 1);

    t.def.pop_back();
    t.price -= players[idx].price;
    t.points -= players[idx].points;
    exh(t, output, idx + 1);
    }

    else if (players[idx].position == "mig" and int(t.mig.size()) < N2) {
    t.mig.push_back(players[idx].name);
    t.price += players[idx].price;
    t.points += players[idx].points;
    exh(t, output, idx + 1);

    t.mig.pop_back();
    t.price -= players[idx].price;
    t.points -= players[idx].points;
    exh(t, output, idx + 1);
    }
   else if (players[idx].position == "dav" and int(t.dav.size()) < N3) {
    t.dav.push_back(players[idx].name);
    t.price += players[idx].price;
    t.points += players[idx].points;
    exh(t, output, idx + 1);

    t.dav.pop_back();
    t.price -= players[idx].price;
    t.points -= players[idx].points;
    exh(t, output, idx + 1);
  }
  else{
    exh(t, output, idx + 1);
  }

}

int main(int argc, char const *argv[]) {
  // Execution syntax
  if (argc != 4) {
    cout << "Syntax: " << argv[0] << " <data_base.txt> <query.txt> <output.txt>"
         << endl;
    exit(1);
  }

  // Reads query
  ifstream query(argv[2]);
  if (query.is_open()) {
    query >> N1 >> N2 >> N3 >> T >> J;
    query.close();
  } else {
    cout << "Unable to read query";
    exit(1);
  }

  // Reads data base
  ifstream db(argv[1]);
  if (db.is_open()) {
    
    while (not db.eof()) {
      string nom, posicio, club;
      int punts, preu;
      getline(db, nom, ';');
      if (nom == "")
        break;
      getline(db, posicio, ';');
      db >> preu;
      char aux;
      db >> aux;
      getline(db, club, ';');
      db >> punts;
      string aux2;
      getline(db, aux2);
      int id = 1;
      if (preu <= J) {
        players.push_back(Player(id, nom, posicio, preu, club, punts));
      }
      ++id;
    }
    db.close();
  } else {
    cout << "Unable to read db";
    exit(1);
  }

  // Executes exhaustive search
  Tactic tactic;
  exh(tactic, argv[3], 0);

  return 0;
}