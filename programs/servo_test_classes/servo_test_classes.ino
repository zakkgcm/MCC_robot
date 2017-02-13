class ServoDescriptor {
    public:  
      boolean inverted;
      double home_pos;

      ServoDescriptor(double hpos=60.0, boolean inv=false) {
        inverted = inv;
        home_pos = hpos;
      }
};

class ServoController {
    public:
      ServoDescriptor serv;

      int pin;
      int pos;
      int max_pos;
      int min_pos;

      ServoController(ServoDescriptor s, int pin, int minp, int maxp) {
        serv = s;
        maxp = max_pos;
        minp = min_pos;

        pos = 0;
      }
    
      void moveServo(double degrees) {
        if (serv.inverted) {
            degrees *= -1;
        }

        // servo moving code        
      }
};

class ServoGroup {
  // some list of servos and relative position descriptors
};

ServoDescriptor servos[15];

void setup() {
  servos[0] = ServoDescriptor(60, false);
}

void loop() {
  ServoController c = ServoController(servos[0], 0, 30, 90);
  c.moveServo(5);
  delay(10);
}
