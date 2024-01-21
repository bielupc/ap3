#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <random>
#include <cmath>

using namespace std;
using namespace chrono;

// Global start execution timer
time_point<high_resolution_clock> START_EX;

// Global constants
int N1, N2, N3, T, J;
int MAX_POINTS = -1;

// Random int generator
random_device rd;
mt19937 gen(rd());

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

  void add(Player& p){
    if (p.position == "por" && goal.empty()) {
      goal = p.name;
      price += p.price;
      points += p.points;
    } else if (p.position == "def" && int(def.size()) < N1) {
      def.push_back(p.name);
      price += p.price;
      points += p.points;
    } else if (p.position == "mig" && int(mid.size()) < N2) {
      mid.push_back(p.name);
      price += p.price;
      points += p.points;
    } else if (p.position == "dav" && int(str.size()) < N3) {
      str.push_back(p.name);
      price += p.price;
      points += p.points;
    }
  }

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


// Player database
vector<Player> PLAYERS;


tuple<double, double> updatePonderations(Tactic& t) {
  // Returns the percentatge of budget used and budget left
  double budgetUsed = t.price / double(T);
  double budgetLeft = 1 - budgetUsed;

  return make_tuple(budgetUsed, budgetLeft);
}


bool compare(const Player& p1, const Player& p2, double pricePond, double pointsPond){
  // Pondered ratio
  return (static_cast<double>(p1.points * pointsPond) / p1.price*pricePond) > (static_cast<double>(p2.points * pointsPond) / p2.price * pricePond);
}


Tactic constructGreedyRandomizedSolution(){
  Tactic s = Tactic();
  int a = 20; 
  vector<Player> playersLeft = PLAYERS;

  double pricePond = 0.5; 
  double pointsPond = 0.5;

  while (s.goal.empty() or int(s.def.size()) < N1 or int(s.mid.size()) < N2 or int(s.str.size()) < N3){

    // generateRestrictedCandidateList()
    sort(playersLeft.begin(), playersLeft.end(), [pricePond, pointsPond](const Player& p1, const Player& p2) {
        return compare(p1, p2, pricePond, pointsPond);
    });

    // Select "a" valid players
    vector<Player> RLC;
    int count = 0;
    for(Player& p : playersLeft){
      if(count == a){
        break;
      }
      else if(s.price + p.price <= T and p.price <= J)
        RLC.push_back(p);
        count += 1;
    }

    // Check if suitable playes have been found
    if(not RLC.empty()){
      // selectElementAtRandom(RLC)
      uniform_int_distribution<> dis(0, int(RLC.size()) - 1);
      int randomIndex = dis(gen);
      Player x = RLC[randomIndex];

      // Add player to solution
      s.add(x);

      // Delete from players left
      playersLeft.erase(remove_if(playersLeft.begin(), playersLeft.end(),
          [x](const Player& player) {
              return player.id == x.id;
          }), playersLeft.end());
      
      // updateGreedyFunction
      tie(pricePond, pointsPond) = updatePonderations(s); // Update ponderations based on budget left
    }
  }
  return s;
}


bool sortByPos(Player& p1, Player& p2){
    return p1.position > p2.position;
}


