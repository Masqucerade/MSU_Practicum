#include <iostream>
#include <cstddef>

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

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    IntArray& operator=(const IntArray& other);
    IntArray& operator=(IntArray&& other) noexcept;

    bool operator==(const IntArray& other) const;
    bool operator!=(const IntArray& other) const;

    IntArray operator-() const;
    IntArray operator+(const IntArray& other) const;
    IntArray& operator+=(const IntArray& other);
    IntArray operator+(int value) const;

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const IntArray& arr);
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
    if (other.size_ ==0) {
        data_ = nullptr;
    } else {
        data_ = new int[other.size_];
        for (int i = 0; i < static_cast<int>(other.size_); i++) {
            data_[i] = other.data_[i];
        }
    }
}

IntArray::IntArray(IntArray&& other) noexcept
    : data_(other.data_), size_(other.size_) {
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
    for (int i = 0; i < static_cast<int>(size_); i++) {
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
        for (size_t i = 0; i < copy_size; i++) {
            new_data[i] = data_[i];
        }
        for (size_t i = copy_size; i < new_size; i++) {
            new_data[i] = 0;
        }
    }

    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}

void IntArray::print() const {
    std::cout << '[';
    for (size_t i = 0; i < size_; i++) {
        if (i > 0) std::cout << ", ";
        std::cout << data_[i];
    }
    std::cout << ']' << std::endl;
}

int& IntArray::operator[](size_t index) {
    return data_[index];
}

const int& IntArray::operator[](size_t index) const {
    return data_[index];
}

IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        if (size_ == 0) {
            data_ = nullptr;
        } else {
            data_ = new int[size_];
            for (size_t i = 0; i<size_; i++) {
                data_[i] = other.data_[i];
            }
        }
    }
    return *this;
}

IntArray& IntArray::operator=(IntArray&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

bool IntArray::operator==(const IntArray& other) const {
    if (size_ != other.size_) return false;
    for (size_t i=0; i < size_; i++) {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}

bool IntArray::operator!=(const IntArray& other) const {
    return !(*this == other);
}

IntArray IntArray::operator-() const {
    IntArray result(size_);
    for (size_t i = 0; i < size_; i++) {
        result.data_[i] = -data_[i];
    }
    return result;
}

IntArray IntArray::operator+(const IntArray& other) const {
    IntArray result(size_);
    for (size_t i = 0; i < size_; i++) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

IntArray& IntArray::operator+=(const IntArray& other) {
    for (size_t i = 0; i < size_; i++) {
        data_[i] += other.data_[i];
    }
    return *this;
}

IntArray IntArray::operator+(int value) const {
    IntArray result(size_);
    for (size_t i = 0; i < size_; i++) {
        result.data_[i] = data_[i] + value;
    }
    return result;
}

IntArray::operator bool() const {
    return size_ != 0;
}

std::ostream& operator<<(std::ostream& os, const IntArray& arr) {
    os << '[';
    for (size_t i = 0; i < arr.size_; i++) {
        if (i > 0) os << ", ";
        os << arr.data_[i];
    }
    os << ']';
    return os;
}

IntArray operator+(int value, const IntArray& arr) {
    return arr + value;
}

/* int main() {
   // 0. Индексация
    IntArray a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    IntArray b(3);
    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    // 1.Конструкторы и операторы присваивания
    IntArray c = a;
    IntArray d;
    d = b;
    std::cout << "d = " << d << std::endl;
    std::cout << "b = " << b << std::endl;
    IntArray e = std::move(c);
    IntArray f;
    f = std::move(d);
    std::cout << "e = " << e << std::endl;
    std::cout << "c = " << c << std::endl;

    // 2. Операторы сравнения
    std::cout << "a == b? " << (a == b) << std::endl;  // false
    std::cout << "a != b? " << (a != b) << std::endl;  // true

    // 3. Арифметические операторы
    IntArray sum = a + b;  // [5, 7, 9]
    std::cout << "a + b = " << sum << std::endl;

    a += b;  // a становится [5, 7, 9]
    std::cout << "a after a += b: " << a << std::endl;

    // 4. Оператор со скаляром (симметричный!)
    IntArray arrPlus5 = a + 5;    // [10, 12, 14]
    IntArray fivePlusArr = 5 + a; // [10, 12, 14] - тот же результат!

    std::cout << "a + 5 = " << arrPlus5 << std::endl;
    std::cout << "5 + a = " << fivePlusArr << std::endl;

    // Проверяем, что результаты одинаковы
    if (arrPlus5 == fivePlusArr) {
        std::cout << "arrPlus5 == fivePlusArr" << std::endl;
    }

    // 5. Унарные операторы
    IntArray neg = -a;  // [-5, -7, -9]
    std::cout << "-a = " << neg << std::endl;


    // 6. Оператор bool
    if (a) {
        std::cout << "array isn't empty" << std::endl;
    }

    IntArray empty;
    if (!empty) {
        std::cout << "array is empty" << std::endl;
    }

    return 0;
} */
