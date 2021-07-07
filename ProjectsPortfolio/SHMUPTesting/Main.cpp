#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <functional>

const float PI = 3.141592f;
const float DEGTORAD = 0.017453f;
enum class BulletType {M_red, M_orang, M_yellow, M_green, M_cyan, M_blue, M_purple};
struct Bullet {
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    float angle;
    BulletType graphic; // enum for determining what texture coordinate it needs
    float r = 1.f;
    bool isAlive = true;
    float anglemomentum = 0.f;
    Bullet(sf::Vector2f pos, sf::Vector2f dir, float sp, float an, BulletType gr) {
        position = pos;
        direction = dir;
        speed = sp;
        angle = an;
        graphic = gr;
    }

    void update() {
        angle += anglemomentum * DEGTORAD;
        direction.x = cosf(angle);
        direction.y = sinf(angle);
        position += direction * speed;
        if (position.x >= 660.f || position.x <= -20.f || position.y >= 500.f || position.y <= -20.f) { isAlive = false; }
    }
};

class BulletsRenderer : public sf::Drawable, public sf::Transformable
{
public:
    std::vector<Bullet> m_bullets;
    std::vector<sf::Vertex> m_vertices;
    sf::Texture m_texture;
    BulletsRenderer(){
        m_texture.loadFromFile("SpritesShots.png");
    }
    void createBullet(float x, float y, float speed, float angle, BulletType graphic, float anglemomentum = 0.f) {
        Bullet bul = { sf::Vector2f(x, y), sf::Vector2f(cosf(angle), sinf(angle)), speed, angle, graphic };
        bul.r = 6.f;
        bul.anglemomentum = anglemomentum;
        //set radius and texture coordinates depending on the enum
        sf::Vector2f texCoord[4];
        switch (graphic) {
        case BulletType::M_red:
            texCoord[0].x = 5.f; texCoord[0].y = 113.f;
            texCoord[1].x = 17.f; texCoord[1].y = 113.f;
            texCoord[2].x = 17.f; texCoord[2].y = 124.f;
            texCoord[3].x = 5.f; texCoord[3].y = 124.f;
            break;
        case BulletType::M_orang:
         
            texCoord[0].x = 23.f; texCoord[0].y = 113.f;
            texCoord[1].x = 35.f; texCoord[1].y = 113.f;
            texCoord[2].x = 35.f; texCoord[2].y = 124.f;
            texCoord[3].x = 23.f; texCoord[3].y = 124.f;
            break;
        case BulletType::M_yellow:
          
            texCoord[0].x = 41.f; texCoord[0].y = 113.f;
            texCoord[1].x = 53.f; texCoord[1].y = 113.f;
            texCoord[2].x = 53.f; texCoord[2].y = 124.f;
            texCoord[3].x = 41.f; texCoord[3].y = 124.f;
            break;
        case BulletType::M_green:
          
            texCoord[0].x = 59.f; texCoord[0].y = 113.f;
            texCoord[1].x = 71.f; texCoord[1].y = 113.f;
            texCoord[2].x = 71.f; texCoord[2].y = 124.f;
            texCoord[3].x = 59.f; texCoord[3].y = 124.f;
            break;
        case BulletType::M_cyan:
           
            texCoord[0].x = 77.f; texCoord[0].y = 113.f;
            texCoord[1].x = 89.f; texCoord[1].y = 113.f;
            texCoord[2].x = 89.f; texCoord[2].y = 124.f;
            texCoord[3].x = 77.f; texCoord[3].y = 124.f;
            break;
        case BulletType::M_blue:
            texCoord[0].x = 95.f; texCoord[0].y = 113.f;
            texCoord[1].x = 107.f; texCoord[1].y = 113.f;
            texCoord[2].x = 107.f; texCoord[2].y = 124.f;
            texCoord[3].x = 95.f; texCoord[3].y = 124.f;
            break;
        case BulletType::M_purple:
            texCoord[0].x = 113.f; texCoord[0].y = 113.f;
            texCoord[1].x = 125.f; texCoord[1].y = 113.f;
            texCoord[2].x = 125.f; texCoord[2].y = 124.f;
            texCoord[3].x = 113.f; texCoord[3].y = 124.f;
            break;
        }

        m_bullets.push_back(bul);
        sf::Vertex quad[4];
        quad[0].position = sf::Vector2f(x - bul.r, y + bul.r); quad[0].texCoords = texCoord[0];
        quad[1].position = sf::Vector2f(x + bul.r, y + bul.r); quad[1].texCoords = texCoord[1];
        quad[2].position = sf::Vector2f(x + bul.r, y - bul.r); quad[2].texCoords = texCoord[2];
        quad[3].position = sf::Vector2f(x - bul.r, y - bul.r); quad[3].texCoords = texCoord[3];

        sf::Transform rotation;
        rotation.rotate((bul.angle * 180.f / PI) - 90 , bul.position);
        quad[0].position = rotation.transformPoint(quad[0].position);
        quad[1].position = rotation.transformPoint(quad[1].position);
        quad[2].position = rotation.transformPoint(quad[2].position);
        quad[3].position = rotation.transformPoint(quad[3].position);

        m_vertices.push_back(quad[0]);
        m_vertices.push_back(quad[1]);
        m_vertices.push_back(quad[2]);
        m_vertices.push_back(quad[3]);
       
     }

    void destroyBullet(size_t index) {
        auto bulIter = m_bullets.size() > 1 ? m_bullets.begin() + index : m_bullets.begin();
        auto vertIter =m_vertices.size() > 1 ? m_vertices.begin() + (index * 4) : m_vertices.begin();
        m_bullets.erase(bulIter);
        m_vertices.erase(vertIter, vertIter + 4);
    }

    void update() {
        for (size_t i = 0; i < m_bullets.size(); ++i) {
            sf::Transform translation; // tranform of the position
            translation.translate(m_bullets[i].direction * m_bullets[i].speed);
            float oldAngle = m_bullets[i].angle;
            m_bullets[i].update();
            translation.rotate((m_bullets[i].angle * 180.f / PI) - oldAngle * 180.f / PI, m_bullets[i].position);

            sf::Vertex* quad = &m_vertices[i * 4];
            quad[0].position = translation.transformPoint(quad[0].position);
            quad[1].position = translation.transformPoint(quad[1].position);
            quad[2].position = translation.transformPoint(quad[2].position);
            quad[3].position = translation.transformPoint(quad[3].position);

            if (!m_bullets[i].isAlive) {
                destroyBullet(i);
            }
        }
    }
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_texture;

        // draw the vertex array
        target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
    }

   
};



int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Entity rendering test");
    srand(unsigned int(std::time(0)));
    window.setVerticalSyncEnabled(1);
    BulletsRenderer bullets;
   
    
   
    sf::Clock clock;
    float angleT = 0.f;
    for (int i = 0; i < 50; ++i) {
        if (i % 2 == 0)
            bullets.createBullet(320.f, 240.f, 2.f, angleT, BulletType::M_cyan, 0.5f);
        else 
            bullets.createBullet(320.f, 240.f, 2.f, angleT, BulletType::M_cyan, -0.5f);

        angleT += (2.f * PI) / 50.f;

    }
    
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        bullets.update();
        
        // draw the map
        window.clear();
        window.draw(bullets); 
        window.display();
        window.setTitle("Entity rendering test " + std::to_string(1.f/ elapsed.asSeconds()) + " fps " + std::to_string(bullets.m_vertices.size() / 4) + " bullets");
    }

    return 0;
}