Player findSubstitute(Tactic& t, const string deletedPlayerName){
  // Find a substitute player for deletedPlayerName

  bool isFake = deletedPlayerName.find("Fake") != string::npos; 

  // Find player in the players database
  vector<Player>::iterator match = find_if(PLAYERS.begin(), PLAYERS.end(),
                [deletedPlayerName](const Player& player) {
                  return player.name == deletedPlayerName;
                });

  // Remove points and price from tactc
  int dataBaseIndex = distance(PLAYERS.begin(), match);
  t.points -= PLAYERS[dataBaseIndex].points;
  t.price -= PLAYERS[dataBaseIndex].price;
  string pos = PLAYERS[dataBaseIndex].position;
  Player substitute = PLAYERS[dataBaseIndex];

  // Replace the deleted player
  bool found = false;
  // Backward search
  for (int j = dataBaseIndex - 1; j >= 0; j--)
  {
    if(PLAYERS[j].position != pos){ //Players sorted by pos, different pos means end of same pos players, wrong search direction.
          break;
    }
    if(PLAYERS[j].price < J and PLAYERS[j].price + t.price < T){
      // Disallow swap from fake to fake
      if(isFake and PLAYERS[j].name.find("Fake") != string::npos) continue;
      found = true;
      substitute = PLAYERS[j];
      break;
    }
  }
  // Forward search
  if(not found){
    for (int k = dataBaseIndex+ 1; k < int(PLAYERS.size()); k++)
      {
        if(PLAYERS[k].position != pos) break;

        if(PLAYERS[k].price < J and PLAYERS[k].price + t.price < T){
          if(isFake and PLAYERS[k].name.find("Fake") != string::npos) continue;
          found = true;
          substitute = PLAYERS[k];
          break;
        }
      }
  }
  return substitute;

}


Tactic neighbour(Tactic t){
  // Select random position
  vector<string> positions = {"por", "def", "mig", "dav"};
  uniform_int_distribution<> dis(0, 3);
  string pos = positions[dis(gen)];

  // Swap random player at that position
  if(pos == "por"){
    string deletedPlayerName = t.goal;
    t.goal = "";
    Player substitute = findSubstitute(t, deletedPlayerName);
    t.goal = substitute.name;
    t.points += substitute.points;
    t.price += substitute.price;
  }
  else if (pos == "dav") {
    uniform_int_distribution<> dis(0, N3-1);
    int positionIndex = dis(gen);

    string deletedPlayerName = t.str[positionIndex];
    t.str.erase(t.str.begin() + positionIndex);
    Player substitute = findSubstitute(t, deletedPlayerName);
    t.str.insert(t.str.begin() + positionIndex, substitute.name);
    t.points += substitute.points;
    t.price += substitute.price;
  }
  else if (pos == "def") {
    uniform_int_distribution<> dis(0, N1-1);
    int positionIndex = dis(gen);

    string deletedPlayerName = t.def[positionIndex];
    t.def.erase(t.def.begin() + positionIndex);
    Player substitute = findSubstitute(t, deletedPlayerName);
    t.def.insert(t.def.begin() + positionIndex, substitute.name);
    t.points += substitute.points;
    t.price += substitute.price;
  }
  else if (pos == "mig") {
    uniform_int_distribution<> dis(0, N2-1);
    int positionIndex = dis(gen);

    string deletedPlayerName = t.mid[positionIndex];
    t.mid.erase(t.mid.begin() + positionIndex);
    Player substitute = findSubstitute(t, deletedPlayerName);
    t.mid.insert(t.mid.begin() + positionIndex, substitute.name);
    t.points += substitute.points;
    t.price += substitute.price;
  }
  return t;
}


void mh(char const *output){
  // Sort players by position
  sort(PLAYERS.begin(), PLAYERS.end(), sortByPos);

  int MAX_POINTS = -1;
  Tactic s;

  int limit = 0;
  while (limit < 1000) 
  {
    s = constructGreedyRandomizedSolution();

    // Simulated Annealing
    double temp = 10;
    int k = 0;

    while (k < 1000) 
    {
      Tactic ns;
      ns = neighbour(s);
      // Solution improves
      if(ns.points > s.points or (ns.points == s.points and ns.price < s.price)) s = ns;

      // Solution does not improve 
      else if(ns.points != s.points) {
        float p = exp(-float(s.points - ns.points) / temp);
        srand(static_cast<unsigned int>(time(nullptr)));
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        if (randomValue < p) {
          s = ns;
        }
      }

      temp *= 0.3;
      temp += 1;
      k += 1;
    }  

    // memorizeBestFoundSolution()
    if(s.points > MAX_POINTS){
      MAX_POINTS = s.points;
      ofstream file(output);
      file << s << endl;
      file.close();
    }
    limit += 1;
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
  mh(argv[3]);

  return 0;
}
