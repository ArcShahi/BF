#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <array>

// Remove the use of std::filesytem and you'll get executable of size ~30KB
namespace fs = std::filesystem;

namespace {

	[[nodiscard]] int interpreter(const fs::path& path) noexcept {

		//  Preprocesser
		if (!fs::is_regular_file(path) || path.extension() != ".bf") {
			std::cout << "bf++: srcfile not found" << path.string();
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

		for (int ip{ 0 }; ip < program.length(); ++ip) {
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
			case '.':
				std::cout << static_cast<char>(tape[arrow]);
				break;
			case ',':
				std::cin >> tape[arrow];
				break;
			case '[':
				if (!tape[arrow])
					ip = loop_lookup.at(ip);
				break;
			case ']':
				if (tape[arrow])
					ip = loop_lookup.at(ip);
				break;
			}
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
