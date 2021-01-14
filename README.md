







## 국문



#### 개발 동기
> 산불, 해상 불법 조업, 야간 산행 등을 단속하기 위해 드론이 이미 이용되고 있다. 하지만 현재의 운용 방식은 사람이 직접 조종하면서 의심되는 정황을 육안으로 확인하는 방식으로, 효과적으로 이용되지 못하고 있다.
>  이런 이유로, 감시용 방범 드론 운용을 자동화하는 시스템을 개발하려고 한다.
> 정해진 구역을 순회하는 경로를 자동으로 생성하고, 비행중에는 하단의 카메라로 실시간으로 영상을 분석해 불법 행위 또는 재난 상황을 확인한다.
> 또한 순회 비행을 수행하면서 취득하는 이미지 데이터를 지상에서 수합하여 해당 구역에 대한 정밀 지도를 자동으로 생성할 수 있도록 한다.
> 가장 큰 특징으로, 자동으로 경로를 생성하는 동시에 gps를 기반으로 한 자율 비행을 진행하며 특정 상황 확인 시 복귀하는 방식으로 구현하기 때문에, 작전 반경에 제한이 거의 없어 고정익 형태의 무인기에 적용하면 더욱 효과적인 감시 체계를 구현할 수 있을 것이다.



#### 기술 
* F450, DIY FC (arm cortex processor)
* raspberry pi zero, camera
* 



#### 역할분담
| 이름 | 담당 | 주요업무 | 비고 |
| - | - | - | - |
| 김태윤 | 팀장 | 시스템 설계, FC 아트웍 | |
| 김하은 | 팀원 | 무인기 프레임 제작, 예산 정리 | |
| 신용준 | 팀원 | 비행 제어, 실시간 영상 분석 구현 | |
| 이진헌 | 팀원 | 촬영 데이터 분석 알고리즘 구현 | |


#### 추진 일정
| 주차 | 일정 | 활동내용 | 비고 |
| - | - | - | -|
| 1 | 2021.03/02 | 전체 시스템 설계, 프로토콜 구성 |
| 2 | 2021.03/08 | 시험용 무인기 설계, 촬영물 분석 알고리즘 시험용 데이터셋 수집
| 3 | 2021.03/15 | 시험용 드론 제작, 비행 알고리즘 설계
| 4 | 2021.03/22 | 시험용 드론 제작, 비행 알고리즘 구현
| 5 | 2021.03/29 | 시험용 드론 비행 시험
| 6 | 2021.04/05 | 무인기 비행 최적화
| 7 | 2021.04/12 | 전원 전압 감지, 자동 복귀 구현
| 8 | 2021.04/19 | 중간보고서 작성 및 제출
| 9 | 2021.04/26 | 경로 생성 알고리즘 설계, 시험
| 10 | 2021.05/03 | 경로 생성 알고리즘 최적화
| 11 | 2021.05/10 | 단거리 비행 시험
| 12 | 2021.05/17 | 촬영물 분석 알고리즘 시험, 검증
| 13 | 2021.05/24 | 발생한 오류 수정, 총 알고리즘 최적화
| 14 | 2021.05/31 | 장거리 비행 시험, 최종 결과물 보고서 작성
| 15 | 2021.06/07 | 최종 결과보고서 및 성찰일기 제출





