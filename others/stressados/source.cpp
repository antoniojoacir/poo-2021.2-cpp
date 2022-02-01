#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

vector<int> makeNewVector(string input) {
    vector<int> output;
    stringstream ss(input);
    int temp;
    while (ss >> temp) {
        if (ss.peek() == ',')
            ss.ignore();
        else
            output.push_back(temp);
    }
    return output;
}

int pos_homem_mais_calmo(vector<int> input) {
    vector<int> temp;
    for (auto &element : input)
        if (element > 0)
            temp.push_back(element);
    auto output = min_element(temp.begin(), temp.end());
    return *output;
}

float estress_medio(vector<int> input) {
    int all{0};
    for (auto element : input)
        all = all + abs(element);
    float output{all / (float)input.size()};
    return output;
}

string qual_metade(vector<int> input) {
    auto metade = (int)input.size() / 2;
    float left{0}, right{0};
    for (auto i = 0; i < metade; i++)
        left = left + abs(input[i]);
    for (auto i = metade; i < (int)input.size(); i++)
        right = right + abs(input[i]);
    if (left > right)
        return "Primeira metade";
    if (left < right)
        return "Segunda metade";
    return "Empatou";
}

string qual_homens_mulheres(vector<int> input) {
    float homens{0}, mulheres{0};
    int countHomens{0}, countMulheres{0};
    for (auto element : input) {
        if (element > 0) {
            countHomens++;
            homens += element;
        }
        else {
            countMulheres++;
            mulheres = mulheres + abs(element);
        }
    }
    if (homens / countHomens > mulheres / countMulheres)
        return "Homens";
    if (homens / countHomens < mulheres / countMulheres)
        return "Mulheres";
    return "Empatou";
}

vector<int> cloneVector(vector<int> input) {
    return input;
}

vector<int> returnPositives(vector<int> input) {
    vector<int> output;
    for (auto element : input)
        if (element > 0)
            output.push_back(element);
    return output;
}

vector<int> menoresQueDez(vector<int> input) {
    vector<int> output;
    for (auto element : input)
        if (abs(element) < 10)
            output.push_back(element);
    return output;
}

vector<int> mulheresMenorQueDez(vector<int> input) {
    vector<int> output;
    for (auto element : input)
        if (element < 0)
            if (abs(element) < 10)
                output.push_back(element);
    return output;
}

vector<int> copiaInversa(vector<int> input) {
    vector<int> output;
    for (auto i = (int)input.size() - 1; i >= 0; i--)
        output.push_back(input[i]);
    return output;
}

vector<int> embaralhar(vector<int> input) {
    vector<int> output{input};
    srand(time(NULL));
    for (auto i = 0; i < (int)output.size(); i++)
    {
        auto random = rand() % (int)output.size();
        auto temp = output[i];
        output[i] = output[random];
        output[random] = temp;
    }
    return output;
}

vector<int> exclusivo(vector<int> input)
{
    vector<int> output;
    for (auto element : input)
        if (find(output.begin(), output.end(), element) == output.end())
            output.push_back(element);
    return output;
}

vector<int> diferentes(vector<int> input) {
    vector<int> output;
    for (auto element : input)
        if (find(output.begin(), output.end(), abs(element)) == output.end())
            output.push_back(abs(element));
    return output;
}

vector<int> abandonados(vector<int> input) {
    vector<int> output;
    for (auto element : input)
        if (find(output.begin(), output.end(), element) == output.end())
            if (count(input.begin(), input.end(), element) >= 2)
                output.push_back(element);
    return output;
}

vector<int> quaisSaoOsUnicos(vector<int> input) {
    vector<int> output, temp;
    for (auto element : input)
        temp.push_back(abs(element));
    for (auto element : temp)
        if (find(output.begin(), output.end(), element) == output.end() &&
            count(temp.begin(), temp.end(), element) == 1)
            output.push_back(element);
    return output;
}

