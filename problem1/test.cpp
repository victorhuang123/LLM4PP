#include <iostream>
#include <format>

int main() {
    std::string name = "Alice";
    int age = 30;
    double height = 1.68;

    // 使用 std::format 格式化字符串
    std::string formatted_str = std::format("Name: {}, Age: {}, Height: {:.2f} meters", name, age, height);

    // 输出格式化后的字符串
    std::cout << formatted_str << std::endl;

    return 0;
}