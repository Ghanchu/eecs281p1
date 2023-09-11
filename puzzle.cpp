// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725

#include <iostream>
#include <map>
#include <deque>
#include "arguments.h"
#include "player.h"


using namespace std;


int main(int argc, char **argv) {
    Arguments argument;
    argument.fill(argc, argv);
    if(argument.helpstate()) {
        return 0;
    }
    
    Map map;
    map.fillMap();
    Player player(map.getstartpos(), map.getheight(), map.getwidth(), map.colornum(), argument.get_container(), 1, map);
    player.algo();
    player.backtrace();
    if(player.returndone() == true) {
        if(argument.printing() == 0) {
            player.mapprint();
        }
        else {
            player.printlist();
        }
    }
    


    return 0;



    
}