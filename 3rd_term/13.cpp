#include <iostream>

#define GG -1


int digits[31] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, 5, 4, 3, 2, 1, 6, 7, 8, 9, 0 
};

int sost[31][2] { // .[1] ||  -[2]
	{1, 2}, {3,4}, {5,6}, {7,8}, {GG, 9},
	{10, GG}, {11, 12}, {13,14}, {GG,15}, {GG,16},
	{17,GG}, {18,GG}, {19,20}, {21,22}, {GG,23},
	{GG,24}, {GG,25}, {26,GG}, {27,GG}, {28,GG}, {29,30}, 
	{GG,GG}, {GG,GG}, {GG,GG}, {GG,GG}, {GG,GG}, {GG,GG},
	{GG,GG}, {GG,GG}, {GG,GG},{GG,GG}
};

char gc() { return std::cin.get(); }

void parse() {
	char ch;
	int sost_now = 0;
	std::string result;

	while ((ch = gc()) != '\n' && ch != EOF) {
		if (ch == '.') {
			sost_now = sost[sost_now][0];
			if (sost_now == GG) {
				std::cerr << "Error in Lexeme: " << ch;
				return;
    		}
		} 
		else if (ch == '-') {
			sost_now = sost[sost_now][1];
			if (sost_now == GG) {
				std::cerr << "Error in Lexeme: " << ch;
				return;
    		}
		} 
		else if (ch == ' ') {
			if (digits[sost_now] != -1) { // если не до конца сост
				result.push_back('0' + digits[sost_now]);
				sost_now = 0;
			} else {
				std::cerr << "Error in Lexeme: " << ch;
				return;
			}
		}
		else {
			std::cerr << "Error in Lexeme: " << ch;
			return;
		}
	}
	if (digits[sost_now] != -1) { // если не до конца сост
		result.push_back('0' + digits[sost_now]);
	} else if (sost_now != 0) {
		std::cerr << "Error in Lexeme: " << ch;
		return;
	}
	std::cout << result << std::endl;

}

int main() {
	parse();

	return 0;
}
