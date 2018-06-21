# ARDUROAD

A spiritual successor to the game Enduro made by Activision in 1983.

Key features:

- Weather conditions changes
- Day/Night transitions
- 4 Channels music selected from a radio at the start


## To do list:

- Save some PROGMEM!
- Add music!
- [WIP] Add 'Start of Day' banner and add logic to increase number of cars each day.
- Change High Score to capture days instead of cars passed.
- [WIP] Smooth out car acceleration.  The current approach results in four distinct speeds with no variations.  Will remove the FixedPoint values to see if it saves memory.
- Detect cars bumping into each other and player.
- Prevent cars 'moving through' each other using bump detection.
- Slow player car when bumping into other cars.
- [Done] [s]Allow car to move onto edge of road which will decrease speed.[/s]
- [Done] [s]Test whether extending ArduboyBase will save memory.  Font4x6 might require some additional library references to work.[/s]
- Test whether drawCompressed() or other compression library for rendering logos and initial splash screen will save memory.
- [Done] [s]Add automatic control to HUD.  Will draw gears or auto shift based on player.isAutomatic();[/s]

## Enhancements:

- Add auto / manual selector on front screen.  Not sure if we want to retain manual but lets assume so.
- Add scenery elements on side of road.  (will depend on available memory).

## Bugs:

- Sometimes you cannot pass other cars.  Can be solved by spacing the cars out a little more but need to resolve the 'bumping' of cars as this will significantly affect car movement.
- Wheels not moving when A Button not pressed.
- Cannot shift down a gear in manual mode.


