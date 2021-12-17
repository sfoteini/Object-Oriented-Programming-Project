#ifndef HELPERS_H
#define HELPERS_H

#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

#include "space.h"
#include "player.h"

using namespace std;

class CSVRow
{
public:
    string const& operator[](size_t index) const;
    size_t size() const;
    void readNextRow(istream& str);
private:
    vector<string> m_data;
};

istream& operator>>(istream& str, CSVRow& data);

void initializeSpaces(Space spaces[]);

void printState(Space spaces[], Player players[]);

#endif
