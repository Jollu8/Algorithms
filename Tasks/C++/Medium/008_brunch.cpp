//
// Created by zholu on 05/11/2021.
//

#include  <iostream>
#include <vector>
#include <string>


class Branch {
    std::string elfName = "uncknow";
    bool elfLodger = false;

public:

    std::string getElfName();

    bool getElfLodger() const;

    void setElfName();
};

class BigBranch : Branch {
    std::vector<Branch> branches;

public:

    bool elfLiveHere(const std::string &elfName);

    int countNeighbors(const std::string &elfName);

    void setElfInHouse(const std::string &nameBranch);
};


class Tree {
    std::vector<BigBranch> bigBranches;

public:

    Tree() {}

    void setTree();


    bool getNeighbors(const std::string &elfName);

};


bool BigBranch::elfLiveHere(const std::string &elfName) {

    for (auto &&branch: branches)
        if (branch.getElfName() == elfName && branch.getElfLodger())
            return true;

    if (this->getElfName() == elfName && this->getElfLodger())
        return true;

    return false;
}

int BigBranch::countNeighbors(const std::string &elfName) {
    int countNeighbors = 0;

    for (auto &&branch: branches)
        if (branch.getElfName() != elfName) {
            countNeighbors += (int) (branch.getElfLodger());
        }


    if (this->getElfName() != elfName)
        countNeighbors += (int) getElfLodger();

    return countNeighbors;
}

void BigBranch::setElfInHouse(const std::string &nameBranch) {
    int countBranch;
    countBranch = rand() % 2 + 2;
    branches.resize(countBranch);

    std::cout << "Branch name: " << nameBranch << std::endl;
    for (auto &&branch: branches)
        branch.setElfName();

    this->setElfName();
}


std::string Branch::getElfName() {
    return elfName;
}

bool Branch::getElfLodger() const {
    return elfLodger;
}

void Branch::setElfName() {
    std::cout << "Please, input elf name:" << std::endl;
    std::string elfName;
    std::cin >> elfName;
    if (elfName != "none") {
        this->elfName = elfName;
        elfLodger = true;
    }
}

void Tree::setTree() {
    std::srand(time(nullptr));
    int countBigBranch = rand() % 2 + 1/*3 + 3*/;
    bigBranches.resize(countBigBranch);

    std::string nameBranch = "Branch#";
    int i = 1;
    for (auto &&branches: bigBranches) {
        branches.setElfInHouse(nameBranch + std::to_string(i++));
    }
}

bool Tree::getNeighbors(const std::string &elfName) {
    bool found = false;
    int i;
    for (i = 0; i < bigBranches.size(); ++i) {
        if (bigBranches[i].elfLiveHere(elfName)) {
            found = true;
            break;
        }
    }

    if (!found) {
        return false;
    } else {
        std::cout << elfName << " has " << bigBranches[i].countNeighbors(elfName) << " neighbors" << std::endl;
        return true;
    }
}


int main() {
    Tree *forest[5];

    for (auto &&tree: forest) {
        tree = new Tree();
        tree->setTree();
    }

    std::cout << "Please, the name of the elf you are looking for" << std::endl;
    std::string elfName;
    std::cin >> elfName;
    bool elfNotfound = true;

    for (auto &&tree: forest) {
        if (tree->getNeighbors(elfName)) {
            elfNotfound = false;
            break;
        }
    }

    if (elfNotfound) {
        std::cout << elfName << " not found." << std::endl;
    }

    for (auto &&tree: forest)
        delete tree;
}