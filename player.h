#ifndef CPLAYER_H
#define CPLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class CPlayer
{
private:
    void CollisionX();
    void CollisionY();

public:
    bool m_win;

    int m_end_games;
    int m_count;

    std::string* m_map;

    float m_Vx, m_Vy;
    sf::FloatRect m_rect;
    bool m_onGround;
    sf::Sprite m_sprite;
    float m_currentFrame;

    sf::Texture m_image[6];

    void Update(float time, float offsetX, float offsetY);

public:
    CPlayer(std::string* map);
    ~CPlayer();

    bool GetFlagWinGame();
    void SetFlagWinGame();
};

#endif // CPLAYER_H