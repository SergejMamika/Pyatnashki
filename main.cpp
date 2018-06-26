#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace sf;

//������ ����
const int WIDTH = 600;
//������ ����
const int HEIGHT = 600;
//������ �����
const float tileWIDTH = WIDTH / 4;
//������ �����
const float tileHEIGHT = HEIGHT / 4;
//������� ��������
const int winCondition[15][2] = {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {0, 1},
    {1, 1},
    {2, 1},
    {3, 1},
    {0, 2},
    {1, 2},
    {2, 2},
    {3, 2},
    {0, 3},
    {1, 3},
    {2, 3}
};
//������� �������� ����� � ������
std::string int_to_string(int i){
    std::stringstream ss;
    ss << i;
    return ss.str();
}
//������� ��������� ���������� ����� �� ����������
int randomRange(int min, int max){
    return min + (rand() % static_cast<int>(max - min + 1));
}
//������� ��� �������� ������
Text createText(Font* font, Color color, std::string sText, int charSize, int x, int y, int offsetX, int offsetY){
    //���������� ���� Text
    Text text;
    //��������� ������
    text.setFont(*font);
    //��������� �����
    text.setColor(color);
    //��������� ������
    text.setString(sText);
    //��������� ������� ������
    text.setCharacterSize(charSize);
    //��������� ����� �������� � �����
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    text.setPosition(Vector2f(x + WIDTH / 2.0f + offsetX, y + HEIGHT / 2.0f + offsetY));
    //���������� text
    return text;
}
//������� ��� ��������� ������ �� ������
Text centerText(Text text, std::string sText, int offsetX, int offsetY){
    //��������� ����� ������
    text.setString(sText);
    //��������� ����� �������� � �����
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    text.setPosition(Vector2f(WIDTH / 2.0f + offsetX, HEIGHT / 2.0f + offsetY));
    //���������� text
    return text;
}
//����� �����
class Tile {
public:
    //���������� ��� �������� ��������� � ����� �����
    int x, y, num;
    //���������� ��� ��������� �����
    RectangleShape body;
    //���������� ��� ��������� ����� �����
    Text numText;
    //����������� ������
    Tile(int _x, int _y, int _num, Font* font){
        //������������ ����������
        x = _x;
        y = _y;
        num = _num;
        //�������� �������������� � ��������� 150 �� 150
        body = RectangleShape(Vector2f(tileWIDTH, tileHEIGHT));
        //��������� ������� ��������������
        body.setPosition(Vector2f(x * tileWIDTH, y * tileHEIGHT));
        //��������� ����� �������
        body.setOutlineColor(Color::Black);
        //��������� ������ �������
        body.setOutlineThickness(-1);
        //�������� �� �� �������� �� ���� ������
        if(num != 0){
            //��������� ������
            numText.setFont(*font);
            //��������� ������� ������
            numText.setCharacterSize(100);
            //��������� �����
            numText.setColor(Color::Black);
            //��������� ������
            numText.setString(int_to_string(num));
            //��������� ����� �������� � �����
            FloatRect textRect = numText.getLocalBounds();
            numText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
            numText.setPosition(Vector2f(x * tileWIDTH + tileWIDTH / 2.0f, y * tileHEIGHT + tileHEIGHT / 2.0f));
        }
    }
    //����� ��� ��������  �����
    void draw(RenderWindow* window){
        //��������� ��������������
        window->draw(body);
        //��������� �����
        window->draw(numText);
    }
    //����� ��� ��������� ����� ��������� �����
    void setPos(int _x, int _y){
        //���������� ����� ���������
        x = _x;
        y = _y;
        //����� ������� ��������������
        body.setPosition(Vector2f(x * tileWIDTH, y * tileHEIGHT));
        if(num != 0){
            //��������� ����� �������� ������ � ����� �������
            FloatRect textRect = numText.getLocalBounds();
            numText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
            numText.setPosition(Vector2f(x * tileWIDTH + tileWIDTH / 2.0f, y * tileHEIGHT + tileHEIGHT / 2.0f));
        }
    }
};
//������� ��� �������� �� �������
bool checkWinCondition(std::vector<Tile> tiles){
    //���� ��� �������� ���� ������
    for(int i = 0; i < tiles.size(); ++i){
        //�������� ������������ ������������ ������
        if(tiles.at(i).x != winCondition[tiles.at(i).num - 1][0] || tiles.at(i).y != winCondition[tiles.at(i).num - 1][1]){
            //���� ���� �� ���� ���� �� �� ����� ����� �� �������� false � ���� ����������
            return false;
        }
    }
    //���� ���� ������ ������� �� ��� ����� �� ����� ������ � �������� true
    return true;
}
//����� ��� ������������� ������
std::vector<Tile> initTiles(Font* font){
    //���������� �������� ������
    std::vector<Tile> tiles;
    //���������� ��� ������������ �������� ����
    int k = 0;
    //���� ��� �������� ������
    for(int i = 0; i < 15; ++i){
        //���� i ��� ������� ������� �� 4 �� ������ ��� ���������� � ����� ������� �� �����
        if(i != 0 && i % 4 == 0) k++;
        //������ � ������ ��������� ����
        tiles.push_back(Tile(i % 4, k, i + 1, font));
    }
    //���������� ��� ��������� �����
    return tiles;
}
//����� �����
int main()
{
    //������������� �������
    srand(time(0));
    //���������� ��� ������������ ��������� ������
    bool won = false;
    //����� �����
    int swapMoves = 0;
    //������ � ������������ ����������� (�����, �����, ����, �����)
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    //���������� ��� �������� ������
    Font font;
    //���������� ��� ��� ��������� ������������ ����� �������� ����
    int shuffleSteps = 100;
    //������� ����� ��������� ������������
    int currentShuffleStep = 0;
    //���������� ��� �������
    Clock clock;
    //���������� ��� ������������ ����������� � �������� ������ ����� ����
    std::array<int, 2> lastDir;
    //�������� ����
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pyatnashki");
    //����� �������
    clock.restart();
    //�������� �� �������� �������� ������
    if(!font.loadFromFile("arial.ttf")){
        //���� �������� �� ������� � ������� ��������� ����� ������
        std::cout << "Failed to load font!" << std::endl;
    }
    //������ ������
    std::vector<Tile> tiles = initTiles(&font);
    //������ ����
    Tile empty = Tile(3, 3, 0, &font);
    //���������� ��� ��������� ������ � ������
    RectangleShape winPanel(Vector2f(400, 200));
    //��������� ����� �������
    winPanel.setOutlineColor(Color::Black);
    //��������� ������ �������
    winPanel.setOutlineThickness(4);
    //��������� ����� �������� � �����
    FloatRect textRect = winPanel.getLocalBounds();
    winPanel.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    winPanel.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));

    //���������� ��� ��������� ������ ������
    Text winText = createText(&font, Color::Black, "You win!", 100, 0, 0, 0, -40);
    //���������� ��� ��������� ������ ��������
    Text restartText = createText(&font, Color::Black, "Press 'R' to restart!", 40, 0, 0, 0, 60);
    //���������� ��� ��������� ����� �����
    Text swapText = createText(&font, Color::Black, "", 30, 0, 0, 0, 25);
    //���� ���� ������� ��� ��� ���� ����� ���������� ���������
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //�������� �� �� ���� �� �������� �� ���� ����� ������� ���� � ��� �� ��� �� �������� � ��������� ������������� ����������
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && currentShuffleStep >= shuffleSteps && !won){
                //������� ���������� �
                int x = event.mouseButton.x / tileWIDTH;
                //������ ���������� �
                int y = event.mouseButton.y / tileHEIGHT;
                //���������� ������ ��� �����
                for(int i = 0; i < 15; i++){
                    //������� ��� �� ������� �� ��������
                    if(tiles.at(i).x == x && tiles.at(i).y == y && tiles.at(i).num != 0){
                        //��� �������� ������� ��� � ����� ����������
                        Tile t = tiles.at(i);
                        //������ ���������� ��� ��������� �����������
                        for(int j = 0; j < 4; ++j){
                            //���� � ����� �� ����������� ����� ������ ���� �� ���������� ����� ������
                            if(t.x + dirs[j][0] == empty.x && t.y + dirs[j][1] == empty.y){
                                //���������� ��������� �����
                                int tx = t.x;
                                int ty = t.y;
                                //��������� ����� ��������� �����
                                tiles.at(i).setPos(empty.x, empty.y);
                                //��������� ����� ��������� ������� �����
                                empty.setPos(tx, ty);
                                //���������� ���������� ������� ������ ����� ����� �� 1
                                swapMoves++;
                                //�������� �� ������� ������
                                if(checkWinCondition(tiles)){
                                    //���� ��� ����� �� ����� ����� �� ���������� won ������������ true
                                    won = true;
                                    //������ ��� ����������� ����� ����� ��������������� ��������������� ����
                                    swapText = centerText(swapText, "Number of swaps: " + int_to_string(swapMoves), 0, 25);
                                }
                                //����� �� �����
                                break;
                            }
                        }
                        //����� �� �����
                        break;
                    }
                }
            }
            //�������� ���� �� ������ �� ������� R � ���� �� ��������
            if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::R) && won){
                //��������� won ������������� false
                won = false;
                //����� �������� �� ���� �����
                tiles = initTiles(&font);
                //������ ��������������
                currentShuffleStep = 0;
                //������ ������������
                clock.restart();
            }
        }
        //������������� � ����������� � 30 ����������
        if(currentShuffleStep < shuffleSteps && clock.getElapsedTime().asMilliseconds() >= 3000 / shuffleSteps){
            //������ ��������� �����
            std::vector<std::array<int, 2>> posDirs;
            //������ ����������  �����������
            for(int i = 0; i < 4; ++i){
                //������������ ������� ��������� �����
                int tx = empty.x += dirs[i][0];
                int ty = empty.y += dirs[i][1];
                //��������� ����� ��� ���� � �������� �������� ���� � �� ���� �������������� ����������� ����
                if(tx > -1 && tx < 4 && ty > -1 && ty < 4 && lastDir[0] != -dirs[i][0] && lastDir[1] != -dirs[i][1]){
                    //���������� ��������� ��� � ������
                    std::array<int, 2> tarr = {dirs[i][0], dirs[i][1]};
                    posDirs.push_back(tarr);
                }
            }
            //���������� ����������� ��� ����
            lastDir = posDirs.at(randomRange(0, posDirs.size() - 1));
            //���������� ������ ��� �����
            for(int i = 0; i < 15; i++){
                //������� ��� ������� ������� � �������� ����������� �� ������� �����
                if(tiles.at(i).x == empty.x + lastDir[0] && tiles.at(i).y == empty.y + lastDir[1]){
                    //������ ������ �� ����������
                    Tile t = tiles.at(i);
                    int tx = t.x;
                    int ty = t.y;
                    tiles.at(i).setPos(empty.x, empty.y);
                    empty.setPos(tx, ty);
                    //������� �� �����
                    break;
                }
            }
            //����������� ��������� ��������� ����������� ������ �� 1
            currentShuffleStep++;
            //���������� ������
            clock.restart();
        }
        //�������� ����� � ��������� ��� ����� ������
        window.clear(Color::White);
        //������ ���������� ��� �����
        for(int i = 0; i < 15; ++i){
            //������ ����
            tiles.at(i).draw(&window);
        }
        //������ ������ ����
        empty.draw(&window);
        //���� �� ��������(���� �����������) �� ������ �������� � ������
        if(won){
            //������ ������ ��������
            window.draw(winPanel);
            //������ ����� � ������
            window.draw(winText);
            //������ ����� � ����������� �������� ����
            window.draw(restartText);
            //������ ����� � ��������� �����
            window.draw(swapText);
        }
        //���������� �� ����� �� ��� �� ����������
        window.display();
    }

    return 0;
}
