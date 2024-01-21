#include <vector>
#include <iostream>

using namespace std;


int paths(int i, int j, const vector<vector<char>>& M, vector<vector<int>>& cache){
    if(cache[i][j] != -1) return cache[i][j];
    if(M[i][j] == 'X') return cache[i][j] = 0;

    int right = 0, down = 0;
    if(j + 1 < M[0].size()) right = paths(i, j+1, M, cache);
    if(i + 1 < M.size()) down = paths(i+1, j, M, cache);
    return cache[i][j] = min(down+right, int(1e6));
}


int main(){
    int n, m;

    while(cin >> n >> m){
        if(n == 0 and m == 0) return 0;

        vector<vector<char>> M(n, vector<char>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> M[i][j];
            }
        }

        
        vector<vector<int>> cache(n, vector<int>(m, -1));
        cache[n-1][m-1] = 1;
        int result = paths(0, 0, M, cache);
        (result < 1e6) ? cout << result : cout << "!!!";
        cout << endl;
    }

    return 0;
}