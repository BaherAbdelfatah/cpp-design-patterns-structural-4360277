#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>

using namespace std;

class Texture
{
public:
    explicit Texture(const string &fileName) : m_FileName(fileName), m_Id(rand()) {
        cout << "Creating texture from " << m_FileName << endl;
    }

    const string description() const
    {
        return "<" + m_FileName + " id" + to_string(m_Id) + ">";
    }
private:
    const string m_FileName;
    const int m_Id;
};

class Sprite
{
public:
    Sprite(const Texture *texture) : m_Texture(texture) {
        cout << "Creating sprite with texture file" << texture->description() << endl;
    }

    void setPositionSize(int x, int y, int width, int height)
    {
        m_X = x;
        m_Y = y;
        m_Width = width;
        m_Height = height;
    }

    void render()
    {
        // draw sprite
        cout << "Rendering sprite with texture: " << m_Texture->description() << endl;
    }

private:
    int m_Width;
    int m_Height;
    int m_X;
    int m_Y;

    const Texture *m_Texture;
};

class SpriteFactory {
public:
    Sprite* makeSprite(const std::string &fileName) {
        auto it = m_SpritePool.find(fileName);
        if (m_SpritePool.end() != it) {
            return it->second;
        } else {
            const auto texture = getTexture(fileName);
            auto newIt = m_SpritePool.emplace(fileName, new Sprite(texture));
            return newIt.first->second;
        }
    }

    ~SpriteFactory() {
        for (auto& sprite_pair : m_SpritePool) {
            delete sprite_pair.second;
        }

        for (auto& texture_pair : m_TexturePool) {
            delete texture_pair.second;
        }
    }

private:
    std::unordered_map<std::string, Sprite*> m_SpritePool;
    std::unordered_map<std::string, Texture*> m_TexturePool;

    const Texture* getTexture(const std::string &fileName) {
        auto it = m_TexturePool.find(fileName);
        if (it != m_TexturePool.end()) {
            // texture already exists in pool, return it.
            return it->second;
        } else {
            // create new texture and add it to the pool.
            auto newIt = m_TexturePool.emplace(fileName, new Texture(fileName));
            return newIt.first->second;
        }
    }
};

int main()
{
    // create a list of sprite objects
    vector<Sprite*> sprites;
    const int numSprites = 10;
    const string textureFile = "spaceship.png";

    SpriteFactory factory;

    for (int i = 0; i < numSprites; ++i)
    {
        auto sprite = factory.makeSprite(textureFile);
        sprite->setPositionSize(10, 10, 10 * i, 10 * i);
        sprites.push_back(sprite);
    }

    return 0;
}
