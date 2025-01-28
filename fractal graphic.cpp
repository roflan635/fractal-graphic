#include "SFML/Graphics.hpp"

using namespace sf; // подключаем пространство имен sf

// Объект, который, собственно, является главным окном приложения
RenderWindow window(VideoMode(800, 600), "Squares");

// xc, yc - координаты центра
// radius - радиус главной окружности
// nestingLength - глубина вложенности рисования (1- одна окружность, 2 - 5 окружностей и т.д.)
void SquareCollection(float xc, float yc, float radius, int nestingLength)
{
    if (nestingLength == 0) return; // если дошли до 0 вложенности - прекращаем рекурсию
    RectangleShape rectangle(Vector2f(2*radius, 2*radius)); // создаем квадрат
    rectangle.setOrigin(radius, radius); // устанавливаем точку привязки по центру окружности
    rectangle.setOutlineColor(Color::Black); // цвет границы черный
    rectangle.setFillColor(Color::Transparent); // заливка прозрачная
    rectangle.setOutlineThickness(1); // толщина 1
    rectangle.setPosition(xc, yc); // перемещаем окружность в точку xc, yc
    window.draw(rectangle); // отрисовываем окружность в буфере кадра
    if (nestingLength > 1) // если глубина вложенности превышает 1, то рисуем окружности по сторонам рекурсивно
    {
        SquareCollection(xc - radius, yc + radius, radius / 2, nestingLength - 1); // радиусом в 2 раза меньшим
        SquareCollection(xc - radius, yc - radius, radius / 2, nestingLength - 1);
        SquareCollection(xc + radius, yc - radius, radius / 2, nestingLength - 1);
        SquareCollection(xc + radius, yc + radius, radius / 2, nestingLength - 1);
    }
}

int main()
{
    // Главный цикл приложения: выполняется, пока открыто окно
    window.setFramerateLimit(1);
    while (window.isOpen())
    {
        // Обрабатываем очередь событий в цикле
        Event event;
        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == Event::Closed)
                window.close(); // тогда закрываем его
        }
        // Установка цвета фона
        window.clear(Color::White);
        // рисуем наш узор рекурсивной функцией
        SquareCollection(400, 300, 150, 4);
        // Отрисовка окна
        window.display();
    }
}