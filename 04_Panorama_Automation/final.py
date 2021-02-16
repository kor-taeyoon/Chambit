import cv2
import sys
import numpy as np
import matplotlib.pyplot as plt
import glob
import os


# 사진 6 장 파일에서 바로 불러와서 이어 붙이기


path_dir = "C:/Users/khe06/Pictures/boat/"  # 특정 디렉터리 경로를 path_dir에 저장

file_list = os.listdir(path_dir) # os 라이브러리의 listdir은 경로를 입력받아서 해당 경로 내부의 파일, 폴더들을 리스트 형식으로 반환.
# 따라서 file_list라는 리스트에 경로 내부의 파일, 폴더 이름들은 원소로 대입

for x in file_list: # x에 리스트 원소 하나씩 대입하면서 리스트원소 갯수만큼 반복-
    print(x)  # 폴더 또는 파일명 하나 출력

imgs = []  # 불러온 사진을 imgs에 저장

for name in file_list:
    img = cv2.imread(path_dir + name)
    
    if img is None:
        print('Image load failed!')
        sys.exit()
        
    imgs.append(img) # 차곡차곡 쌓기

# 객체 생성
stitcher = cv2.Stitcher_create()

# 이미지 스티칭
status, stitched = stitcher.stitch(imgs)

if status != cv2.Stitcher_OK:
    print('Stitch failed!')
    sys.exit()
    

# 가로로 이어붙이니, 이미지가 늘어나거 검정 부분이 생김 
# 검정 부분 지우기


gray = cv2.cvtColor(stitched, cv2.COLOR_BGR2GRAY) #BGR -> GRAY로 바꿔주기
real_boat = cv2.bitwise_not(cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY)[1]) #threshold로 0,255값으로 만들고 반전시키기( 검은 부분이 흰부분이 됨)
real_boat = cv2.medianBlur(real_boat, 5) #medianblur를 이용해서 중간중간의 잔여 이물질들 없애기 ( 블러처리 )

stitched_copy = stitched.copy()
thresh_copy = real_boat.copy()

while np.sum(thresh_copy) > 0: #모든 요소의 합 = 0 (모두 검정 부분이 되어야함) ; 흰색=255, 검정=0
    # np.sum = 0 이 될때까지 가로 세로 한줄 씩 지우기 (원본 파일도)
    thresh_copy = thresh_copy[1:-1, 1:-1]
    stitched_copy = stitched_copy[1:-1, 1:-1]
    

# 결과 영상 저장
cv2.imwrite('boat_output!!.png', stitched_copy)
