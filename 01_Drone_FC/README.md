## Quadcopter Flight Controller Develop

- - -

### 부품 구성
- stm32f103rb (ST Nucleo)
- nRF24L01 + PA + LNA (Communication module) -> https://www.hotmcu.com/nrf24l01palna-24ghz-wireless-transceiver-module-1100-meters-p-276.html
- MPU9250 (IMU)
- PRF-G189 (GPS) -> https://www.devicemart.co.kr/goods/view?no=1346018


<br>


### 회로 구성 및 다이어그램

- Remote Controller Circuits
![Remote Controller Circuits](./images/RC_v2.jpg)





- - -
### 참고 자료
* 하버사인 GPS 기반 거리계산법(py): https://stricky.tistory.com/283
* nRF24L01+ 기본 문자열 통신: https://innoaus.com/posts/20190415/
* 라디안 <-> 오일러각: https://m.blog.naver.com/PostView.nhn?blogId=msyang59&logNo=220859527436&proxyReferer=https:%2F%2Fwww.google.com%2F
* Quaternion Mahony AHRS: https://m.blog.naver.com/PostView.nhn?blogId=ysahn2k&logNo=221410891895&proxyReferer=https:%2F%2Fwww.google.com%2F
* MPU 센서의 DMP 오류 : https://www.i2cdevlib.com/forums/topic/6-dmp-output-stopped-working/
* MultiWii 펌웨어 분석: https://www.slideshare.net/chcbaram/v2-48540216




<br>

- - -

### 변경 사항
2021.02/05
- 칩셋 변경
  - vscode의 platformio를 이용한 기존 아두이노 라이브러리 이용을 위해 st nucleo stm32f103rb로 교체

- 센서 변경
  - yaw 교정을 위한 mpu9250의 제어 난이도 너무 높아, 지자기계 제외, yaw는 추정으로만 계산

<br>
 


2021.01/31
- 칩셋 변경
  - 개발중이던 stm32f103c8t6 칩셋의 상당수가 클론 칩셋 -> 신뢰도 부족

  - 따라서 칩셋 사이즈 상관 없이 nucleo 계열, 또는 stm32f407vet6(black)으로 교체 예정

- 플랫폼 변경
  - 또한 아두이노 -> stm32 포팅 과정에서 불안정한 모습 관찰

  - 따라서 Mbed 기반으로 변경 (라이브러리 충분함 확인)

- 모듈 변경
  - HM-1X -> nRF24L01
    - HM-1X 계열의 블루투스 칩셋 사용하려 했으나 통신 거리 문제로 nRF 계열로 교체

    - NRF24L01 + PA + LNA로 양쪽 변경 -> 통신거리 1.1km(이론)까지 확보
    
  - MPU6050 -> MPU9250
    - YAW에 대한 필터링 불충분 -> 장시간 체공에는 부적함
    
    - 9축 제어 가능한 MPU9250으로 교체, 라이브러리 확인중
    
- 전체적인 흐름 변경
  - 기존 목표
    - CLDC 드론 완성 이후, F450 수동 비행 이후, F450 자율비행 구현
  
  - (수정)1차 목표
    - CLDC 드론 완성 이후, F450 nRF 기반 수동 비행 구현
    
    - 수동 조작을 기반으로 딥러닝 모델 및 거의 대부분의 자료 확보하기
  
  - (수정)2차 목표
    - GPS 기반 F450 자율 비행 구현, 최종 완성
