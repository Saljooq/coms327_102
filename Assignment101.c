#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROOMS 12
#define MIN_ROOMS 6

#define xlenMax 78
#define ylenMax 19


#define minRoomxlen 4
#define minRoomylen 3

#define maxStairs 3
#define minStairs 1

/*the room is a struct to save the relevant coordinates and leghts of a room*/
typedef struct room
{
	int xloc;
	int yloc;
	int xlen;
	int ylen;
}room;

int makes_sense(room rooms[], int numRooms);
int not_so_rand_roomsize_resizer(int numRooms);

int main(int argc, char* argv[])
{
	int i, j, x, y; //we declare most of the common variables we'll be using late
	
	//we will start out by creating a seed with time-0 to access some randomeness
	srand(time(0));
	
	int numRooms = MIN_ROOMS + (rand() % (MAX_ROOMS - MIN_ROOMS + 1));
	
	room rooms[numRooms];
	
	int resizer = not_so_rand_roomsize_resizer(numRooms);//we use this function to obtain a denominator to limit the size of the rooms
	
	//the if conditions used to obtain the max length of the room help avoid the floating point exception (core dump) later when we use it with modulus later
	int maxRoomxlen = xlenMax / resizer;
	if (maxRoomxlen <= minRoomxlen) maxRoomxlen = minRoomxlen + 1;
	
	
	int maxRoomylen = ylenMax / resizer;
	if (maxRoomylen <= minRoomylen) maxRoomylen = minRoomylen + 1;
	
	//printf("num Rooms = %d\n", numRooms); //uncomment to see num of rooms generated

	//this loop keeps going till random coordinates and lengths are obtained from random function that make sense
	while (1)
	{
		for (i = 0; i < numRooms; i++)
		{
			rooms[i].xloc = rand() % xlenMax;
			rooms[i].yloc = rand() % ylenMax;
			rooms[i].xlen = minRoomxlen + rand() % ((maxRoomxlen) - minRoomxlen);
			rooms[i].ylen = minRoomylen + rand() % ((maxRoomylen) - minRoomylen);
		}
		if (makes_sense(rooms, numRooms)) break;
	}
	
	//the grid below will be use to store all the characters for dungeon
	char grid[xlenMax][ylenMax];
	
	//first we populate the grid with spaces
	for (i = 0; i < xlenMax; i++)
	{
		for (j = 0; j < ylenMax; j++)
		{
			grid[i][j] = ' ';
		}
	}
	//Next we populate the grid with '.' as per the randomised coordinates that made sense that we obtained earlier
	for (x = 0; x < numRooms; x++)
	{
		
		for (i = rooms[x].xloc; i < (rooms[x].xloc + rooms[x].xlen); i++)
		{
			for (j = rooms[x].yloc; j < (rooms[x].yloc + rooms[x].ylen); j++)
			{
				grid[i][j] = '.';
			}
		}
	}
	
	//next we carve out a path between adjacent rooms in which we use the former's x coordinate and latter's y-coordinates to create a mid-point
	for (int x = 0; x < numRooms - 1; x++)
	{
		int middlex = rooms[x].xloc;
		int middley = rooms[x + 1].yloc;
		int i;//i will save the direction of the path
		
		if (rooms[x].yloc > middley) i = 1;
		else i = -1;
		
		//first we go from from midpoint to former room
		for ( j = middley; j != rooms[x].yloc; j += i)
		{
			if (grid[middlex][j] != '.') grid[middlex][j] = '#';
		}
		
		//then we go from midpoint to latter room
		if (rooms[x + 1].xloc > middlex) i = 1;
		else i = -1;
		
		for ( j = middlex; j != rooms[x + 1].xloc; j += i)
		{
			if (grid[j][middley] != '.') grid[j][middley] = '#';
		}
		
	}
	
	
	//here we randomise the upwards and downward staircases and insert them wherever the random coordinates and its horizontal neighbours are part of room
	for (i = 0; i < 2; i++)
	{
		//first iteration adds random number of '<' to the grid, second adds '<'
		char staircase;
		if (i == 0) staircase = '<';
		else staircase = '>';
		
		int numStairs = minStairs + rand() % ((maxStairs) - minStairs);
		
		for (j = 0; j < numStairs; j++)
		{
			//while loops below keeps going till a successfuk coordinate is found	
			while (1)
			{
				x = 1 + (rand() % (xlenMax - 2));//this ensures that we're not on the left or the right edge because the condition below checks horizontal neighbours
				y = (rand() % (ylenMax));

				if (grid[x][y] == '.' && grid[x - 1][y] == '.' && grid[x + 1][y] == '.')
				{
					grid[x][y] = staircase;
					break;
				}
			}
			
			
		}
	}
	//below is where we print out the actual grid
	for (i = 0; i < xlenMax; i++) {printf("-");}
	printf("\n");
	
	for (i = 0; i < ylenMax; i++)
	{
		printf("|");
		for (j = 0; j < xlenMax; j++)
		{
			printf("%c", grid[j][i]);
		}
		printf("|\n");
	}
	
	for (i = 0; i < xlenMax; i++) {printf("-");}
	printf("\n\n\n");
	

	
	return 0;
}
/*The first is the makes_sense function that takes the array of rooms and number of Rooms as the argument. 
It tries to see if the top edge of one room coincides with area occupied with all the other rooms. 
This it does in four ways - first it check if the y coordinates of the top edge are inside 
the range+1(1 is added to keep a gap of 1) of the other rooms. If a room is coincides on
 the y-coordinates, then we check the x-coordinates. This we do in three ways, by checking the left corner, 
 the right corner and the middle. If any of these indicate intersection then the program ends soonafter because 
 it 'doesnt make sense' so the random function will pick some other coordinates. This function also makes sure 
 the rooms are within the grid we have and don't exceed.*/
