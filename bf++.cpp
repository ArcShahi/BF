#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdint>


namespace {

	[[nodiscard]] int interpreter(const std::string& path, const bool binary_mode = false) noexcept {

		if (!path.ends_with(".bf") && !path.ends_with(".b")) {
			std::cerr << "error: no src file";
			return 1;
		}

		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "Can't open file";
			return 1;
		}

		std::string program{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
		file.close();

		// Filter comments
		program.erase(std::remove_if(program.begin(), program.end(),
					   [](char c) {
						   static const std::string ins{ "+-<>.,[]" };
						   return ins.find(c) == std::string::npos;
					   }),
		    program.end());

		std::array<uint8_t, 3000> tape{};
		size_t arrow{ 0 };

		// IIFE : Loop Lookup table
		const auto loop_lookup = [&]() {
			std::vector<int> stk{};
			std::unordered_map<int, int> lookup{};
			for (int i{ 0 }; i < program.length(); ++i) {
				if (program[i] == '[')
					stk.push_back(i);
				else if (program[i] == ']') {
					lookup[stk.back()] = i;
					lookup[i] = stk.back();
					stk.pop_back();
				}
			}
			return lookup;
		}();

		// Execution
		int ip{ 0 };
		while (ip < program.length()) {
			switch (program[ip]) {
			case '+':
				++tape[arrow];
				break;
			case '-':
				--tape[arrow];
				break;
			case '>':
				++arrow;
				break;
			case '<':
				--arrow;
				break;
			case '.': {

				uint8_t val{ tape[arrow] };
				if (!binary_mode) [[likely]]
					std::cout << (val == 10 ? '\n' : static_cast<char>(val));
				else
					std::cout << static_cast<char>(val);

				break;
			}
			case ',': {

				int input{ std::cin.get() };
				if (input == -1)
					tape[arrow] = 0;
				if (!binary_mode) [[likely]]
					tape[arrow] = (input == '\n' || input == '\r') ? 10 : static_cast<uint8_t>(input);
				else
					tape[arrow] = static_cast<uint8_t>(input);

				break;
			}
			case '[':
				if (!tape[arrow])
					ip = loop_lookup.at(ip);
				break;
			case ']':
				if (tape[arrow])
					ip = loop_lookup.at(ip);
				break;
			}
			++ip;
		}

		return 0;
	}

}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cerr << "bf++: error: no input file";
		return 1;
	}
	return interpreter(argv[1]);
}
