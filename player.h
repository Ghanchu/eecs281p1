// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725


#include <iostream>
#include <deque>
#include <vector>
#include "map.h"



class Player {
    private:
        int mode;
        vector<int> currentstate = {-1, -1, -1};
        vector<vector<vector<char>>> state;
        int printmode;
        deque<vector<int> > search_container;
        bool startdone = true;
        int currentcolor = 0;
        bool done = false;
        vector<int>current;
        vector<int> goal;
        deque<vector<int>> back;
        pair<int,int> start;
        vector<vector<char> > thing;
        int height;
        int width;
        
    public:
        Player(pair<int,int> startpos, int height, int width, int numcolors, int stackqueue, int printer, Map &m);
        void algo();
        void discoverneighbors(int row, int column, int color, char c);
        void printmap();
        void backtrace();
        void printlist();
        bool returndone();
        void mapprint();
    

        



};