int makes_sense(room rooms[], int numRooms)
{

	int checker = 1;//this essentially marks whether the program makes any sense, 0 indicates it doesnn't
	
	for (int i = 0; i < numRooms; i++)
	{
		for (int j = 0; j < numRooms; j++)
		{
			if (i != j)
			{
				//first it check if the y coordinates of the top edge are inside the range+1(1 is added to keep a gap of 1) of the other rooms. If a room is coincides on the y-coordinates, then we check the x-coordinates
				if(
				rooms[i].yloc >= rooms[j].yloc &&
				rooms[i].yloc <= (rooms[j].yloc + rooms[j].ylen + 1)
				)
				{
					//If a room is coincides on the y-coordinates, then we check the x-coordinates by checking the left corner, the right corner and the middle.
					if(
					(rooms[i].xloc >= rooms[j].xloc &&//this checks left corner
					rooms[i].xloc <= (rooms[j].xloc + rooms[j].xlen + 1) 
					) || (
					rooms[i].xloc + rooms[i].xlen >= rooms[j].xloc &&//this checks right corner
					rooms[i].xloc + rooms[i].xlen <= (rooms[j].xloc + rooms[j].xlen + 1) 
					) || (
					rooms[i].xloc < rooms[j].xloc &&//this checks middle
					rooms[i].xloc + rooms[i].xlen > (rooms[j].xloc + rooms[j].xlen + 1)
					)
					) checker = 0;
				}
				
				
			}
			
			if (checker == 0) break;//this helps end the program soon if the coordinates don't make sense
			
		}
		
		if (//this condition just makes sure all the coordinates will map the rooms in the available grid
			(rooms[i].xloc + rooms[i].xlen > xlenMax - 1) || 
			(rooms[i].yloc + rooms[i].ylen > ylenMax - 1)
			) checker = 0;
		
		if (checker == 0) break;//this, along with the break above, ensures we swiftly end the program soon if the coordinates don't make sense
	}
	
	return checker;
}

/*The second function simply creates a number that we use as a denominator for calculating max_size of the rooms. 
The reason for this function was because the program took too long to find coordinates that made sense of number 
of rooms greater than 8. This restricts the random function a little bit more - hence the not_so_random part of the name.*/
int not_so_rand_roomsize_resizer(int numRooms)
{
	int roomSizer = (numRooms/2) - 1;

	return roomSizer;
}