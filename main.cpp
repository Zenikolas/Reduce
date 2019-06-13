#include <iostream>
#include <unistd.h>
#include <tuple>
#include <sstream>

#include "reducedsum.h"
#include "stringnumber.h"

bool isNumber(const char *pstr, const size_t maxLen = 0, const bool isSigned = true) {
    if (!pstr || *pstr == '\0') {
        return false;
    }

    bool isFirstChar = true;
    size_t len = 0;
    while (*pstr) {
        switch (*pstr) {
            case '-':
                if (!isSigned) {
                    return false;
                }
            case '+':
                if (!isFirstChar) {
                    return false;
                }
                break;
            default:
                if (*pstr < '0' || *pstr > '9') {
                    return false;
                }
        }

        if (maxLen != 0 && ++len > maxLen) {
            return false;
        }

        isFirstChar = false;
        ++pstr;
    }

    return true;
}

std::tuple<bool, size_t, long int, long int> parseArgs(int argc, char *argv[]) {
    const char *usage = "Usage: <program_name> -nUNSIGNEDINT -aINT -bINT [-h]";
    const char *options = "n:a:b:h";
    const size_t maxIntDimension = std::numeric_limits<long int>::digits10;
    const size_t maxUIntDimension = std::numeric_limits<unsigned long int>::digits10;
    opterr = 0;
    int key{};
    long int a{}, b{};
    size_t n{};
    bool nPassed = false, aPassed = false, bPassed = false;
    std::string msg;
    while ((key = getopt(argc, argv, options)) != -1) {
        std::stringstream ss;
        if (optarg) {
            ss << optarg;
        }
        switch (key) {
            case 'n':
                if (isNumber(optarg, maxUIntDimension, false)) {
                    ss >> n;
                    nPassed = true;
                }
                break;
            case 'a':
                if (isNumber(optarg, maxIntDimension)) {
                    ss >> a;
                    aPassed = true;
                }
                break;
            case 'b':
                if (isNumber(optarg, maxIntDimension)) {
                    ss >> b;
                    bPassed = true;
                }
                break;
            case 'h':
                printf("%s", usage);
                return {false, n, a, b};
            case '?':
            default:
                msg += "Argument parsing error! Option: ";
                msg += (char) optopt;
                msg += "\n";
                break;
        }
    }

    bool allPassed = nPassed && aPassed && bPassed;
    if (!allPassed) {
        printf("Command line parsing was failed, see usage:\n%s\n"
               "\n%s", usage, msg.c_str());
    }

    return {allPassed, n, a, b};
}

int main(int argc, char *argv[]) {
    auto[ret, n, a, b] = parseArgs(argc, argv);
    if (!ret) {
        return 0;
    }

    printf("Received params n: %lu, a: %ld, b: %ld\n", n, a, b);
    printf("R arguments calculating ...");

    scientific::ReducedSumParams rParams(n, a, b);
    rParams.init();
    printf(" done!\n");

    printf("R calculating ...");
    if (rParams.isSmallDimension()) {
        auto r = scientific::backwardReducedSum(rParams.getSmallDimensionNParam(),
                                                rParams.getSmallDimensionMParam());

        printf(" done!\n");
        printf("R: %ld", r);
    } else {
//        auto r = scientific::backwardReducedSum(rParams.getBigDimensionNParam(),
//                                       rParams.getBigDimensionMParam());
        printf(" done!\n");
//        printf("R: %s", r.c_str());
    }
}