#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>

struct Grid
{
    const int xSize{41};
    const int ySize{41};
    bool maze[41][41]{{false},{false}};
};

struct Cell
{
    int xpos = 0;
    int ypos = 0;
};

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void dispMaze(Grid grid)
{
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), {0, 0} );

    ShowConsoleCursor(false);
    for(int y = grid.ySize-1; y >= 0; --y)
    {
        for(int i = 0; i <= 40; ++i)
        {
            std::cout << " ";
        }

        for(int x = 0; x < grid.xSize; ++x)
        {
            if(grid.maze[x][y])
                std::cout << "  ";
            else
                std::cout << static_cast<char>(219) << static_cast<char>(219);
        }
        std::cout << '\n';
    }
}

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int getDirection(bool usedDir[4])
{
    int direction = getRandomNumber(0, 3);

    if(!usedDir[direction])
        return direction;
}

void drawMaze(Grid &grid, int x, int y)
{
    dispMaze(grid);

    grid.maze[x][y] = true;
    bool usedDir[4]{false};

    int direction = 0;
    while(true)
    {
        if(usedDir[0] && usedDir[1] && usedDir[2] && usedDir[3])
            return;
        direction = getDirection(usedDir);

        int x1 = x;
        int x2 = x;
        int y1 = y;
        int y2 = y;

        if(direction == 0)
        {
            x1 += 1;
            x2 += 2;
        }

        else if(direction == 1)
        {
            x1 -= 1;
            x2 -= 2;
        }

        else if(direction == 2)
        {
            y1 += 1;
            y2 += 2;
        }

        else if(direction == 3)
        {
            y1 -= 1;
            y2 -= 2;
        }

        usedDir[direction] = true;

        if((x2 <= 0 || x2 >= grid.xSize-1) || (y2 <= 0 || y2 >= grid.ySize-1))
            continue;
        else if(grid.maze[x2][y2])
            continue;

        grid.maze[x1][y1] = true;
        drawMaze(grid, x2, y2);
    }
}

void findStartEnd(Grid &grid)
{
    int start = 0;
    int finish = 0;

    while(!grid.maze[0][start])
    {
        start = getRandomNumber(1, grid.ySize-2);
        if(grid.maze[1][start])
        {
            grid.maze[0][start] = true;
        }
    }
    while(!grid.maze[grid.xSize-1][finish])
    {
        finish = getRandomNumber(1, grid.ySize-2);
        if(grid.maze[grid.xSize-2][finish])
        {
            grid.maze[grid.xSize-1][finish] = true;
        }
    }
}

int main()
{
    char x;
    std::cin >> x;

    srand(time(0));
    Grid grid;
    Cell currentCell;

    drawMaze(grid, 1, 1);

    findStartEnd(grid);
    dispMaze(grid);

    return 0;
}
