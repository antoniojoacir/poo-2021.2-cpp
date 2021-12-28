#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include "solver.hpp"

int main() {

    srand(time(NULL));

    // ---- Criando meu vector ----

    std::cout << "\nDigite a fila: ";
        std::string fila;
        getline(std::cin, fila);
    std::vector<int> intFila { fazer_vector(fila) }; // função para criar meu vector
    
    std::cout << "\n\n---- Filter";

    // ---- Copiando meu vector ----

    std::vector<int> intFila2 { copiar(intFila) }; // função para copiar meu vector
    std::cout << "\n\nCopia: ";
    show(intFila2);

    // ---- Pegar possitivos ----

    std::vector possitivos { pegar_posstivos(intFila) }; // função para pegar os positivos
    std::cout << "Possitivos: ";
    show(possitivos);

    // ---- Pegar calmos ----

    std::vector<int> menores { menor_que_dez(intFila) }; // função para pegar os menores que 10 (abs)
    std::cout << "Menores que 10: ";
    show(menores);

    // ---- Pegar mulheres calmas ----

    std::vector<int> mulheres { mulheres_dez(intFila) }; // função para pegar as mulheres menores que 10 (abs)
    std::cout << "Mulheres menores que -10: ";
    show(mulheres);

    std::cout << "\n---- Acesso";

    // ---- Inverter com copia ----

    std::vector<int> invert { invert_aux(intFila) }; // função para inverter meu vector
    std::cout << "\n\nInvertido: ";
    show(invert);

    // ---- Inverter sem copia ----

    std::reverse(intFila.begin(), intFila.end()); // função para inverter meu vector sem aux
    std::cout << "Invertido sem aux: ";
    show(intFila);

    // ---- Sortear valor aleatorio ----

    std::cout << "Sorteando valor aleatorio: ";
    std::cout << intFila[rand() % (int) intFila.size()] << "\n";
    
    // ---- Embaralhar meu vector ----

    embralhar(intFila); // função para embaralhar meu vector
    std::cout << "Embaralhado: ";
    show(intFila);

    // ---- Ordenar meu vector ----

    sort(intFila); // função para ordenar meu vector
    std::cout << "Ordenado: ";
    show(intFila);

    std::cout << "\n---- Conjuntos";

    // ---- Unicos da fila ----

    std::vector<int> unics { unicos_da_fila(intFila) }; // função para pegar os unicos
    std::cout << "\n\nUnicos: ";
    show(unics);

    // ---- Diferentes da fila ----

    std::vector<int> diferentes { diferentes_da_fila(intFila) }; // função para pegar os diferentes
    std::cout << "Diferentes: ";
    show(diferentes);

    // ---- Abandonados ----
    
    std::vector<int> abandonados { abandonados_da_fila(intFila) }; // função para pegar os abandonados
    std::cout << "Andanados: ";
    show(abandonados);
    
    std::cout << "\nEnd Bloco II\n";
    return 0;
}