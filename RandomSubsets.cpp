#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <vector>
#include <random>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage:" << std::endl << "\t./a.out <K> <N>" << std::endl;
        exit(1);
    }
    std::string kStr = argv[1];
    std::string nStr = argv[2];
    int k;
    int n;
    try {
        k = std::stoi(kStr);
        n = std::stoi(nStr);
    } catch (...) {
        std::cout << "N and K must be integer values" << std::endl;
        exit(1);
    }
    /*
        Using set to store generated numbers because
        it is typically implemented as a red-black tree so:
            a. Sorted, no need to sort later and lose performance
            b. Guaranteed worst case O(log n) insert and retrieval
    */
    std::set<int> numbers;
    std::vector<std::tuple<int, int>> gaps (1, std::make_tuple(1, n));
    /* keeps track of how many numbers in subset are available */
    int size = n;
   
    std::default_random_engine generator;
    generator.seed(time(nullptr));
    for (int i = 0; i < k; ++i) {
        bool contains;
        int num;
        do {
            num = std::uniform_int_distribution<int>{1, size}(generator);
        } while (contains);
        numbers.insert(num);
    }

    std::set<int>::iterator it;
    for (it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << std::endl;
    }
}