#include <Servo.h>

#define MAX_DEFLECTION 20

class Fin
{
    private:
        Servo servo;
        int servo_pin;
        int deflection_offset;
        int deflection_to_servo_angle(int);
    public:
        int max_deflection;
        Fin(int); // constructor
        int set_deflection(int);
        int set_deflection_offset(int);
        int set_max_deflection(int);
        ~Fin();
};

