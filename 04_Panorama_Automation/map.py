import cv2
import sys
import numpy as np
import matplotlib.pyplot as plt
import glob
import os


path_dir = "C:/Users/khe06/Pictures/map/"   # 특정 디렉터리 경로를 path_dir에 저장

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
    
# 결과 영상 저장
cv2.imwrite('map_output.jpg', stitched)



'''
# 출력 영상이 화면보다 커질 가능성이 있어 WINDOW_NORMAL 지정
cv2.namedWindow('stitched', cv2.WINDOW_NORMAL)
cv2.imshow('stitched',stitched)
cv2.waitKey()
cv2.destroyAllWindows()

'''
