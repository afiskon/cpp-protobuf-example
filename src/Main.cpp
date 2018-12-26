#include <iostream>
#include <fstream>
#include <stdexcept>
#include <Game.pb.h>

using namespace std;
using namespace me::eax::examples::game;

void saveHero(const char* fname, const Hero& hero) {
    fstream out(fname, ios::out | ios::trunc | ios::binary);
    if(!hero.SerializeToOstream(&out))
        throw runtime_error("saveHero() failed");
}

void loadHero(const char* fname, Hero& hero) {        
    fstream in(fname, ios::in | ios::binary);
    if(!hero.ParseFromIstream(&in))
        throw runtime_error("loadHero() failed");
}

void printHero(const Hero& hero) {
    cout << "Name: " << hero.name() << endl;
    cout << "HP: " << hero.hp() << endl;
    cout << "XP: " << hero.xp() << endl;

    if(hero.has_mage_info()) {
        cout << "Class: mage" << endl;
        cout << "Spellbook: ";
        for(int i = 0; i < hero.mage_info().spellbook_size(); i++) {
            switch(hero.mage_info().spellbook(i)) {
                case Spell::FIREBALL:
                    cout << "fireball, ";
                    break;
                case Spell::THUNDERBOLT:
                    cout << "thunderbolt, ";
                    break;
                default:
                    cout << "(unknown spell), ";
                    break;
            }
        }
        cout << endl;
        cout << "Mana: " << hero.mage_info().mana() << endl;
    } else if(hero.has_warrior_info()) {
        cout << "Class: warrior" << endl;
        cout << "Weapon: " << (
                hero.warrior_info().weapon() == Weapon::SWORD ? "sword" :
                hero.warrior_info().weapon() == Weapon::BOW ? "bow" :
                "(unknown weapon)"
            ) << endl;
        cout << "Arrows: " << hero.warrior_info().arrows_number() << endl;
    } else {
        cout << "Class: (unknown class)" << endl;
    }

    cout << endl;
}

int main() {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    Hero warrior;
    warrior.set_name("eax");
    warrior.set_hp(50);
    warrior.set_xp(256);
    warrior.mutable_warrior_info()->set_weapon(Weapon::SWORD);
    warrior.mutable_warrior_info()->set_arrows_number(15);

    Hero mage;
    mage.set_name("afiskon");
    mage.set_hp(25);
    mage.set_xp(1024);
    mage.mutable_mage_info()->add_spellbook(Spell::FIREBALL);
    mage.mutable_mage_info()->add_spellbook(Spell::THUNDERBOLT);
    mage.mutable_mage_info()->set_mana(100);

    cout << "Saving heroes..." << endl;
    saveHero("eax.dat", warrior);
    saveHero("afiskon.dat", mage);

    cout << "Loading heroes..." << endl;
    Hero warrior2;
    Hero mage2;
    loadHero("eax.dat", warrior2);
    loadHero("afiskon.dat", mage2);

    cout << endl;
    printHero(warrior2);
    printHero(mage2);
}
