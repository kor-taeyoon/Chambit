
# 재난 모니터링과 방범을 위한 능동형 드론 자동화 시스템 README.md
KW-방범대 (광운대학교 전자통신공학과 21년도 1학기 참빛설계학기 프로젝트)


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
- GUI 프로그램에서 오토파일럿을 시행하면, 입력된 구역을 순회하는 경로를 자동비행한다.
- 연직 방향의 카메라로부터 영상을 실시간으로 받아 분석하여, 목표하는 객체를 검출한다.
- 목표한 객체가 검출되면, 현재 좌표와 해당 이미지를 관리자에게 전송한다. (텔레그램 API)
- 관리자는 오토파일럿을 해제하여 수동으로 조작할 수 있다.
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
        - 성능면에서 너무 부족함을 확인(라즈베라파이4 기준 장당 70초
<br>
<br>

## 팀 구성 및 역할 분배
- 김태윤(팀장, 전자통신공학과 19학번)
    - 무인기 제어시스템 개발
    - 전체 프로젝트 구성
- 김하은(팀원, 전자통신공학과 20학번)
    - 촬영 데이터 후처리
    - 객체 검출(실종자 수색, 해상 불법 조업)
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
    - https://papago.naver.net/website?locale=ko&source=en&target=ko&url=https%3A%2F%2Fardupilot.org%2Fplane%2Fdocs%2Fcommon-mavlink-mission-command-messages-mav_cmd.html

2. 짐벌 개발
    - 아두이노 1축 짐벌 개발기: http://blog.naver.com/PostView.nhn?blogId=123gtf&logNo=221289162607

3. 실시간 영상분석
    - YOLO 활용, 화재/연기 분석: http://pkban.blogspot.com/2020/06/windows10-yolo-c-library-ai-cctv-3-fire.html
4. 지상 촬영물 후처리
    - 파이썬 파노라마: https://deep-learning-study.tistory.com/266
<br>
<br>

