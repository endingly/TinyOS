#include <stdio.h>
#include <stdlib.h>

struct point
{
    double x;
    double y;
};

int main(int argc, char const* argv[])
{
    struct point* test = malloc(sizeof(struct point));
    test->x            = 1.0;
    test->y            = 2.0;

    printf_s("x=%f,y=%f\n", test->x, test->y);
    free(test);
    return 0;
}