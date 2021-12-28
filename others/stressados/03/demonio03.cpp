#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>


/*
std::vector<int> fazer_vector() {
    
    std::vector<int> vector {};
    
    srand(time(NULL));

    auto size = rand() % 10;

    for (int i = 0; i < size; i++) {
        
        i % 2 == 0 ? vector.push_back(rand() % 100) : vector.push_back(-rand() % 100);
    
    }

    return vector;

}
*/

std::vector<int> unico(std::vector<int> vect) {

    std::vector<int> unics {};
    std::vector<int>::iterator it;

    for (auto frist = 0;frist < (int) vect.size(); frist++) {

        int count { 0 };

        for ( auto second {0}; second < (int) vect.size(); second++) {

            auto aux { abs(vect[frist]) };

            if (aux == abs(vect[second])) {

                count++;

            }
        }
        
        if (count == 1) {

            unics.push_back(vect[frist]);

        }
    }
    return unics;
}

int ocorrencias(std::vector<int> vect) {
    
    int count {}; int maior_ocorrencia {};

    for (auto frist = 0;frist < (int) vect.size(); frist++) {

            count = 0;

            for ( auto second {0}; second < (int) vect.size(); second++) {

                auto aux {vect[frist]};

                if (aux == abs(vect[second])) {

                    count++;

                }
            }

            if (count > maior_ocorrencia) {

                maior_ocorrencia = count;

            }
        }
    return maior_ocorrencia;
}

std::vector<int> recorrentes(std::vector<int> vect) {
    
    int count {}; int maior_ocorrencia {};

    std::vector<int> indices; std::vector<int> rep;

    for (auto frist = 0;frist < (int) vect.size(); frist++) {

            count = 0;

            for ( auto second {0}; second < (int) vect.size(); second++) {

                auto aux {vect[frist]};

                if (aux == abs(vect[second])) {

                    count++;

                }
            }

            if (count >= maior_ocorrencia) {

                maior_ocorrencia = count;
                indices.push_back(frist);
                rep.push_back(maior_ocorrencia);

            }
    }

    int maior { 0 };

    for (auto frist = 0;frist < (int) rep.size(); frist++) {
        
        if (rep[frist] > maior) {

            maior = rep[frist];
        
        }
    }

    std::vector<int> recorrente;
    std::vector<int>::iterator it;
    
    for (auto frist = 0;frist < (int) rep.size(); frist++) {

        it = std::find (recorrente.begin(), recorrente.end(), abs(vect[frist]));
        
        if (it == recorrente.end()) {
            rep[frist] == maior ? recorrente.push_back(vect[indices[frist]]) : (void) recorrente;
        }
    }
    return recorrente;
}

int briga(std::vector<int> vect) {
    
    int brigas {};

    for (auto frist = 0; frist < (int) vect.size(); frist++) {

        if (abs(vect[frist]) > 50) {

            if(abs(vect[abs(frist - 1)]) && abs(vect[frist + 1]) > 30) {

                brigas++;
            
            }
        }
    }
    return brigas;
}

std::vector<int> apaziguado(std::vector<int> vect) {
        
    std::vector<int> apaziguado;

    for (auto frist = 0; frist < (int) vect.size(); frist++) {

        if (abs(vect[frist]) > 80) {

            if(abs(vect[abs(frist - 1)]) || abs(vect[frist + 1]) < 10) {

                apaziguado.push_back(frist);
            }
        }
    }
    return apaziguado;
}

int quantos_times(std::vector<int> vect) {
    
    int times {}; int count {};

    for (auto fr = 0; fr < (int) vect.size(); fr++) {

        if (vect[fr] > 0) {

            count++;

            if (count >= 2) {
            
                times++;

            }

        } else {

            count = 0;
            
        }

        if (vect[fr] < 0) {

            count++;

            if (count >= 2) {
            
                times++;

            }

        } else {

            count = 0;
            
        }
        
    }
    return times;
}

