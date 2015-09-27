 

# ServoPlus
This library simplifies code for systems containing multiple servos with odd physical configurations. This library allows each servo to be configured in `setup()`, and then have the servo values modified on write automatically. This prevents cluttering the code with  multiple instances of `map()`,`constrain()`, and addition of magic values that account for physical irregulatirites. 
 
# Features

## Drop in replacement 
This library can be used in place of the standard [Servo library](https://www.arduino.cc/en/Reference/Servo) with minimal code changes. Simply change `Servo myservo;` to `ServoPlus myservo;`, and you're good to go. From there, you can start taking advantage of other features as needed. 

## Simpler code
Moves all the positional adjustment and math on each servo write to a single set of configured values. This lets you save code for more interesting things. 

# Helpful Configuration Functions

## `map(low_input, high_input,  low output, high_output)`
Simplify mapping physical systems to the servo's 0-180 range. This makes it easier to do things such as operate in a 0-based range (such as -90 to 90), or scale for mechanical advantage (eg, an input of 90 generates a 45* arm position).

It works just as if you had used Arduino's [`map` function](https://www.arduino.cc/en/Reference/Map) on the values you're passing to the servo `write()` function, except automatically.

## `offset(degrees)`
Add in a small offset to help with physical systems being a bit non-ideal, and helps get the `map` in the right position. 

This is particularly helpful for continous rotation servos, especially if you can no longer reach the adjustment potentiometer to adjust the offset via the hardware.

## `mirror()`
Reverses the servo mapping. This is mostly useful to simplify configuration of servos mounted opposite eachother on a physical system, such as the two drive wheels for a small robot, or opposed servos working to lift an arm.

## `restrict(int, int)`
Specify the min/max angle you want your servo to stop at. This makes it easier to avoid mechanical constraints.

## `read()`
Returns the last value written, but after applying limits set by `restrict()` or the servo's hard-coded 0*-180* range. This way you can detect boundaries in code, or use `read()` to incriment/decriment position reliably.

## `readAbsolute()`
Returns the "physical" servo position, as if you were using a standard servo library.

# License
This code is released under the [MIT liscence](LICENSE.md).