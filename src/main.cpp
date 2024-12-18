#include <Arduino.h>
#include <fin.h>
#include <imu.h>

#define ROLL_THRESHOLD 5 //deg/s? how high roll rate do we want to ignore

Fin fin1 = Fin(2); // Create a fins using pins 2-5
Fin fin2 = Fin(3);
Fin fin3 = Fin(4);
Fin fin4 = Fin(5);

IMU *imu = NULL;

void adv_fin_test()
{
  while(1)
  {
    Serial.println("Fin 1");
    fin1.set_deflection(10);
    delay(500);
    fin1.set_deflection(0);
    fin1.set_deflection(-10);
    delay(500);
    fin1.set_deflection(0);
    delay(500);

    Serial.println("Fin 2");
    fin2.set_deflection(10);
    delay(500);
    fin2.set_deflection(0);
    fin2.set_deflection(-10);
    delay(500);
    fin2.set_deflection(0);
    delay(500);

    Serial.println("Fin 3");
    fin3.set_deflection(10);
    delay(500);
    fin3.set_deflection(0);
    fin3.set_deflection(-10);
    delay(500);
    fin3.set_deflection(0);
    delay(500);

    Serial.println("Fin 4");
    fin4.set_deflection(10);
    delay(500);
    fin4.set_deflection(0);
    fin4.set_deflection(-10);
    delay(500);
    fin4.set_deflection(0);
    delay(500);

    delay(5000);
  }
}

void fin_test()
{
  while(1)
  {
    Serial.println("+10");
    fin1.set_deflection(10);
    fin2.set_deflection(10);
    fin3.set_deflection(10);
    fin4.set_deflection(10);
    delay(1000);
    Serial.println("-10");
    fin1.set_deflection(-10);
    fin2.set_deflection(-10);
    fin3.set_deflection(-10);
    fin4.set_deflection(-10);
    delay(1000);
  }
}

void centre_fins()
{
  while(1)
  {
    // hold all fins at centre
    fin1.set_deflection(0);
    fin2.set_deflection(0);
    fin3.set_deflection(0);
    fin4.set_deflection(0);
    Serial.println("Holding fins at centre.");
    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);


  // fin_test(); // DEBUG
  // adv_fin_test(); // DEBUG
  // centre_fins(); // DEBUG

  // Create an IMU object
  imu = new IMU();

  // Connect to the IMU
  int max_imu_retry = 20;
  int num_imu_retries = 0;
  while(imu->initialize() != 0 && num_imu_retries < max_imu_retry)
  {
    Serial.println("IMU initialization failed, retrying");
    num_imu_retries++;
    delay(250);
  }
  if (num_imu_retries == max_imu_retry)
  {
    Serial.println("IMU initialization failed too many times, exiting");
    digitalWrite(LED_BUILTIN, LOW);
    while (1); // infinite loop
  }


  Serial.println("IMU ready!");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

  // Read the roll rate from the IMU
  int roll_velocity = 0;
  int roll_dir = 0;
  (void) imu->get_vel_z(&roll_velocity);

  if (abs(roll_velocity) > ROLL_THRESHOLD)
  {
    // Check which direction the vehicle is rolling
    if (roll_velocity > 0)
    {
      roll_dir = -1;
      Serial.print("[+] roll detected, ");
    }
    else
    {
      Serial.print("[-] roll detected, ");
      roll_dir = 1;
    }

    // Deflect the fin in the correct direction
    int fin_deflection = roll_dir * fin1.max_deflection; 
    fin1.set_deflection(fin_deflection);
    fin2.set_deflection(fin_deflection);
    fin3.set_deflection(fin_deflection);
    fin4.set_deflection(fin_deflection);

    Serial.print("setting fins deflection to: ");
    Serial.println(fin_deflection);

  }
  else
  {
    // Return fins to neutral position
    fin1.set_deflection(0);
    fin2.set_deflection(0);
    fin3.set_deflection(0);
    fin4.set_deflection(0);
    Serial.println("Rolling fins back to neutral");
  }

  delay(100);
  
}