std::vector<int> maior_time(std::vector<int> vect) {
    int count {}; int maior {}; int indice_pos; int indice_neg;
    std::vector<int> time;
    for (auto fr = 0; fr < (int) vect.size(); fr++) {
        if (vect[fr] > 0) {
            count++;
            if (count >= 2) {
                if (count > maior) { 
                    maior = count;
                    indice_pos = fr;
                }
            }
        } else {
            count = 0;
        }
    }
    for (auto fr = 0; fr < (int) vect.size(); fr++) {
        if (vect[fr] < 0) {
            count++;
            if (count >= 2) {
                if (count > maior) { 
                    maior = count;
                    indice_neg = fr;
                }
            }
        } else {
            count = 0;
        }        
    }
    if (indice_pos > indice_neg) {
        for (auto a = indice_pos; a > 0; a--) {
            if (vect[a] < 0){
                break;
            }
            time.push_back(vect[a]);
        }
    } else if (indice_neg > indice_pos) {
        for (auto a = indice_neg; a > 0; a--) {
            if (vect[a] > 0){
                break;
            }
            time.push_back(vect[a]);
        }
    }
    return time;
}

int sozinhos(std::vector<int> vect) {
    
    int sozinhos {}; int c {};
    
    for (auto fr = 0; fr < (int) vect.size(); fr++) {
        
        if (vect[fr] > 0) {
            
            c++;
            
        } else {
            if (c == 1) {
                
                sozinhos++;
            
            }
            
            c = 0;
        }
        

        if (vect[fr] < 0) {

            c++;
        
        } else {
            if (c == 1) {

                sozinhos++;

            }
                
            c = 0;
        }
    }
    return sozinhos;
}

int casal(std::vector<int> vect) {
    
    std::vector<int> casais;
    std::vector<int>::iterator it;
    int quantidade_de_casais {};
    int quantidade {};

    for (auto a = 0; a < (int) vect.size(); a++) {
        
        it = std::find (casais.begin(), casais.end(), abs(vect[a]));
        
        if (it == casais.end()) {
            int aux = vect[a];
            for (auto b = 0; b < (int) vect.size(); b++) {
                int c { 0 };
                if (-aux == vect[b]) {
                    c++;
                    
                    if(c == 1) {
                        
                        quantidade++;
                        casais.push_back(vect[a]);

                        if (quantidade == 2){
                            quantidade_de_casais++;
                            quantidade = 0;
                        }
                    }
                }
            }
        }
    }
    
    return quantidade_de_casais;
}

int trio(std::vector<int> vect) {
    

    int trios {};
    std::vector<int>::iterator it;
    std::vector<int> ttrios;
    
    for (auto a = 0; a < (int) vect.size(); a++) {
        int quantidade_de_trios {};
        
        int aux = abs(vect[a]);
        
        it = std::find (ttrios.begin(), ttrios.end(), abs(vect[a]));

        if (it == ttrios.end()) {
            for (auto b = 0; b < (int) vect.size(); b++) {
                if (aux == abs(vect[b])) {
                    quantidade_de_trios++;

                    if (quantidade_de_trios == 3) {
                        ttrios.push_back(vect[a]);
                        trios++;

                    }   
                }
                
            }
        }
    }
    return trios;
}

std::vector<int> remover(std::vector<int> vect, int quero_remover) {
    std::vector<int> remove;
    
    for (auto a = 0; a < (int) vect.size(); a++) {
        if (quero_remover == vect[a]) {
            vect[a] = 0;
        }
    }
    
    for (auto a = 0; a < (int) vect.size(); a++) {
        if (vect[a] != 0) {
            remove.push_back(vect[a]);
        }
    }
    return remove;
}

std::vector<int> inserir(std::vector<int> vect, int quero_inserir, int nessa_possicao) {
    std::vector<int> inserir;
    
    for (auto a = 0; a < (int) vect.size(); a++) {
        inserir.push_back(vect[a]);
    }

    inserir[nessa_possicao] = quero_inserir;

    return inserir;
}

std::vector<int> dancar(std::vector<int> vect) {
    std::vector<int> dance;

    for (auto a = 0; a < (int) vect.size(); a++) {
        dance.push_back(vect[a]);
    }
    
    for (auto a = 0; a < (int) vect.size(); a++) {
        if (abs(dance[a]) == abs(dance[a + 1])) {
            dance[a] = 0;
            dance[a + 1] = 0;
        }
    }
    return dance;
}

