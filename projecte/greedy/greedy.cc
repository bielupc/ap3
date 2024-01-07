#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;


float TIMER;


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
    out << fixed << setprecision(1) << TIMER << endl;

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

bool compare(const Player &p1, const Player &p2) {
  return (static_cast<double>(p1.points) / p1.price) > (static_cast<double>(p2.points) / p2.price);

}

void greedy(Tactic& t, char const *output){
  time_point<high_resolution_clock> startTimer, endTimer;
  startTimer = high_resolution_clock::now();
  sort(PLAYERS.begin(), PLAYERS.end(), compare);

  for(auto p: PLAYERS){
    cout << p << endl;
  }

  for(const Player& p : PLAYERS){
    if(t.price + p.price > T or p.price > J){
      continue;
    }

    if(p.position == "por" and t.goal.empty()){
      t.goal = p.name;
      t.points += p.points;
      t.price += p.price;
    }

    if(p.position == "def" and int(t.def.size()) < N1){
      t.def.push_back(p.name);
      t.points += p.points;
      t.price += p.price;
    }
    if(p.position == "mig" and int(t.mid.size()) < N2){
      t.mid.push_back(p.name);
      t.points += p.points;
      t.price += p.price;
    }

    if(p.position == "dav" and int(t.str.size()) < N3){
      t.str.push_back(p.name);
      t.points += p.points;
      t.price += p.price;
    }

   if(not t.goal.empty() and int(t.def.size()) == N1 and int(t.mid.size()) == N2 and int(t.str.size()) == N3){
      endTimer = high_resolution_clock::now();
      TIMER = duration_cast<duration<double>>(endTimer - startTimer).count();
      ofstream file(output);
      file << t << endl;
      file.close();
      return;
   }
  }
  exit(1);
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
  Tactic t;
  greedy(t, argv[3]);
  return 0;
}

