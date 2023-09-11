// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <iostream>
#include "player.h"
using namespace std;


Player::Player(pair<int,int> startpos, int height, int width, int numcolors, int stackqueue, int printer, Map &m) {
            state = vector<vector<vector<char>>>(numcolors + 1, vector<vector<char>>(height, vector<char>(width, '-')));
            mode = stackqueue;
            printmode = printer;
            search_container.push_back({0, startpos.first, startpos.second});
            current.reserve(3);
            current = {-1,-1,-1};
            goal.reserve(3);
            start = startpos;
            thing.reserve(numcolors);
            thing = m.getvec();
            this->height = height;
            this->width = width;
            
}

void Player::algo() {
    vector<int> compare = {-1,-1,-1};
    while(!search_container.empty()  && !done) {
        
        if(current == compare) {
            state[0][start.second][start.first] = '@';
        }
        if(mode == 1) {
            current = search_container.back();
            search_container.pop_back();
            currentcolor = current[0];
        }

        else {
            current = search_container.front();
            search_container.pop_front();
            currentcolor = current[0]; 
        }

        int y = current[2];
        int x = current[1];
        
        
        char c = thing[y][x];
        if(isalpha(c) && islower(c) && c-96!=currentcolor) {
            discoverneighbors(y, x, c-96, 'B');
            continue;
        }
 
        if(c == '^' && currentcolor != 0) {
            discoverneighbors(y, x, 0, 'L');
            continue;
        }

        discoverneighbors(y - 1, x, currentcolor, 'S');
        discoverneighbors(y, x + 1, currentcolor, 'E');
        discoverneighbors(y + 1, x, currentcolor, 'N');
        discoverneighbors(y, x - 1, currentcolor, 'W');
    }

    if(done == false) {
        cout << "No solution." << '\n' << "Discovered:"<< '\n';
        int n = static_cast<int>(thing.size());
        int m = static_cast<int>(thing[0].size());
        int o = static_cast<int>(state.size());
        for(int i = 0; i<n; i++) {
            for(int j = 0; j<m; j++) {
                bool found = false;
                for(int k = 0; k<o; k++) {
                    if(state[k][i][j] != '-') {
                        found = true;
                    }
                }

                if(found) {
                    cout << thing[i][j];
                }

                else {
                    cout << '#';
                }

            }

            cout << '\n';
        }

        

        
        
    }

    
}



void Player::discoverneighbors(int row, int column, int color, char e) {
    if(row < 0 || row > height - 1 || column < 0 || column > width - 1) return;
    if(state[color][row][column] != '-') {
        return;
    }
    char c = thing[row][column];
    if(c == '#') return;
    if(c == '?') {
        goal[0] = color;
        goal[1] = column;
        goal[2] = row;
        search_container.push_back({color, column, row});
        done = true;
        return;
    }
    if(isupper(c)) {
        if(c-64 != currentcolor) {
            return;
        }
    }
    

    if(color != currentcolor) {
        char c;
        if(currentcolor == 0) {
            c = '^';
        }

        else {
            c = static_cast<char>(currentcolor + 96);
        }

 
        
        state[color][row][column] = c;
        search_container.push_back({color, column, row});
        return; 
    }

   state[color][row][column] = e;
    search_container.push_back({color, column, row});
    


}

void Player::printmap() {
    int n = static_cast<int>(state.size());
    int m = static_cast<int>(state[0].size());
    int o = static_cast<int>(state[0][0].size());
    for(int i = 0; i<n; i++) {
        if(i == 0) {
            cout << "// color ^" << '\n';
        }

        else {
            cout << "// color " << static_cast<char>(i + 96) << '\n';
        }
        for(int j = 0; j<m; j++) {
            for(int k = 0; k<o; k++) {
                char c = state[i][j][k];
                if(c=='.' || c == '#') {
                    cout << c;
                    continue;
                }
                if(c == '^') {
                    if(i == 0) {
                        cout << '.';
                    }

                    else {
                        cout << c;
                    }
                }

                
                    if(isupper(c)) {
                        if(static_cast<int>(c) - 64 == i) {
                            cout << '.';
                            continue;
                        }

                        else {
                            cout << c;
                            continue;
                        }
                    }

                    else {
                        if(static_cast<int>(c) - 96 == i) {
                        cout << '.';
                        continue;
                    }

                    else {
                        cout << c;
                        continue;
                    }
                    }
                    
                


                
                    cout << c;
                    continue;
                
            }

            

            cout << '\n';
        }
    }
}


