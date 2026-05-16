#include <iostream>
#include <vector>
#include <string>

class Matrixx {
private: 
	std::vector<int> data;
	int rows, cols;

public:
	Matrixx(int r, int c, const std::vector<int>& d): rows(r), cols(c), data(d) {}

	bool insertRowBefore(int pos);
	bool insertRowAfter(int pos);
	bool insertColBefore(int pos);
	bool insertColAfter(int pos);
	
	bool deleteRow(int pos);
	bool deleteCol(int pos);

	bool swapRow(int r1, int r2);
	bool swapCol(int c1, int c2);

	bool transp();
	void print() const;
};

bool Matrixx::insertRowBefore(int pos) {
	if (pos < 1 || pos > rows+1) return false;

	std::vector<int> newRow(cols);
	for (int i =0; i < cols; i++) {
		if (!(std::cin >> newRow[i])) return false;
	}
	
	auto it = data.begin() + (pos -1) * cols;
	data.insert(it, newRow.begin(), newRow.end());
	rows++;
	return true;
}

bool Matrixx::insertRowAfter(int pos) {
	if (pos < 1 || pos > rows) return false;
	return insertRowBefore(pos + 1);
}

bool Matrixx::insertColBefore(int pos) {
	if (pos < 1 || pos > cols+1) return false;
	std::vector<int> newCol(rows);

	for (int i = 0; i < rows; i++) {
		if (!(std::cin >> newCol[i])) return false;
	}

	std::vector<int> newData;
	newData.reserve(rows*(cols+1));

	for (int i = 0; i < rows; i++) {
		int rowStart = i * cols;

		for (int j = 0; j < pos-1; j++) {
			newData.push_back(data[rowStart+j] );
		}
		newData.push_back(newCol[i]);
		for (int j = pos - 1; j < cols; ++j) {
            newData.push_back(data[rowStart + j]);
        }
	}

	data.swap(newData);
	cols++;
	return true;
}

bool Matrixx::insertColAfter(int pos) {
	if (pos < 1 || pos > cols) return false;
	return insertColBefore(pos+1);
}

bool Matrixx::deleteRow(int pos) {
	if (pos < 1 || pos > rows) return false;
	auto start = data.begin() + (pos-1)*cols;
	data.erase(start, start+cols);
	rows--;
	return true;
}

bool Matrixx::deleteCol(int pos) {
	if (pos < 1 || pos > cols) return false;

	std::vector<int> newData;
	newData.reserve(rows * (cols-1));
	for (int i = 0; i < rows; i++) {
		int rowStart = i * cols;
		for (int j = 0; j < cols; j++) {
			if (j != pos-1) newData.push_back(data[rowStart + j]);
		}
	}
	data.swap(newData);
	cols--;
	return true;
}

bool Matrixx::swapRow(int r1, int r2) {
	if (r1 < 1 || r1 > rows || r2 < 1 || r2 > rows) return false;
	if (r1 == r2) return true;

	int x1 = (r1-1) * cols;
	int x2 = (r2-1) * cols;
	
	for (int j = 0; j < cols; j++) std::swap(data[x1+j], data[x2+j]);
	return true;
}

bool Matrixx::swapCol(int c1, int c2) {
	if (c1 < 1 || c1 > cols || c2 < 1 || c2 > cols) return false;
	if (c1 == c2) return true;
	for (int i =0; i < rows; i++) {
		int x1 = i * cols + (c1-1);
		int x2 = i * cols + (c2-1);
		std::swap(data[x1],data[x2]);
	}
	return true;
}

bool Matrixx::transp() {
	std::vector<int> newData (rows*cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			newData[j*rows+i] = data[i*cols+j];
		}
	}
	data.swap(newData);
	std::swap(rows, cols);
	return true;
}

void Matrixx::print() const {
	for (int i = 0; i < rows; ++i) {
    	for (int j = 0; j < cols; ++j) {
        	if (j > 0) std::cout << ' ';
           	std::cout << data[i * cols + j];
       	}
       	std::cout << '\n';
   	}
}

int main(int argc, char* argv[]) {
	int rows, cols;
	std::cin >> rows >> cols;

	int vsego = rows*cols;
	std::vector<int> data(vsego);
	for (int i=0; i<vsego; i++) std::cin >> data[i];

	Matrixx matrixx(rows, cols, data);

	if (argc < 2) {
		matrixx.print();
		return 0;
	}

	std::string cmd = argv[1];
	bool flag = false;

	if (cmd == "-irb") {                
			if (argc == 3) {
            int pos = std::atoi(argv[2]);
            flag = matrixx.insertRowBefore(pos);
        }
    } else if (cmd == "-ira") {  
        if (argc == 3) {
            int pos = std::atoi(argv[2]);
            flag = matrixx.insertRowAfter(pos);
        }
    } else if (cmd == "-icb") {
        if (argc == 3) {
            int pos = std::atoi(argv[2]);
            flag = matrixx.insertColBefore(pos);
        }
    } else if (cmd == "-ica") { 
        if (argc == 3) {
            int pos = std::atoi(argv[2]);
            flag = matrixx.insertColAfter(pos);
        }
    } else if (cmd == "-dr") {
        if (argc == 3) {
            int pos = std::atoi(argv[2]);
            flag = matrixx.deleteRow(pos);
        }
    } else if (cmd == "-dc") {
        if (argc == 3) {
            int pos = std::atoi(argv[2]);
            flag = matrixx.deleteCol(pos);
        }
    } else if (cmd == "-sr") {
        if (argc == 4) {
            int r1 = std::atoi(argv[2]);
            int r2 = std::atoi(argv[3]);
            flag = matrixx.swapRow(r1, r2);
        }
    } else if (cmd == "-sc") {
        if (argc == 4) {
            int c1 = std::atoi(argv[2]);
            int c2 = std::atoi(argv[3]);
            flag = matrixx.swapCol(c1, c2);
        }
    } else if (cmd == "-t") {
        if (argc == 2) {
            flag = matrixx.transp();
        }
    }
	matrixx.print();
	return 0;
}
