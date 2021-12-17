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
    if (!line.empty() && line[line.size() - 1] == '\r')
        line.erase(line.size() - 1);

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
