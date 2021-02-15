#include <algorithm>
#include <vector>

std::vector<int> converter(int n, int base) {
    std::vector<int> res;
    while (n) {
        res.push_back(n % base);
        n /= base;
    }
    std::reverse(res.begin(), res.end());
    return res;
}