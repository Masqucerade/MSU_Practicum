#include <iostream>
#include <map>
#include <array>
#include <cmath>
#include <tuple>

class Parser {
public:
	std::tuple<char, int, int, int, int> parse(const std::string& line) {
		int pos1 = line.find(' ');
		int pos2 = line.find(' ', pos1 + 1);

		std::string figure = line.substr(0, pos1);
		std::string from = line.substr(pos1 + 1, pos2-pos1-1); // Q H5 H4
		std::string to = line.substr(pos2+1);

		char figure_code = figure[0];

		int from_letter = from[0] - 'a' + 1;
		int from_num = from[1] - '0';
		int to_letter = to[0] - 'a' + 1;
		int to_num = to[1] - '0';

		return {figure_code, from_letter, from_num, to_letter, to_num};
	}
};

class Figure {
public:
	virtual ~Figure() {};
	virtual bool move(int fX, int fY,int  toX,int toY) const = 0;
};

class King : public Figure {
public:
	bool move(int fx, int fy, int tx, int ty) const override { // E4 -> F5/F4/D3
		int disp_x = std::abs(fx - tx);
		int disp_y = std::abs(fy - ty);
		return (disp_x<=1) && (disp_y<=1);
	}
};

class Queen : public Figure {
public:
	bool move(int fx, int fy, int tx, int ty) const override {
		int disp_x = std::abs(fx - tx);
		int disp_y = std::abs(fy - ty);
		return ( (disp_x == disp_y) || (disp_x == 0) || (disp_y == 0));
	}
};

class Knight : public Figure {
public:
	bool move(int fx, int fy, int tx, int ty) const override {
		int disp_x = std::abs(fx - tx);
		int disp_y = std::abs(fy - ty);
		return ( (disp_x == 2 && disp_y == 1) || (disp_x == 1 && disp_y == 2 ));
	}
};

class Bishop : public Figure {
public:
	bool move(int fx, int fy, int tx, int ty) const override {
		int disp_x = std::abs(fx - tx);
		int disp_y = std::abs(fy - ty);
		return (disp_x == disp_y);
	}
};

class Rook : public Figure {
public:
	bool move(int fx, int fy, int tx, int ty) const override {
		int disp_x = std::abs(fx - tx);
		int disp_y = std::abs(fy - ty);
		return ((disp_x == 0) || (disp_y == 0));
	}
};

class ChessChecker {
private:
	std::array<Figure*, 5> figures;
	std::map<char, int> toIndex = { {'K', 0}, {'Q', 1}, {'N', 2}, {'B', 3}, {'R', 4}};

public:
	ChessChecker() {
		figures[0] = new King();
		figures[1] = new Queen();
		figures[2] = new Knight();
		figures[3] = new Bishop();
		figures[4] = new Rook();
	} 

	~ChessChecker() {
    	for (Figure* f : figures) delete f;
	}

	void start() {
		std::string line;
		std::getline(std::cin, line);

		Parser p;
		char fig; 
		int fx, fy, tx, ty;
		std::tie(fig, fx, fy, tx, ty) = p.parse(line);

		if (fx < 1 || fx > 8 || fy < 1 || fy > 8 ||
			tx < 1 || tx > 8 || ty < 1 || ty > 8) {
			std::cout << "NO\n";
			return;
		}

		if ( (fx == tx) && (fy == ty) ) {
			std::cout << "NO\n";
			return;
		}
		
		int indexFig = toIndex[fig];
		bool res = figures[indexFig]->move(fx, fy, tx, ty);

		if (res == 1) std::cout << "YES\n";
		else std::cout << "NO\n";
	}
};

int main() {
	ChessChecker gogo;
	gogo.start();
}
