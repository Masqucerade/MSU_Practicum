#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

void test_players();

class PlayerException : public std::exception {
protected:
	std::string msg;
	std::string team;
	int number;
	bool need_num;

public:
	PlayerException (const std::string& message, const std::string& t, int n = -1)
		: msg(message), team(t), number(n), need_num(n != -1) {}

	const char* what() const noexcept override {  return msg.c_str(); }

	const std::string& getTeam() const { return team; }
	int getNumber() const { return number; }
	bool needNumber() const { return need_num; }
};

class WrongName : public PlayerException {
public:
	WrongName(const std::string& t) : PlayerException("Wrong name", t) {}
};

class WrongNumber : public PlayerException {
public:
	WrongNumber(const std::string& t, int n) : PlayerException("Wrong number", t, n) {}
};

class DoubleNum : public PlayerException {
public:
    DoubleNum(const std::string& t, int n) : PlayerException("Double number", t, n) {}
};

class TooMany : public PlayerException {
public:
    TooMany(const std::string& t) : PlayerException("Too many players", t) {}
};


class Player {
private:
	std::string team;
	int num;

	static std::vector<Player*> zenit;
	static std::vector<Player*> cska;

public:
	Player (const std::string& t, int n);
	~Player();

	void Print() const;
	static void Print_teams();

	int getNumber() const { return num; }
	std::string getTeam() const { return team; }
};

std::vector<Player*> Player::zenit;
std::vector<Player*> Player::cska; // сразу

Player::Player(const std::string& t, int n) {
	if (t != "Zenit" && t != "CSKA") throw WrongName(t);
	if (n < 1) throw WrongNumber(t,n);

	std::vector<Player*>* vec = nullptr;
	if (t == "Zenit") vec = &zenit;
	else vec = &cska;

	if (vec->size() >= 11) throw TooMany(t);

	for (Player* p : *vec) {
		if (p->getNumber() == n) throw DoubleNum(t, n);
	}


	team = t;
	num = n;
	vec->push_back(this);
}

Player::~Player() {

	std::vector<Player*>* vec = nullptr;
	if (team == "Zenit") vec = &zenit;
	else vec = &cska;

	auto it = std::find(vec->begin(), vec->end(), this);
	if (it != vec->end()) vec->erase(it);
}

void Player::Print() const {
	std::cout << team << " " << num << std::endl;
};

void Player::Print_teams() {
	if (!zenit.empty()) {
		std::cout << "Zenit:";
		for (Player* p : zenit) std::cout << " " << p->getNumber();
		std::cout << std::endl;
	}
	
	if (!cska.empty()) {
		std::cout << "CSKA:";
		for (Player* p : cska) std::cout << " " << p->getNumber();
		std::cout << std::endl;
	}
}

/* void test_players()
{
        Player pl1("Zenit", 10);
        Player pl2("Zenit", 11);
        Player pl3("CSKA", 23);
        Player pl4("CSKA", 10);
        Player pl5("Zenit", 4);
        Player pl6("Zenit", 1);
        Player pl7("CSKA", 7);
        Player pl8("Zenit", 8);

        pl1.Print();
        pl3.Print();
        Player::Print_teams();
} */

/* void test_players()
{
        Player pl1("Zenit", 10);
        Player pl2("Zenit", 11);
        Player pl3("CSKA", 23);
        Player pl4("CSKA", 10);
        Player pl5("Zenit", 4);
        Player pl6("Zenit", 1);
        Player pl7("CSKA", 7);
        Player pl8("Zenit", 4);

        pl1.Print();
        pl3.Print();
        Player::Print_teams();
} */
int main() {
	try {
        test_players();
    } catch (const WrongName& e) {
        std::cerr << "Exception: Wrong name in team " << e.getTeam() << std::endl;
    } catch (const WrongNumber& e) {
        std::cerr << "Exception: Wrong number in team " << e.getTeam()
                  << " Error number: " << e.getNumber() << std::endl;
    } catch (const DoubleNum& e) {
        std::cerr << "Exception: Double number in team " << e.getTeam()
                  << " Error number: " << e.getNumber() << std::endl;
    } catch (const TooMany& e) {
        std::cerr << "Exception: Too many players in team " << e.getTeam() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }

	return 0;
}
