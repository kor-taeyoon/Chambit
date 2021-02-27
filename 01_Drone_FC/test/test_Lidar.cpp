#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial LidarSerial(2, A3);

int dist;
int check;
int uart[9];
const int HEADER=0x59;

void setup() {
    Serial.begin(115200);
    LidarSerial.begin(115200);
}

void loop() {
    if(LidarSerial.available()){            // 스트림에 데이터가 들어오면
        if(LidarSerial.read() == HEADER){   // HEADER 바이트일 때만 통과
            uart[0] = HEADER;               // 수신 데이터 보관 배열 0 위치에 저장
            if(LidarSerial.read() == HEADER){   // 그 다음 데이터도 HEADER일 때만 통과
                uart[1] = HEADER;
                for(int i=2;i<9;i++){ // index 2 ~ 8
                    uart[i] = LidarSerial.read();   // 수신 데이터 보관 배열에 하나씩 저장
                }
                check = uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
                if(uart[8] == (check&0xff)){    // 프로토콜에 맞게 수신했는지 확인
                    dist = uart[2] + uart[3]*256;   // 거리 계산
                    Serial.print(dist);
                    Serial.print(" ");
                    Serial.println();
                }
            }
        }
    }
}
