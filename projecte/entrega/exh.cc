#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Global start execution timer
time_point<high_resolution_clock> START_EX;

// Data structures 
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

  friend ostream & operator << (ostream &out, const Player& p) {
    out << p.name << "(id " << p.id << ") price = " << p.price << " points = " << p.points;
    return out;
  }
};

class Tactic {
public:
  string goal;
  vector<string> def;
  vector<string> mid;
  vector<string> str;
  int price;
  int points;

  Tactic():price(0), points(0) {}
  Tactic(string g, vector<string> d, vector<string> m, vector<string> s, int pr, int po):
  goal(g), def(d), mid(m), str(s), price(pr), points(po){}

  friend ostream & operator << (ostream &out, const Tactic& t) {
    auto END_EX = high_resolution_clock::now();
    out << fixed << setprecision(1) << duration_cast<duration<double>>(END_EX - START_EX).count() << endl;

    out << "POR: " << t.goal << endl;
    out << "DEF: ";
    for(uint i = 0; i < t.def.size(); ++i){
      out << t.def[i];
      if(i != t.def.size() - 1) out << ";";
    }
    out << endl;
    out << "MIG: ";
    for(uint i = 0; i < t.mid.size(); ++i){
      out << t.mid[i];
      if(i != t.mid.size() - 1) out<< ";";
    }
    out << endl;
    out << "DAV: ";
    for(uint i = 0; i < t.str.size(); ++i){
      out << t.str[i];
      if(i != t.str.size() - 1) out << ";";
    }
    out << endl;
    out << "Punts: " << t.points << endl;
    out << "Preu: " << t.price << endl;
    return out;
  }
};


// Global constants
vector<Player> PLAYERS;
int N1, N2, N3, T, J;
int MAX_POINTS = -1;


void exh(Tactic& t, int i, char const *output){
  // Base Cases
  if (i >= int(PLAYERS.size())) return;

  if (PLAYERS[i].price > J){
    exh(t, i+1, output);
  } 

  if (t.price > T) return;

  if (not t.goal.empty() and int(t.def.size()) == N1 and int(t.mid.size()) == N2 and int(t.str.size()) == N3){
    if(t.points > MAX_POINTS){
      MAX_POINTS = t.points;
      ofstream file(output);
      file << t << endl;
      file.close();
    }
    return;
  }

  // Recursive Cases
  if(PLAYERS[i].position == "por"){
    if(t.goal.empty()){
      t.goal = PLAYERS[i].name;
      t.price += PLAYERS[i].price;
      t.points += PLAYERS[i].points;
      exh(t, i+1, output);

      t.goal = "";
      t.price -= PLAYERS[i].price;
      t.points -= PLAYERS[i].points;
      exh(t, i+1, output);
    }
  }

  else if(PLAYERS[i].position == "def"){
    if(int(t.def.size()) < N1){
      t.def.push_back(PLAYERS[i].name);
      t.price += PLAYERS[i].price;
      t.points += PLAYERS[i].points;
      exh(t, i+1, output);

      t.def.pop_back();
      t.price -= PLAYERS[i].price;
      t.points -= PLAYERS[i].points;
      exh(t, i+1, output);
    }
  }
  else if(PLAYERS[i].position == "mig"){
    if(int(t.mid.size()) < N2){
      t.mid.push_back(PLAYERS[i].name);
      t.price += PLAYERS[i].price;
      t.points += PLAYERS[i].points;
      exh(t, i+1, output);

      t.mid.pop_back();
      t.price -= PLAYERS[i].price;
      t.points -= PLAYERS[i].points;
      exh(t, i+1, output);
    }
  }
  else if(PLAYERS[i].position == "dav"){
    if(int(t.str.size()) < N3){
      t.str.push_back(PLAYERS[i].name);
      t.price += PLAYERS[i].price;
      t.points += PLAYERS[i].points;
      exh(t, i+1, output);

      t.str.pop_back();
      t.price -= PLAYERS[i].price;
      t.points -= PLAYERS[i].points;
      exh(t, i+1, output);
    }
  }
}


int main(int argc, char const *argv[])
{

 // Syntax check 
  if (argc != 4) {
      cout << "Syntax: " << argv[0] << " data_base.txt query.txt out.txt" << endl;
      exit(1);
    }

  // Read data base
  ifstream in(argv[1]);
  int nextId = 1;
  while (not in.eof()) {
    string name, club, position;
    int p;
    getline(in,name,';');    if (name == "") break;
    getline(in,position,';');
    int price; in >> price;
    char aux; in >> aux;
    getline(in,club,';');
    in >> p;
    string aux2;
    getline(in,aux2);

    PLAYERS.push_back(Player(nextId++,name,position,price,club,p));
  }
  in.close();

  // Read query
  ifstream in2(argv[2]);
  in2 >> N1 >> N2 >> N3 >> T >> J;
  in2.close();

  // Start timer & execute search
  START_EX = high_resolution_clock::now();
  Tactic t;
  exh(t, 0, argv[3]);

  return 0;
}
