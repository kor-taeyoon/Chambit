2개의 서브모터 와 mpu6050 센서 코딩
MPU6050 mpu;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
Servo myservo;
Servo myservo1;
 
int val;
int prevVal;
int val1;
int prevVal1;
 
void setup() 
{
    Wire.begin();
    Serial.begin(38400);
 
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
    myservo.attach(9);
    myservo1.attach(7);
}
 
void loop() 
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
    val = map(ay, -17000, 17000, 0, 179);
    val1 = map(ax, -17000, 17000, 0, 179);
    /*
    if (val != prevVal)
    {
        Serial.print(val);
        myservo.write(val);
        prevVal = val;
    }
    if (val1 != prevVal1)
    {
        Serial.print("\t");
        Serial.println(val1);
        myservo1.write(val1);
        prevVal1 = val1;
    }
    */
    myservo.write(val);
    myservo1.write(val1);
    Serial.print(val);
    Serial.print("\t\t");
    Serial.println(val1);
    
    delay(50);
}
