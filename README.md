# SoftwareEngineeringProject2
This is a repository created specifically for my second Software Engineering Project
Software Engineering Assignment 2 - Othello

Structure
I used a structure to represent the main elements of the game which will be needed in 
various functions. This includes the board (which i store as a 2-D array), the names of the 
players, their individual scores, who's turn it is, and who's turn it isn't. The who's turn
it isnt part may seem strange at first but is used to make the code more general - functions
like the movechecker don't need to be replicated and customised for each player.

Board
A 2-D array was the obvious choice for storing the boards data as it allows for a clearer 
representation of the board. As the program functionality requires the x-coordinate to be
entered as a letter, i created a function to convert this letter into a number which i 
could use more easily for indexing. I also decremented the y-coordinate to allow me to use
array indexing.

Move checker
The move checker was the most difficult part of the project. Figuring out how to make sure
the move was tricky. I ended up dissecting the checker so it would start at the coords 
entered and then move in eight separate directions - vertical upwards, vertical downwards, 
horizontal left, horizontal right, bottom right diagonal, bottom left diagonal, top left 
diagonal and top right diagonal. In each direction it searches for a counter of the 
same colour. If it finds one, it then checks to see if there is a counter of the opposite 
colour directly beside the postion you want to place the counter. If there is a counter 
of the opposite counter, the move is valid. The function then proceeds to change every
counter between the position you want to place the counter and the closest counter of the 
same colour you found earlier. The counter is then placed in the position you wanted it.

Valid move checker
My valid move checker is essentially the move checker, but without changing the variables
I initially set both coords to zero and iterate through each space on the board.

Score updater
After each turn the score is reset to zero. I then loop through the board and increment 
Player 1's score whenever a 'B' is found in the [ith][jth] position and increment Player 2's
score whenever a 'W' is found
