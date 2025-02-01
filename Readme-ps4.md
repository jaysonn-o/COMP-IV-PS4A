# PS4: Sokoban

## Contact
Name:Jason Ossai
Section: COMP IV 2040
Time to Complete:4 hours


## Description
The Sokoban project introduces a graphical Sokoban game, requiring players to push boxes into designated storage locations, with mechanics to be developed in Part B.

### Features
The development process involved several significant decisions, including:

#### Part a
1.) Implemented a robust method for reading level dimensions and the game grid from a text file format.

2.)The game was rendered using the SFML library, which significantly improved graphics handling and event management.

#### Part b

1.) Game mechanics: Strategies for managing player mobility, box pushing, and win condition verification are planned and will be put into practice in Part B.

### Memory
The game grid is represented using a two-dimensional vector of characters for level data storage, eliminating the need for smart pointers for minimal memory usage.

### Lambdas
In this section of the assignment, no special lambda expressions were constructed, but I used the <algorithm> functions to search and modify grid data. Lambdas may be used in the following section to handle movement or detect collisions.

### Issues
I had lots of lint and valgrind errors which I was unable to fix all. By doing so it changes my code and gives more errors.

### Extra Credit
I didn't attempt the extra credit.


## Acknowledgements
I did this project myself without any help.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban


I didn't use any other resources. I only used the ones given to us.
