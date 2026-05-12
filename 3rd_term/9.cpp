#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

class Pet {
private:
    string type_;
    double mass_;
    static int cat_cnt;
    static int dog_cnt;
    static double total_mass;

public:
    Pet(const string& type, double mass) : type_(type), mass_(mass) {
        if (type_ == "cat" || type_ == "dog") {
            if (type_ == "cat") ++cat_cnt;
            else ++dog_cnt;
            total_mass += mass_;
        } else {
            string new_type;
            if (cat_cnt == dog_cnt) {
                int total = cat_cnt + dog_cnt;
                if (total == 0) {
                    new_type = "cat";
                } else {
                    double avg = total_mass / total;
                    if (mass_ < avg) new_type = "cat";
                    else new_type = "dog";
                }
            } else {
                if (cat_cnt < dog_cnt) new_type = "cat";
                else new_type = "dog";
            }
            type_ = new_type;
            if (type_ == "cat") ++cat_cnt;
            else ++dog_cnt;
            total_mass += mass_;
        }
    }

    Pet(const Pet& other) : type_(other.type_), mass_(other.mass_) {
        if (type_ == "cat") ++cat_cnt;
        else ++dog_cnt;
        total_mass += mass_;
    }

    ~Pet() {
        if (type_ == "cat") --cat_cnt;
        else --dog_cnt;
        total_mass -= mass_;
    }

    static void Print_pets() {
        printf("Cat: %d Dog: %d\n", cat_cnt, dog_cnt);
    }
};

int Pet::cat_cnt = 0;
int Pet::dog_cnt = 0;
double Pet::total_mass = 0.0;
