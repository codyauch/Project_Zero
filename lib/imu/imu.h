#include <Wire.h>
#include <MPU6050_6Axis_MotionApps20.h>

class IMU
{
    private:
        MPU6050 mpu;
        uint16_t dmp_packet_size;
        uint8_t FIFOBuffer[64];
    public:
        IMU();
        ~IMU();
        int initialize();
        int get_roll_z(int*);
        int get_vel_z(int*);
};
