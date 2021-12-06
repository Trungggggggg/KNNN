#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
void gotoxy(int column, int line);
int Width_Box = 40, Height_Box = 40;
struct Point {
    int x, y;
};
class SNAKE {
public:
    struct Point A[100];
    int Snake_Length;
    SNAKE() {
        Snake_Length = 3;
        A[0].x = Width_Box / 2 + 2; A[0].y = Height_Box / 2;
        A[1].x = Width_Box / 2 + 1; A[1].y = Height_Box / 2;
        A[2].x = Width_Box / 2; A[2].y = Height_Box / 2;
    }
    void Draw_Snake() {
        for (int i = 0; i < Snake_Length; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }
    void move(Direction direction) {
        for (int i = Snake_Length - 1; i > 0; i--)
            A[i] = A[i - 1];
        if (direction == Direction::right) A[0].x = A[0].x + 1;
        if (direction == Direction::down) A[0].y = A[0].y + 1;
        if (direction == Direction::left) A[0].x = A[0].x - 1;
        if (direction == Direction::up) A[0].y = A[0].y - 1;

    }
    // kiểm tra rắn chạm tường
    bool isHitwall()
    {
        return A[0].x == 0 || A[0].y == 0 || A[0].x == Width_Box || A[0].y == Height_Box;
    }
    //kiểm tra rắn tự cắn chính mình
    bool isBiteItself()
    {
        Point head = A[0];
        for (size_t i = 1; i < Snake_Length; i++)
            if (head.x == A[i].x && head.y == A[i].y)
                return true;
        return false;
    }
};
SNAKE r;
int main()
{
    Direction direction = Direction::right;
    char t;
    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a' && direction != Direction::right)
                direction = Direction::left;
            else if (t == 's' && direction != Direction::down)
                direction = Direction::up;
            else if (t == 'w' && direction != Direction::up)
                direction = Direction::down;
            else if (t == 'd' && direction != Direction::left)
                direction = Direction::right;
        }
        system("cls");
        r.Draw_Snake();
        r.move(direction);
        Sleep(300);
    }

    return 0;
}


void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}


Direction direction = Direction::right;

// hàm vẽ khung - phạm vi chơi
void draw_Box(int Height_Box, int Width_Box)
{
    for (size_t i = 0; i < Width_Box; i++)
        cout << '=';
    gotoxy(0, Height_Box);
    for (size_t i = 0; i < Width_Box; i++)
        cout << '=';
    for (size_t i = 1; i < Height_Box; i++)
    {
        gotoxy(0, i);
        cout << '|';
    }
    for (size_t i = 1; i < Height_Box; i++)
    {
        gotoxy(Width_Box, i);
        cout << '|';
    }
}


enum class Direction
{
    up,
    right,
    down,
    left
};