int main() {

    std::cout << "\n\nVector gerado: ";
    std::vector<int> vector {5, 3, 1, -11, 1, 99, -11, -1, -2, 44};
        for (int i = 0; i < (int) vector.size(); i++) {
            
            std::cout << vector[i] << " ";
        
        }
        
        std::cout << "\n\n";

    std::cout << "-- Manipulacao\n\n\n";

    std::cout << "Unicos\n";
        std::vector<int> unics { unico(vector) };
        std::cout << "Os numeros que sao unicos sao esses: ";
    for (auto i = 0; i < (int) unics.size(); i++) {
        
        std::cout << unics[i] << ' ';
    
    }
    
    std::cout << "\n\n";


    std::cout << "Mais ocorrencia\n";
        int maior_ocorrencia { ocorrencias(vector) };
        std::cout << "O maior numero de ocorrencia foi esse: " << maior_ocorrencia << " vezes\n\n";

    std::cout << "Mais recorrentes\n";
        std::vector<int> recorrente { recorrentes(vector) };
        std::cout << "Os numeros mais recorrentes foram: ";
            for (int i = 0; i < (int) recorrente.size(); i++) {
                std::cout << recorrente[i] << " ";
            }
            std::cout << "\n\n";
    
    std::cout << "\n-- Proximidade\n\n\n";
    
    std::cout << "Briga\n";
        int brigas { briga(vector) };
        std::cout << "O numero de brigas que podem ocorrer e esse: " << brigas << "\n\n";

    std::cout << "Apaziguado\n";
        std::vector<int> apaz { apaziguado(vector) };
        std::cout << "A pocisão das brigas que foram evitadas foram: ";
            for (int value : apaz) {
                std::cout << value << " ";
            }
            std::cout << "\n\n";
    
    std::cout << "\n-- Sequencias\n\n\n";
    
    std::cout << "Quantos times\n";
        int times { quantos_times(vector) };
        std::cout << "O numero total de times e esse: " << times << "\n\n";

    std::cout << "Maior time\n";
        std::vector<int> time { maior_time(vector) };
        std::cout << "O maior time e esse: ";
        for (int a = 0; a < (int)time.size(); a++) {
            std::cout << time[a] << " ";
        }
        std::cout << "\n\n";

    std::cout << "Sozinhos\n";
        int sozinho { sozinhos(vector) };
        std::cout << "Existem " << sozinho << " pessoas sem um time" << "\n\n";


    std::cout << "\n-- Grupos\n\n\n";

    std::cout << "Casais\n";
        int casais { casal(vector) };
        std::cout << "Existem " << casais << " na fila" << "\n\n";
    
    std::cout << "Trios\n";
        int triplos { trio(vector) };
        std::cout << "Existem " << triplos << " na fila" << "\n\n";

    std::cout << "\n-- Alteracao\n\n\n";

    std::cout << "Remove\n";
        std::cout << "Qual pessoa voce deseja remover? ";
        int x {};
        std::cin >> x;
        std::vector<int> remove { remover(vector, x) };
            std::cout << "A fila fica assim sem o " << x << " : ";
            for (int value : remove) {
                std::cout << value << " ";
            }
            std::cout << "\n\n";
    
    std::cout << "Insert\n";
        std::cout << "Possicoes disponiveis: ";
            for (auto a = 0; a < (int) vector.size(); a++) {
                std::cout << a << " ";
            }
            std::cout << '\n';
        std::cout << "Em qual possicao voce deseja inserir o " << x << "? ";
        int y {};
        std::cin >> y;
        std::vector<int> insert { inserir(vector, x, y) };
            std::cout << "Apos colocar o " << x << " na possicao " << y << " a fila fica assim: ";
            for (int value : insert) {
                std::cout << value << " ";
            }
            std::cout << "\n\n";

    std::cout << "Dance\n";
        std::cout << "Apos as pessoas proximas com niveis de stress semelhantes sairem da fila ela ficou assim: ";
        std::vector<int> dance { dancar(vector) };
        for (auto a = 0; a < (int) dance.size(); a++) {
            if (dance[a] != 0) {
                std::cout << dance[a] << " ";
            }
        }
            std::cout << "\n\n";
    
    return 0;
}
