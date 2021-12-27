#include <iostream>
#include <vector>
#include <sstream>
#include "solver.hpp"

int main(){
    // ---- Gerando vector ----

    std::cout << "\nDigite a fila: ";
    std::string fila;
       // getline(std::cin, fila);
    std::vector<int> intFila {5, 3, 1, -11, 1, 99, -11, -1, -2, 11}; // gerando meu vector

    std::cout << "\n\n----Manipulacao";

    // ---- Sozinhas ----

    std::cout << "\n\nSozinhas: ";
    std::vector<int> sozinhas { find_solos(intFila) };
    show(sozinhas);

    // ---- Maior número de ocorrencia ----

    int maior_ocorrencia { find_maior_ocorrencia(intFila) }; // função que retorna o maior número de ocorrencia
    std::cout << "Maior número de ocorrencia: " << maior_ocorrencia << "\n";

    // ---- Maior número recorrente ----
    
    std::cout << "Maior recorrencia: ";
    std::vector<int> maior_recorrencia { find_maior_recorrencia(intFila) }; // função para encontrar o maior número recorrente  
    show(maior_recorrencia);

    std::cout << "\n\n---- Proximidade";

    // ---- Briga ----

    int brigas { quantidade_de_brigas(intFila) }; // função para encontrar a quantidade de brigas
    std::cout << "\n\nQuantidade de brigas: " << brigas << "\n";

    // ---- Apaziguado ----

    std::cout << "Locais onde os apaziguados entao: ";
    std::vector<int> apaziguados { find_apaziguados(intFila) }; // função para encontrar os locais onde os apaziguados entao
    show(apaziguados);

    std::cout << "\n\n---- Sequencia";

    // ---- Quantos times ----

    int quantidade_de_times { quantos_times_tem(intFila) }; // função para encontrar a quantidade de times
    std::cout << "\n\nQuantidade de times: " << quantidade_de_times << "\n";

    // ---- Maior time ----

    std::cout << "Maior time: ";
    std::vector<int> maior_time { find_maior_time(intFila) }; // função para encontrar o maior time
    show(maior_time);

    // ---- Sem time ----

    int sem_time { quantidade_de_sem_time(intFila) }; // função para encontrar a quantidade de sem time
    std::cout << "Sem time: " << sem_time << "\n";

    std::cout << "\n\n---- Grupo";

    // ---- Casais ----

    int casais { quantidade_de_casais(intFila) }; // função para encontrar a quantidade de casais
    std::cout << "\n\nQuantidade de casais: " << casais << "\n";

    // ---- trios ----

    int trios { quantidade_de_trios(intFila) }; // função para encontrar a quantidade de trios
    std::cout << "Quantidade de trios: " << trios << "\n";

    std::cout << "\n\n---- Alteracao";

    // ---- remove ----
    
    std::cout << "Remove: ";
    std::vector<int> remove { remove_elemento(intFila, -1) }; // função para remover um elemento

    return 0;
}