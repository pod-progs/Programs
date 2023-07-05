#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <fstream>

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
    void run(const std::string& path) {
        if(parseInput(path))
            return;

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
    int parseInput(const std::string& path) {
        try {
            std::ifstream input(path);
            std::string line;

            while (getline(input, line) && !line.empty()) {
                if (line[0] == '#')
                    continue;

                std::istringstream iss(line);
                Scale scale;
                std::getline(iss, scale.name, ',');
                std::getline(iss, scale.left, ',');
                std::getline(iss, scale.right, ',');

                if(scales.count(scale.name))
                    throw std::runtime_error("Invalid input as it duplicated scale details for " + scale.name);

                if (scales.count(scale.left))
                    throw std::runtime_error("Invalid input as it contains loop in scales for " + scale.left);

                if (scales.count(scale.right))
                    throw std::runtime_error("Invalid input as it contains loop in scales for " + scale.right);

                scaleNames.push_back(scale.name);
                scales[scale.name] = std::move(scale);
            }

            input.close();
        }
        catch (const std::exception& e) {
            std::cerr << "An error occurred while parsing the inputs: " << e.what() << std::endl;
            return 1;
        }
        return 0;
    }

    void doBalancing(Scale& scale) {
        int leftMass = 0, rightMass = 0;

        if (std::isdigit(scale.left[0]) || scale.left[0]=='-') {
            leftMass = std::stoi(scale.left);
        }
        else {
            if(scales[scale.left].total == -1)
                doBalancing(scales[scale.left]);
            leftMass = scales[scale.left].total;
        }

        if (std::isdigit(scale.right[0]) || scale.right[0] == '-') {
            rightMass = std::stoi(scale.right);
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: balancing_scale.exe <file_path>" << std::endl;
        return 1;
    }

    std::filesystem::path path(argv[1]);

    if (!std::filesystem::exists(path)) {
        std::cout << "File does not exist." << std::endl;
        return false;
    }
    std::string extension = path.extension().string();
    if (extension != ".txt" && extension != ".text") {
        std::cout << "Invalid text file extension." << std::endl;
        return false;
    }

    BalancedScaleTree bst;
    bst.run(argv[1]);

    return 0;
}

