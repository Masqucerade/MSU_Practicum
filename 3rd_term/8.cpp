#include <iostream>
#include <list>
#include <algorithm>
#include <string>

void out(const std::list<int> &nums) {
	for (int val : nums) {
        std::cout << val << ' ';
    }
} 

void in(std::list<int> &nums) {
	int cur;
	while ((std::cin >> cur)) {
		nums.push_back(cur);
	}
}

void check_param(int args, int n, const std::list<int> &nums) {
	if (args-2 != n) {
		//std::cout << args - 2 << " " << n << std::endl;
		out(nums);
		exit(0);
	}
}

int main(int argc, char** argv) {
	std::list<int> nums;
	in(nums);

	if (argc < 2) {
		out(nums);
		return 0;
	}
	std::string com = argv[1];

	if (com == "-af") {
		check_param(argc, 1, nums);
		nums.push_front(std::stoi(argv[2]));
	} else if (com == "-ae"){
		check_param(argc, 1, nums);
		nums.push_back(std::stoi(argv[2]));
	} else if (com == "-ib") {
		check_param(argc, 2, nums);
		auto it = std::find(nums.begin(), nums.end(), std::stoi(argv[3]));
		if (it != nums.end()) {
			nums.insert(it, std::stoi(argv[2]));
		}
	} else if (com == "-ia") {
		check_param(argc, 2, nums);
		auto it = std::find(nums.begin(), nums.end(), std::stoi(argv[3]));
		if (it != nums.end()) {
			nums.insert(++it, std::stoi(argv[2]));
		}
	} else if (com == "-d") {
		check_param(argc, 1, nums);
		auto it = std::find(nums.begin(), nums.end(), std::stoi(argv[2]));
		if (it != nums.end()) {
			nums.erase(it);
		}
	} else if (com == "-sa") {
		check_param(argc, 0, nums);
		nums.sort();
	} else if (com == "-sd") {
		check_param(argc, 0, nums);
		nums.sort();
		nums.reverse();
	} else if (com == "-mf") {
		check_param(argc, 0, nums);
		auto maxim = std::max_element(nums.begin(), nums.end());
		nums.splice(nums.begin(), nums, maxim);
	} else if (com == "-me") {
		check_param(argc, 0, nums);
		auto maxim = std::max_element(nums.begin(), nums.end());
		nums.splice(nums.end(), nums, maxim);
	}

	out(nums);

	return 0;
}
