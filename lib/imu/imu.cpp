#include <imu.h>

IMU::IMU()
{
    Serial.println("IMU constructor");
    mpu = MPU6050();
    Serial.println("IMU created");
}

int IMU::initialize()
{
    Wire.begin(); // Begin I2C protocol
    // Wire.setClock(400000);
    mpu.initialize(); // initialize the sensor

    Serial.println("IMU initialize()");
    if (mpu.testConnection() && mpu.dmpInitialize() == 0)
    {
        // MPU 6050 and DMP are initialized, now calibrate
        mpu.setXGyroOffset(0);
        mpu.setYGyroOffset(0);
        mpu.setZGyroOffset(0);
        mpu.setXAccelOffset(0);
        mpu.setYAccelOffset(0);
        mpu.setZAccelOffset(0);

        mpu.CalibrateAccel(6); //calibrate with 600 readings
        mpu.CalibrateGyro(6);

        // Enable the DMP
        mpu.setDMPEnabled(true);

        // Get the DMP packet size
        dmp_packet_size = mpu.dmpGetFIFOPacketSize();
        return 0;
    }
    // An error occurred during initialization
    return 1;
}

int IMU::get_roll_z(int *z_roll)
{
    // Check if we can get data from the DMP
    if(mpu.dmpGetCurrentFIFOPacket(FIFOBuffer))
    {
        Quaternion quat;
        VectorFloat gravity;
        float ypr[3];
        
        mpu.dmpGetQuaternion(&quat, FIFOBuffer);
        mpu.dmpGetGravity(&gravity, &quat);

        mpu.dmpGetYawPitchRoll(ypr, &quat, &gravity);
        
        // It doesnt make sense but ypr[0] seems to correspond to 
        // roll about the z axis as defined by the silkscreen on the sensor
        *z_roll = (int)(RAD_TO_DEG * ypr[0]);
        return 0;
    }
    
    return 1;
}

int IMU::get_vel_z(int *z_vel)
{
    if(mpu.dmpGetCurrentFIFOPacket(FIFOBuffer))
    {
        VectorInt16 gyro;

        // Read the gyro and get angular velocity about the z axis
        mpu.dmpGetGyro(&gyro, FIFOBuffer);
        *z_vel = (int)gyro.z;

        // Quaternion quat;
        // VectorFloat gravity;
        // VectorInt16 accel;
        // VectorInt16 linAccel;

        // mpu.dmpGetQuaternion(&quat, FIFOBuffer);
        // mpu.dmpGetAccel(&accel, FIFOBuffer);
        // mpu.dmpGetGravity(&gravity, &quat);
        // mpu.dmpGetLinearAccel(&linAccel, &accel, &gravity);
        // Serial.print("gyro: ");
        // Serial.print(gyro.x);
        // Serial.print(" ");
        // Serial.print(gyro.y);
        // Serial.print(" ");
        // Serial.println(gyro.z);

        // Serial.print("accel: ");
        // Serial.print(accel.x);
        // Serial.print(" ");
        // Serial.print(accel.y);
        // Serial.print(" ");
        // Serial.println(accel.z);

        // Serial.print("linAccel: ");
        // Serial.print(linAccel.x);
        // Serial.print(" ");
        // Serial.print(linAccel.y);
        // Serial.print(" ");
        // Serial.println(linAccel.z);

        return 0;
    }

    // Something went wrong
    return 1;
}

IMU::~IMU()
{
    Wire.end(); // I don't know if this is needed
}