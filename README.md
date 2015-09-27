 

# Intention
I got tired of writing map, constrain and other functions for multi-servo systems. This is a wrapper around the standard Servo library, which lets you set the defaults for those functions, which will apply to any future `servo.write()` calls without cluttering the code.
 
# Features


## `offset(int)`
Add in a small offset to help with physical systems being a bit non-ideal

## `map(low_input, high_input,  low output, high_output)`
Simplify mapping physical systems to the servo's 0-180 range. As with the "map" function, you can invert the servo by mapping

## `mirror()`
Sets the map to an inverted operation, in case you feel lazy.


## `constrain(int, int)`
Specify the physical constraints your servo needs to stop at. 

## `constrainMapped(int min, int max)`
Similar to the Constrain function, but 
