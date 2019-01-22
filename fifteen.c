#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIM_MIN 3
#define DIM_MAX 9

int board[DIM_MAX][DIM_MAX];

int d;

int squl(int a);
void swap(int *a, int *b);

void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    greet();

    init();

    while (true)
    {
        clear();

        draw();

        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        if (won())
        {
            printf("Congratulations!!!\n");
            break;
        }

        printf("Tile to move: ");
        int tile = get_int();
        
        if (tile == 0)
        {
            break;
        }

        fprintf(file, "%i\n", tile);
        fflush(file);

        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        usleep(50000);
    }
    
    fclose(file);

    return 0;
}

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

void init(void)
{
    int f = d - 1;
    int bord = squl(d);
    int t = d % 2;
    if (t == 1)
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
               if (bord >= 2)
               {
                   bord = bord - 1;
                   board[i][j] = bord;
               }
           }
       }
    }
    else
    {
        int w, e, r;
        w = d - 1;
        e = d - 2;
        r = d - 3;
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (bord >= 2)
                {
                    bord = bord - 1;
                    board[i][j] = bord;
                }
            }
        }
        swap(&board[w][e], &board[w][r]);
    }
    board[f][f] = 0;
}

void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != 0)
            {
                printf("%2d  ", board[i][j]);
            }
            else
            {
                printf(" _  ");
            }
            
        }
        printf("\n\n");
    }
}

bool move(int tile)
{
    int p1, p2, e1, e2;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                p1 = i;
                p2 = j;
            }
            if (board[i][j] == 0)
            {
                e1 = i;
                e2 = j;
            }
        }
    }
    int l1, s1, l2, s2;
    l1 = e1 - 1;
    s1 = e2 - 1;
    l2 = e1 + 1;
    s2 = e2 + 1;
    if (board[p1][p2] == board[l1][e2] || board[p1][p2] == board[e1][s1] || board[p1][p2] == board[l2][e2] || board[p1][p2] == board[e1][s2])
    {
        swap(&board[p1][p2], &board[e1][e2]);
        return true;
    }
    else
    {
        return false;
    }
}

bool won(void)
{
    int last = 0;
    int f = d - 1;
    if (board[f][f] == 0)
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
               if (board[i][j] > last)
               {
                   last = board[i][j];
               }
               else
               {
                   return false;
               }
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}



int squl(int a)
{
    int b = a * a;
    return b;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}