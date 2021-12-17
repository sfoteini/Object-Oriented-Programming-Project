#ifndef CSVROW_H
#define CSVROW_H

#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

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

#endif // CSVROW_H
