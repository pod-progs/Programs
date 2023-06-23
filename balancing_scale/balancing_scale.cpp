#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

#include "utils.h"

struct Scale {
    std::string name;
    std::string left;
    std::string right;
    int additionalLeftMass = 0;
    int additionalRightMass = 0;
    int total = -1;

    friend std::ostream& operator << (std::ostream& os, const Scale& scale)
    {
        os << scale.name << ',' << scale.additionalLeftMass << ',' << scale.additionalRightMass;
        return os;
    }
};

class BalancedScaleTree
{
    std::unordered_map<std::string, Scale> scales;
    std::vector<std::string> scaleNames;

public:
    void run() {
        parseInput();

        if (!Utils::isSorted(scaleNames)){
            Utils::sort(scaleNames);
        }

        for (const auto& name: scaleNames){
            if (scales[name].total == -1)
                doBalancing(scales[name]);
        }
        std::cout << "Balanced Scale Tree Output:" << '\n';
        for (const auto& name : scaleNames) {
            std::cout << scales[name] << '\n';
        }
    }
private:
    void parseInput() {
        try {
            std::string line;
            std::cout << "Enter scale tree details:" << '\n';

            while (getline(std::cin, line) && !line.empty()) {
                if (line[0] == '#')
                    continue;

                std::istringstream iss(line);
                Scale scale;
                std::getline(iss, scale.name, ',');
                std::getline(iss, scale.left, ',');
                std::getline(iss, scale.right, ',');

                scaleNames.push_back(scale.name);
                scales[scale.name] = std::move(scale);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "An error occurred while parsing the inputs: " << e.what() << std::endl;
        }
    }

    void doBalancing(Scale& scale) {
        int leftMass = 0, rightMass = 0;

        if (Utils::isDigit(scale.left[0])) {
            leftMass = Utils::stoi(scale.left);
        }
        else {
            if(scales[scale.left].total == -1)
                doBalancing(scales[scale.left]);
            leftMass = scales[scale.left].total;
        }

        if (Utils::isDigit(scale.right[0])) {
            rightMass = Utils::stoi(scale.right);
        }
        else {
            if (scales[scale.right].total == -1)
                doBalancing(scales[scale.right]);
            rightMass = scales[scale.right].total;
        }

        scale.additionalLeftMass = std::max(0, rightMass - leftMass);
        scale.additionalRightMass = std::max(0, leftMass - rightMass);

        scale.total = leftMass + rightMass + 1 + scale.additionalLeftMass + scale.additionalRightMass;
    }
};

int main() {
    BalancedScaleTree bst;
    bst.run();    
    return 0;
}

