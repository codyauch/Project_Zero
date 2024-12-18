#include <fin.h>

Fin::Fin(int servo_pin)
{
    servo = Servo();
    servo.attach(servo_pin);
    deflection_offset = 0;
    max_deflection = MAX_DEFLECTION;
}

int Fin::set_deflection(int deflection_angle)
{
    if (deflection_angle <= MAX_DEFLECTION && deflection_angle >= -MAX_DEFLECTION)
    {
        int servo_angle = deflection_to_servo_angle(deflection_angle);
        servo.write(servo_angle);
        return 0;
    }
    else
    {
        // Attempting to push fin past max deflection angle
        return 1;
    }
}

int Fin::deflection_to_servo_angle(int deflection)
{
    int servo_angle = (90 + deflection) + deflection_offset;

    // Clamp to 180 degrees (to compensate for offset)
    if (servo_angle > 180)
    {
        servo_angle = 180;
    }
    else if (servo_angle < 0)
    {
        servo_angle = 0;
    }

    return servo_angle;
}

// int Fin::set_max_deflection(int max_angle)
// {
//     if (max_deflection < 90)
//     {
//         max_deflection = max_angle;
//         return 0;
//     }
//     else
//     {
//         return 1;
//     }
    
// }

int Fin::set_deflection_offset(int offset)
{
    deflection_offset = offset;
    return 0;
}

Fin::~Fin()
{
    // Detach the servo (for fun I guess)
    servo.detach();
}