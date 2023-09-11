// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725


#include <iostream>

#include "map.h"
using namespace std;

Map::Map() {
    
}

void Map::fillMap() {
        cin >> numcolors >> height >> width;
        string junk;
        getline(cin, junk);
        getline(cin, junk);
        while(junk[0] == '/') {
            getline(cin, junk);
        }

        if(width < 1 || height <1) {
            cerr << "The width or height of the provided map are too small, and consequently invalid" << '\n';
            exit(1);
        }

        if(numcolors < 0 || numcolors > 26) {
            cerr << "Too many or too little colors, please try again" << '\n';
            exit(1);
        }
        layout.reserve(height);
        vector<string> stuff;
        stuff.resize(height);
        stuff[0] = junk;
        for(int i = 1; getline(cin, junk); i++) {
            stuff[i] = junk;
        }
        for(int i = 0; i<height; i++) {
            vector<char> temp;
            temp.reserve(width);
            for(int j = 0; j<width; j++) {
                char c = stuff[i][j];
                if(!errCheck(i,j, c)) {
                    cerr << "There was an error with the map input" << '\n';
                    exit(1);
                }
                temp.push_back(c);

            }

            layout.push_back(temp);
            
        }

        if(goalpos.first == -1 && goalpos.second == -1) {
            cerr << "This map does not have a provided goal" << '\n';
            exit(1);
        } 

        if(startpos.first == -1 && startpos.second == -1) {
            cerr << "This map does not have a provided entry point" << '\n';
            exit(1);
        } 


            
            
}

bool Map::errCheck(int i, int j, char b) {
    if (isalpha(b)) {
        int number = tolower(b) - 96;
        if (number > numcolors) {
            cerr << "Either a door or button is a color that exceeds what it should" << '\n';
            exit(1);
        }
        return true;
    }
    else if (b == '.' || b == '#' || b == '^') {
        return true;
    }
    else if (b == '@') {
        if (startpos.first == -1 && startpos.second == -1) {
            startpos.first = j;
            startpos.second = i;
            return true;
        }
        else {
            cerr << "There was an error with this map, there were two start positions" << '\n';
            exit(1);
        }
    }
    else if (b == '?') {
        if (goalpos.first == -1 && goalpos.second == -1) {
            goalpos.first = j;
            goalpos.second = i;
            return true;
        }
        else {
            cerr << "There was an error with this map, there were two positions to find in the map" << '\n';
            exit(1);
        }
    }
    return false;
}




void Map::printlayout() {
    for(int i = 0; i<static_cast<int>(layout.size()); i++) {
        for(int j = 0; j<static_cast<int>(layout[i].size()); j++) {
            cout << layout[i][j];
        }

        cout << '\n';
    }
    cout << "These are the goal positions and the end positions" << endl;
    cout << startpos.first << " " << startpos.second << endl;
    cout << goalpos.first << " " << goalpos.second << endl;
}

int Map::colornum() {
    return numcolors;
}

int Map::getheight() {
    return height;
}

int Map::getwidth() {
    return width;
}

pair<int,int> Map::getgaolpos() {
    return goalpos;
}

pair<int,int> Map::getstartpos() {
    return startpos;
}

vector<vector<char> > &Map::getvec() {
    return layout;
}



