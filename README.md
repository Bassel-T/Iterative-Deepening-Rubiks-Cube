# Iterative-Deepening-Rubiks-Cube

## Usage

`make run START=[StartState]`

To get `StartState`, a given face's "tile order" is read like a book: start top left, read across, including the immovable cube, end in the bottom right. A lowercase character represents the color you see on the given tile (represented by the first character of the color, i.e. w for white).

The cube is assumed to have white opposite to yellow, blue opposite to green, and orange opposite to red. The proper order for these is to:
1. Place the cube such that yellow is on the bottom and white is on top.
2. Point the cube such that the orange face is closest to you.
3. Read the white face.
4. Turn the cube to the blue face and read it.
5. Do the same, but with orange, green, then red.
6. Point the orange face in your direction again, then rotate the cube so it's on top and yellow is facing you.
7. Read the yellow face.

You should end up with something like `yywywwywwroobbgrrobbgoorbggroobggrgogrbrrogbbwyywywwyy` or `ooyrwobwogbwwbgrggrgbroowbbyyrggwwrogwybrrwbyrooyyybyg`.

## The Algorithm

Iterative Deepening is an algorithm that comes Breadth-First-Search (BFS) and Depth-First-Search (DFS). In the algorithm, we run DFS to a limited depth of 1, then 2, then 3, and so on. Because it uses the priority of a DFS, but still scans every item at a depth before going to the next depth, its time complexity is O(b^d), but only uses O(bd) space.

The cube's heuristic function is the 3D manhattan distance of every point from its goal point, though it's divided by 8 to take into account the fact a single turn moves 8 pieces.

## Rubiks Cube

The Rubiks Cube, for anyone unaware of it, is a 3x3 cube with 20 movable tiles. As a result, there can be over 43 quintillion possible (valid) configurations. The initial state can be turned in one of 18 ways, three for each of its six faces: clockwise, counterclockwise, or a 180° turn. After that, I've limited each move to not turn the same one as the previous step, bringing the branching factor down to 15.

This causes a slight problem with this program: My computer isn't fast enough to handle this. It's probably a factor of the large amount of string manipulations (I'm sure there's a more efficient way to do some of this stuff), but running the algorithm basically forces it to never terminate on my current configuration when trying to turn it back to normal.

When tested continuously against a cube 20 turns away from its solved state, the algorithm takes too long to run. However, when running the algorithm on a cube 6 moves away from its solved state, the program manages to terminate within 50k turns. More research is needed for this. I may even return to optimize this in some way.

## Output

Rather than dealing with a clockwise and counterclockwise rotation differently, I treated a CCW rotation as three clockwise rotations. Thus, the output will have a list of moves telling which face to turn and how many times to turn it clockwise. `R3` means turn the red face clockwise three times (or counterclockwise once), while `G2` means turn the green face twice, essentially flipping it 180°.

You'll also see some debug lines every 10,000 iterations. For example:

`10000 (6.25, 4) : bybowrgwgogoobgrbrybwwowwgyogoogrrbrwrywryybwbybryogyg`

The first number (10000) tells you what number iteration it's on. The second (6.25) tells you the heuristic cost of that state. The third (4) tells you the depth of the current node. The long string tells you what the state looks like, based on the information provided in the "Usage" section.