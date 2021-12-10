#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
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
enum class Direction
{
    up,
    right,
    down,
    left
};
const int Width_Box = 40, Height_Box = 20;
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
        if (direction == Direction::down) A[0].y = A[0].y - 1;
        if (direction == Direction::left) A[0].x = A[0].x - 1;
        if (direction == Direction::up) A[0].y = A[0].y + 1;

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
// hàm vẽ khung - phạm vi chơi
void draw_Box()
{
    for (int i = 0; i < Width_Box; i++)
        cout << '=';
    gotoxy(0, Height_Box);
    for (int i = 0; i < Width_Box; i++)
        cout << '=';
    for (int i = 1; i < Height_Box; i++)
    {
        gotoxy(0, i);
        cout << '|';
    }
    for (int i = 1; i < Height_Box; i++)
    {
        gotoxy(Width_Box, i);
        cout << '|';
    }
}
void drawStartMenu()
{
    system("cls");
    cout<< "########################" << endl
        << "#                      #" << endl
        << "#      SNAKE GAME      #" << endl
        << "#                      #" << endl
        << "########################" << endl << endl
        << "________________________" << endl
        << "Press 1 to start game" << endl
        << "Press 2 to exit" << endl;
}
//tạo mồi random
Point Food;

void unitFood()
{
    srand(time(0));
    int x = rand() % (Width_Box - 1) + 1;
    int y = rand() % (Height_Box - 1) + 1;
    Food =
    {
        x,
        y,
    };
    gotoxy(x, y);
    cout << "X";
}
//kiểm tra đầu rắn chạm mồi
bool isEatFood()
{
    return A[0].x == Food.x && A[0].y == Food.y;
}
int main()
{
    drawStartMenu();
    int check;
    cin >> check;
    if (check == 2) exit(1);
    else if (check == 1)
    {
        SNAKE r;
        system("cls");
        Direction direction = Direction::right;
        char t;
        draw_Box();
        while (1) {
            system("cls");
            draw_Box();
            if (_kbhit()) {
                t = _getch();
                if (t == 'a' && direction != Direction::right)
                    direction = Direction::left;
                else if (t == 's' && direction != Direction::down)
                    direction = Direction::up;
                else if (t == 'w' && direction != Direction::up)
                    direction = Direction::down;
                else if (t == 'd' && direction != Direction::left)
                    direction = Direction::right;
            }
            r.Draw_Snake();
            r.move(direction);
            Sleep(300);
        }
    }
    return 0;
}










