#include <iostream>

const size_t FieldX = 10;
const size_t FieldY = 10;
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
    node Field[FieldX][FieldY];
public:
    field()
    {
        mines = Mines;
        Flags = 0;
        for (uint16_t i = 0; i < mines; i++)
        {
            size_t rx = rand() % FieldX;
            size_t ry = rand() % FieldY;
            if (Field[rx][ry].minesCount != 9)
                Field[rx][ry].minesCount = 9;
        }
    }
    void print()
    {
        std::cout << "Mines:" << mines << " Flags:" << Flags << std::endl;
        std::cout << "*";
        for (int i = 0; i < FieldX; i++) { std::cout << "-"; }
        std::cout << "*" << std::endl;
        for (int i = 0; i < FieldY; i++)
        {
            std::cout << "|";
            for (int j = 0; j < FieldX; j++)
            {
                     if (Field[j][i].minesCount == 9 && Field[j][i].seen == true) std::cout << '*';
                else if (Field[j][i].minesCount >= 1 && Field[j][i].seen == true) std::cout << Field[j][i].minesCount;
                else if (Field[j][i].minesCount == 0 && Field[j][i].seen == true) std::cout << ' ';
                else if (Field[j][i].flag == true) std::cout << 'F';
                else std::cout << "X";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "*";
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
            }
            if (Field[x][y].flag == false)
            {
                Field[x][y].flag = false;
                Flags--;
            }
        }
    }

};


int main()
{
    field f;
    f.print();
}