void Player::backtrace() {
    back.push_back({goal[0], goal[1], goal[2]});
    bool meme = true;
    vector<int> temp;
    temp.reserve(3);
    while(meme) {
        temp.reserve(3);
        char c = state[current[0]][current[2]][current[1]];
        if(c == '@') {
            back.push_back(current);
            meme = false;
            break;
        }
        if(c == 'W') {
            back.push_back(current);
            current = {current[0], current[1]+1, current[2]};

        }

        else if(c == 'E') {
            back.push_back(current);
            current = {current[0], current[1]-1, current[2]};
        }

        else if(c == 'S') {
            back.push_back(current);
            current = {current[0], current[1], current[2]+1};
        }

        else if(c == 'N') {
            back.push_back(current);
            current = {current[0], current[1], current[2]-1};
        }

        else if(c == '^') {
            back.push_back(current);
            current = {0, current[1], current[2]};

        }

        else if(isalpha(c)) {
            int number = static_cast<int>(c) - 96;
            back.push_back(current);
            current = {number, current[1], current[2]};
        }
        
        

        

        



        
    
    }

    
}

void Player::printlist() {
    vector<int> temp;
    temp.reserve(3);
    while(!back.empty()) {
        
        temp = back.back();
        back.pop_back();
        if(temp[0] == 0) {
            cout << "(^, (" << temp[2] << ", " << temp[1] << "))";
        }

        else {
            char c = static_cast<char>(temp[0] + 96);
            cout << "(" << c << ", (" << temp[2] << ", " << temp[1] << "))";
        }
        cout << '\n';
    }
}

bool Player::returndone() {
    return done;
}

void Player::mapprint() {
    int n = static_cast<int>(state.size());
    state.erase(state.begin(), state.end());
    state.resize(n, thing);
    for(int i = 1; i<n; i++) {
        state[i][start.second][start.first] = '.';
    }
    
    int prevcolor = -1;
    vector<int> temp;
    temp.reserve(3);
    while(!back.empty()) {
        
        temp = back.back();
        back.pop_back();
        currentcolor = temp[0];
        
        char c = thing[temp[2]][temp[1]];
        if(isalpha(c) && islower(c)) {
            if(currentcolor == 0) {
                state[currentcolor][temp[2]][temp[1]] = '%';
            }

            else {
                char compare = static_cast<char>(currentcolor + 96);
                if(compare == c) {
                    if(prevcolor == currentcolor) {
                        state[currentcolor][temp[2]][temp[1]] = '+';
                    }
                    else {
                        state[currentcolor][temp[2]][temp[1]] = '@';
                    }
                    
                }

                else {
                    state[currentcolor][temp[2]][temp[1]] = '%';
                }
            }
        }

        else if(c == '@') {
            if(currentcolor != 0) {
                state[currentcolor][temp[2]][temp[1]] = '+';
            }
        }

        else if(c == '^') {
            if(currentcolor == 0) {
                if(prevcolor == currentcolor) {
                    state[currentcolor][temp[2]][temp[1]] = '+'; 
                }
                
                else {
                    state[currentcolor][temp[2]][temp[1]] = '@';
                }
            }

            else {
                state[currentcolor][temp[2]][temp[1]] = '%';
            }
        }

        else if(c == '?') {
            state[currentcolor][temp[2]][temp[1]] = '?';
        }

        else {
            state[currentcolor][temp[2]][temp[1]] = '+';
        }

        prevcolor = currentcolor;
        

    }

    

    printmap();
}







