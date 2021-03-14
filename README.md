
# 재난 모니터링과 방을 위한 능동형 드론 자동화 시스템 README.md
kw-방범대 (광운대학교 전자통신공학과 21년도 1학기 참빛설계학기 프로젝트)


<br>

## 개발 동기
산불 감시, 불법 조업 단속, 실종자 수색 등 실생활의 많은 부분에서 이미 무인기가 이용되고 있다.
<br>
하지만 현재 운용되는 방식은 사람이 직접 조종을 하고, 실시간으로 전송되는 화면을 육안으로 확인하는 방식으로, 효과적으로 이용되지 못하고 있다.
<br>
따라서, 단속 및 순찰을 위한 무인기 및 무인기 운용 시스템을 개발하고자 한다.
<br>
입력된 구역 내의 체크포인트를 스스로 순환하며 비행하고, 목표 객체가 인식이 되면 네트워크를 통해 관리자에게 알리고 실시간 영상을 송출한다.
<br>
<br>

## 시스템의 운용
##### (실제 구현은 현 무인기 관리 정책에 따라 축소시켜 구현하도록 한다.)
- 펌웨어에 정해진 체크포인트를 입력해 수동 조작과 동시에 순환 비행을 수행시킨다. ("자율 비행"의 구현은 불법)
- 연직 방향의 카메라를 통해 얻는 영상에서 목표 객체(화재, 실종자 등)을 검출한다.
- 목표 객체가 검출되면 현재 좌표와 최근 이미지 여러개를 관리자에게 전송한다.
    - 현재 GPS 좌표와, 최근 촬영 이미지 여러장을 파노라마처리 후 전송.
- 동시에 무인기는 해당 구역에 머무르며 실시간 영상을 송출하기 시작한다.
- 알림을 받은 관리자는 해당 무인기에 접속하여 수신한 데이터와 실시간 영상을 확인한다.
<br>
<br>

## 기술의 구현
- 무인기 제어 (사진 넣기)
    - 자세 추정, 제어
        - NAZA m Lite Module
    - 무선 송수신
        - nRF24L01 + PA + LNA
    - 지면과의 상대 고도 유지
        - TF-Luna Lidar
    - way-point 비행
        - PRF-G189 GPS Sensor
- 객체 검출
    - YOLO V3
<br>
<br>

## 팀 구성 및 역할 분배
- 김태윤(팀장, 전자통신공학과 19학번)
    - 무인기 제어시스템 개발
    - 전체 프로젝트 구성
- 김하은(팀원, 전자통신공학과 20학번)
    - 촬영 데이터 후처리
    - 객체 검출(실종자 수색)
- 신용준(팀원, 전자통신공학과 17학번)
    - 2축 짐벌 개발
    - 객체 검출(산불 감시)
- 이진헌(팀원, 전자통신공학과 17학번)
    - 이미지 획득 및 기록
    - 무인기-지상국 데이터 송수신 시스템 구현
<br>
<br>

## 참고 문헌
1. 무인기 제어시스템 개발
    - 하버사인 GPS 기반 거리계산법(py): https://stricky.tistory.com/283
    - nRF24L01+ 기본 문자열 통신: https://innoaus.com/posts/20190415/
    - 라디안 <-> 오일러각: https://m.blog.naver.com/PostView.nhn?blogId=msyang59&logNo=220859527436&proxyReferer=https:%2F%2Fwww.google.com%2F
    - Quaternion Mahony AHRS: https://m.blog.naver.com/PostView.nhn?blogId=ysahn2k&logNo=221410891895&proxyReferer=https:%2F%2Fwww.google.com%2F
    - MPU 센서의 DMP 오류 : https://www.i2cdevlib.com/forums/topic/6-dmp-output-stopped-working/

2. 짐벌 개발
    - 아두이노 1축 짐벌 개발기: http://blog.naver.com/PostView.nhn?blogId=123gtf&logNo=221289162607

3. 실시간 영상분석
    - YOLO 활용, 화재/연기 분석: http://pkban.blogspot.com/2020/06/windows10-yolo-c-library-ai-cctv-3-fire.html
4. 지상 촬영물 후처리
    - 파이썬 파노라마: https://deep-learning-study.tistory.com/266
<br>
<br>

