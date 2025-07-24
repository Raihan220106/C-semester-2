#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Interface untuk kemampuan dasar karakter
class IAbility {
public:
    virtual void execute() = 0;
    virtual ~IAbility() = default;
};

// Interface untuk interaksi karakter
class ICharacterInteraction {
public:
    virtual void takeDamage(int damage) = 0;
    virtual bool isAlive() const = 0;
    virtual ~ICharacterInteraction() = default;
};

// Abstract base class untuk karakter
class GameCharacter : public ICharacterInteraction {
protected:
    std::string name;
    int health;
    int maxHealth;

public:
    GameCharacter(const std::string& charName, int initialHealth)
        : name(charName), health(initialHealth), maxHealth(initialHealth) {}

    // Implementasi default untuk interface ICharacterInteraction
    void takeDamage(int damage) override {
        health = std::max(0, health - damage);
    }

    bool isAlive() const override {
        return health > 0;
    }

    // Getter untuk informasi karakter
    std::string getName() const { return name; }
    int getHealth() const { return health; }

    // Method virtual untuk tipe karakter
    virtual std::string getCharacterType() const = 0;

    virtual ~GameCharacter() = default;
};

// Ability untuk menyerang
class AttackAbility : public IAbility {
private:
    GameCharacter* attacker;
    GameCharacter* target;
    int damage;

public:
    AttackAbility(GameCharacter* atk, GameCharacter* tgt, int dmg)
        : attacker(atk), target(tgt), damage(dmg) {}

    void execute() override {
        std::cout << attacker->getName() << " menyerang "
                  << target->getName() << " dengan damage " << damage << std::endl;
        target->takeDamage(damage);
    }
};

// Ability untuk healing
class HealingAbility : public IAbility {
private:
    GameCharacter* character;
    int healAmount;

public:
    HealingAbility(GameCharacter* chr, int amount)
        : character(chr), healAmount(amount) {}

    void execute() override {
        int currentHealth = character->getHealth();
        int newHealth = std::min(currentHealth + healAmount, 100); // Contoh max health 100

        std::cout << character->getName() << " melakukan healing sebesar "
                  << healAmount << std::endl;
    }
};

// Ability untuk bertahan
class DefendAbility : public IAbility {
private:
    GameCharacter* character;
    int defendAmount;

public:
    DefendAbility(GameCharacter* chr, int amount)
        : character(chr), defendAmount(amount) {}

    void execute() override {
        std::cout << character->getName() << " memasang pertahanan "
                  << defendAmount << std::endl;
    }
};

// Implementasi konkret untuk Player
class Player : public GameCharacter {
private:
    int level;
    std::vector<std::unique_ptr<IAbility>> abilities;

public:
    Player(const std::string& name, int initialHealth, int initialLevel)
        : GameCharacter(name, initialHealth), level(initialLevel) {}

    void addAbility(std::unique_ptr<IAbility> ability) {
        abilities.push_back(std::move(ability));
    }

    void executeAbility(size_t index) {
        if (index < abilities.size()) {
            abilities[index]->execute();
        }
    }

    std::string getCharacterType() const override {
        return "Player";
    }

    int getLevel() const { return level; }
};

// Implementasi konkret untuk Enemy
class Enemy : public GameCharacter {
private:
    std::string enemyType;

public:
    Enemy(const std::string& name, int initialHealth, const std::string& type)
        : GameCharacter(name, initialHealth), enemyType(type) {}

    std::string getCharacterType() const override {
        return "Enemy (" + enemyType + ")";
    }
};

// Implementasi konkret untuk NPC
class NPC : public GameCharacter {
private:
    std::string role;

public:
    NPC(const std::string& name, int initialHealth, const std::string& npcRole)
        : GameCharacter(name, initialHealth), role(npcRole) {}

    std::string getCharacterType() const override {
        return "NPC (" + role + ")";
    }
};

int main() {
    // Membuat player
    Player hero("Pahlawan", 100, 5);

    // Membuat musuh
    Enemy goblin("Goblin Jahat", 50, "Prajurit");

    // Membuat NPC
    NPC merchant("Pedagang", 80, "Penjual Barang");

    // Menambahkan abilities untuk player
    hero.addAbility(std::make_unique<AttackAbility>(&hero, &goblin, 20));
    hero.addAbility(std::make_unique<HealingAbility>(&hero, 30));
    hero.addAbility(std::make_unique<DefendAbility>(&hero, 15));

    // Menampilkan informasi karakter
    std::cout << "Karakter: " << hero.getName()
              << " (" << hero.getCharacterType() << ")"
              << " - Health: " << hero.getHealth() << std::endl;

    std::cout << "Musuh: " << goblin.getName()
              << " (" << goblin.getCharacterType() << ")"
              << " - Health: " << goblin.getHealth() << std::endl;

    // Menjalankan ability player
    hero.executeAbility(0); // Attack
    hero.executeAbility(1); // Healing
    hero.executeAbility(2); // Defend

    // Menampilkan status health setelah abilities
    std::cout << "Status Health Goblin: " << goblin.getHealth() << std::endl;
    std::cout << "Status Health Hero: " << hero.getHealth() << std::endl;

    return 0;
}
