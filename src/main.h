#pragma once

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>

void run_file(std::string& path);
void run_prompt();
void run(std::vector<uint8_t>& bytes);
void run(std::string_view source);

namespace Lox {
    void report(int line, std::string_view where, std::string_view message);
    void error(int line, std::string_view message);
}
