#include "player.h"

const int H = 16;
const int W = 20;

std::string TileMapz[H] = {
    "BBBBBBBBBBBBBBBBBBBB",
    "B        0         B",
    "B                  B",
    "B                00B",
    "B 00          BBBBBB",
    "B                  B",
    "B      BBBB        B",
    "B                  B",
    "B          00      B",
    "B          BBBB    B",
    "B                  B",
    "B                 0B",
    "B               BBBB",
    "B        000       B",
    "B                 0B",
    "BBBBBBBBBBBBBBBBBBBB",
};

#define HSCREEN 640
#define WSCREEN 480

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(HSCREEN, WSCREEN), "Mario Games");
    CPlayer player(TileMapz);
    sf::Clock clock;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(32, 32));

    float offsetX = 0;
    float offsetY = 0;

    while(window.isOpen()) {

        while(player.GetFlagWinGame()) {
            window.clear(sf::Color::White);
            sf::Texture im;
            im.loadFromFile("../fangs/end.png");
            sf::Sprite sp;
            sp.setTexture(im);
            window.draw(sp);
            window.display();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                player.SetFlagWinGame();
                window.close();
            }
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time /= 800;

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.m_Vx = -0.1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.m_Vx = 0.1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(player.m_onGround) {
                player.m_Vy = -0.32;
                player.m_onGround = false;
            }
        }

        player.Update(time, offsetX, offsetY);

        if(player.m_rect.left > HSCREEN / 2)
            offsetX = player.m_rect.left - HSCREEN / 2;
        
        if(player.m_rect.top > WSCREEN / 2)
            offsetY = player.m_rect.top - WSCREEN / 2;

        window.clear(sf::Color::White);

        for(int i = 0; i < H; i++)
            for(int j = 0; j < W; j++) {
                if(TileMapz[i][j] == 'B')
                    rectangle.setFillColor(sf::Color::Black);
                if(TileMapz[i][j] == '0')
                    rectangle.setFillColor(sf::Color::Green);
                if(TileMapz[i][j] == '1')
                    rectangle.setFillColor(sf::Color::Blue);
                if(TileMapz[i][j] == ' ')
                    continue;
                rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
                window.draw(rectangle);
            }

        window.draw(rectangle);

        window.draw(player.m_sprite);
        window.display();
    }
    return 0;
}