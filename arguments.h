// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725


class Arguments {
    private:
        bool gethelp = false;
        int deque_type = 0;
        int print_option = 0;
    public:

       
        int get_container();
        int printing();
        void fill(int argc, char **argv);
        bool helpstate();


};