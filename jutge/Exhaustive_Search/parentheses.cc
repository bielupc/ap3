#include <iostream>
#include <vector>

using namespace std;


const int UNDEF = -1;
const int MAX_N = 67;
vector<long int> t(MAX_N+1, UNDEF);

long int parentheses(int n){
    if (t[n] != UNDEF) {return t[n];}
    if (n == 0){
        return t[n] = 1;
    }
    else{
        long int res = 0;
        for (int len1 = 2; len1 <= n; ++len1)
            res += parentheses(len1-2) * parentheses(n-len1);
            t[n] = res;
            return res;
    }

}

int main()
{
    int n;
    while (cin >> n)
    {
        cout << parentheses(n) << endl;
    }
    return 0;
}
