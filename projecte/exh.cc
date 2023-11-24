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
int MAX_POINTS = 0;

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



void write(Tactic& t, const char *output){
  ofstream file(output);
  if (file.is_open()){

    // output << fixed << setprecision(1) << duration.count() << endl;
    file << "POR: " << players[t.por].name << endl;
    file << print_players("DEF", t.def) << endl;
    file << print_players("MIG", t.mig) << endl;
    file << print_players("DAV", t.dav) << endl;
    file << "Punts: " << t.points << endl;
    file << "Preu: " << t.price << endl;
    file.close();
  }
  else{
    cout << "Unable to open file";
    exit(1);
  }

}

void exh(Tactic& t, const char *output, int idx){


  if (t.def.size() == N1 and t.mig.size() == N2 and t.dav.size() == N3 and t.points > MAX_POINTS)
  {
    write(t, output);
  }

  





  

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

    vector<int> def;
    vector<int> mig;
    vector<int> dav;

    def.push_back(65);
    def.push_back(66);
    def.push_back(67);

    mig.push_back(65);
    mig.push_back(66);
    mig.push_back(67);

    dav.push_back(65);
    dav.push_back(66);
    dav.push_back(67);

    Tactic tactic = Tactic(64, def, mig, dav, 7, 4);

    // Executes exhaustive search
    // auto start = high_resolution_clock::now();
    // Tactic tactic;
    // Tactic tactic = Tactic();
    exh(tactic, argv[3]);
    // auto end = high_resolution_clock::now();
    // duration<double> duration = end - start;


    // Writes output


    return 0;
}