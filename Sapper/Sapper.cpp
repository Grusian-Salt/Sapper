#include <iostream>
#include <ctime>


const size_t FieldX = 9;
const size_t FieldY = 9;
uint16_t Mines = 10;

class field
{
private:
    struct node
    {
        uint8_t minesCount;
        bool seen;
        bool flag;
        node()
        {
            minesCount = 0;
            seen = false;
            flag = false;
        }
        void setmine()
        {
            minesCount = 9;
        }
        void setmine(uint8_t count)
        {
            minesCount = count;
        }
    };
    uint16_t mines;
    uint16_t Flags;
    uint16_t opens;
    node Field[FieldX][FieldY];
    bool life;
    bool win;
public:
    field(uint16_t mines1)
    {
        srand(time(0));
        life = true;
        win = false;
        opens = 0;
        mines = 0;
        Flags = 0;
        while (mines<mines1)
        {
            size_t rx = rand() % FieldX;
            size_t ry = rand() % FieldY;
            if (Field[rx][ry].minesCount != 9)
            {
                Field[rx][ry].minesCount = 9;
                mines++;
            }
        }
        for (size_t i = 0; i < FieldY; i++)
        {
            for (size_t j = 0; j < FieldX; j++)
            {
                if (Field[j][i].minesCount == 0)
                {
                    if (Field[j - 1][i - 1].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j - 1][i    ].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j - 1][i + 1].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j    ][i - 1].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j    ][i + 1].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j + 1][i - 1].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j + 1][i    ].minesCount == 9)Field[j][i].minesCount++;
                    if (Field[j + 1][i + 1].minesCount == 9)Field[j][i].minesCount++;
                }
            }
        }
    }

    void print()
    {
        std::cout << "Mines:" << Mines << " Flags:" << Flags << std::endl;
        std::cout << "*";
        for (int i = 0; i < FieldX; i++) { std::cout << int(i); }
        std::cout << "X" << std::endl;
        for (int i = 0; i < FieldY; i++)
        {
            std::cout << int(i);
            for (int j = 0; j < FieldX; j++)
            {
                     if (Field[j][i].minesCount == 9 && Field[j][i].seen == true) std::cout << '*';
                else if (Field[j][i].minesCount >= 1 && Field[j][i].seen == true) std::cout << int(Field[j][i].minesCount);
                else if (Field[j][i].minesCount == 0 && Field[j][i].seen == true) std::cout << ' ';
                else if (Field[j][i].flag == true) std::cout << 'F';
                else std::cout << "X";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "Y";
        for (int i = 0; i < FieldX; i++) { std::cout << "-"; }
        std::cout << "*" << std::endl;
    }
    void setFlag(size_t x, size_t y)
    {
        if (Field[x][y].seen == false)
        {
            if (Field[x][y].flag == false)
            {
                Field[x][y].flag = true;
                Flags++;
                if (Field[x][y].minesCount == 9)
                {
                    mines--;
                    if (mines == 0&&opens == Flags) win = true;
                }
            }
            if (Field[x][y].flag == false)
            {
                Field[x][y].flag = false;
                Flags--;
                if (Field[x][y].minesCount == 9)
                {
                    mines++;
                }
            }
        }
    }
    bool getLife() { return life; }
    bool getWin() { return win; }
    void openRecursive(size_t x, size_t y)
    {
        if (Field[x][y].seen == false)
        {
            Field[x][y].seen = true;
            opens++;
            if (Field[x][y].minesCount == 9) life = false;
            if (mines == 0 && opens == Flags) win = true;
            if (Field[x][y].minesCount == 0)
            {
                if (x != 0 && y != 0)openRecursive(x - 1, y - 1);
                if (x != 0)openRecursive(x - 1, y);
                if (x != 0 && y != FieldY)openRecursive(x - 1, y + 1);
                if (y != 0)openRecursive(x, y - 1);
                if (y != FieldY)openRecursive(x, y + 1);
                if (x != FieldX && y != 0)openRecursive(x + 1, y - 1);
                if (x != FieldX)openRecursive(x + 1, y);
                if (x != FieldX && y != FieldY)openRecursive(x + 1, y + 1);
            }
        }

    }

};


int main()
{
    setlocale(LC_ALL, "RUS");
    field f(Mines);
    while (f.getLife() == true || f.getWin() == false)
    {
        f.print();
        uint8_t temp;
        size_t tempX, tempY;
        std::cout << "Выберите действие \n1 - открыть клетку \n2 - поставить флаг\n";
        std::cin >> temp;
        std::cout << "Введите координаты X и Y\n";
        std::cin >> tempX >> tempY;
        if (temp == 1)
            f.openRecursive(tempX, tempY);
        if (temp == 2)
            f.setFlag(tempX, tempY);
        else throw("Неверный аргумент");
        system("CLS");
    }
}
