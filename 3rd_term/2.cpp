#include <iostream>

class IntArray {

private:
	int* data_;
	size_t size_;

public:
	IntArray();
	explicit IntArray(size_t size); 
	IntArray(const IntArray& other);
	IntArray(IntArray&& other) noexcept;
	~IntArray();

	bool isEmpty() const;
	size_t getSize() const;
	void setAt(size_t index, int value);
	int getAt(int index) const;
	void fill(int value);
	void resize(size_t new_size);
	void print() const;
};

IntArray::IntArray() : data_(nullptr), size_(0) {}

IntArray::IntArray(size_t size) : size_(size) {
	if (size == 0) {
		data_ = nullptr;
	} else {
		data_ = new int[size]();
	}
}

IntArray::IntArray(const IntArray& other) : size_(other.size_) {
	if (other.size_ == 0) {
		data_ = nullptr;
	} else {
		data_ = new int[other.size_];
		for (int i = 0; i < other.size_; i++) {
			data_[i] = other.data_[i];
		}
	}
}

IntArray::IntArray(IntArray&& other) noexcept : data_(other.data_), size_(other.size_) {
	other.data_ = nullptr;
	other.size_ = 0;
}

IntArray::~IntArray() {
	delete[] data_;
}

bool IntArray::isEmpty() const {
	return size_ == 0;
}

size_t IntArray::getSize() const {
	return size_;
}

void IntArray::setAt(size_t index, int value) {
	if (index < size_) {
		data_[index] = value;
	}
}

int IntArray::getAt(int index) const {
	if (index >= 0 && static_cast<size_t>(index) < size_) {
		return data_[index];
	}
	return 0;
}

void IntArray::fill(int value) {
	for (int i = 0; i < size_; i++) {
		data_[i] = value;
	}
}

void IntArray::resize(size_t new_size) {
    if (new_size == size_) {
        return;
    }

    int* new_data = nullptr;
    if (new_size > 0) {
        new_data = new int[new_size];
        size_t copy_size = (size_ < new_size) ? size_ : new_size;
        for (size_t i = 0; i < copy_size; ++i) {
            new_data[i] = data_[i];
        }
        for (size_t i = copy_size; i < new_size; ++i) {
            new_data[i] = 0;
        }
    }

    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}

void IntArray::print() const {
    std::cout << '[';
    for (size_t i = 0; i < size_; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << data_[i];
    }
    std::cout << ']' << std::endl;
}

/* int main()
{
    std::cout << "Test 1" << std::endl;
    IntArray arr1;           // пустой массив
    IntArray arr2(5);        // массив из 5 нулей
    IntArray arr3(arr2);     // копия arr2 (копирование)

    std::cout << "arr1 (empty): ";
    arr1.print();
    std::cout << "arr2 (size 5): ";
    arr2.print();
    std::cout << "arr3 (copy arr2): ";
    arr3.print();

    // Тестирование конструктора перемещения
    std::cout << "\nTest 2" << std::endl;

    // Создаём объект
    IntArray temp(4);
    temp.fill(99);
    std::cout << "temp before moved: ";
    temp.print();

    // Используем конструктор перемещения
    IntArray arr4(std::move(temp));
    std::cout << "arr4 after moved from temp: ";
    arr4.print();
    std::cout << "temp after moved: ";
    temp.print();
    std::cout << "size of temp  " << temp.getSize() << std::endl;
    std::cout << "Is empty? " << (temp.isEmpty() ? "yes" : "no") << std::endl;

    // Тестирование методов
    std::cout << "\nTest 3" << std::endl;
    arr2.fill(10);
    arr2.setAt(2, 42);
    int value = arr2.getAt(2);

    std::cout << "arr2 after fill(10) and setAt(2, 42): ";
    arr2.print();
    std::cout << "arr2[2] = " << value << std::endl;

    // Тестирование изменения размера
    std::cout << "\nTest 4" << std::endl;

    arr2.resize(3);
    std::cout << "arr2 after resize(3): ";
    arr2.print();

    arr2.resize(6);
    std::cout << "arr2 after resize(6): ";
    arr2.print();

    // Проверка глубокого копирования
    std::cout << "\nTest 5" << std::endl;
    IntArray original(3);
    original.fill(7);

    IntArray copy = original;
    copy.setAt(1, 99);

    std::cout << "original: ";
    original.print();
    std::cout << "copy: ";
    copy.print();

    return 0;
} */
