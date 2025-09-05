typedef struct stru stru;

typedef void print(stru *ptr);

struct stru {
    print PrintMe;
    int i;
    stru* ptr;
};


