#include <iostream>
#include <chrono>
#include <string>
#include <set>
#include <tuple>
#include <vector>
#include <random>
#include <regex>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage:" << std::endl << "\t./a.out <K> <N>" << std::endl;
        exit(1);
    }

    std::string k_str = argv[1];
    std::string n_str = argv[2];

    if (!std::regex_match(k_str, std::regex("[0-9]+")) || !std::regex_match(n_str, std::regex("[0-9]+"))) {
        std::cout << "N and K must be integer values less than 2^64 - 1" << std::endl;
        exit(1);
    }

    unsigned long long int k;
    unsigned long long int n;
    
    try {
        k = std::stoull(k_str);
        n = std::stoull(n_str);
    } catch (...) {
        std::cout << "N and K must be integer values less than 2^64 - 1" << std::endl;
        exit(1);
    }
    if (k > n) {
        std::cout << "K must be less than or equal to N" << std::endl;
        exit(1);
    }
    /*
        Using set to store generated numbers because
        it is typically implemented as a red-black tree so:
            a. Sorted, no need to sort later and lose performance
            b. Guaranteed worst case O(log n) insert and retrieval
    */
    std::set<unsigned long long int> numbers;
   
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned long long int> distribution(1, n);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    for (unsigned long long int i = 0; i < k; ++i) {
        bool contains;
        unsigned long long int num;
        do {
            num = distribution(generator);
            contains = numbers.find(num) != numbers.end();
        } while (contains);
        numbers.insert(num);
    }

    std::set<unsigned long long int>::iterator it;
    for (it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << std::endl;
    }
}