#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
 
int main()
{
    int n;
    std::cin >> n;
 
    std::vector<int> d(n);
    for (auto& it : d) std::cin >> it;
 
    std::vector<int> a(n);
    std::vector<bool> f(n, true);
 
    for (int i(n - 1); i >= 0; --i) {
        int j{}, m(n - 1);
        while (j < d[i] || !f[m]) {
            if (f[m]) ++j;
            --m;
        }
        a[i] = m + 1;
        f[m] = false;
    }
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
 
    return 0;
}