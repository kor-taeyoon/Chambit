import cv2
import sys
import numpy as np
import matplotlib.pyplot as plt
import glob, os

# 4장의 이미지를 리스트로 묶어서 반복문으로 하나하나 갖고옴 -> 무조건 하나씩 적어야 하나요 한 번에는 못 쓰나 욤 ??
img_names = ['opencv_test/lake1.png', 'opencv_test/lake2.png', 'opencv_test/lake3.png', 'opencv_test/lake4.png']

# 불러온 영상을 imgs에 저장

imgs = [] 

for name in img_names:
    img = cv2.imread(name)
    
    if img is None:
        print('Image load failed!')
        sys.exit()
        
    imgs.append(img)
    
# 객체 생성
stitcher = cv2.Stitcher_create()

# 이미지 스티칭
status, stitched = stitcher.stitch(imgs)

if status != cv2.Stitcher_OK:
    print('Stitch failed!')
    sys.exit()
    
# 결과 영상 저장
cv2.imwrite('lake_output.jpg', stitched)


'''
# 출력 영상이 화면보다 커질 가능성이 있어 WINDOW_NORMAL 지정
cv2.namedWindow('stitched', cv2.WINDOW_NORMAL)
cv2.imshow('stitched',stitched)
cv2.waitKey()
cv2.destroyAllWindows()


'''
