#include <iostream>
#include <cstddef>
#include <exception>

class arrSize : public std::exception {
    size_t requested_;
public:
    arrSize(size_t size) : requested_(size) {}
    size_t getSize() const { return requested_; }
};

class indOut : public std::exception {
    int index_;
    size_t size_;
public:
    indOut(int idx, size_t sz) : index_(idx), size_(sz) {}
    int getIndex() const { return index_; }
    size_t getSize() const { return size_; }
};

class arrgg : public std::exception {
    size_t left_;
    size_t right_;
public:
    arrgg(size_t l, size_t r) : left_(l), right_(r) {}
    size_t getLeft() const { return left_; }
    size_t getRight() const { return right_; }
};

template <typename T_Type>
class Array {
private:
    T_Type* data_;
    size_t size_;

public:
    static constexpr size_t MAX_ARRAY_SIZE = 1000000;

	Array() noexcept;
    explicit Array(size_t size);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void setAt(size_t index, const T_Type& value);
    T_Type getAt(int index) const;
    void fill(const T_Type& value);
    void resize(size_t new_size);
    void print() const;

    T_Type& operator[](size_t index);
    const T_Type& operator[](size_t index) const;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

    Array operator-() const;        
    Array operator+() const;       
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    Array operator+(const T_Type& value) const;

    explicit operator bool() const noexcept;

    template <typename gg>
    friend std::ostream& operator<<(std::ostream& os, const Array<gg>& arr);
};

template <typename T_Type>
Array<T_Type>::Array() noexcept : data_(nullptr), size_(0) {}

template <typename T_Type>
Array<T_Type>::Array(size_t size) : size_(size) {
    if (size > MAX_ARRAY_SIZE) {
        throw arrSize(size);
    }
    if (size == 0) {
        data_ = nullptr;
    } else {
        data_ = new T_Type[size](); 
	}
}

template <typename T_Type>
Array<T_Type>::Array(const Array& other) : size_(other.size_) {
    if (other.size_ == 0) {
        data_ = nullptr;
    } else {
        data_ = new T_Type[other.size_];
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

template <typename T_Type>
Array<T_Type>::Array(Array&& other) noexcept
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

template <typename T_Type>
Array<T_Type>::~Array() {
    delete[] data_;
}

template <typename T_Type>
bool Array<T_Type>::isEmpty() const noexcept {
    return size_ == 0;
}

template <typename T_Type>
size_t Array<T_Type>::getSize() const noexcept {
    return size_;
}

template <typename T_Type>
void Array<T_Type>::setAt(size_t index, const T_Type& value) {
    if (index >= size_) {
        throw indOut(static_cast<int>(index), size_);
    }
    data_[index] = value;
}

template <typename T_Type>
T_Type Array<T_Type>::getAt(int index) const {
    if (index < 0 || static_cast<size_t>(index) >= size_) {
        throw indOut(index, size_);
    }
    return data_[index];
}

template <typename T_Type>
void Array<T_Type>::fill(const T_Type& value) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

template <typename T_Type>
void Array<T_Type>::resize(size_t new_size) {
    if (new_size > MAX_ARRAY_SIZE) {
        throw arrSize(new_size);
    }
    if (new_size == size_) {
        return;
    }

    T_Type* new_data = nullptr;
    if (new_size > 0) {
        new_data = new T_Type[new_size]();  
		size_t copy_size = (size_ < new_size) ? size_ : new_size;
        for (size_t i = 0; i < copy_size; ++i) {
            new_data[i] = data_[i];
        }
    }

    delete[] data_;
    data_ = new_data;
    size_ = new_size;
}

template <typename T_Type>
void Array<T_Type>::print() const {
    std::cout << *this;
}

template <typename T_Type>
T_Type& Array<T_Type>::operator[](size_t index) {
    if (index >= size_) {
        throw indOut(static_cast<int>(index), size_);
    }
    return data_[index];
}

template <typename T_Type>
const T_Type& Array<T_Type>::operator[](size_t index) const {
    if (index >= size_) {
        throw indOut(static_cast<int>(index), size_);
    }
    return data_[index];
}

template <typename T_Type>
Array<T_Type>& Array<T_Type>::operator=(const Array& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        if (size_ == 0) {
            data_ = nullptr;
        } else {
            data_ = new T_Type[size_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }
    return *this;
}

template <typename T_Type>
Array<T_Type>& Array<T_Type>::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T_Type>
bool Array<T_Type>::operator==(const Array& other) const {
    if (size_ != other.size_) return false;
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) return false;
    }
    return true;
}

template <typename T_Type>
bool Array<T_Type>::operator!=(const Array& other) const {
    return !(*this == other);
}

template <typename T_Type>
Array<T_Type> Array<T_Type>::operator-() const {
    Array result(size_);
    for (size_t i = 0; i < size_; ++i) {
        result.data_[i] = -data_[i];
    }
    return result;
}

template <typename T_Type>
Array<T_Type> Array<T_Type>::operator+() const {
    return Array(*this); 
}

template <typename T_Type>
Array<T_Type> Array<T_Type>::operator+(const Array& other) const {
    if (size_ != other.size_) {
        throw arrgg(size_, other.size_);
    }
    Array result(size_);
    for (size_t i = 0; i < size_; ++i) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

template <typename T_Type>
Array<T_Type>& Array<T_Type>::operator+=(const Array& other) {
    if (size_ != other.size_) {
        throw arrgg(size_, other.size_);
    }
    for (size_t i = 0; i < size_; ++i) {
        data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T_Type>
Array<T_Type> Array<T_Type>::operator+(const T_Type& value) const {
    Array result(size_);
    for (size_t i = 0; i < size_; ++i) {
        result.data_[i] = data_[i] + value;
    }
    return result;
}

template <typename T_Type>
Array<T_Type>::operator bool() const noexcept {
    return size_ != 0;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Array<U>& arr) {
    os << '[';
    for (size_t i = 0; i < arr.size_; ++i) {
        if (i > 0) os << ", ";
        os << arr.data_[i];
    }
    os << ']';
    return os;
}

template <typename T_Type>
Array<T_Type> operator+(const T_Type& value, const Array<T_Type>& arr) {
    return arr + value;
}


int main() {
    try {
        RunTemplateTests();  
    } catch (const arrSize& e) {
        std::cerr << "Error: Invalid array size requested: " << e.getSize() << std::endl;
    } catch (const indOut& e) {
        std::cerr << "Error: Index out of range: index = " << e.getIndex() << ", size = " << e.getSize() << std::endl;
    } catch (const arrgg& e) {
        std::cerr << "Error: Arrays size mismatch: left size = " << e.getLeft() << ", right size = " << e.getRight() << std::endl;
    } catch (const std::exception&) {
        std::cerr << "Error: Unknown error!" << std::endl;
    } catch (...) {
        std::cerr << "Error: Unknown error!" << std::endl;
    }
    return 0;
}
