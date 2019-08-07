#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<algorithm>

enum class State {kEmpty, kObstacle, kStart, kFinish, kClose, kPath};

int delta[4][2] {{-1,0},{1,0},{0,1},{0,-1}};

std::vector<State> ParseLine(std::string &sline)
{
    std::vector<State> result;
    int n;
    char c;
    std::istringstream slinestream(sline);
    while(slinestream >> n >> c)
    {
        if (n == 0)
        {
            result.push_back(State::kEmpty);
        }else
        {
            result.push_back(State::kObstacle);
        }
        
    }
    return result;
}

std::vector<std::vector<State>> ReadBoardFile(std::string filepath)
{
    std::ifstream my_file(filepath);
    std::vector<std::vector<State>> board{};

    if (my_file)
    {
        std::string line;
        while(getline(my_file, line))
        {
            board.push_back(ParseLine(line));
        }
    }

    return board;
}

bool Compare(const std::vector<int> a, const std::vector<int> b)
{
    return (a[2] + a[3]) > (b[2] + b[3]);
}

void OpenSorting(std::vector<std::vector<int>>* v)
{  
    return std::sort(v->begin(), v->end(), Compare);
}

int Heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x1-x2) + std::abs(y1-y2);
}

bool ValidCell(int x, int y, std::vector<std::vector<State>>& grid )
{
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && grid[0].size());
    if (on_grid_x && on_grid_y)
    {
        return grid[x][y] == State::kEmpty;
    }
    return false;
}


void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>>& Open, std::vector<std::vector<State>>& grid)
{
    Open.push_back(std::vector<int>{x,y,g,h});
    grid[x][y] = State::kClose;
}

void ExpandSearch(std::vector<int>& current, std::vector<std::vector<int>>& Open, std::vector<std::vector<State>>& grid, int goal[2])
{
    int x = current[0];
    int y = current[1];
    int g = current[2];

    for(int i = 0; i<4; i++)
    {
        int x1 = x + delta[i][0];
        int y1 = y + delta[i][1];
        
        if(ValidCell(x1, y1, grid))
        {
            int g1 = g+1;
            int h1 = Heuristic(x1, y1, goal[0], goal[1]);
            AddToOpen(x1,y1,g1,h1,Open,grid);
        }
    }
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid, int init[2], int goal[2])
{
    std::vector<std::vector<int>> Open{};

    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x,y,goal[0],goal[1]);

    AddToOpen(x,y,g,h,Open,grid);

    while (Open.size() > 0)
    {
        OpenSorting(&Open);
        auto cell = Open.back();
        Open.pop_back();
        int x = cell[0];
        int y = cell[1];
        

        grid[x][y] = State::kPath;

        if (x == goal[0] && y == goal[1])
        {
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;

            return grid;
        }
        ExpandSearch(cell, Open, grid, goal);
        
    }
    

    std::cout << "Path Not Found" << "\n";
    return std::vector<std::vector<State>>{};
}

std::string CellString(State cellState)
{
    switch(cellState)
    {
        case State::kObstacle:
            return "X   ";
            break;
        case State::kPath:
            return "P   ";
            break;
        case State::kStart:
            return "S   ";
            break;
        case State::kFinish:
            return "F   ";
            break;
        default:
            return "0   ";
    }
}

void PrintBoard(const std::vector<std::vector<State>>& board)
{
    for(std::vector<State> row : board)
    {
        for(State cell : row)
        {
            std::cout << CellString(cell) << " ";
        }
        std::cout << "\n";
    }
}


int main()
{
    int init[2]{0,0},goal[2]{4,5};

    auto fullboard = ReadBoardFile("1.board");
    //PrintBoard(fullboard);
    auto solution = Search(fullboard, init, goal);
    PrintBoard(solution);

    return 0;
}