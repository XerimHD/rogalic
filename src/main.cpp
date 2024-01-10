#include <iostream>
#include <vector>
#include <time.h>
#include <E:\Desktop\school\ctest\lib\PDCurses-3.9\curses.h>
using namespace std;
void dangens(bool &t_placed, int &r_placed, bool &p_placed, int rows, int cols, vector<vector<char>> &map);

void movement(int &c, vector<vector<char>> &map);
int px, py;         // координата игрока
int tx, ty;         // координата гоблина
int rx = 0, ry = 0; // кордината комнаты
int p_gold = 0;
int r_size_x, r_size_y;
int rum_num = 2;
int main()
{

    int c = 0;
    int cols, rows;
    bool t_placed = false;
    bool p_placed = false;
    int r_placed = 0;
    initscr();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);

    do
    {
        getmaxyx(stdscr, rows, cols);
        vector<vector<char>> map(rows, vector<char>(cols));

        dangens(t_placed, r_placed, p_placed, rows, cols, map);
        movement(c, map);
        refresh();                 // Обновление экрана
    } while ((c = getch()) != 27); // 27 - ESC

    getch();
    endwin();
    return 0;
}

/////////////////////

void dangens(bool &t_placed, int &r_placed, bool &p_placed, int rows, int cols, vector<vector<char>> &map)
{

    resize_term(rows, cols); // Изменение размеров терминала

    /*if (!r_placed) // создания комнаты
    {
        // rand() % 5 + 5;
        ry = rand() % (rows - 4) + 1;
        rx = rand() % (cols - 4) + 1;
        r_size_y = rand() % 5 + 5;
        r_size_x = rand() % 10 + 5;
        }*/
    /// база даных
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {

            if (y == 0 || y == rows - 2 || x == 0 || x == cols - 1)
            {
                map[y][x] = '%'; // записываем  барьер в базу
            }
            else
            {
                map[y][x] = '#'; // записываем  стену в базу
            }
        }
    }

    /// рисования стен
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {

            if (map[y][x] == '%')
            {
                mvaddch(y, x, '%'); // рисуем  барьер
            }

            else if (map[y][x] == '#')
            {
                mvaddch(y, x, '#'); // рисуем  стену
            }
        }
    }

    do
    {

        ry = rand() % (rows - 4) + 1;
        rx = rand() % (cols - 4) + 1;
        r_size_y = rand() % 5 + 5;
        r_size_x = rand() % 10 + 5;

        // записываем в базу комнаты
        for (int y = ry; y < ry + r_size_y; y++)
        {
            for (int x = rx; x < rx + r_size_x; x++)
            {
                if (map[y][x] != '%')
                {
                    map[y][x] = ' ';
                }
            }
        }

        /// рисуем комнату
        for (int y = ry; y < ry + r_size_y; y++)
        {
            for (int x = rx; x < rx + r_size_x; x++)
            {
                if (map[y][x] == ' ')
                {
                    mvaddch(y, x, ' ');
                }
                else if (map[y][x] == '#')
                {
                    mvaddch(y, x, '#');
                }
            }
        }
        r_placed++;
    } while (r_placed <= rum_num);

    //////////////////////////////////////////////////////////
    // чистим последню строку для информации
    for (int x = 0; x < cols; x++)
    {
        mvaddch(rows - 1, x, ' ');
    }

    if (!t_placed)
    {

        do
        {
            tx = rand() % cols;
            ty = rand() % rows;
        } while (map[ty][tx] != ' ');
        t_placed = true;
    }
    if (px == tx && py == ty)
    {

        mvaddch(ty, tx, ' ');

        p_gold += rand() % 9 + 1; // получения золота
        do
        {
            tx = rand() % cols;
            ty = rand() % rows;
        } while (map[ty][tx] != ' ');
    }
    mvprintw(rows - 1, 0, "Gold %d", p_gold); // вывод золота
    if (!p_placed)
    {

        do
        {
            px = rand() % cols;
            py = rand() % rows;
        } while (map[py][px] != ' ');

        p_placed = true;
    }
}

void movement(int &c, vector<vector<char>> &map)
{

    if (c == KEY_UP && map[py - 1][px] == ' ')
        py--;
    else if (c == KEY_DOWN && map[py + 1][px] == ' ')
        py++;
    else if (c == KEY_LEFT && map[py][px - 1] == ' ')
        px--;
    else if (c == KEY_RIGHT && map[py][px + 1] == ' ')
        px++;
    mvaddch(ty, tx, 't'); // печать гоблина
    mvaddch(py, px, '@'); // печать игрока
}
