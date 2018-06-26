#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace sf;

//Ширина окна
const int WIDTH = 600;
//Высота окна
const int HEIGHT = 600;
//Ширина тайла
const float tileWIDTH = WIDTH / 4;
//Высота тайла
const float tileHEIGHT = HEIGHT / 4;
//Условия виыгрыша
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
//Функция перевода числа в строку
std::string int_to_string(int i){
    std::stringstream ss;
    ss << i;
    return ss.str();
}
//Функция генерации случайного числа из промежутка
int randomRange(int min, int max){
    return min + (rand() % static_cast<int>(max - min + 1));
}
//Функция для создания текста
Text createText(Font* font, Color color, std::string sText, int charSize, int x, int y, int offsetX, int offsetY){
    //Переменная типа Text
    Text text;
    //Установка црифта
    text.setFont(*font);
    //Установка цвета
    text.setColor(color);
    //Установка строки
    text.setString(sText);
    //Установка размера шрифта
    text.setCharacterSize(charSize);
    //Установка точки вращения в центр
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    text.setPosition(Vector2f(x + WIDTH / 2.0f + offsetX, y + HEIGHT / 2.0f + offsetY));
    //Возврашаем text
    return text;
}
//Функция для утсановки текста по центру
Text centerText(Text text, std::string sText, int offsetX, int offsetY){
    //Установка новой строки
    text.setString(sText);
    //Установка точки вращения в центр
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    text.setPosition(Vector2f(WIDTH / 2.0f + offsetX, HEIGHT / 2.0f + offsetY));
    //Возврашаем text
    return text;
}
//Класс тайла
class Tile {
public:
    //Переменные для зранения координат и цифры тайла
    int x, y, num;
    //Переманная для отрисовки тайла
    RectangleShape body;
    //Переменная для отрисовки цифры тайла
    Text numText;
    //Конструктор класса
    Tile(int _x, int _y, int _num, Font* font){
        //Присваивание переменных
        x = _x;
        y = _y;
        num = _num;
        //Создание прямоугольника с размерами 150 на 150
        body = RectangleShape(Vector2f(tileWIDTH, tileHEIGHT));
        //установка позиции прямоугольника
        body.setPosition(Vector2f(x * tileWIDTH, y * tileHEIGHT));
        //установка цвета обводки
        body.setOutlineColor(Color::Black);
        //установка ширины обводки
        body.setOutlineThickness(-1);
        //проверка на то являестя ли тайл пустым
        if(num != 0){
            //установка црифта
            numText.setFont(*font);
            //Установка размера шрифта
            numText.setCharacterSize(100);
            //Установка цвета
            numText.setColor(Color::Black);
            //Установка строки
            numText.setString(int_to_string(num));
            //Установка точки врашения в центр
            FloatRect textRect = numText.getLocalBounds();
            numText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
            numText.setPosition(Vector2f(x * tileWIDTH + tileWIDTH / 2.0f, y * tileHEIGHT + tileHEIGHT / 2.0f));
        }
    }
    //Метод для отрисоки  тайла
    void draw(RenderWindow* window){
        //Отрисовка прямоугольника
        window->draw(body);
        //Отрисовка цифры
        window->draw(numText);
    }
    //метод для установки новых координат тайла
    void setPos(int _x, int _y){
        //присвоение новых координат
        x = _x;
        y = _y;
        //смена позиции прямоугольника
        body.setPosition(Vector2f(x * tileWIDTH, y * tileHEIGHT));
        if(num != 0){
            //установка точки вращения текста в новую позицию
            FloatRect textRect = numText.getLocalBounds();
            numText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
            numText.setPosition(Vector2f(x * tileWIDTH + tileWIDTH / 2.0f, y * tileHEIGHT + tileHEIGHT / 2.0f));
        }
    }
};
//функция для проверки на выигрыш
bool checkWinCondition(std::vector<Tile> tiles){
    //цикл для перебора всех тайлов
    for(int i = 0; i < tiles.size(); ++i){
        //проверка правильности расположения тайлов
        if(tiles.at(i).x != winCondition[tiles.at(i).num - 1][0] || tiles.at(i).y != winCondition[tiles.at(i).num - 1][1]){
            //если хотя бы один тайл не на своем месте то вернется false и цикл закончится
            return false;
        }
    }
    //если цикл прошел успешно то все тайлы на своих местах и вернется true
    return true;
}
//метод для инициализации тайлов
std::vector<Tile> initTiles(Font* font){
    //Переменная массивва тайлов
    std::vector<Tile> tiles;
    //Переменная для отслеживания текушего ряда
    int k = 0;
    //цикл для создания тайлов
    for(int i = 0; i < 15; ++i){
        //если i без остатка делится на 4 то значит ряд закончился и нужно передти на новый
        if(i != 0 && i % 4 == 0) k++;
        //кладем в массив созданный тайл
        tiles.push_back(Tile(i % 4, k, i + 1, font));
    }
    //возвращаем все созданные тайлы
    return tiles;
}
//точка входа
int main()
{
    //инициализацтя рандома
    srand(time(0));
    //переменная для отслеживания состояния победы
    bool won = false;
    //колво щагов
    int swapMoves = 0;
    //массив с воординатами направлений (враво, влево, вниз, вверх)
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    //Переменная для хранения шрифта
    Font font;
    //Количество раз для случайных перестановок перед началовм игры
    int shuffleSteps = 100;
    //текущее колво случайных перестановок
    int currentShuffleStep = 0;
    //Переменная для таймера
    Clock clock;
    //Переменная для отслеживания направления с которого пришел путой тайл
    std::array<int, 2> lastDir;
    //создания окна
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pyatnashki");
    //сброс таймера
    clock.restart();
    //проверка на успешную загрузку шрифта
    if(!font.loadFromFile("arial.ttf")){
        //если загрузка не удалась в консоле появиться текст ошибки
        std::cout << "Failed to load font!" << std::endl;
    }
    //массив тайлов
    std::vector<Tile> tiles = initTiles(&font);
    //пустой тайл
    Tile empty = Tile(3, 3, 0, &font);
    //Переменная для отрисовки панели с тектом
    RectangleShape winPanel(Vector2f(400, 200));
    //установка цвета обводки
    winPanel.setOutlineColor(Color::Black);
    //установка ширины обводки
    winPanel.setOutlineThickness(4);
    //установка точки вращения в центр
    FloatRect textRect = winPanel.getLocalBounds();
    winPanel.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
    winPanel.setPosition(Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));

    //Переменная для отрисовки текста победы
    Text winText = createText(&font, Color::Black, "You win!", 100, 0, 0, 0, -40);
    //переменная для отрисовки текста рестарта
    Text restartText = createText(&font, Color::Black, "Press 'R' to restart!", 40, 0, 0, 0, 60);
    //переменная для отрисовки колва ходов
    Text swapText = createText(&font, Color::Black, "", 30, 0, 0, 0, 25);
    //пока окно октрыто все что ниже будет выполнятся покадрово
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //проверка на то если мы кликнули по окну левой кнопкой мыши и что мы еще не виыграли и начальное перемешивание законченно
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && currentShuffleStep >= shuffleSteps && !won){
                //рассчет координаты х
                int x = event.mouseButton.x / tileWIDTH;
                //расчет координаты у
                int y = event.mouseButton.y / tileHEIGHT;
                //перебираем циклов все тайлы
                for(int i = 0; i < 15; i++){
                    //находим тот на который мы кликнули
                    if(tiles.at(i).x == x && tiles.at(i).y == y && tiles.at(i).num != 0){
                        //для удобсвта запишем его в новую переменную
                        Tile t = tiles.at(i);
                        //циклом перебираем все возможные направления
                        for(int j = 0; j < 4; ++j){
                            //если в одном из направления лежит пустой тайл то происходит смена тайлов
                            if(t.x + dirs[j][0] == empty.x && t.y + dirs[j][1] == empty.y){
                                //сохранение координат тайла
                                int tx = t.x;
                                int ty = t.y;
                                //установка новых координат тайла
                                tiles.at(i).setPos(empty.x, empty.y);
                                //установка новых координат пустого тайла
                                empty.setPos(tx, ty);
                                //увеличение переменной которая хранит колво шагов на 1
                                swapMoves++;
                                //проверка на условие победы
                                if(checkWinCondition(tiles)){
                                    //если все тайлы на своих метах то переменной won присваивется true
                                    won = true;
                                    //тексту для отображения колва ходов устанавливается соответствующий тест
                                    swapText = centerText(swapText, "Number of swaps: " + int_to_string(swapMoves), 0, 25);
                                }
                                //выход из цикла
                                break;
                            }
                        }
                        //выход из цикла
                        break;
                    }
                }
            }
            //проверка если мы нажали на клавишу R и если мы победили
            if(event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::R) && won){
                //перменной won присваивается false
                won = false;
                //тайлы ставятся на свои места
                tiles = initTiles(&font);
                //заново перемещиваются
                currentShuffleStep = 0;
                //таймер сбрасывается
                clock.restart();
            }
        }
        //Перемашивание с промежутком в 30 милисекунд
        if(currentShuffleStep < shuffleSteps && clock.getElapsedTime().asMilliseconds() >= 3000 / shuffleSteps){
            //массив возможных ходов
            std::vector<std::array<int, 2>> posDirs;
            //циклом перебираем  направления
            for(int i = 0; i < 4; ++i){
                //рассчитываем будушие положение тайла
                int tx = empty.x += dirs[i][0];
                int ty = empty.y += dirs[i][1];
                //проверяем чтобы оно было в границах игрового поля и не было противополжным предыдушему ходу
                if(tx > -1 && tx < 4 && ty > -1 && ty < 4 && lastDir[0] != -dirs[i][0] && lastDir[1] != -dirs[i][1]){
                    //записываем возможный ход в массив
                    std::array<int, 2> tarr = {dirs[i][0], dirs[i][1]};
                    posDirs.push_back(tarr);
                }
            }
            //записываем направление для хода
            lastDir = posDirs.at(randomRange(0, posDirs.size() - 1));
            //перебираем циклом все тайлы
            for(int i = 0; i < 15; i++){
                //находим тот который надится в выбраном направлении от пустого тайла
                if(tiles.at(i).x == empty.x + lastDir[0] && tiles.at(i).y == empty.y + lastDir[1]){
                    //меняем метами их координаты
                    Tile t = tiles.at(i);
                    int tx = t.x;
                    int ty = t.y;
                    tiles.at(i).setPos(empty.x, empty.y);
                    empty.setPos(tx, ty);
                    //выходим из цикла
                    break;
                }
            }
            //увеличиваем количесво рандомных перемещений тайлов на 1
            currentShuffleStep++;
            //сбрасываем таймер
            clock.restart();
        }
        //отчищаем экран и заполняем его белым цветом
        window.clear(Color::White);
        //циклом перебираем все тайлы
        for(int i = 0; i < 15; ++i){
            //рисуем тайл
            tiles.at(i).draw(&window);
        }
        //рисуем пустой тайл
        empty.draw(&window);
        //если мы победили(игра закончилась) то рисуем табличку о победе
        if(won){
            //рисуем пустую табличку
            window.draw(winPanel);
            //рисуем текст о победе
            window.draw(winText);
            //рисуем текст о предложении рестарта игры
            window.draw(restartText);
            //рисуем текст о количесте ходов
            window.draw(swapText);
        }
        //отобрадаем на экран то что мы нарисовали
        window.display();
    }

    return 0;
}
