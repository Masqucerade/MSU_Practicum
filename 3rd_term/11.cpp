#include <iostream>
#include <string>

class Analyz {
private:
	enum Sost { H, B, C, S };
	const char* input;
	char ggChar = 0;

public:
	Analyz(const char* str) : input(str), ggChar(0) {}
	bool analyze();
	char getGGChar() const noexcept {return ggChar;}
};

bool Analyz::analyze() {
	const char* p = input;
	Sost state = H;
	char lastChr = 0;

	while (*p != '\n' && *p != '\0') {
		char c = *p;
		lastChr = c;

		switch (state) {
			case H:
				if (c == 'a') state = B;
				else state = C;
				break;
			case B:
				if (c == 'a')  state = S;
				else if (c == 'd') state = B;
				else state = C;
				break;
			case C:
				state = C;
				break;
			case S:
				if (c == 'a') state = B;
				else state = C;
		}

		if (state == C) {
			ggChar = lastChr;
			return false;
		}
		p++;
	}
	if (state == S) {
		return true;
	} else {
		if (p != input) ggChar = *p;
		else ggChar = 0;
		return false;
	}
}

int main() {
	std::string str;
	std::getline(std::cin, str);
	Analyz analyzerr(str.c_str());

	if (analyzerr.analyze()) {
		std::cout << str << std::endl;
	} else {
		char err = analyzerr.getGGChar();
		if (err != 0)
    		std::cerr << "Error in Lexcem: " << err << std::endl;
		else
    		std::cerr << "Error in Lexcem: " << std::endl;
	}

}
