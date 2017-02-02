## Description:
 - Game take 0-4 command line arguments
  - 1st - FPS (1-100)
    - frame per second "$fps"
  - 2nd - SPEED (1-10)
    - move "$speed" block per second
  - 3rd - DIFFICULTY (1-10)
    - generate "$difficulty" obstacles each time eat fruit
  - 4th - Cross Screen Mode (true/false)
    - will die when crush on wall if "$mode" == 'false'
 - Block:
  - Size:
    - 10x10 pixel
  - Color: 
    - Black: Obstacles
    - Red: Fruit
    - Green: Snake
 - Ex ./snake 60 10 5 false

## Control:
 - Start: 'ENTER'
 - Direction: 'W', 'S', 'A', 'D'
 - Pause/Resume: 'SPACE'
 - Restart: 'R'
 - Quit: 'Q'


## Enhancement:
 - Creative level design. A classic level is a bounded square region with no obstacles inside. You can enhance this by adding obstacles that the snake must avoid and gaps on the border that lets the snake wrap around to other side of the screen.
 - Command line argument see above (section 1.1)
