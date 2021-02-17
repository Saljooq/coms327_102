Name: Saljooq Altaf
Net ID: saltaf

Assignment 1.01

Everthing in the program deals with a struct of room that contains 4 coordinates, x and y coordinates and vetical and horizontal length of the rooms.

There are two basic function outside of main that I utilised to generate the dungeon. 

The first is the makes_sense function that takes the array of rooms and number of Rooms as the argument. It tries to see if the top edge of one room coincides with area occupied with all the other rooms. This it does in four ways - first it check if the y coordinates of the top edge are inside the range+1(1 is added to keep a gap of 1) of the other rooms. If a room is coincides on the y-coordinates, then we check the x-coordinates. This we do in three ways, by checking the left corner, the right corner and the middle. If any of these indicate intersection then the program ends soonafter because it 'doesnt make sense' so the random function will pick some other coordinates. This function also makes sure the rooms are within the grid we have and don't exceed.

The second function simply creates a number that we use as a denominator for calculating max_size of the rooms. The reason for this function was because the program took too long to find coordinates that made sense of number of rooms greater than 8. This restricts the random function a little bit more - hence the not_so_random part of the name.

The main function starts off with creating an array of random number of rooms [6-12] and then using the not_so_rand_roomsize_resizer function to calculate the max length of the rooms. Then it gets into a while true loop, that calculates the coordinates for all the rooms randomly and the make_sense function decideds whether the loop will end.

After than we create a 2D array of char for the dungeon, populate it with spaces and put in the dots where the rooms go. Next, we simply create a path between rooms in adjacent arrays by simply choosing a midpoint based o x-coordinate of one and y-coordinates of the other. Finally we add the upstairs and downstairs randomly [1-3] in the dungeon and finally print out the result.