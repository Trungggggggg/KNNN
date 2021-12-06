#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
void gotoxy(int column, int line);
struct Point {
    int x, y;
};
class CONRAN {
public:
    struct Point A[100];
    int DoDai;
    SNAKE() {
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }
    void Ve() {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
    }
    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];
        if (Huong == 0) A[0].x = A[0].x + 1;
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1;
        if (Huong == 3) A[0].y = A[0].y - 1;

    }
};

int main()
{
    CONRAN r;
    int Huong = 0;
    char t;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 'x') Huong = 1;
        }
        system("cls");
        r.Ve();
        r.DiChuyen(Huong);
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

//vị trí rắn xuất hiện: giữa khung
void startSnake()
{
    direction = Direction::right;
    SNAKE = 
    {
        Point{ Width_Box / 2 + 2, Height_Box / 2 },
        Point{ Width_Box / 2 + 1, Height_Box / 2 },
        Point{ Width_Box / 2, Height_Box / 2 },
        Point{ Width_Box / 2 - 1, Height_Box / 2 },
        Point{ Width_Box / 2 - 2, Height_Box / 2 }
    };
}
enum class Direction
{
    up,
    right,
    down,
    left
};

//hàm tránh quay đầu 180 độ
void Checking_180(char direct)
{
    if (direct == 'a' && direction != Direction::right)
        direction = Direction::left;
    else if (direct == 'x' && direction != Direction::down)
        direction = Direction::up;
    else if (direct == 'w' && direction != Direction::up)
        direction = Direction::down;
    else if (direct == 'd' && direction != Direction::left)
        direction = Direction::right;
    else if (direct == 'q') 
        break;
}

// kiểm tra rắn chạm tường
bool isHitwall()
{
    return SNAKE[0].x == 0 || SNAKE[0].y == 0 || SNAKE[0].x == Width_Box || SNAKE[0].y == Height_Box;
}

//kiểm tra rắn tự cắn chính mình
bool isBiteItself()
{
    Point head = SNAKE[0];
    for (size_t i = 1; i < SNAKE.size(); i++)
        if (head.x == SNAKE[i].x && head.y == SNAKE[i].y)
            return true;
    return false;
}
