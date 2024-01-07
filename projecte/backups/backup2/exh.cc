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
         int p)
      : id(ident), name(n), position(pos), price(pr), club(c), points(p) {}
};

class Tactic {
public:
  int por = -1;
  vector<int> def;
  vector<int> mig;
  vector<int> dav;
  int points;
  int price;

  Tactic() : por(-1), points(0), price(0) {}
  Tactic(int por, vector<int> &def, vector<int> &mig, vector<int> &dav,
         int points, int price)
      : por(por), def(def), mig(mig), dav(dav), points(points), price(price) {}

  void showTactic() {
    cout << "Por: " << this->por << endl;
    cout << "Def: ";
    for (int p : this->def) {
      cout << p << " ";
    }
    cout << endl;
    cout << "Mig: ";
    for (int p : this->mig) {
      cout << p << " ";
    }
    cout << endl;

    cout << "Dav: ";
    for (int p : this->dav) {
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
Players porters;
Players defenses;
Players migcampistes;
Players davanters;
int MAX_POINTS = 0;

string print_players(const string label, const vector<int> &ids,
                     Players &players) {
  stringstream phrase;
  phrase << label << ": ";
  bool first = true;
  for (int id : ids) {
    if (first) {
      phrase << players[id].name;
      first = false;
    } else {
      phrase << ";";
      phrase << players[id].name;
    }
  }
  return phrase.str();
}

void write(Tactic &t, const char *output) {
  ofstream file(output);
  if (file.is_open()) {

    // output << fixed << setprecision(1) << duration.count() << endl;
    file << "POR: " << porters[t.por].name << endl;
    file << print_players("DEF", t.def, defenses) << endl;
    file << print_players("MIG", t.mig, migcampistes) << endl;
    file << print_players("DAV", t.dav, davanters) << endl;
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

  // test
  if (fullMig) {
    MAX_POINTS = t.points;
    // t.showTactic();
    // cout << "________________" << endl;
    return;
  }

  // idx

  if (fullPor and fullDef and fullMig and fullDav and t.points > MAX_POINTS) {
    write(t, output);
    return;
  }

  if (!fullPor) {
    for (Player p : porters) {
      t.por = p.id;
      t.price += p.price;
      t.points += p.points;
      exh(t, output, 0, true, false, false, false);

      t.price -= p.price;
      t.points -= p.points;
    }
  } else if (!fullDef) {
    if (idx > defenses.size())
      return;

    if (t.def.size() == N1) {
      exh(t, output, 0, true, true, false, false);
    }
    else{
      t.def.push_back(defenses[idx].id);
      t.price += defenses[idx].price;
      t.points += defenses[idx].points;
      exh(t, output, idx + 1, true, false, false, false);

      t.def.pop_back();
      t.price -= defenses[idx].price;
      t.points -= defenses[idx].points;
      exh(t, output, idx + 1, true, false, false, false);
    }
  } else if (!fullMig) {
    if (idx > migcampistes.size())
      return;

    if (t.mig.size() == N2) {
      exh(t, output, 0, true, true, true, false);
    }else{
      t.mig.push_back(migcampistes[idx].id);
      t.price += migcampistes[idx].price;
      t.points += migcampistes[idx].points;
      exh(t, output, idx + 1, true, true, false, false);

      t.mig.pop_back();
      t.price -= migcampistes[idx].price;
      t.points -= migcampistes[idx].points;
      exh(t, output, idx + 1, true, true, false, false);
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
    int id = 0;
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
      ++id;
      }
    }
    db.close();
  } else {
    cout << "Unable to read db";
    exit(1);
  }

  // Executes exhaustive search
  // auto start = high_resolution_clock::now();
  Tactic tactic;
  exh(tactic, argv[3], 0, false, false, false, false);
  // auto end = high_resolution_clock::now();
  // duration<double> duration = end - start;

  return 0;
}