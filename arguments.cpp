// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
#include "arguments.h"
#include <iostream>
#include <getopt.h>
#include <cstring>

using namespace std;



int Arguments:: get_container() {
    return deque_type;
}

int Arguments::printing() {
    return print_option;
}

bool Arguments::helpstate() {
    return gethelp;
}

void Arguments::fill(int argc, char **argv) {
    int opt;
    opterr = 0;
    const char* const tinyoptions = "ho:sq";
    const option longoptions[] = {
        {"help", no_argument, nullptr, 'h'},
        {"output", required_argument, nullptr, 'o'},
        {"stack", no_argument, nullptr, 's'},
        {"queue", no_argument, nullptr, 'q'},
        {nullptr, 0, nullptr, '\0'}
    };
    while ((opt = getopt_long(argc, argv, tinyoptions, longoptions, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                cout << "This is the help statement of my own design" << '\n';
                gethelp = true;
                return;
                break;

            case 's':
                if (deque_type == 0) {
                    deque_type = 1;
                    break;
                } else {
                    cerr << "User specified both stack and queue when only one can be used" << '\n';
                    exit(1);
                    break;
                }

            case 'q':
                if (deque_type == 0) {
                    deque_type = 2;
                    break;
                } else {
                    cerr << "User specified both stack and queue when only one can be used" << '\n';
                    exit(1);
                    break;
                }

            case 'o':
                if(optarg == nullptr) {
                    cerr << "output option requires list or map input" << '\n';
                    exit(1);
                    break;
                }
                if(strcmp(optarg, "map") == 0|| strcmp(optarg, "list") == 0) {
                    if(strcmp(optarg, "list") == 0) {
                        print_option = 1;
                    }
                    break;
                }

                else {
                    cerr << "Invalid input, input can be either map or list" << '\n';
                    exit(1);
                    break;
                }
                 
            default:
                cerr << "Invalid option" << endl;
                exit(1);
                break;
        }
    }

    if(deque_type == 0) {
        cout << "--stack or --queue must be specified" << '\n';
        exit(1);
    }
}
