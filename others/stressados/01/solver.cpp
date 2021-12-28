#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template <typename T>
using vet = vector<T>;

template <typename T>
void show(vet<T> vec) {
    for (auto& elem : vec)
        cout << elem << " ";
    cout << "\n";
}

bool existe(vet<int> vec, int value) {
    if (vec.end() == find(vec.begin(), vec.end(), value)) {
        cout << "Valor {" << value << "} não se encontra nessa fila\n";
        return false;
    }
    cout << "Valor {" << value << "} se encontra na fila\n";
    return true;
}

int main() {
    /*string line {};
    getline(cin, line);*/  
    vet<int> eUm {-1, -50, -99};
    existe(eUm, -1);
    vet<int> eDois {-1, -50, -99};
    existe(eDois, 10);

    cout << "\n";

    vet<int> countOne {-1, -50, -1, -99};
    cout << "Aparece {" << count(countOne.begin(), countOne.end(), -1) << "}\n";
    vet<int> countTwo {-1, -50, -1, -99};
    cout << "Aparece {" << count(countTwo.begin(), countTwo.end(), 10) << "}\n";

    cout << "\n";

    if (countOne.end() == std::search(countOne.begin(), countOne.end(), -1))
        cout << "Valor {" << -1 << "} não se encontra nessa fila\n";
    else
        cout << "Valor {" << -1 << "} se encontra na fila\n";

}
