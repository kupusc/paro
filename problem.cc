#include "problem.hpp"

using namespace std;

namespace problem
{


    Calculator::Calculator()
    {
        cout << "blah" << endl;
    }

    void Calculator::calcForEach(boost::function<int(int)> convert, std::vector<int> &data)
    {
        for(std::vector<int>::iterator i = data.begin(); data.end() != i; ++i)
        {
            *i = convert(*i);
        }
    }

}
