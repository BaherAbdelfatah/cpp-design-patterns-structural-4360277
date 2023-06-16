#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Character
{
public:
    explicit Character(char c) : m_Char(c) {}
    char getChar() const { return m_Char; }

private:
    const char m_Char;
};

class CharacterFactory {
public:
    Character* getCharacters(const char c) {
        auto it = m_CharacterPool.find(c);
        if (it != m_CharacterPool.end()) {
            // character already exists in pool, return it.
            return it->second;
        } else {
            // create new character and add it to the pool.
            auto newIt = m_CharacterPool.emplace(c, new Character(c));
            return newIt.first->second;
        }
    }

~CharacterFactory() {
    for (auto char_pair : m_CharacterPool) {
        delete char_pair.second;
    }
}

private:
    std::unordered_map<char, Character*> m_CharacterPool;
};

class Document
{
public:
    Document(CharacterFactory* factory) : m_Factory(factory) {}

    void insert(char c) 
    { 
        m_Chars.emplace_back(m_Factory->getCharacters(c));
    }

    void print() const
    {
        for (const auto &c : m_Chars)
        {
            std::cout << c->getChar();
        }
    }

private:
    std::vector<const Character*> m_Chars;
    CharacterFactory* m_Factory;
};



int main()
{
    CharacterFactory factory;
    Document doc(&factory);
    doc.insert('H');
    doc.insert('e');
    doc.insert('l');
    doc.insert('l');
    doc.insert('o');
    doc.insert(',');
    doc.insert(' ');
    doc.insert('w');
    doc.insert('o');
    doc.insert('r');
    doc.insert('l');
    doc.insert('d');
    doc.insert('!');
    doc.print();
    return 0;
}