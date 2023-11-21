#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Programa
{
    int inicia;
    int finalitza;
};

bool abans(const Programa& p1,const Programa& p2){
    return p1.finalitza < p2.finalitza;
}

int main()
{
    int n, inicia, finalitza;

    while (cin >> n)
    {
        vector<Programa> programes(n);
        for (int i = 0; i < n; i++)
        {
            cin >> inicia >> finalitza;
            programes[i] = Programa{inicia, finalitza};
        }

        sort(programes.begin(), programes.end(), abans);
        
        int counter = 0;
        int finalitza_seleccionat = INT_MIN;

        int idx = 0;
        while (idx < n)
        {
            if (programes[idx].inicia > finalitza_seleccionat)
            {
                ++counter;
                finalitza_seleccionat = programes[idx].finalitza;
            }

            ++idx;
        }
        
        cout << counter << endl;
    }

    return 0;
}
