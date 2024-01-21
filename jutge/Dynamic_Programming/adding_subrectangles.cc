#include <iostream>
#include <vector>
#include <string>


using namespace std;

const int UNDEF = 0;


int punts(const char C){
    int n = C - 'A' + 1;
    return n*(n+1)/2;
}

int S(int i, int j, const vector<vector<int>>& P, vector<vector<int>>& cache){
    if(i < 0 or j < 0){
        return 0;
    }
    if(cache[i][j] != UNDEF) return cache[i][j];

    int sum = S(i-1, j, P, cache) + S(i, j-1, P, cache) - S(i-1, j-1, P, cache) + P[i][j];
    cache[i][j] = sum;
    return sum;
}


int main()
{
    vector<vector<char>> M;
    string s;
    while (cin >> s) {
        M.push_back({});
        for (uint i = 0; i < s.size(); ++i) 
        M.back().push_back(s[i]);
    }


    vector<vector<int>> P(M.size(), vector<int>(M[0].size()));
    for (uint i = 0; i < P.size(); i++)
    {
        for (uint j = 0; j < P[0].size(); j++)
        {
            P[i][j] = punts(M[i][j]);
        }
    }


    vector<vector<int>> cache(M.size(), vector<int>(M[0].size(), UNDEF));

    for (uint i = 0; i < M.size(); i++)
    {
        for (uint j = 0; j < M[0].size(); j++)
        {
            cout << (j == 0 ? "" : " ") << S(i, j, P, cache);
        }
        cout << endl;
    }


    return 0;
}
