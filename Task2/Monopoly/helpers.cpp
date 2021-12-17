#include <sstream>
#include <cstring>
#include <iostream>

#include "helpers.h"

using namespace std;

string const& CSVRow::operator[](size_t index) const
{
    return m_data[index];
}

size_t CSVRow::size() const
{
    return m_data.size();
}

void CSVRow::readNextRow(istream& str)
{
    string line;
    getline(str, line);

    stringstream lineStream(line);
    string cell;

    m_data.clear();
    while(getline(lineStream, cell, ';'))
    {
        m_data.push_back(cell);
    }
    if (!lineStream && cell.empty())
    {
        m_data.push_back("");
    }
}

istream& operator>>(istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

void initializeSpaces(Space spaces[])
{
    std::ifstream file("data/spaces.csv");
    CSVRow row;
    int rowindex = -1;
    while(file >> row)
    {
        if (rowindex >= 0)
        {
            int id = atoi(row[0].c_str());
            string name = row[1].c_str();
            string type = row[2].c_str();
            string actionText = row[3].c_str();
            spaces[rowindex].setId(id);
            spaces[rowindex].setName(name);
            spaces[rowindex].setType(type);
            spaces[rowindex].setActionText(actionText);
            spaces[rowindex].setOwner(-1);
            spaces[rowindex].setBuyingCost(atoi(row[4].c_str()));
            spaces[rowindex].setRent(atoi(row[6].c_str()));
            spaces[rowindex].setTax(atoi(row[12].c_str()));
        }
        rowindex++;
    }
}

void printState(Space spaces[], Player players[])
{
    cout << endl;
    for(int p = 0; p < 2; p++)
    {
        cout << "PLAYER " << p + 1 << "  POS: ";
        if (players[p].getLocation() >= 10)
            cout << players[p].getLocation();
        else
            cout << " " << players[p].getLocation();
        cout << "  $" << players[p].getMoney() << "  PRP:";
        for(int i = 0; i < 40; i++)
        {
            if (spaces[i].getOwner() == players[p].getId())
            {
                if (spaces[i].getType() == "Property")
                    cout << " " << i << "";
                else if (spaces[i].getType() == "RailRoad")
                    cout << " " << i << "[R]";
                else if (spaces[i].getType() == "Utility")
                    cout << " " << i << "[U]";
            }
        }
        cout << endl;
    }
}

