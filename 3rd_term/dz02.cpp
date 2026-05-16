#include <iostream>
#include <cstring>

class mstring {
private:
    char* data;
    int len;
public:
    mstring();
    mstring(const mstring& other);
    mstring(mstring&& other) noexcept;
    mstring(const char* s);
    ~mstring();

    int length() const;
    bool isempty() const;
    void add(char c);
    void add(const char* c);
    void insert(char c, int i);
    void insert(const char* c, int i);
    void del(int i);
    void del(int i, int j);
    int search(const char* str) const;
    void replace(const char* sub_str, const char* new_str);
    void print() const;
};

mstring::mstring() : data(new char[1]), len(0) { // дефолт
    data[0] = '\0';
}

mstring::mstring(const mstring& other) : len(other.len) { // копирование
    data = new char[len + 1];
    std::strcpy(data, other.data);
}

// переещение
mstring::mstring(mstring&& other) noexcept : data(other.data), len(other.len) {
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

int mstring::length() const {
    return len;
}

bool mstring::isempty() const {
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
    if (i < 0 || i > len) return;
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

    if (i < 0 || i > len) return;

    char* newStr = new char[len + add_len + 1];
    std::strncpy(newStr, data, i);
    std::strcpy(newStr + i, c);
    std::strcpy(newStr + i + add_len, data + i);

    delete[] data;
    data = newStr;
    len += add_len;
}

void mstring::del(int i) { // гг символ
    if (i < 0 || i >= len) return;
    char* newStr = new char[len];  // new length = len-1

    std::strncpy(newStr, data, i);
    std::strcpy(newStr + i, data + i + 1);
    delete[] data;
    data = newStr;
    --len;
}

void mstring::del(int i, int j) { // гг подстрока
    if (i < 0 || j >= len || i > j) return;


    int new_len = len - (j - i + 1);
    char* newStr = new char[new_len + 1];
    std::strncpy(newStr, data, i);
    std::strcpy(newStr + i, data + j + 1);

    delete[] data;
    data = newStr;
    len = new_len;
}

// надо на подстроку !
int mstring::search(const char* str) const { 
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

void mstring::print() const {
    std::cout << data << std::endl;
}

/* int main()
{
        mstring s ("hello world");
        mstring s1 = s;
        mstring s2;
        std::cout << s.length() << std::endl;
        if (s2.isempty())
        {
          s.add('!');
          s2.add("HI!");
          s.print();
          s2.print();
        }
        if (!s1.isempty())
        {
           s1.insert(' ',5);
           s1.insert('m',6);
           s1.insert('y',7);
           s.insert(" my",5);
           s.print();
           s1.print();
        }
        s.del(9);
        s1.del(5,7);
        s.print();
        s1.print();
        return 0;
} */
