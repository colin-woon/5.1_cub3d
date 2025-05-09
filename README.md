
```
git clone --recursive git@github.com:colin-woon/5.1_cub3d.git
```
West = Left
East = Right
# Project Requirements
- Display different wall textures (N,S,E,W)
- Different Tones for floor and ceiling
- Left Right arrow keys allow to look left and right
- WASD for movement

## Parsing Requirements:
- 6 possible characters inside .cub file
	- 0 empty space
	- 1 wall
	- N, S, E, W for player start position and orientation
- Map must be surrounded by walls(1)
- Elements (except for the Map itself) (\<identifier> \<args>) :
	- NO ./path_to_texture
	- SO ./path_to_texture
	- WE ./path_to_texture
	- EA ./path_to_texture
	- F R,G,B (0-255)
	- C R,G,B (0-255)
- Order of contents in the .cub file:
	- each element can be seperated by 1 or more lines
	- map content is always last
	- elements can be in any order
	- each information of an element can be seperated by 1 or more spaces

Example:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Breakdown
- how to read from a file and display texture
- how to display colour


## Execution
- render raycast first
	- init pixels texture?
	- init player variables
	- init raycasting variables
	- run raycasting (will loop window width)
		- calculate the rays from the player position
		- setup DDA
		- perform DDA
		- calculate the line height
		- update pixel textures
	- render frame
		- sets the image frame pixels

player start position
posX
posY

player direction vector (defines the camera direction)
dirX = -1
dirY = 1

camera (should always be perpendicular to the direction)
planeX = 0
planeY = 0.66
FOV depends on ratio between (length of direction:camera plane)

when rotating around with input keys, the values of
dir
plane
will change, but they always remain perpendicular to each other and keep the same length

time and old time, used for FPS, difference between them can determine how much the rays should move when a key is pressed

EVERYTHING IN A LOOP
- use DDA to determine whether hit to a wall or not
- once hit a wall, only calculate its line height