int maiorOcorrencia(vector<int> input) {
    vector<int> temp;
    for (auto element : input)
        temp.push_back(abs(element));
    auto output = count(temp.begin(), temp.end(), *max_element(temp.begin(), temp.end()));
    return output;
}

vector<int> maisRecorrentes(vector<int> input) {
    vector<int> output, temp;
    for (auto element : input)
        temp.push_back(abs(element));
    auto it = count(temp.begin(), temp.end(), *max_element(temp.begin(), temp.end()));
    for (auto element : temp)
        if (find(output.begin(), output.end(), element) == output.end() && count(temp.begin(), temp.end(), element) == it)
            output.push_back(element);
    return output;
}

int brigas(vector<int> input) {
    int output{0};
    vector<int> temp;
    for (auto element : input)
        temp.push_back(abs(element));
    for (auto i = 1; i < (int)temp.size() - 1; i++)
        if (temp[i] > 50 && temp[i - 1] > 30 && temp[i + 1] > 30)
            output++;
    return output;
}

vector<int> apaziguados(vector<int> input) {
    vector<int> output, temp;
    for (auto element : input)
        temp.push_back(abs(element));
    for (auto i = 0; i < (int)temp.size(); i++)
        if ((temp[i] > 80 
            && temp[i - 1] < 10) 
                || (temp[i] > 80 
                    && temp[i + 1] < 10))
                       output.push_back(i);
    return output;
}

int quantosTimes(vector<int> input) {
    int output { 0 };
    int start { 0 };
    while(1)
        // * o proximo valor tem que conter o mesmo sinal, caso contrario, nao eh um time
        for (auto i = start; i < (int)input.size() - 1; i++)
            if (input)
        
        
        
    return output;
}

