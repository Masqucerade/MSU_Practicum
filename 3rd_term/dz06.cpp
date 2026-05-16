#include <iostream>

template <typename T>
class Set {
private:
	T* data;
	size_t size;
	size_t memory;

	void more_memory(size_t new_memory);
	void can_add(); //есть хотяб 1 место под новый
	size_t where_input(const T& value) const; 
	// бин поиском первое место вставки
	bool have(const T& value) const;
	void swap(Set& other) noexcept;; // обмен

public:
	Set() noexcept;
	Set(const T* arr, size_t cnt);
	Set(const Set<T>& other);
	~Set() noexcept;

	Set<T>& operator=(const Set<T>& other);

	
	void add(const T& value);
	void add(const T* arr, size_t cnt);
	void del(const T& value);
	bool in(const T& value) const noexcept;;
	void print() const noexcept;;

	Set<T> operator*(const Set<T>& other) const;
	Set<T> operator+(const Set<T>& other) const;
};

template <typename T>
Set<T>::Set(const Set<T>& other) : data(nullptr), size(other.size), memory(other.memory)
{
    if (memory > 0) {
        data = new T[memory];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
}

template <typename T>
void Set<T>::more_memory(size_t new_memory) {
	if (new_memory <= memory) return;
	T* new_data = new T[new_memory];
	for (size_t i = 0; i < size; i++)
		new_data[i] = data[i];
	delete[] data;
	data = new_data;
	memory = new_memory;
}

template <typename T>
void Set<T>::can_add() {
    if (size == memory) {
        more_memory(memory == 0 ? 1 : memory * 2);
    } // по крутому попробую
}

template <typename T>
size_t Set<T>::where_input(const T& value) const{ // бин поиск
	size_t left = 0, right = size;
	while (left < right) {
		size_t mid = left + (right-left)/2;
		if (data[mid] < value) left = mid + 1;
		else right = mid;
	}
	return left;
}

template <typename T>
bool Set<T>::have(const T& value) const {
    size_t pos = where_input(value);
    return pos < size && !(value < data[pos]) && !(data[pos] < value);
}

// main_jh43vk3hg4j3242g34v5ygtf4v3yg54325hio23j4
// IBshk

template <typename T>
Set<T>::Set() noexcept : data(nullptr), size(0), memory(0) {}

template <typename T>
Set<T>::Set(const T* arr, size_t cnt) : Set() {
	for (size_t i = 0; i < cnt; i++) add(arr[i]);
}

template <typename T>
Set<T>::~Set() noexcept {
	delete[] data;
}

template <typename T> // ??????
Set<T>& Set<T>::operator=(const Set<T>& other) {
	if (this != &other) {
		Set tmp(other);
		swap(tmp);
	}
	return *this;
}

template <typename T>
void Set<T>::swap(Set& other) noexcept {
	T* tmp_data = data;	
	data = other.data;
	other.data = tmp_data;

	size_t tmp_size = size;
	size = other.size;
	other.size = tmp_size;
	
	size_t tmp_memory = memory;
	memory = other.memory;
	other.memory = tmp_memory;
}

template <typename T>
void Set<T>::add(const T& value) {
	if (have(value)) return;
	size_t pos = where_input(value);
	can_add();
	for (size_t i = size; i > pos; i--) 
		data[i] = data[i -1 ];
	data[pos] = value;
	size++;
}

template <typename T>
void Set<T>::add(const T* arr, size_t cnt) {
    for (size_t i = 0; i < cnt; i++)
        add(arr[i]);
}

template <typename T>
void Set<T>::del(const T& value) {
	size_t pos = where_input(value);
	if (pos < size && !(value < data[pos]) && !(data[pos] < value)) {
		for (size_t i = pos; i < size-1; i++)
			data[i] = data[i+1];
		size--;
	}
}

template <typename T>
bool Set<T>::in(const T& value) const noexcept {
	return have(value);
}

template <typename T>
void Set<T>::print() const noexcept {
	for (size_t i = 0; i < size; i++) {
		if (i > 0) std::cout << ' ';
		std::cout << data[i];
	}
	std::cout << std::endl;
}


template <typename T>
Set<T> Set<T>::operator*(const Set<T>& other) const {
    Set<T> result;
    size_t i = 0, j = 0;
    while (i < size && j < other.size) {
        if (data[i] < other.data[j]) ++i;
        else if (other.data[j] < data[i]) ++j;
        else {
            result.add(data[i]);
            ++i; ++j;
        }
    }
    return result;
}

template <typename T>
Set<T> Set<T>::operator+(const Set<T>& other) const {
    Set<T> result;
    size_t i = 0, j = 0;
    while (i < size && j < other.size) {
        if (data[i] < other.data[j])
            result.add(data[i++]);
        else if (other.data[j] < data[i])
            result.add(other.data[j++]);
        else {
            result.add(data[i]);
            ++i; ++j;
        }
    }
    while (i < size) result.add(data[i++]);
    while (j < other.size) result.add(other.data[j++]);
    return result;
}

/* int main()
{
        int a[] = { 1,2,3,4,5 };
        int b[] = { 3,2,6};
        Set<int> seti1(a,5),seti2,seti3,seti4;
        seti2.add(b, 3);
        seti1.print();
        seti2.print();
        seti3 = seti1*seti2;
        std::cout << "Intersect: ";
        seti3.print();
        seti4 = seti1 + seti2;
        std::cout << "Union: ";
        seti4.print();
        seti3.add(7);
        seti4.del(3);
        seti3.print();
        seti4.print();
        return 0;
} */
