#include <iostream>
#include <vector>
#include <string>

class Root {
public:
    std::vector<std::string> names;

    void amountGeneration();

    void placement();

    void foundNeighborsStick(std::string foo);
};

class Tree {
public:
    std::vector<class Root> tree;

    void amountOfBigRoot();

    void treePlacement();

    void foundTree(std::string foo);
};

class Village {
public:
    std::vector<class Tree> village;

    Village();

    void settlement();

    void foundVillage(std::string foo);

};


//    func ===================================
void Root::amountGeneration() {
    names.resize(std::rand() % 2 + 2);
}

//    func ===================================
void Root::placement() {
    for (int i = 0; i < names.size(); i++) {
        std::cout << "middle stick " << i + 1 << " settlement" << std::endl;
        std::cout << " Please enter a name of Elf" << std::endl;
        std::cin >> names[i];
    }
}

//   func =========================================
void Root::foundNeighborsStick(std::string foo) {
    for (int i = 0; i < names.size(); i++) {
        if (foo == names[i]) {
            std::cout << "Neighbors of " << foo << " are:" << std::endl;
            for (int j = 0; j < names.size(); j++) {
                if (j != i) std::cout << names[j] << std::endl;
            }
        }
    }
}

void Tree::amountOfBigRoot() {
    tree.resize(std::rand() % 3 + 3);
}

void Tree::treePlacement() {
    for (int i = 0; i < tree.size(); i++) {
        std::cout << "Root " << i + 1 << " settlement" << std::endl;
        tree[i].amountGeneration();
        tree[i].placement();
    }
}

void Tree::foundTree(std::string foo) {
    for (int i = 0; i < tree.size(); i++) {
        tree[i].foundNeighborsStick(foo);
    }
}


Village::Village() : village(5) {}

void Village::settlement() {
    std::cout << "Village Settlement" << std::endl;
    for (int i = 0; i < village.size(); i++) {
        std::cout << "Tree " << i + 1 << " settlement" << std::endl;
        village[i].amountOfBigRoot();
        village[i].treePlacement();
    }
}

void Village::foundVillage(std::string foo) {
    for (int i = 0; i < village.size(); i++) {
        village[i].foundTree(foo);
    }
}

int main() {
    Village myVillage;
    myVillage.settlement();
    std::cout << "Who are we looking for?" << std::endl;
    std::string answer;
    std::cin >> answer;
    myVillage.foundVillage(answer);
}