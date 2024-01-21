#include <vector>
#include <iostream>
#include <climits>

using namespace std;

int count(int c, const vector<int>& cards, vector<int>& cache){
    for (int i = 1; i < c+1; i++)
    {
        for(int card : cards){
            if(card <= i and cache[i - card] != -1){
                cache[i] = min(cache[i], cache[i - card] + 1);
            }
        }
    }

    return cache[c];
    

}

int main(){
    int n;
    while(cin >> n){
        if (n == -1) return 0;

        vector<int> cards = {1, 5, 8, 14};
        vector<int> cache(n+1, INT_MAX);
        cache[0] = 0;
        cout << count(n, cards, cache) << endl;
    }
    return 0;
}