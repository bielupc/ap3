#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;


int main () {
  int x, D, n;

  while (cin >> x >> D >> n) {

    vector<int> stations(n);

    for (int i = 0; i < n; i++) {
      cin >> stations[i];
    }
    sort(stations.begin(), stations.end());

    if (n == 0){
      cout << 0 << endl;
      continue;
    }

    if (n == 1){
      if (x >= D){
        cout << 0 << endl;
        continue;
      }
      else{
        cout << 1 << endl;
        continue;
      }
    }


    int count_stations = 0;
    int current_station = 0;
    int tank = x-stations[0];
    int odometer = stations[0];
    int distance;

    while (odometer < D and current_station < n-1){
      distance = stations[current_station+1] - stations[current_station];
      
      if (tank >= distance)
      {
        tank -= distance;
        ++current_station;
        odometer = stations[current_station];
      }
      else{
        tank = x;
        ++count_stations;
      }
    }

    if (current_station == n-1)
    {
      if (odometer + tank < D)
      {
        ++count_stations;
      }
      
    }
    
    cout << count_stations << endl;
  }
  return 0;
}
