#include <iostream>
#include <vector>

using namespace std;

const int UNDEF = -1;



int scores(vector<int>& A,vector<int>& B, int i, int j, vector<vector<int>>& CACHE){

    if (i < 0 or j < 0) return 0;
    if (CACHE[i][j] != UNDEF) return CACHE[i][j];

    
    int res;
    if (A[i] == B[j]) res = 1 + scores(A, B, i-1, j-1, CACHE); // subseq end with the same value.
    else res = max(scores(A, B, i-1, j, CACHE), scores(A, B, i, j-1, CACHE));

    CACHE[i][j] = res;
    return res;

}



int main()
{
    int M, N;

    while(cin >> M >> N){
        vector<int> A(M);
        vector<int> B(N);

        for (int i = 0; i < M; i++)
        {
            cin >> A[i];
        }
        
        for (int i = 0; i < N; i++)
        {
            cin >> B[i];
        }
        
        vector<vector<int>> CACHE(M, vector<int>(N, UNDEF));
        cout << scores(A, B, M-1, N-1, CACHE) << endl;
    }

    return 0;
}
