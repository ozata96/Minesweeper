# Minesweeper
A C++ application that recreates the classic game Minesweeper. The program contains a graphical user interface that can be interacted with using the console. There are two main aspects to the program:
* The GUI Board - varying levels of difficulty
* The recursive flood fill algorithm
 
# The GUI Board
There are three different levels of difficulty: Easy, Medium, and Hard. The different levels of difficulty change the size of the board players interact with. An easy board is 10x6, a medium board is 12x7, and a hard board is 18x9.

# Flood Fill Algorithm
In order to fill up the board and replicate the minesweeper mechanic of revealing empty squares, the flood fill algorithm was used. A player will first input a coordinate. From this coordinate, the program will "flood" all adjacent squares that can be revealed. The recursive flood fill will first check the top left square. If it is a valid empty square with no mines around it then we continue to check that square's top left and so on. Once an adjacent mine is discovered, on the next "top left," then the number of mines is placed in that square. After that we return recursively to the previous square and then check the "top top." This continues on until we return all the way back to the user's initial coordinate. The program then checks that coordinate's "top top." To clarify, each square and it's adjacent squares are recursively checked. Additionally, those adjacent square's adjacent squares are also checked and so on.
Below is an example of how this works within the program and how the coordinates are calculated.

             1    2    3    4    5
          +----+----+----+----+----+            
       A  |      TL   TT   TR                       
          +----+----+----+----+----+         
       B  |      LL        RR                       
          +----+----+----+----+----+
       C  |      BL   BB   BR
          +----+----+----+----+----+
          
         BASE: [1][2] - B3
                                    
         TL: [0][1]   - A2
         TT: [0][2]   - A3
         TR: [0][3]   - A4
    
         BL: [2][1]   - C2
         BB: [2][2]   - C3
         BR: [2][3]   - C4
         
         LL: [1][1]   - B2
         RR: [1][3]   - B4

Additionally, the algorithm will place the number of adjacent mines from on the edges of a cluster of revealed squares, replicating the equivalent mechanic in minesweeper. 

# How to Play
Download the game files and unzip, then run in a C++ environment. To play, users must interact with the console which contains directions.
