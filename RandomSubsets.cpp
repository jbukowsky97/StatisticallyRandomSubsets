#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <vector>
#include <random>
#include <time.h>

int get_number(std::default_random_engine &generator, std::vector<std::tuple<int, int>> &gaps, int &size) {
    std::vector<std::tuple<int, int>>::iterator it;
    // std::cout << "Begin" << std::endl;
    // for (it = gaps.begin(); it != gaps.end(); ++it) {
    //     std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it) << ")" << std::endl;
    // }

    int num = std::uniform_int_distribution<int>{0, size - 1}(generator);
    // std::cout << "num:\t" << num << std::endl;
    // std::vector<std::tuple<int, int>>::iterator it;
    for (it = gaps.begin(); it != gaps.end(); ++it) {
        int &lower = std::get<0>(*it);
        int &upper = std::get<1>(*it);
        if (lower + num <= upper) {

            int index = it - gaps.begin();

            /* edit gaps */
            if (num == 0) {
                // trim range
                const int return_int = lower + num;
                if (upper == lower) {
                    gaps.erase(it);
                } else {
                    lower += 1;
                }

                // std::cout << "End" << std::endl;
                // for (it = gaps.begin(); it != gaps.end(); ++it) {
                //     std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it) << ")" << std::endl;
                // }

                size--;
                return return_int;
            } else if (lower + num == upper) {
                // trim range
                upper -= 1;

                // std::cout << "End" << std::endl;
                // for (it = gaps.begin(); it != gaps.end(); ++it) {
                //     std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it) << ")" << std::endl;
                // }

                size--;
                return lower + num;
            }
            const int prev_lower = lower;
            lower = lower + num + 1;
            if (index > 0) {
                int &prev_upper = std::get<1>(gaps.at(index - 1));
                if (prev_upper + 1 == prev_lower + num - 1) {
                    prev_upper+= 1;
                } else {
                    // std::cout << "inserting" << std::endl;
                    gaps.insert(gaps.begin() + index, std::make_tuple(prev_lower, prev_lower + num - 1));
                }
            } else {
                // std::cout << "inserting" << std::endl;
                gaps.insert(gaps.begin() + index, std::make_tuple(prev_lower, prev_lower + num - 1));
            }

            // std::cout << "End" << std::endl;
            // for (it = gaps.begin(); it != gaps.end(); ++it) {
            //     std::cout << "(" << std::get<0>(*it) << ", " << std::get<1>(*it) << ")" << std::endl;
            // }

            size--;
            return prev_lower + num;
        } else {
            num -= upper - lower + 1;
        }
    }
}

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
            // num = std::uniform_int_distribution<int>{1, size}(generator);
            num = get_number(generator, gaps, size);
            contains = numbers.find(num) != numbers.end();
            if (contains) {
                std::cout << "THAT IS IMPOSSIBLE" << std::endl;
                exit(-1);
            }
        } while (contains);
        numbers.insert(num);
    }

    std::set<int>::iterator it;
    for (it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << std::endl;
    }
}