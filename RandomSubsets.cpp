#include <chrono>
#include <iostream>
#include <random>
#include <regex>
#include <set>
#include <string>

int main(int argc, char* argv[]) {

    /* check arguments */
    if (argc != 3) {
        std::cout << "Usage:" << std::endl << "\t./a.out <K> <N>" << std::endl;
        exit(1);
    }

    std::string k_str = argv[1];
    std::string n_str = argv[2];

    /* check if strings match desired regex pattern */
    if (!std::regex_match(k_str, std::regex("[0-9]+")) || !std::regex_match(n_str, std::regex("[0-9]+"))) {
        std::cout << "N and K must be integer values less than 2^64 - 1" << std::endl;
        exit(1);
    }

    unsigned long long int k;
    unsigned long long int n;

    /* parse strings, catch in case number is larger than 2^64 - 1 */
    try {
        k = std::stoull(k_str);
        n = std::stoull(n_str);
    } catch (...) {
        std::cout << "N and K must be integer values less than 2^64 - 1" << std::endl;
        exit(1);
    }

    /* ensure k <= n */
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

    /* to hold return value of insert into set, to see if number already existed */
    std::pair<std::set<unsigned long long int>::iterator,bool> returnValue;

    /* create random number generator */
    std::default_random_engine generator;

    /* create uniform distribution so each number is equally likely */
    std::uniform_int_distribution<unsigned long long int> distribution(1, n);

    /* seed generator with system clock */
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);

    /* generate K integers in range 1..N */
    for (unsigned long long int i = 0; i < k; ++i) {
        /* generate number, redo if number already in numbers */
        do {
            /* capture returnValue, to check if number already existed without performance cost */
            returnValue = numbers.insert(distribution(generator));
        } while (!returnValue.second);
    }

    /* print out numbers */
    std::set<unsigned long long int>::iterator it;
    for (it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << std::endl;
    }
}