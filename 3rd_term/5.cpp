#include <iostream>
#include <cstring>

class Creature {
	protected:
		std::string name;
		int health;
	public:
		Creature(const std::string& n, int h) : name(n), health(h) {}
		virtual ~Creature(){};

		virtual void display() const noexcept = 0;
		virtual void attack(Creature& target) = 0;

		bool isAlive() const noexcept;
		std::string getName() const noexcept;
		int getHealth() const noexcept;
		void setHealth(int new_health);
};

void Creature::setHealth(int new_health) {
	health = new_health;
}

std::string Creature::getName() const noexcept{
	return name;
}

bool Creature::isAlive() const noexcept{
	return health > 0;
}

int Creature::getHealth() const noexcept {
	if (health > 0) return health;
	else return 0;
}

class Warrior: public Creature {
	private:
		unsigned int strength;
	public:
		Warrior(const std::string& n, int h, int s) : Creature(n, h), strength(s) {}


		void display() const override noexcept {
			std::cout << "[Warrior] " << name << ", health: "<< getHealth() 
							<< ", strength: " << strength << std::endl;
		}
		void attack(Creature& target) override;
		~Warrior(){};
};

void Warrior::attack(Creature& target){
			if (!isAlive()) return;
			std::cout << "[Warrior] " << name << " attacks with a sword!" << std::endl;
			int hp = target.getHealth();
			target.setHealth(hp - strength);
		}


class Mage : public Creature {
	private:
    	int mana;
	public:
    	Mage(const std::string& n, int h, int m) : Creature(n, h), mana(m) {}
    	void display() const override noexcept {
     	   std::cout << "[Mage] " << name << ", health: " << getHealth() 
                  << ", mana: " << mana << std::endl;
    	}
		void attack(Creature& target) override;
   		~Mage(){};
};

void Mage::attack(Creature& target) {
        	if (!isAlive()) return;

        	if (mana >= 10) {
            	std::cout << "[Mage] " << name << " casts a fireball!" << std::endl;

				int hp = target.getHealth();
				target.setHealth(hp - 20);

            	mana -= 10;
        	} else {
            	std::cout << "[Mage] " << name << " does not have enough mana to cast a spell!" << std::endl;
        	}
    	}


/*int main()
{
    // Create polymorphic array
    Creature* creatures[4];

    creatures[0] = new Mage("Merlin", 80, 9);
    creatures[1] = new Warrior("Thor", 120, 30);
    creatures[2] = new Mage("Gandalf", 90, 20);
    creatures[3] = new Warrior("Arthur", 20, 25);

    // Display all creatures using base class pointer
    std::cout << "All creatures:" << std::endl;
    for (int i = 0; i < 4; i++) {
        creatures[i]->display();
    }

    // Demonstrate attacks through base class pointer
    std::cout << "\nBattle simulation:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "\nRound " << i + 1 << ":" << std::endl;
        creatures[i]->attack(*creatures[i+1]);
        std::cout << "Target health: " << creatures[i+1]->getHealth() << std::endl;
    }

    // Check who's alive
    std::cout << "\nSurvivors:" << std::endl;
    for (int i = 0; i < 4; i++) {
        if (creatures[i]->isAlive()) {
            std::cout << creatures[i]->getName() << " is still alive!" << std::endl;
        } else {
            std::cout << creatures[i]->getName() << " has been defeated!" << std::endl;
        }
    }

    // Cleanup
    for (int i = 0; i < 4; i++) {
        delete creatures[i];
    }

}*/
