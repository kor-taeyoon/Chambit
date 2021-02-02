
#include "mbed.h"
#define SPI_READ 0x80   // where is mpu-9250
#define WHO_AM_I 0x75   // where is who_am_i

SPI spi(D11, D12, D13); // mosi, miso, sclk
DigitalOut ss(D2);      // select sensor


int main(){
    // SPI 통신 설정
    ss = 1;             // 제어권 초기화(통신 시작 x)
    spi.format(8, 3);           // 8bit data, spi mode 3
    spi.frequency(1000000);     // 1Mhz
    
    
    while (1) {
        // 통신 시작
        ss = 0;     // MPU-9250 제어권 획득
        
        // 주소 송수신
        spi.write(SPI_READ | WHO_AM_I);                     // WHO_AM_I 주소와 0x80을 or 연산 해 MSB를 
        
        // 데이터 송수신
        int whoami = spi.write(0);          // whoami라는 변수에 아무 값이나 전송 -> 응답 요구
        
        // 데이터 처리
        printf("WHO_AM_I register = 0x%X\n", whoami);       // 수신 데이터 출력
        
        // 통신 종료
        ss = 1;     // 제어권 놓기
        
        // 지연
        wait(1);    // 1초 딜레이
    }
}
