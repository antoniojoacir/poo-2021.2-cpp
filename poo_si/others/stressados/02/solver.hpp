void show(std::vector<int> v) {
    for (auto value : v) {
        std::cout << value << " ";
    }
    std::cout << "\n";
}

std::vector<int> fazer_vector(std::string line) {
    std::vector<int> vetor;
    std::stringstream ss(line);
    int value;
    
    while (ss >> value) {
        vetor.push_back(value);
    }
    
    return vetor;
}

std::vector<int> copiar(std::vector<int> v) {
    return v;
}

std::vector<int> pegar_posstivos(std::vector<int> v) {
    std::vector<int> v_pos;
    for (auto value : v) {
        if (value > 0) {
            v_pos.push_back(value);
        }
    }
    return v_pos;
}

std::vector<int> menor_que_dez(std::vector<int> v) {
    std::vector<int> v_menor;
    for (auto value : v) {
        if (abs(value) < 10) {
            v_menor.push_back(value);
        }
    }
    return v_menor;
}

std::vector<int> mulheres_dez(std::vector<int> v) {
    std::vector<int> v_mulher;
    for (auto value : v) {
        if (value < -10) {
            v_mulher.push_back(value);
        }
    }
    return v_mulher;
}

std::vector<int> invert_aux(std::vector<int> v) {
    std::vector<int> v_invert;
    for (auto value = v.crbegin(); value != v.crend(); value++) {
        v_invert.push_back(*value);
    }
    return v_invert;
}

void embralhar(std::vector<int>& v) {
    for (auto i = 0; i < (int) v.size(); i++) {
        auto random = rand() % (int) v.size();
        auto temporary = v[i];
        v[i] = v[random];
        v[random] = temporary;
    }
}

void sort(std::vector<int>& v) {
    for (auto i = 0; i < (int) v.size(); i++) {
        auto min = i;
        for (auto j = i; j < (int) v.size(); j++) {
            if (v[j] < v[min]) {
                min = j;
            }
            if (i != min) {
                auto temporary = v[i];
                v[i] = v[min];
                v[min] = temporary;
            }
        }
    }

}

std::vector<int> unicos_da_fila(std::vector<int> v) {
    std::vector<int> v_unicos;
    for (auto value : v) {
        if (std::find(v_unicos.begin(), v_unicos.end(), value) == v_unicos.end()) {
            v_unicos.push_back(value);
        }
    }
    return v_unicos;
}

std::vector<int> diferentes_da_fila(std::vector<int> v) {
    std::vector<int> v_diferentes;
    for (auto value : v) {
        if (std::find(v_diferentes.begin(), v_diferentes.end(), abs(value)) == v_diferentes.end()) {
            v_diferentes.push_back(abs(value));
        }
    }
    return v_diferentes;
}

std::vector<int> abandonados_da_fila(std::vector<int> v) {
    std::vector<int> v_abandonados {};

    for (auto i = 0; i < (int) v.size(); i++) {
        auto aux = 0;
        for (auto j = i; j < (int) v.size(); j++) {
            if (v[j] == v[i]) {
                aux++;
                if (aux > 1) {
                    v_abandonados.push_back(v[i]);
                }
            }
        }
    }
    return v_abandonados;
}
