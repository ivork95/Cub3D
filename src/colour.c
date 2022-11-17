#include <stdio.h>

typedef union u_rgba
{
    unsigned int rgba;
    struct
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;    
    };
}           t_rgba;

int main()
{
    t_rgba colour;
    colour.rgba = 0x01003204;
    printf("%d, %d, %d %d\n", colour.r, colour.g, colour.b, colour.a);
    return(0);
}