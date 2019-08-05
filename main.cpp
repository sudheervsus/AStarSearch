#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>

std::vector<int> ParseLine(std::string &sline)
{
    std::vector<int> result;
    int n;
    char c;
    std::istringstream slinestream(sline);
    while(slinestream >> n >> c)
    {
        result.push_back(n);
    }
    return result;
}

std::vector<std::vector<int>> ReadBoardFile(std::string filepath)
{
    std::ifstream my_file(filepath);
    std::vector<std::vector<int>> board{};

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

void PrintBoard(const std::vector<std::vector<int>>& board)
{
    for(std::vector<int> row : board)
    {
        for(int cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}


int main()
{
    auto fullboard = ReadBoardFile("1.board");
    PrintBoard(fullboard);

    return 0;
}