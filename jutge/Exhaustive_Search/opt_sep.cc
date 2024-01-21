#include <iostream>
#include <vector>
#include <math.h>
#include <climits>

using namespace std;


int MIN_DIFF = INT_MAX;


void optSep(const vector<int>& N, vector<int>& S1, vector<int>& S2, int i){
    
    if ((S1.size() + S2.size() == N.size())){
        int s1Sum = 0;
        int s2Sum = 0;
        for (int n : S1){
            s1Sum += n;
        }
        for (int n : S2){
            s2Sum += n;
        }

        int diff = abs(s1Sum - s2Sum);
        if (diff < MIN_DIFF){
            MIN_DIFF = diff;
        }
        return;
    }

    if (i >= int(N.size())){
        return;
    }

    S1.push_back(N[i]);
    optSep(N, S1, S2, i+1);

    S1.pop_back();
    S2.push_back(N[i]);
    optSep(N, S1, S2, i+1);

    S2.pop_back();
    optSep(N, S1, S2, i+1);
}


int main()
{
    int n;
    while (cin >> n)
    {
        vector<int> N;
        vector<int> S1, S2;
        int num;

        for (int i = 0; i < n; i++)
        {
            cin >> num;
            N.push_back(num);
        }

        optSep(N, S1, S2, 0);
        cout << MIN_DIFF << endl;
        MIN_DIFF = INT_MAX;
    }
    
    return 0;
}




