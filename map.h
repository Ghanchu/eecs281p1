// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <vector>
#include <iostream>
#include <string>
#include <utility>
using namespace std;


class Map {
    private:
        int numcolors;
        int width;
        int height;
        pair<int,int> startpos = {-1, -1};
        pair<int,int> goalpos = {-1, -1};
        vector<vector<char> > layout;

    public:
        Map();
        void fillMap();
        bool errCheck(int i, int j, char b);
        void printlayout();
        int colornum ();
        int getwidth();
        int getheight();
        pair<int,int> getstartpos();
        pair<int,int> getgaolpos();
        vector<vector<char > >& getvec();
};


