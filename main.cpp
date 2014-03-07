#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

typedef char char_type;

class caesar_cipher {
private:
	int shift;
	bool is_upper;
public:
	caesar_cipher(int s) : shift(s) {}
	char_type operator()(char_type c) {
		if (std::isspace(c))
			return c;
		else {
			is_upper = false;
			static std::string letters("abcdefghijklmnopqrstuvwxyz");
			if (isupper(c)) { is_upper = true; }
			auto found = letters.find(std::tolower(c)) ;
			int shiftedpos = (static_cast<int>(found) + shift) % letters.size();
			if (shiftedpos < 0) shiftedpos += letters.size();
			return (is_upper) ? std::toupper(letters[shiftedpos]) : letters[shiftedpos];
		}
	}
};

int main(int argc, char** argv) {
	std::ifstream in_file(argv[1]);
	std::string input((std::istreambuf_iterator<char_type>(in_file)), std::istreambuf_iterator<char_type>());
	std::transform(input.begin(), input.end(), input.begin(), caesar_cipher(std::atoi(argv[2])));
	std::ofstream out_file("caesar_cipher.txt");
	std::cout << input << std::endl;
	out_file << input;
}