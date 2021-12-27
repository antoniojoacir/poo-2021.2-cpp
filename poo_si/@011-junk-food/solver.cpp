#include <iostream>
#include <memory>
#include <vector>

class Storage {
    std::string name;
    int unidad;
    float price;
public:

    Storage(std::string name= "", int unidad= 0, float price= 0.0) : 
    name(name), unidad(unidad), price(price) {}

    std::string getName() const { return name; }
    
    int getUnidad() const { return unidad; }
    
    double getPrice() const { return price; }

    void setUnidad() { 
        this->unidad--;
    }

    friend std::ostream& operator<<(std::ostream& os, const Storage& storage);
};
std::ostream& operator<<(std::ostream& os, const Storage& storage) {
    os << "[" << storage.name << " [" << storage.unidad << "U] - " << storage.price << "R$]";
    return os;
}

class Junk {
    std::vector<std::shared_ptr<Storage>> storages;
    int quantidadeMaxima;
    float lucroTotal;
    float saldoCliente;
    bool validadeIndex(const int index) {
        if (index >= (int) storages.size() || index < 0)
            return false;
        return true;
    }
public:

    Junk(int size, int quantidadeMaxima= 0) :
    storages(size, nullptr), quantidadeMaxima(quantidadeMaxima) {}

    friend std::ostream& operator<<(std::ostream& os, const Junk& junk);

    bool addProduto(const std::shared_ptr<Storage>& storage, int index) {
        if (!validadeIndex(index)) {
            std::cout << "Index invalido\n";
            return false;
        }
        if (this->storages[index] != nullptr) {
            std::cout << "Produto ja existe na posicao " << index << std::endl;
            return false;
        }
        if (storage->getUnidad() > this->quantidadeMaxima) {
            std::cout << "Quantidade maxima excedida\n";
            return false;
        }
        this->storages[index] = storage;
        return true;
    }

    Storage * clearStorage(int index) {
        if (!validadeIndex(index)) {
            std::cout << "Index invalido\n";
            return nullptr;
        }
        Storage * storage = this->storages[index].get();
        this->storages[index] = nullptr;
        return storage;
    }

    bool addSaldo(float value) {
        if (value < 0) {
            std::cout << "Valor invalido\n";
            return false;
        }
        this->saldoCliente += value;
        return true;
    }

    bool pedirTroco() {
        if (this->saldoCliente < 0) {
            std::cout << "Não há dinheiro na maquina\n";
            return false;
        }
        std::cout << "Troco: " << this->saldoCliente << "R$\n";
        this->saldoCliente = 0;
        return true;
    }

    bool venderProduto(int index) {
        if (!validadeIndex(index)) {
            std::cout << "Index invalido\n";
            return false;
        }
        if (this->storages[index] == nullptr) {
            std::cout << "Produto nao existe na posicao " << index << std::endl;
            return false;
        }
        if (this->storages[index]->getUnidad() <= 0) {
            std::cout << "Não há produtos em estoque\n";
            return false;
        }
        this->storages[index]->setUnidad();
        this->lucroTotal += this->storages[index]->getPrice();
        return true;
    }

    void quantoLucrei() {
        std::cout << "O lucro total foi de " << this->lucroTotal << "R$\n";
    }

    bool alterarStorage(int index, const std::shared_ptr<Storage>& storage) {
        if (!validadeIndex(index)) {
            std::cout << "Index invalido\n";
            return false;
        }
        if (this->storages[index] == nullptr) {
            std::cout << "Produto nao existe na posicao " << index << std::endl;
            return false;
        }
        this->storages[index] = storage;
        return true;
    }

    
};
std::ostream& operator<<(std::ostream& os, const Junk& junk) {
    os << "Saldo: " << junk.saldoCliente << "R$\n";
    for (auto& storage : junk.storages) {
        if (storage) {
            os << *storage << std::endl;
        }
        else {
            os << "[Empty] " << std::endl;
        }
    }
    return os;
}

int main() {
    Junk junk(3, 3);
    junk.addProduto(std::make_shared<Storage>("Coca-Cola", 2, 2.5), 0);
    // quantidade excedida
    junk.addProduto(std::make_shared<Storage>("Fanta", 5, 1.5), 1);
    // invalid index
    junk.addProduto(std::make_shared<Storage>("Sprite", 1, 1.5), 4);

    // vai ter produto somente no indice 0
    std::cout << junk << "\n\n";

    junk.clearStorage(0);

    // limpo
    std::cout << junk << "\n\n";

    junk.addSaldo(10);
    junk.addProduto(std::make_shared<Storage>("Coca-Cola", 2, 2.5), 0);
    // quantidade excedida
    junk.addProduto(std::make_shared<Storage>("Fanta", 5, 1.5), 1);
    junk.addProduto(std::make_shared<Storage>("Sprite", 3, 1.5), 2);

    std::cout << junk;

    junk.venderProduto(0);
    junk.venderProduto(1);

    std::cout << junk;

    junk.pedirTroco();
    junk.quantoLucrei();

}