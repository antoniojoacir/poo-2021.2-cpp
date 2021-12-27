#include <iostream>
#include <vector>
#include <sstream>

void __show__(std::vector<int>& vector) {
    std::cout << "[";
    for (auto& i : vector) {
        std::cout << " " << i;
    }
    std::cout << " ]\n";
}

std::vector<int> make_vector(std::string value) {
    std::stringstream ss(value);
    std::vector<int> vect;
    int val;
    while (ss >> val) {
        vect.push_back(val);
    }
    return vect;
}

std::vector<int> __alones__(std::vector<int>& vector) {
    std::vector<int> result;
    for (auto& i : vector) {
        if (std::count(vector.begin(), vector.end(), abs(i)) == 1 && std::find(result.begin(), result.end(), abs(i)) == result.end()) {
            result.push_back(abs(i));
        }
    }
    return result;
}

int __highest_occurrence__(std::vector<int>& vector) {
    auto highest_occurrence = 0;
    for (auto& value : vector) {
        if (std::count(vector.begin(), vector.end(), abs(value)) > highest_occurrence) {
            highest_occurrence = std::count(vector.begin(), vector.end(), abs(value));
        }
    }
    return highest_occurrence;
}

std::vector<int> __highest_recurrence__(std::vector<int>& vector) {
    std::vector<int> result;
    auto highest_occurrence = __highest_occurrence__(vector);
    for (auto& i : vector) {
        if (std::count(vector.begin(), vector.end(), i) == highest_occurrence && std::find(result.begin(), result.end(), abs(i)) == result.end()) {
            result.push_back(abs(i));
        }
    }
    return result;
}

int main() {
    //std::string line;
    //getline(std::cin, line);
    std::vector<int> vect { 1, 3, 4, 5, -1, -5, -5, 3, -3 };
    //make_vector(line);

    std::vector<int> alones { __alones__(vect) };
    std::cout << "Alones - ";
    __show__(alones);

    std::cout << "Highest occurrence: " << __highest_occurrence__(vect) << "\n";

    std::vector<int> highest_recurrence { __highest_recurrence__(vect) };
    std::cout << "Highest recurrence - ";
    __show__(highest_recurrence);
}