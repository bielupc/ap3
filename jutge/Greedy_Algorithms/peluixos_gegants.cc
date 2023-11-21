#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    int n;
    int price;

    while (cin >> n)
    {
        price = 0;
        vector<int> bears(3*n);

        for (int i = 0; i < 3*n; i++)
        {
            cin >> bears[i];
        }

        sort(bears.begin(), bears.end());

        for (int i = 0; i < 3*n; i+=3)
        {
            price += bears[i+1] + bears[i+2];
        }

        cout << price << endl;
        
    }
    

    return 0;
}
