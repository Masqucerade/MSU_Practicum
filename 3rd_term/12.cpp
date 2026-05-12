#include <iostream>

class Parser {
private:
	char ch;
public:
	void gc() noexcept { ch = std::cin.get();}
	void S();
	void A();
	void B();
	bool analyze() noexcept;
};
void Parser::S() {
	if (ch == 'a') {
		gc();
		A();
		B();
	} else if (ch == 'b') {
		gc();
		B();
	} else {
		throw ch;
	}
	if (ch != '\n') {
        throw ch;
    }
}


void Parser::A() {
	if (ch == 'a') {
		gc();
		A();
	} else if (ch == 'b') {
		gc();
	} else {
		throw ch;
	}
}


void Parser::B() {
	if (ch == 'b') {
		gc();
		B();
	} 
}


bool Parser::analyze() noexcept {
	gc();
	try {
		S();
	} catch(char c) {
		return false;
	}
	return true;
}

int main() {
	Parser p;
	bool res = p.analyze();
	std::cout << (res ? "YES" : "NO") << std::endl; 
}
