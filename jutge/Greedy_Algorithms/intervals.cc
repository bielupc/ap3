#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main()
{
    int k, n;

    while (cin >> k >> n)
    {
        vector<int> X(n);
        pair<int, int> interval; 
        int counter = 0;
        bool first = true;

        for (int i = 0; i < n; i++)
        {
            cin >> X[i];
        }
        
        sort(X.begin(), X.end());

        for (int x : X){
            if (x > interval.second or first)
            {
                interval.first = x;
                interval.second = x+k;
                ++counter;
                first = false;
            }
        }

        cout << counter << endl;
    }
    return 0;
}
