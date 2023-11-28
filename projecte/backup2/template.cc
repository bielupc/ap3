#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace std::chrono;

class Player {
public:
  int    id;
  string name;
  string position;
  int    price;
  string club;
  int    points;

  Player(int ident, const string& n, const string& pos, int pr, const string& c, int p):
    id(ident), name(n), position(pos), price(pr), club(c), points(p){}
};

using Players = vector<Player>;

class Tactic {
public:
  int por;
  vector<int> def;
  vector<int> mig;
  vector<int> dav;
  int points;
  int price;


  Tactic(){}
  Tactic(int por, vector<int>& def, vector<int>& mig, vector<int>& dav, int points, int price):
    por(por), def(def), mig(mig), dav(dav), points(points), price(price){}
};

// Constants 
int N1, N2, N3, T, J;
Players players;

void exh(Tactic& tactic){


}

string print_players(const string label, const vector<int>& ids){
  stringstream phrase;
  phrase << label << ": ";
  bool first = true;
  for (int id: ids){
    if (first){
      phrase << players[id].name;
      first = false;
    } 
    else{
      phrase << ";";
      phrase << players[id].name;
    }
  }
  return phrase.str();
}


int main(int argc, char const *argv[])
{
    // Execution syntax
    if (argc != 4)
    {
        cout << "Syntax: " << argv[0] << " <data_base.txt> <query.txt> <output.txt>" << endl;
        exit(1);
    }

    // Reads data base
    ifstream db(argv[1]);
    if (db.is_open())
    {
      int id = 0;
      while (not db.eof()) {
          string nom, posicio, club;
          int punts, preu;
          getline(db,nom,';');    if (nom == "") break;
          getline(db,posicio,';');
          db >> preu;
          char aux; db >> aux;
          getline(db,club,';');
          db >> punts;
          string aux2;
          getline(db,aux2);
          // The player id is the index in the players vector.
          players.push_back(Player(id, nom, posicio, preu, club, punts));
          ++id;
      }
      db.close();
    }
    else{
      cout << "Unable to open file";
      exit(1);
    }

    // Reads query
    ifstream query(argv[2]);
    if (query.is_open()){
      query >> N1 >> N2 >> N3 >> T >> J;
      query.close();
    }
    else{
      cout << "Unable to open file";
      exit(1);
    }

    // Executes exhaustive search
    auto start = high_resolution_clock::now();
    // Tactic tactic;
    Tactic tactic = Tactic();
    exh(tactic);
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;

    // vector<int> def;
    // vector<int> mig;
    // vector<int> dav;

    // def.push_back(65);
    // def.push_back(66);
    // def.push_back(67);

    // mig.push_back(65);
    // mig.push_back(66);
    // mig.push_back(67);

    // dav.push_back(65);
    // dav.push_back(66);
    // dav.push_back(67);

    // tactic = Tactic(64, def, mig, dav, 7, 4);


    // Writes output
    ofstream output(argv[3]);
    if (output.is_open()){
      output << fixed << setprecision(1) << duration.count() << endl;
      output << "POR: " << players[tactic.por].name << endl;
      output << print_players("DEF", tactic.def) << endl;
      output << print_players("MIG", tactic.mig) << endl;
      output << print_players("DAV", tactic.dav) << endl;
      output << "Punts: " << tactic.points << endl;
      output << "Preu: " << tactic.price << endl;
      output.close();
    }
    else{
      cout << "Unable to open file";
      exit(1);
    }

    return 0;
}
