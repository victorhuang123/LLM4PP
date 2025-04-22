

#include <string>
#include <vector>

std::string baseline(const std::string& a) {
    std::string result = a;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] != 'z' && islower(result[i])) {
            result[i]++;
        }
    }
    return result;
}