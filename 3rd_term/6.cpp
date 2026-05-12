#include <iostream>
#include <cstring>

template <typename T>
T minn (const T arr[], int size) noexcept {
	T minim = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] < minim) {
			minim = arr[i];
		}	
	}	
	return minim;
}

template <>
const char* minn<const char*>(const char* const arr[], int size) noexcept{
	const char* minim = arr[0]; 
	int lenMin = std::strlen(arr[0]);
	for (int j = 0; j < size; j++) {
		int cur_len = std::strlen(arr[j]);
		if (cur_len < lenMin) {
			lenMin = cur_len;
			minim = arr[j];
		}
	}

	return minim;
}

/* int main()
{
    int arri[6] = {1, 2, 5, 3, 1, -1};
    double arrd[4] = {2.3, -1.3, 8.7, 4.5};
    const char * arrc[7] = {"first", "second", "third", "min", "long string", "short", "another string"};

    std::cout << "min of integer = " << minn(arri, 6) << std::endl;
    std::cout << "min of double = " << minn(arrd, 4) << std::endl;
    std::cout << "min string is " << minn(arrc, 7) << std::endl;

    return 0;
} */
