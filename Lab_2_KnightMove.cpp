#include <iostream>

using namespace std;

int Steps[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {1, -2},{-1, 2}, {2, -1}, {1, 2}, {2, 1}};


int Enter(int from, int to);
void KnghtMove(int size, int x, int y);
int CheckMove(int x, int y, int** desk, int size);
int Path(int x, int y, int numMove, int** desk, int& back, int maxMove);

int main()
{
    setlocale(LC_ALL, "Ru");
    int size, x, y;

    cout << "Введите размерность доски (от 2 до 8):\n";
    size = Enter(2, 9);
    cout << "Введите начальное положение коня\nx = ";
    x = Enter(0, size);
    cout << "y = ";
    y = Enter(0, size);

    
    KnghtMove(size, x, y);
}

void KnghtMove(int size, int x, int y)
{
    time_t start, end;
    int ** global;
    start = time(NULL);
    int** board = new int* [size];
    for (int i = 0; i < size; i++)
        board[i] = new int[size];
 

    global = board;

    int back = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            global[i][j] = 0;
    }

    if (Path(x, y, 1, global, back, size))
    {
        cout << "Решение\n\n";
        for (int i = 0; i < size; ++i) {
            cout << endl;
            for (int j = 0; j < size; ++j)
                cout << global[i][j] << "\t";
            cout << endl;
        }
    }
    else cout << "Решение не найдено" << endl;

    for (int i = 0; i < size; i++)
        delete[] global[i];
    delete[] global;
}
int Path(int x, int y, int numMove, int** global, int &back, int size)
{
    int xNext = 0, yNext = 0, maxMove = size * size - 1;

    global[x][y] = numMove;

    if (numMove > maxMove)
        return 1;

    for (int i = 0; i < 8; i++)
    {
        xNext = x + Steps[i][0];
        yNext = y + Steps[i][1];
        if (CheckMove(xNext, yNext, global, size) && Path(xNext, yNext, numMove + 1, global, back, maxMove))
            return 1;
    }

    global[x][y] = 0;
    back++;
    numMove++;
    return 0;
}

int CheckMove(int x, int y, int** desk, int size)
{
    return x >= 0 && y >= 0 && x < size && y < size && desk[x][y] == 0;
}

int Enter(int from, int to)
{
    int x;
    cin >> x;
    if ((x >= from) && (x < to))
        return x;
    else
    {
        cout << "Ошибка, введите другое число\n";
        Enter(from, to);
    }
}
