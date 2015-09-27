#ifndef SERVOPLUS_H
#define SERVOPLUS_H

#include <Arduino.h>
#include <Servo.h>

void DEBUG(String str, int val) {
  Serial.print("DBG:");
  Serial.print(str);
  Serial.print(" ");
  Serial.println(val);
}

#define DEBUG(x,y){};

class ServoPlus: public Servo {
  private:
    //All these values will be saved as microseconds, which improves the precision of the math
    struct Map {
      int inlow;
      int inhigh;
      int outlow;
      int outhigh;
    } _map, _pos_to_micros;

    //Used for physical constraints
    int _min_us;
    int _max_us;

    //Used for re-calibrating servo positions if they're not where you want them
    int _offset;

    //Save the last written value
    int _last_write_us;


    //Shortcut functions for converting between servo angles and microsecond writes
    int position_to_micros(int pos) {
      return ::map(pos, 0, 180, 1000, 2000);
    }
    int micros_to_position(int micro) {
      return ::map(micro, 1000, 2000, 0, 180);
    }

  public:
    ServoPlus() {
      //Set defaults to match standard servo inputs
      _map = {0, 180.0, 180};

      _min_us = 1500;
      _max_us = 2000;

      _last_write_us = 1500;
    }


    /** Safe version of writeMicroseconds
    * Does not let you write stupid values to a servo that could potentially cause damage
    */
    void writeMicroseconds(int pulse) {
      Servo::writeMicroseconds(constrain(pulse, 1000, 2000));
    }


    /** This reverses the output of the servo.
    * Very helpful when two servos are physically inverted, but should be driven the same way
    */
    void mirror() {
      _map = {
        _map.inlow,
        _map.inhigh,
        _map.outhigh,
        _map.outlow
      };
    }

    /** This reverses the output of the servo.
    * Very helpful when two servos are physically inverted, but should be driven the same way
    */
    void map(int inlow, int inhigh, int outlow, int outhigh) {
      _map = {
        inlow,
        inhigh,
        outhigh,
        outlow
      };
    }

    /** Set physical constrains on the servo's movement
    */
    void restrict(int min, int max) {
      _max_us = position_to_micros(max);
      _min_us = position_to_micros(min);
    }

    void write(int pos) {
      DEBUG("Raw Position:", pos);

      //Step 1: Map the values to where they should be
      //Note the offset is implimented by adjusting the input range
      pos =::map(pos, _map.inlow + _offset, _map.inhigh + _offset, _map.outlow , _map.outhigh);
      DEBUG("Mapped Pos:", pos);

      //Step 2: Convert position to microseconds
      pos = position_to_micros(pos);
      DEBUG("Mapped us:", pos);

      //Step 4: Make sure we're not exceeding our specified boundaries
      pos = constrain(pos, _min_us, _max_us);
      DEBUG("Constrained us:", pos);


      DEBUG("Final Position", micros_to_position(pos));
      DEBUG("_______________", 0);


      //Save our last used value so that we can recall it
      _last_write_us = pos;

      writeMicroseconds(pos);
    }

    void offset(int value) {
      _offset = value;
    }

    int read() {
      return ::map( micros_to_position(_last_write_us),
                  _map.outhigh,
                  _map.outlow,
                  _map.inhigh,
                  _map.inlow
                );

    }

    /** Returns the actual physical position of the servo
    */
    int readAbsolute() {
      return micros_to_position(_last_write_us);
    }
};



#endif
