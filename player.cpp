#include "player.h"

#define GROUND 400

CPlayer::CPlayer(std::string* map)
{
    m_map = map;

    m_end_games = 12;
    m_count = 0;
    m_win = false;

    m_image[0].loadFromFile("../fangs/fang1.png");
    m_image[1].loadFromFile("../fangs/fang2.png");
    m_image[2].loadFromFile("../fangs/fang3.png");
    m_image[3].loadFromFile("../fangs/fang4.png");
    m_image[4].loadFromFile("../fangs/fang5.png");
    m_image[5].loadFromFile("../fangs/fang6.png");

    m_onGround = true;
    m_sprite.setTexture(m_image[0]);
    m_rect = sf::FloatRect(100, 100, 38, 52);

    m_Vx = m_Vy = 0;
    m_currentFrame = 0;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(float time, float offsetX, float offsetY)
{
    /*std::cout << "m_Vx = " << m_Vx << "\t"
              << "m_Vy = " << m_Vy;

    std::cout << "\t"
              << "m_rect.left = " << m_rect.left << "\t"
              << "m_rect.top = " << m_rect.top << "\t";*/

    std::cout << m_count << std::endl;

    m_rect.left += m_Vx * time;
    CollisionX();

    if(!m_onGround)
        m_Vy = m_Vy + 0.0005 * time;
    m_rect.top += m_Vy * time;
    m_onGround = false;
    CollisionY();

    /*if(m_rect.top > GROUND) {
        m_rect.top = GROUND;
        m_Vy = 0;
        m_onGround = true;
    }*/

    m_currentFrame += 0.005 * time;
    if(m_currentFrame > 6)
        m_currentFrame = 0;

    if(m_Vx < 0) {
        m_sprite.setTextureRect(sf::IntRect(52, 0, -52, 54));
        m_sprite.setTexture(m_image[int(m_currentFrame)]);
    }

    if(m_Vx > 0) {
        m_sprite.setTextureRect(sf::IntRect(0, 0, 52, 54));
        m_sprite.setTexture(m_image[int(m_currentFrame)]);
        // m_sprite.setTextureRect(sf::IntRect(40 * int(m_currentFrame) + 40, 244, -40, 50));
    }

    m_sprite.setPosition(m_rect.left - offsetX, m_rect.top - offsetY);

    m_Vx = 0;

    if(m_count == m_end_games) {
        m_map[13][0] = '1';
        m_map[14][0] = '1';
        m_count = 0;
    }
}

void CPlayer::CollisionX()
{
    for(int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)
        for(int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++) {
            if(m_map[i][j] == 'B') {
                if(m_Vx > 0)
                    m_rect.left = j * 32 - m_rect.width;
                if(m_Vx < 0)
                    m_rect.left = j * 32 + 32;
            }

            if(m_map[i][j] == '0') {
                m_map[i][j] = ' ';
                m_count++;
            }

            if(m_map[i][j] == '1') {
                m_win = true;
            }
        }
}

bool CPlayer::GetFlagWinGame()
{
    return m_win;
}

void CPlayer::SetFlagWinGame()
{
    m_win = false;
}

void CPlayer::CollisionY()
{
    for(int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)
        for(int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++) {
            if(m_map[i][j] == 'B') {
                if(m_Vy > 0) {
                    m_rect.top = i * 32 - m_rect.height;
                    m_Vy = 0;
                    m_onGround = true;
                }
                if(m_Vy < 0) {
                    m_rect.top = i * 32 + 32;
                    m_Vy = 0;
                }
            }

            if(m_map[i][j] == '0') {
                m_map[i][j] = ' ';
                m_count++;
            }
        }
}