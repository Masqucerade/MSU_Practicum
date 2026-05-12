#include <iostream>

class Parser {
private:
	char ch;
	std::string str;
public:
	void gc() { ch = std::cin.get(); }
	void S();
	void A();
	bool pars();
};

void Parser::S() {
	if (ch == 'a') {
		str.push_back('2');
		gc();
		A();
		str.push_back('a');
	} 
	else if (ch == 'b') {
		gc();
		A();
		str.push_back('b');
	} else {
		throw ch;
	}
}

void Parser::A() {
	if (ch == 'a') {
		str.push_back('2');
		gc();
		A();
		str.push_back('a');
	}
	else if (ch == 'b') {
		gc();
		A();
		str.push_back('b');
	}
}

bool Parser::pars() {
	gc();
	try {
		S();
		if (ch != '\n') throw ch;
		std::cout << str;
		return true;
	} catch (char ch) {
		std::cerr << "Error in: " << ch << std::endl;
        return false;
	}

}

int main() {
	Parser p;
	p.pars();
	return 0;
}
