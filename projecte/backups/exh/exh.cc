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

  Tactic() : points(0), price(0) {}
  Tactic(string por, vector<string>& def, vector<string>& mig, vector<string>& dav,
         int points, int price)
      : por(por), def(def), mig(mig), dav(dav), points(points), price(price) {}

  // void showTactic() {
  //   cout << "Por: " << this->por << endl;
  //   cout << "Def: ";
  //   for (string p : this->def) {
  //     cout << p << " ";
  //   }
  //   cout << endl;
  //   cout << "Mig: ";
  //   for (string p : this->mig) {
  //     cout << p << " ";
  //   }
  //   cout << endl;

  //   cout << "Dav: ";
  //   for (string p : this->dav) {
  //     cout << p << " ";
  //   }
  //   cout << endl;
  //   cout << "Points: " << this->points << endl;
  //   cout << "Price: " << this->price << endl;
  // }
};

using Players = vector<Player>;

// Constants
int N1, N2, N3, T, J;
Players porters;
Players defenses;
Players migcampistes;
Players davanters;
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

void exh(Tactic &t, const char *output, int idx, bool fullPor, bool fullDef,
         bool fullMig, bool fullDav) {

  if(t.price > T){
    return;
  }

  if (fullDav and t.points > MAX_POINTS) {
    // auto end = high_resolution_clock::now();
    // duration<double> duration = end - startTimer;
    MAX_POINTS = t.points;
    write(t, output);
    return;
  }

  if (!fullPor) {
    for (const Player& p : porters) {
      t.por = p.name;
      t.price += p.price;
      t.points += p.points;

      // auto startTimer = high_resolution_clock::now();
      exh(t, output, 0, true, false, false, false);

      t.price = 0;
      t.points = 0;
    }
  } else if (!fullDef) {
    if (idx > defenses.size() - 1)
      return;

    if (t.def.size() == N1) {
      exh(t, output, 0,  true, true, false, false);
    }
    else{
      t.def.push_back(defenses[idx].name);
      t.price += defenses[idx].price;
      t.points += defenses[idx].points;
      exh(t, output, idx + 1, true, false, false, false);

      t.def.pop_back();
      t.price -= defenses[idx].price;
      t.points -= defenses[idx].points;
      exh(t, output, idx + 1, true, false, false, false);
    }
  } else if (!fullMig) {
    if (idx > migcampistes.size() - 1)
      return;

    if (t.mig.size() == N2) {
      exh(t, output, 0, true, true, true, false);
    }else{
      t.mig.push_back(migcampistes[idx].name);
      t.price += migcampistes[idx].price;
      t.points += migcampistes[idx].points;
      exh(t, output, idx + 1, true, true, false, false);

      t.mig.pop_back();
      t.price -= migcampistes[idx].price;
      t.points -= migcampistes[idx].points;
      exh(t, output, idx + 1, true, true, false, false);
    }
  } else if (!fullDav) {
    if (idx > davanters.size() - 1)
      return;

    if (t.dav.size() == N3) {
      exh(t, output, 0, true, true, true, true);
    }else{
      t.dav.push_back(davanters[idx].name);
      t.price += davanters[idx].price;
      t.points += davanters[idx].points;
      exh(t, output, idx + 1, true, true, true, false);

      t.dav.pop_back();
      t.price -= davanters[idx].price;
      t.points -= davanters[idx].points;
      exh(t, output, idx + 1, true, true, true, false);
    }
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
    int id = 1;
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

      if (preu <= J) {
        if (posicio == "por") {
          porters.push_back(Player(id, nom, posicio, preu, club, punts));
        } else if (posicio == "def") {
          defenses.push_back(Player(id, nom, posicio, preu, club, punts));
        } else if (posicio == "dav") {
          davanters.push_back(Player(id, nom, posicio, preu, club, punts));
        } else if (posicio == "mig") {
          migcampistes.push_back(Player(id, nom, posicio, preu, club, punts));
        }
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


  
  exh(tactic, argv[3], 0, false, false, false, false);

  return 0;
}