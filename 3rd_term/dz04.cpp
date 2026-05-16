#include <iostream>
#include <cstring>
#include <sstream>
#include <string>

// =========----===--=-=-=-==-=--=-=-= 44444 task
class strExpt {
    std::string msg;

public:
    strExpt(const char* method, int p) { //1 
		msg = std::string("Exception: problem in ") + method + " incorrect parameter:" + std::to_string(p);
    }

    strExpt(const char* method, int p1, int p2) { // 2
		msg = std::string("Exception: problem in ") + method + " incorrect parameter:" + std::to_string(p1) + " " + std::to_string(p2);
    }
    const char* what() const noexcept { return msg.c_str(); }
};

// -==--==-=--==--=-==-=-=-=-=-=---=-=-=-= 

class mstring {
private:
    char* data;
    int len;
public:
    mstring();
    mstring(const mstring& other);
    mstring(mstring&& other);
    mstring(const char* s);
    ~mstring();

    int length() const noexcept; // 4
    bool isempty() const noexcept; // 4 
    void add(char c);
    void add(const char* c);
    void insert(char c, int i);
    void insert(const char* c, int i);
    void del(int i);
    void del(int i, int j);
    int search(const char* str) const noexcept; // 4
    void replace(const char* sub_str, const char* new_str);
    void print() const noexcept;

    mstring& operator=(const mstring& other);
    mstring& operator=(mstring&& other);

    char& operator[](int i); // индекс
    const char& operator[](int i) const;

    bool operator==(const mstring& other) const noexcept; // 44
    bool operator!=(const mstring& other) const noexcept; // 4
    bool operator<(const mstring& other) const noexcept; //4
    bool operator>(const mstring& other) const noexcept; //4
    bool operator<=(const mstring& other) const noexcept; //4 
    bool operator>=(const mstring& other) const noexcept; // 4

    friend mstring operator+(const mstring& lhs, const mstring& rhs);
    friend mstring operator*(const mstring& s, int n);
    friend mstring operator*(int n, const mstring& s);
    friend std::ostream& operator<<(std::ostream& os, const mstring& s);
    friend std::istream& operator>>(std::istream& is, mstring& s);
};

mstring::mstring() : data(new char[1]), len(0) { // дефолт
    data[0] = '\0';
}

mstring::mstring(const mstring& other) : len(other.len) { // копирование
    data = new char[len + 1];
    std::strcpy(data, other.data);
}

// переещение
mstring::mstring(mstring&& other) : data(other.data), len(other.len) {
    other.data = new char[1];
    other.data[0] = '\0';
    other.len = 0;
}

mstring::mstring(const char* s) { // str
    if (s) {
        len = std::strlen(s);
        data = new char[len + 1];
        std::strcpy(data, s);
    } else {
        data = new char[1];
        data[0] = '\0';
        len = 0;
    }
}

mstring::~mstring() {
    delete[] data;
}

int mstring::length() const noexcept {
    return len;
}

bool mstring::isempty() const noexcept {
    return len == 0;
}

void mstring::add(char c) { // в конец chr
    char* newStr = new char[len + 2];
    std::strcpy(newStr, data);
    newStr[len] = c;
    newStr[len + 1] = '\0';
    delete[] data;
    data = newStr;
    ++len;
}

void mstring::add(const char* c) { // str в конец
    if (!c) return;
    int add_len = std::strlen(c);
    char* newStr = new char[len + add_len + 1];

    std::strcpy(newStr, data);
    std::strcat(newStr, c);

	// do
    delete[] data;
    data = newStr;
    len += add_len;
}

void mstring::insert(char c, int i) { // вставка в i симв

    if (i < 0 || i > len) throw strExpt("insert", i);
    char* newStr = new char[len + 2];

    std::strncpy(newStr, data, i);
    newStr[i] = c;
    std::strcpy(newStr + i + 1, data + i);

    delete[] data;
    data = newStr;
    ++len;
}

void mstring::insert(const char* c, int i) { // строку аналогич
    if (!c) return;
    int add_len = std::strlen(c);

    if (i < 0 || i > len) throw strExpt("insert", i); // =====44444 ========

    char* newStr = new char[len + add_len + 1];
    std::strncpy(newStr, data, i);
    std::strcpy(newStr + i, c);
    std::strcpy(newStr + i + add_len, data + i);

    delete[] data;
    data = newStr;
    len += add_len;
}