int main() {
    // string input;
    // cout << "$"; getline(cin, input);
    vector<int> tokens{1, 1, 1, -1, 1, -1, -1};
    /*
    // ! existe
    cout << "Elemento de busca: ";
    int elementFind;
    cin >> elementFind;
    find(tokens.begin(), tokens.end(), elementFind) != tokens.end() ? cout << "existe\n" : cout << "não existe\n";

    // ! contar
    cout << "Elemento de busca: ";
    int elementCount;
    cin >> elementCount;
    cout << count(tokens.begin(), tokens.end(), elementCount) << endl;

    // ! procurar posição
    cout << "Elemento de busca: ";
    int elementPosition;
    cin >> elementPosition;
    cout << distance(tokens.begin(), find(tokens.begin(), tokens.end(), elementPosition)) << endl;

    // ! procurar a partir de uma posição
    cout << "Elemento de busca e possição: ";
    int elementFindPosition;
    int elementPositionFromPosition;
    cin >> elementFindPosition >> elementPositionFromPosition;
    if(elementPositionFromPosition >= (int) tokens.size()) cout << "Possição inválida\n";
    else cout << distance(tokens.begin() + elementPositionFromPosition, find(tokens.begin() + elementPositionFromPosition, tokens.end(), elementFindPosition)) << endl;

    // ! procurar menor
    auto menor = min_element(tokens.begin(), tokens.end());
    cout << *menor << endl;

    // ! procurar posição do menor
    cout << distance(tokens.begin(), menor) << endl;

    // ! procurar menor partir de uma posição
    cout << "Posição incial da busca: ";
    int menorFindPositionFromPosition;
    cin >> menorFindPositionFromPosition;
    if(menorFindPositionFromPosition >= (int) tokens.size()) cout << "Possição inválida\n";
    else {
        cout << min_element(tokens.begin() + menorFindPositionFromPosition, tokens.end()) - tokens.begin() << endl;
    }

    // ! posição do homem mais calmo
    cout << pos_homem_mais_calmo(tokens) << endl;

    // ! calcular estresse medio
    cout << estress_medio(tokens) << endl;
    return 0;

    // ! qual metade é mais estressada
    cout << qual_metade(tokens) << endl;

    // ! os homens são mais estressados que as mulheres ?
    cout << qual_homens_mulheres(tokens) << endl;

    // ? BLOCO II

    // ! clonar um vetor (copia)

    cout << "Clonando vetor...\n";
    vector<int> tokensClone { cloneVector(tokens) };
    for (auto element : tokensClone)
        cout << element << " ";
    cout << endl;

    // ! pegar somente os positivos
    cout << "Pegando somente os positivos...\n";
    vector<int> tokensPositive  { returnPositives(tokens) };
    for (auto element : tokensPositive)
        cout << element << " ";
    cout << endl;

    // ! pegar somente os menores que 10
    cout << "Pegando somente os menores que 10...\n";
    vector<int> tokensLessThanTen { menoresQueDez(tokens) };
    for (auto element : tokensLessThanTen)
        cout << element << " ";
    cout << endl;

    // ! mulheres menores que dez
    cout << "Mulheres menores que dez...\n";
    vector<int> tokensWomenLessThanTen { mulheresMenorQueDez(tokens) };
    for (auto element : tokensWomenLessThanTen)
        cout << element << " ";
    cout << endl;

    // ! copiar inversamente
    cout << "Copiando inversamente...\n";
    vector<int> tokensInverse { copiaInversa(tokens) };
    for (auto element : tokensInverse)
        cout << element << " ";
    cout << endl;

    // ! invertendo sem auxiliar
    cout << "Invertendo sem auxiliar...\n";
    vector<int> tokensInverse { tokens };
    reverse(tokensInverse.begin(), tokensInverse.end());
    for (auto element : tokensInverse)
        cout << element << " ";
    cout << endl;
    return 0;

    // ! sortear um valor aleatorio
    srand(time(NULL)); // * isso faz com que seja um valor aleatorio diferente a cada execução
    cout << "Sorteando um valor aleatorio...\n";
    cout << tokens[rand() % (int) tokens.size()] << endl;

    // ! embaralhar
    cout << "Embaralhando...\n";
    vector<int> tokensShuffled { embaralhar(tokens) };
    for (auto element : tokensShuffled)
        cout << element << " ";
    cout << endl;

    // ! exclusivo
    cout << "Exclusivo...\n";
    vector<int> tokensExclusive { exclusivo(tokens) };
    for (auto element : tokensExclusive)
        cout << element << " ";
    cout << endl;

    // ! diferentes
    cout << "Diferentes...\n";
    vector<int> tokensDifferent { diferentes(tokens) };
    for (auto element : tokensDifferent)
        cout << element << " ";
    cout << endl;

    // ! abandonados
    cout << "Abandonados...\n";
    vector<int> tokensAbandoned { abandonados(tokens) };
    for (auto element : tokensAbandoned)
        cout << element << " ";
    cout << endl;

    // ? BLOCO III

    // ! quais são os unicos
    cout << "Quais são os unicos...\n";
    vector<int> tokensUnique { quaisSaoOsUnicos(tokens) };
    for (auto element : tokensUnique)
        cout << element << " ";
    cout << endl;

    // ! maior ocorrencia
    cout << "Maior ocorrencia...\n";
    cout << maiorOcorrencia(tokens) << endl;

    // ! mais recorrentes
    cout << "Mais recorrentes...\n";
    vector<int> tokensRecurrent{maisRecorrentes(tokens)};
    for (auto element : tokensRecurrent)
        cout << element << " ";
    cout << endl;

    // ! briga(valor 50 > proximo(esquerda, direita) de um valor > 30)
    cout << "Briga...\n";
    cout << brigas(tokens) << endl;
    
    // ! apaziguados(valor 80 > proximo(esquerda, direita) de um valor < 10)
    cout << "Apaziguados...\n";
    vector<int> tokensApaziguados{apaziguados(tokens)};
    for (auto element : tokensApaziguados)
        cout << element << " ";
    cout << endl;
    */
    // ! quantos times(valores positivos e negativos)
    cout << "Quantos times...\n";
    cout << quantosTimes(tokens) << endl;
}