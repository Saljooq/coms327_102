Name: Saljooq Altaf
Net ID: saltaf

Assignment 1.02

The main begins by checking if there is a load switch ("--load"), and if there is it loads all the data onto the grid of hardness and the variables that were initially in the file.

The main uses data uploaded in load to populate the grid, first with floors, then with stairs, next with corridors  wherever hardness is zero and no stairs or floors exist.

This update adds a few new variables to the main to make sure data from the loaded file makes into the saved file.

If there isn't a load switch, it processes the program like usual and generates a random dungeon. The only addition is it checks if there is a room available from top and places the PC coordinates wherever it is found.

The print function remains intact, and it functions regardless of the load switch. This has been updated to include PC position.

The main ends with checking for the save switch ("--save") and if its found, it saves all the data to recreate the dungeon in the binary file.