void mstring::del(int i) { // гг символ

    if (i < 0 || i >= len) throw strExpt("del", i); // ========444444444========

    char* newStr = new char[len];  // new length = len-1

    std::strncpy(newStr, data, i);
    std::strcpy(newStr + i, data + i + 1);
    delete[] data;
    data = newStr;
    --len;
}

void mstring::del(int i, int j) { // гг подстрока

    if (i < 0 || j >= len || i > j) throw strExpt("del", i, j); // ===== 444444444444 ======

    int new_len = len - (j - i + 1);
    char* newStr = new char[new_len + 1];
    std::strncpy(newStr, data, i);
    std::strcpy(newStr + i, data + j + 1);

    delete[] data;
    data = newStr;
    len = new_len;
}

// надо на подстроку !
int mstring::search(const char* str) const noexcept { 
    if (!str) return -1;

    const char* pos = std::strstr(data, str);
    if (pos) {
        return pos - data;
    }

    return -1;
}

// замена первой
void mstring::replace(const char* sub_str, const char* new_str) {
    if (!sub_str || !new_str) return;
    int pos = search(sub_str);
    if (pos == -1) return;

    int sub_len = std::strlen(sub_str);
    int new_len = std::strlen(new_str);
    int vsego_len = len - sub_len + new_len;

    char* newStr = new char[vsego_len + 1];
    std::strncpy(newStr, data, pos);
    std::strcpy(newStr + pos, new_str);
    std::strcpy(newStr + pos + new_len, data + pos + sub_len);

    delete[] data;
    data = newStr;
    len = vsego_len;
}

void mstring::print() const noexcept {
    std::cout << data << std::endl;
}

// ------============-------=========================== 3333
mstring& mstring::operator=(const mstring& other) {
    if (this != &other) {
        delete[] data;

        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}

mstring& mstring::operator=(mstring&& other) {
    if (this != &other) {
        delete[] data;
        data = other.data;
        len = other.len;
        other.data = new char[1];
        other.data[0] = '\0';
        other.len = 0;
    }
    return *this;
}

// ops
char& mstring::operator[](int i) { //индекс
    if (i < 0 || i >= len) throw strExpt("operator[]", i); // ========4444444444========
    return data[i];
}

const char& mstring::operator[](int i) const {
    if (i < 0 || i >= len) throw strExpt("operator[]", i);
    return data[i];
}

bool mstring::operator==(const mstring& other) const noexcept {
    return std::strcmp(data, other.data) == 0;
}

bool mstring::operator!=(const mstring& other) const noexcept {
    return !(*this == other);
}

bool mstring::operator<(const mstring& other) const noexcept {
    return std::strcmp(data, other.data) < 0;
}

bool mstring::operator>(const mstring& other) const noexcept {
    return std::strcmp(data, other.data) > 0;
}

bool mstring::operator<=(const mstring& other) const noexcept {
    return !(*this > other);
}

bool mstring::operator>=(const mstring& other) const noexcept {
    return !(*this < other);
}

////////////////////

mstring operator+(const mstring& lhs, const mstring& rhs) {
    mstring res(lhs); // копи
    res.add(rhs.data);
    return res;
}

mstring operator*(const mstring& s, int n) {
    if (n < 0) throw strExpt("operator*", n); // ======444444=========

    mstring res;
    for (int i = 0; i < n; ++i) { // добавить n раз
        res.add(s.data);
    }
    return res;
}

mstring operator*(int n, const mstring& s) {
    return s * n; // см выше
}

std::ostream& operator<<(std::ostream& os, const mstring& s) {
    os << s.data;
    return os; // ссылка на поток
}

std::istream& operator>>(std::istream& is, mstring& s) {
    mstring temp;
    char ch;
    while (is.get(ch)) {
        if (ch == '\n') break;
        temp.add(ch);
    }
    s = std::move(temp);
    return is;
}

int main()
{
    try
    {
        error(); 
	}
    catch (const strExpt& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
