void show(std::vector<int> v) {
    for (int i = 0; i < (int) v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> make_vector(std::string list){
    std::vector<int> v;
    std::stringstream ss(list);
    int value;

    while (ss >> value) {
        v.push_back(value);
    }

    return v;
}

std::vector<int> find_solos(std::vector<int> v) {
    std::vector<int> solos;
    for (int value : v) {
        int count = 0;

        for (auto i = 0; i < (int) v.size(); i++) {
            if (abs(value) == abs(v[i])) {
                count++;
            }
        }
        
        if (count == 1) {
            solos.push_back(value);
        }
    }

    return solos;
}

int find_maior_ocorrencia(std::vector<int> v) {
    int maior = 0;      int aux;
    
    for (int value : v) {
        int count = 0;
        for (auto i = 0; i < (int) v.size(); i++) {
            if (abs(value) == abs(v[i])) {
                count++;
            }
        }
        if (count > maior) {
            maior = count;
            aux = value;
        }
    }
    
    return aux;
}

std::vector<int> find_maior_recorrencia(std::vector<int> v) {
    std::vector<int> v_recorrencias;
    int aux {};     int count {};
    
    for (auto value : v) {
        for (auto i = 0; i < (int) v.size(); i++) {
            if (abs(value) == abs(v[i])) {
                count++;
            }
            if (count > aux) {
                aux = count;
            }
        }
        count = 0;
    }
    
    std::vector<int>::iterator it; // controle para não adicionar o mesmo valor mais de uma vez

    for (auto value : v) {
        for (auto i = 0; i < (int) v.size(); i++) {
            if (abs(value) == abs(v[i])) {
                count++;
            }
            if (count == aux) {
                it = std::find(v_recorrencias.begin(), v_recorrencias.end(), abs(value));
                if (it == v_recorrencias.end()) {
                    v_recorrencias.push_back(abs(value));
                }
            }
        }
        count = 0;
    }

    return v_recorrencias;
} 

int quantidade_de_brigas(std::vector<int> v) {
    int count = 0;
    for (auto i = 1; i < (int) v.size() - 1; i++) {
        if (abs(v[i]) > 50) {
            if (abs(v[i -1]) > 30 && abs(v[i + 1]) > 30) {
                count++;
            }
        }
    }
    return count;
}

std::vector<int> find_apaziguados(std::vector<int> v) {
    std::vector<int> v_apaziguados;
    for (auto i = 0; i < (int) v.size(); i++) {
        if (abs(v[i]) > 80) {
            if (abs(v[i -1]) < 10 || abs(v[i + 1]) < 10) {
                v_apaziguados.push_back(i);
            }
        }
    }
    return v_apaziguados;
}

bool se_e_time(int x) {
    if (x >= 2)
        return true;
    return false;
}

int quantos_times_tem(std::vector<int> vect) {
    auto seguidos_possitivos = 0;
    auto seguidos_negativos = 0;
    auto quantidade_que_tem_de_time = 0;
    for (auto x = 0; x < (int)vect.size(); x++) {
        if (vect[x] > 0) {
            seguidos_possitivos++;
        } else {
            if (se_e_time(seguidos_possitivos)) {
                quantidade_que_tem_de_time++;
            }
            seguidos_possitivos = 0;   
        }
    }
    if (quantidade_que_tem_de_time == 0 && seguidos_possitivos == (int) vect.size()) {
        quantidade_que_tem_de_time++;
    }
    for (auto x = 0; x < (int)vect.size(); x++) {
        if (vect[x] < 0) {
            seguidos_negativos++;
        }  else {
            if (se_e_time(seguidos_negativos)) {
                quantidade_que_tem_de_time++;
            }
            seguidos_negativos = 0;
        }
    }
    if (quantidade_que_tem_de_time == 0 && seguidos_negativos == (int) vect.size()) {
        quantidade_que_tem_de_time++;
    }
    return quantidade_que_tem_de_time;
}

std::vector<int> find_maior_time(std::vector<int> vect) {
    std::vector<int> maior_time;
    auto posicao_maior_time = 0;
    auto seguido = 0;
    auto maior_seguido = 0;
    for (auto i = 0; i < (int) vect.size(); i++) {
        if (vect[i] > 0) {
            seguido++;
            if (se_e_time(seguido) && seguido > maior_seguido) {
                posicao_maior_time = i;
                maior_seguido = seguido;
            }
        } else {
            seguido = 0;
        }
    }
    for (auto i = 0; i < (int) vect.size(); i++) {
        if (vect[i] < 0) {
            seguido++;
            if (se_e_time(seguido) && seguido > maior_seguido) {
                posicao_maior_time = i;
                maior_seguido = seguido;
            }
        } else {
            seguido = 0;
        }
    }
    

    for (auto i = posicao_maior_time; i < (int) vect.size(); i--) {
        if (vect[i] > 0) { maior_time.push_back(vect[i]);} 
        else { break; }
    }
    for (auto i = posicao_maior_time; i < (int) vect.size(); i--) {
        if (vect[i] < 0) { maior_time.push_back(vect[i]);} 
        else { break; }
    }

    std::reverse(maior_time.begin(), maior_time.end());
    return maior_time;
}

int quantidade_de_sem_time(std::vector<int> vector) {
    int count {}; int sem_time {};
    for (auto value : vector) {
        if (value > 0) {
            count++;
        } else {
            if (count == 1) {
                sem_time++;
            }
            count = 0;
        }
    }
    for (auto value : vector) {
        if (value < 0) {
            count++;
        } else {
            if (count == 1) {
                sem_time++;
            }
            count = 0;
        }
    }    
    return sem_time;
}

int quantidade_de_casais(std::vector<int> vect) {
    std::vector<int> casais { vect };
    auto quantidade_de_casal = 0;

    for (auto x = 0 ; x < (int)vect.size(); x++) {
        for (auto y = x + 1; y < (int)vect.size(); y++) {
            if (casais[x] == -casais[y] || -casais[x] == casais[y]) {
                if (casais[x] != 0) {
                    quantidade_de_casal++;
                    casais[y] = 0;
                    casais[x] = 0;
                }
            }
        }
    }
    return quantidade_de_casal;
}

int quantidade_de_trios(std::vector<int> vect) {
    auto quantidade_de_trio = 0;
    auto count = 0;
    for (auto x = 0 ; x < (int)vect.size(); x++) {
        for (auto y = x + 1; y < (int)vect.size(); y++) {
            if (abs(vect[x]) == abs(vect[y])) {
                count++;
                if (count == 2) {
                    quantidade_de_trio++;
                }
            }
        }
        count = 0;
    }
    return quantidade_de_trio;
}

