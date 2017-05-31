#include <graphics.h>
#include <bitmap_image.hpp>
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>
#define infinity 9999

///AUTHOR : SHENI HAMITAJ

//! map = "map.bmp"
//! koordinatlar = "kod.txt"
//! kod = "sehirkod.txt"
//! mesafe = "sehirmesafe.txt"

int path[10][1]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
int b=0;

int howManyCities()
{
    int many=0;
    FILE *file;

    if ((file = fopen("sehirkod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                while(fscanf(file, "%s", str)!=EOF)
                {
                    many++;
                }
            }

        }
        fclose(file);

    return many;
}

int cityID(char cityName[])
{
    FILE *file;

        if ((file = fopen("sehirkod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int i;
                char city[20];
                while(fscanf(file, "%s", str)!=EOF)
                {
                           const char s[2] = "-";
                           char *token;

                        token = strtok(str, s);
                        strcpy(city, token);
                        token = strtok(NULL, s);
                        i=atoi(token);
                             if(strcmp(cityName, city)==0)
                            {
                                return i;
                            }
                }

            }

        }
        fclose(file);
}

const char * IDcity(int id)
{
    FILE *file;

        if ((file = fopen("sehirkod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int i;
                char city[20];
                while(fscanf(file, "%s", str)!=EOF)
                {
                           const char s[2] = "-";
                           char *token;

                        token = strtok(str, s);
                        strcpy(city, token);
                        token = strtok(NULL, s);
                        i=atoi(token);

                        if(id==i)
                        {
                            return city;
                        }
                }

            }

        }
        fclose(file);
}

void savePath(int previous[], int city1, int city2)
{
    if (previous[city1]==-1) //! if city1 is -1 then something went wrong, terminate the function
        return;
    if(city2!=-1) //! if city2 is not -1 it means that the cities are being processed, save to path array
    {
        path[b][0] = city1+1;
        b++;
    }
    savePath(previous, previous[city1], city2); //! do a recursive call but now we are located in the second (third,fourth ...) city in the path
                                                //! because in this array the values and the index'es are connected and showing each-other
    const char* helper = IDcity(city1+1);
    char ct1[30];
    strcpy(ct1,helper);
    printf("%s ", ct1); //! by putting printf after the recursive call, it means that there will be a reverse print of the cities
                        //! because the previous array
}

int showWay(int dist[], int n, int previous[],int city1, int city2)
{
    int i;
    char first[20];
    char second[20];

    printf("City \t\t\t\t Distance  \t\tPath");
    for (i = 0; i < howManyCities(); i++)
    {
        if(city2==-1) //! if all the paths are being processed , don't change the path array, just print the shortest paths
        {
            const char* helper = IDcity(city1);
            strcpy(first,helper);

            helper = IDcity(i+1);
            strcpy(second,helper);

            printf("\n%s ->   %s\t\t %d km(s)\t\t%s ", first, second, dist[i], first);
            savePath(previous, i,-1);
        }
        else
        {
            if(city2==i+1) //! if the city2 is equal to the city being processed in the loop save its path and print it
            {
                const char* helper = IDcity(city1);
                strcpy(first,helper);

                helper = IDcity(i+1);
                strcpy(second,helper);

                printf("\n%s ->   %s\t %d km(s)\t\t%s ", first, second, dist[i], first);
                savePath(previous, i,city2);
            }
        }

    }
}

void paintonMap(int path[10][1])
{
        int numberofCities=howManyCities();
        int info[numberofCities][3];
    FILE *file;

        if ((file = fopen("kod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int x,y,i,help1,help2;
                help1=help2=0;
                char city[20];
                while(fscanf(file, "%s", str)!=EOF)
                {
                    x=atoi(str);

                    if (fscanf(file, "%s", str)!=EOF)
                    {
                        y = atoi(str);

                    }
                   if (fscanf(file, "%s", str)!=EOF)
                    {
                           const char s[2] = "-";
                           char *token;

                        token = strtok(str, s);
                        strcpy(city, token);
                        token = strtok(NULL, s);
                        i=atoi(token);
                    }

                    info[help1][help2]=x;
                    help2++;
                    info[help1][help2]=y;
                    help2++;
                    info[help1][help2]=i;
                    help1++;
                    help2=0;

                }

            }

        }
        fclose(file);


    int i ,j,x1,y1;

    i=0;
    j=0;
    int coords[10][2];
    for (int j=0; j<10;j++)
    {
        coords[j][0]=0;
        coords[j][1]=0;
    }

    while(path[i][0]!=0)
    {
        for(int j=0; j<numberofCities;j++)
        {
            if(info[j][2]==path[i][0])
            {
                x1=info[j][0];
                y1=info[j][1];
            }
        }
        i++;
        coords[j][0]=x1;
        coords[j][1]=y1;
        j++;
    }

    for ( j=0; j<10;j++)
    {
        if(coords[j+1][0] != 0)
        {
            setcolor(3);
            line(coords[j][0]+10,coords[j][1]+102,coords[j+1][0]+10,coords[j+1][1]+102);
            setcolor(13);
            line(coords[j][0]+8,coords[j][1]+100,coords[j+1][0]+8,coords[j+1][1]+100);
            setcolor(2);
            line(coords[j][0]+6,coords[j][1]+98,coords[j+1][0]+6,coords[j+1][1]+98);
        }
        if(coords[j+1][0] == 0)
            break;

    }


}

void hintbar(char *hints, int col) /// reset and write hints into hint-bar
{
    setfillstyle(SOLID_FILL, WHITE);
    bar(400,20,800,80); // reset white bar
    setbkcolor(WHITE);
    setcolor(0);
    outtextxy(410,40,hints);
    setfillstyle(SOLID_FILL,col);
    bar(760,40,780,60);
}

int rgb_tographicsColor(int red, int green , int blue) /// color conversions, used to import the map
{

    if(red == 0 && green ==0 && blue == 0)
    return 0;

    if(red == 0 && green ==0 && blue == 255)
    return 1;

    if(red == 0 && green ==128 && blue == 0)
    return 2;

    if(red == 0 && green ==128 && blue == 128)
    return 3;

    if(red == 128 && green ==0 && blue == 0)
    return 4;

    if(red == 128 && green ==0 && blue == 128)
    return 5;

    if(red == 128 && green ==128 && blue == 0)
    return 6;

    if(red == 192 && green ==192 && blue == 192)
    return 7;

    if(red == 128 && green ==128 && blue == 128)
    return 8;

    if(red == 128 && green ==255 && blue == 255)
    return 9;

    if(red == 128 && green ==255 && blue == 128)
    return 10;

    if(red == 128 && green ==255 && blue == 255)
    return 11;

    if(red == 255 && green ==128 && blue == 128)
    return 12;

    if(red == 255 && green ==128 && blue == 255)
    return 13;

    if(red == 255 && green ==255 && blue == 0)
    return 14;

    if(red == 255 && green ==255 && blue == 255)
    return 15;

    return 404; //!on default return 404 (debug)

}

void mapWindow()
{
    setfillstyle(SOLID_FILL, 8);
    bar(3,3,1200,700); // whole window in dark grey
    setfillstyle(SOLID_FILL, 15);
    int i,j,o;
    setcolor(15);

    ///BUILD THE INTERFACE
    setcolor(7);

        // OPENING ANIMATION
                o=70;
                for(i=9; i<13;i++)
                {
                    setfillstyle(SOLID_FILL, i);
                    bar(378-o,470-o,830+o,330+o);
                    o+=70;
                    delay(333);
                }

                setfillstyle(SOLID_FILL, WHITE);
                bar(8,100,1195,695); // painting window

                for(j=8;j<=1195;j++)
                    {
                    for(i=95,o=695;i<=100, o <=700;i++,o++)
                        {
                        putpixel(j,i,7);
                        putpixel(j,o,7);
                        }
                    }
                for(i=700;i>=95;i--)
                    {
                    for(j=8, o=1200;j>=3, o>=1195;j--, o--)
                        {
                        putpixel(j,i,7);
                        putpixel(o,i,7);
                        }
                    }
                for(i=95;i>=3;i--)
                    {
                    for(j=100, o=1100;j>=95, o>=1095;j--, o--)
                        {
                        putpixel(j,i,7);
                        putpixel(o,i,7);
                        }
                    }
        //END OF ANIMATION


                char patho[199];
                strcpy(patho, "map.bmp");

                if(strcmp(patho,"")!=0)
                {
                    bitmap_image openthis(patho);

                    if (!openthis)
                    {
                       printf("couldn't open the map");
                    }
                    else
                    {
                        int x,y,graph_color;
                        for (y = 0; y < 595; ++y)
                        {
                            for (x = 0; x < 1187; ++x)
                            {
                                rgb_t colour;
                                openthis.get_pixel(x, y, colour);

                                graph_color = rgb_tographicsColor(colour.red , colour.green , colour.blue);
                                if(graph_color == 404)
                                {
                                        graph_color = 0;
                                }

                                if(getpixel(x+8,y+100) != graph_color)
                                    putpixel(x+8,y+100,graph_color);

                }
            }

        }
    }

/// end of the map
hintbar("Welcome to mapNavigation, select your location", 0);
//!start opening files and putting cities over the map

        int numberofCities=howManyCities();
        int info[numberofCities][3];
    FILE *file;

        if ((file = fopen("kod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int x,y,i,help1,help2;
                help1=help2=0;
                char city[20];
                while(fscanf(file, "%s", str)!=EOF)
                {
                    x=atoi(str);

                    if (fscanf(file, "%s", str)!=EOF)
                    {
                        y = atoi(str);

                    }
                   if (fscanf(file, "%s", str)!=EOF)
                    {
                           const char s[2] = "-";
                           char *token;

                        token = strtok(str, s);
                        strcpy(city, token);
                        token = strtok(NULL, s);
                        i=atoi(token);
                    }

                    info[help1][help2]=x;
                    help2++;
                    info[help1][help2]=y;
                    help2++;
                    info[help1][help2]=i;
                    help1++;
                    help2=0;

                }

            }

        }
        fclose(file);

        //! make city connections
        int c1,c2;

        int costs[numberofCities][numberofCities] ;

        for (c1=0;c1<numberofCities;c1++)

        {
            for(c2=0;c2<numberofCities; c2++)
            {
                costs[c1][c2]=0;
            }
        }


            if ((file = fopen("sehirmesafe.txt", "r")) == NULL)
            {
                printf("Error! opening file");
            }
            else
            {
                char str[99];

                if (file)
                {
                    int x,y,i,j,f;
                    char first[20];
                    char second[20];
                    char dist[5];


                    while(fscanf(file, "%s", str)!=EOF)
                    {
                        for(j=0;j<20;j++)
                        {
                            first[j]='\0';
                            second[j]='\0';

                                if(j<5)
                                    dist[j]='\0';
                        }
                        j=0;
                        while(1)
                        {
                            if(!isalpha(str[j]))
                                break;

                            first[j]=str[j];
                            j++;
                        }
                        j++;
                        f=0;
                        while(1)
                        {
                            if(!isalpha(str[j]))
                                break;

                            second[f]=str[j];
                            j++;
                            f++;
                        }
                        j++;
                        f=0;
                        while(1)
                        {
                            if(str[j]=='\0')
                                break;

                            dist[f]=str[j];
                            j++;
                            f++;
                        }
                        x=cityID(first);
                        y=cityID(second);
                        i=atoi(dist);

                       costs[x-1][y-1]=i;

                    }
                }
            }
            fclose(file);

            for (c1=0; c1<numberofCities;c1++)
            {
                for(c2=0; c2<numberofCities;c2++)
                {
                    if(costs[c1][c2] != 0)//! they have connection
                    {
                        setcolor(2) , line(info[c1][0]+8,info[c1][1]+100,info[c2][0]+8,info[c2][1]+100);
                    }
                }
            }

        setcolor(15), setbkcolor(0);

        if ((file = fopen("kod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int x,y,i;
                char city[20];
                while(fscanf(file, "%s", str)!=EOF)
                {
                    x=atoi(str);

                    if (fscanf(file, "%s", str)!=EOF)
                    {
                        y = atoi(str);

                    }
                   if (fscanf(file, "%s", str)!=EOF)
                    {
                           const char s[2] = "-";
                           char *token;

                           token = strtok(str, s);

                            strcpy(city, token);
                            token = strtok(NULL, s);
                            i=atoi(token);

                    }

                    outtextxy(x+8,y+100,city);

                }

            }

        }
        fclose(file);


}

void dijkstra(int city1, int city2)
{
    int c1,c2;
    int numberofCities=howManyCities();
    int costs[numberofCities][numberofCities] ;

    for (c1=0;c1<numberofCities;c1++)

    {
        for(c2=0;c2<numberofCities; c2++)
        {
            costs[c1][c2]=0;
        }
    }

            FILE *file;

        if ((file = fopen("sehirmesafe.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int x,y,i,j,f;
                char first[20];
                char second[20];
                char dist[5];
                while(fscanf(file, "%s", str)!=EOF)
                {
                        for(j=0;j<20;j++)
                        {
                            first[j]='\0';
                            second[j]='\0';

                                if(j<5)
                                    dist[j]='\0';
                        }
                        j=0;
                        while(1)
                        {
                            if(!isalpha(str[j]))
                                break;

                            first[j]=str[j];
                            j++;
                        }
                        j++;
                        f=0;
                        while(1)
                        {
                            if(!isalpha(str[j]))
                                break;

                            second[f]=str[j];
                            j++;
                            f++;
                        }
                        j++;
                        f=0;
                        while(1)
                        {
                            if(str[j]=='\0')
                                break;

                            dist[f]=str[j];
                            j++;
                            f++;
                        }
                        x=cityID(first);
                        y=cityID(second);
                        i=atoi(dist);

                       costs[x-1][y-1]=i;

                    }
            }
        }
        fclose(file);




    for (c1=0;c1<numberofCities;c1++)
    {
        for(c2=0;c2<numberofCities; c2++)
        {
            if(costs[c1][c2] != 0)
                costs[c2][c1]=costs[c1][c2]; //! from city 1 to city 2 is the same as from city 1 to city 2
        }
    }
//! djikstra starting
    int C = howManyCities();//! hold the value for the number of the cities in the txt file
    int cities;
    int distance[C]; //! This array will hold the shortest distance from city1 to other cities
    bool connection[C]; //! connection is a bool array which holds the information if the city has been processed or not
    int previous[C]; //! previous is an array to hold the dedicated path from city1 to city2
    previous[city1-1]=-1; //! put the city1 value to -1

    for (int i = 0; i < C; i++)
        distance[i] = infinity, connection[i] = false; //! the distance array is unprocessed so it will have infinity distances from the city1
                                                        //! the connection array is also unprocessed so it will have false values for all the cities

    distance[city1-1] = 0; //! the value for the city1 will be 0km

    //!  This loop is the main function , as it finds the shortest paths from city1
    for (cities = 0; cities < C-1; cities++)
    {
        int minimum = infinity;
        int vertex, min_index,i;

        for (vertex = 0; vertex < C; vertex++) //! find the minimum distance vertex from the set of cities that aren't processed.
            if (connection[vertex] == false && distance[vertex] <= minimum)
                minimum = distance[vertex], min_index = vertex;

        int u = min_index; //! integer U will be equal to city1 in the first loop

        connection[u] = true; //! After throwing the value of the distance, the city connection is marked as processed

        //! Update the distance of the other cities from the picked city(vertex).
        for (vertex = 0; vertex < C; vertex++)

            if (!connection[vertex] && costs[u][vertex]  && distance[u]+costs[u][vertex] < distance[vertex])
            {
                previous[vertex]=u; //! here the shortest path is kept in the "previous" array but not in a ordered way
                distance[vertex] = distance[u] + costs[u][vertex];
            }
    }


    showWay(distance, C, previous, city1,-1); //! this shows the shortest path from the city selected to other cities
    puts("\n\n***\n");
    showWay(distance, C, previous, city1,city2); //! here we show only the path from city1 to city2
    path[b][0]=city1; //! the first city in the path will always be the city selected (city1)
    b=0; //! reset the index of the path array
    paintonMap(path); //! show the way from city1 to city2
    for(int i =0; i<10;i++)
            path[i][0]=0; //! reset the path to empty so it can be used again
}

void mouseclick()
{
    int numberofCities=howManyCities();
        int info[numberofCities][3];
    FILE *file;

        if ((file = fopen("kod.txt", "r")) == NULL)
        {
            printf("Error! opening file");
        }
        else
        {
            char str[99];

            if (file)
            {
                int x,y,i,help1,help2;
                help1=help2=0;
                char city[20];
                while(fscanf(file, "%s", str)!=EOF)
                {
                    x=atoi(str);

                    if (fscanf(file, "%s", str)!=EOF)
                    {
                        y = atoi(str);

                    }
                   if (fscanf(file, "%s", str)!=EOF)
                    {
                           const char s[2] = "-";
                           char *token;

                           token = strtok(str, s);

                            strcpy(city, token);
                            token = strtok(NULL, s);
                            i=atoi(token);

                    }

                    info[help1][help2]=x;
                    help2++;
                    info[help1][help2]=y;
                    help2++;
                    info[help1][help2]=i;
                    help1++;
                    help2=0;

                }

            }

        }
        fclose(file);

        //!mouse clicking over cities
    int xcoord,ycoord,i;
    int city1, city2;
    city1=city2=404;
    while(1)
    {
        delay(10);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(20);

        if(ismouseclick(WM_LBUTTONDOWN)) ///Detects Mouse Left-Click
            {
                xcoord = mousex(); ycoord = mousey();//gets x and y of mouse position
                clearmouseclick(WM_LBUTTONDOWN);

                for(i=0;i<numberofCities;i++)
                {
                    if((xcoord>info[i][0]+8 && xcoord<(info[i][0]+58)) && (ycoord>info[i][1]+97 && ycoord < (info[i][1]+113)))
                    {
                        city1= info[i][2];
                        char source[100];
                        strcpy(source,IDcity(city1));
                        strcat(source," was chosen as current location");
                        hintbar(source, 2);
                    }
                }

            }
        if (city1!=404)
            break;
    }

    while(1)
    {
        delay(10);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(20);

        if(ismouseclick(WM_LBUTTONDOWN)) ///Detects Mouse Left-Click
            {
                xcoord = mousex(); ycoord = mousey();//gets x and y of mouse position
                clearmouseclick(WM_LBUTTONDOWN);

                for(i=0;i<numberofCities;i++)
                {
                    if((xcoord>info[i][0]+8 && xcoord<(info[i][0]+58)) && (ycoord>info[i][1]+97 && ycoord < (info[i][1]+113)))
                    {
                        city2= info[i][2];
                        char destination[100];
                        strcpy(destination,IDcity(city2));
                        strcat(destination," is your destination, routing...");
                        hintbar(destination,2);
                        delay(333);
                    }
                }

            }
        if (city2!=404)
            break;
    }
                dijkstra(city1,city2);
                hintbar("Check Command prompt for full information", 12);

}

int main()
{
    printf("Close this window to terminate the program! \n");
    initwindow(1203, 703,"Navigator",50,5); /// main window : 1203 x 703 , open at point(50,5)
    mapWindow();
    while(1)
    mouseclick();
}
