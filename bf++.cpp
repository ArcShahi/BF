#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

namespace bf {

	void interpreter(std::string&& program) noexcept {
		std::vector<uint8_t> tape(100, 0);
		size_t arrow{ 0 };

		// IIFE : for loop index lookup
		const auto loop_lookup = [&]() {
			std::vector<int> symbol_stk{};
			std::unordered_map<int, int> loop_lookup{};
			for (int i{ 0 }; i < program.length(); ++i) {
				if (program[i] == '[')
					symbol_stk.push_back(i);
				else if (program[i] == ']') {
					loop_lookup[symbol_stk.back()] = i;
					loop_lookup[i] = symbol_stk.back();
					symbol_stk.pop_back();
				}
			}
			return loop_lookup;
		}();

		for (int ip{ 0 }; ip < program.length(); ++ip) {
			switch (program[ip]) {
			case '+':
				++tape[arrow];
				break;
			case '-':
				--tape[arrow];
				break;
			case '>': {
				++arrow;
				if (arrow >= tape.size()) {
					std::cerr << "Tape overflow\n";
					return;
				}
				break;
			}

			case '<': {
				--arrow;
				if (arrow < 0) {
					std::cerr << "Tape pointer out of bounds\n";
				}
				break;
			}

			case '.': {
				std::cout << static_cast<char>(tape[arrow]);
				break;
			}

			case ',': {
				char input{};
				std::cin >> input;
				tape[arrow] = static_cast<uint8_t>(input);
				break;
			}
			case '[': {
				if (!tape[arrow])
					// Skip to matching ']'
					ip = loop_lookup.at(ip);
				break;
			}

			case ']': {
				// loop back to '[' if current tape pointer is non-zero
				if (tape[arrow])
					ip = loop_lookup.at(ip);

				break;
			}
			default:
				break;
			}
		}
	}

	int preprocessor(const fs::path& path) noexcept {
		if (!fs::is_regular_file(path) || path.extension() != ".bf") {
			std::cout << "NO BRAINFUCK SOURCE FOUND -_- " << path.string();
			return 1;
		}

		std::ifstream srcfile{ path };
	
		if (!srcfile.is_open()) {
			std::cerr << "Can't open file";
			return 1;
		}
		const std::string instructions{ "+-<>.,[]" };
		std::string program{};
		program.reserve(100);

		char token{};
		while (srcfile.get(token))
			if (instructions.find(token) != std::string::npos)
				program.push_back(token);

		srcfile.close();
		interpreter(std::move(program));
		return 0;
	}

}

int main(int argc, char* argv[]) {

	if (argc == 1) {
		std::cout << "USAGE: bf++ <src.bf>";
		return 1;
	}
	bf::preprocessor(argv[1]);
}
