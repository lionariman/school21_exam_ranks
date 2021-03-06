#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset
#include <math.h> // for sqrtf and powf

FILE *file;

int width;
int height;
char background;

char type;
float rec_x;
float rec_y;
float radius;
char color;

char *canvas;

int exec()
{
    int x, y, count;
    float dist;

    if (fscanf(file, "%d %d %c\n", &width, &height, &background) != 3)
        return (0);
    if (width <= 0 || width > 300 || height <= 0 || height > 300)
        return (0);
    if (!(canvas = (char *)malloc(sizeof(char) * (width * height))))
        return (0);

    memset(canvas, background, width * height);

    while ((count = fscanf(file, "%c %f %f %f %c\n", &type, &rec_x, &rec_y, &radius, &color)) == 5)
    {
        if (radius < 0 && (type != 'C' || type != 'c'))
            return (0);
        y = -1;
        while (++y < height)
        {
            x = -1;
            while(++x < width)
            {
                dist = sqrtf(powf(x - rec_x, 2) + powf(y - rec_y, 2));
                if (dist <= radius)
                {
                    if (((radius - dist) < 1 && type == 'c') || (type == 'C'))
                        canvas[y * width + x] = color;
                }
            }
        }
    }
    if (count != EOF)
        return (0);
    count = -1;
    while (++count < height)
    {
        write(1, canvas + (count * width), width);
        write(1, "\n", 1);
    }
    return (1);
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "err_1\n", 7);
        return (1);
    }
    file = fopen(av[1], "r");
    if (!file)
    {
        write(2, "err_2\n", 7);
        return (1);
    }
    if (!exec())
    {
        write(2, "err_3\n", 7);
        return (1);
    }

    fclose(file);
    free(canvas);

    return (0);
}