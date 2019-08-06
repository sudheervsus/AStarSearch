#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>

enum class State {kEmpty, kObstacle};

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

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> InBoard, int init[2], int goal[2])
{
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

    auto solution = Search(fullboard, init, goal);
    PrintBoard(solution);

    return 0;
}