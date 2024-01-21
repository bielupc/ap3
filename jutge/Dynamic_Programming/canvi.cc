#include <iostream>
#include <vector>
#include <string>
#include <climits>



using namespace std;

int count(const vector<int>& coins, int c){
    vector<int> cache(c+1, INT_MAX);

     cache[0] = 0;


     for (int i = 1; i < c+1; i++)
     {
        for(int coin : coins){
            if(coin <= i and cache[i - coin] != INT_MAX){
                cache[i] = min(cache[i], cache[i - coin] + 1);
            }
        }
     }
    return cache[c];

}

int main()
{
    int n, c;
    int coin;
    while (cin >> c >> n)
    {
        vector<int> coins(n);
        for (int i = 0; i < n; i++)
        {
            cin >> coins[i];
        }

        int result = count(coins,c);
        cout << (result == INT_MAX ? "no" : to_string(result)) << endl;
        
    }

    return 0;
}
