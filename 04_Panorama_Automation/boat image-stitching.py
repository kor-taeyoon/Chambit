import cv2
import sys

# 3장의 영상을 리스트로 묶어서 반복문으로 하나하나 갖고옴
img_names = ['opencv_test/boat/01.jpg', 'opencv_test/boat/02.jpg', 'opencv_test/boat/03.jpg']

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
status, dst = stitcher.stitch(imgs)

if status != cv2.Stitcher_OK:
    print('Stitch failed!')
    sys.exit()
    
# 결과 영상 저장
cv2.imwrite('output.jpg', dst)

# 출력 영상이 화면보다 커질 가능성이 있어 WINDOW_NORMAL 지정
cv2.namedWindow('dst', cv2.WINDOW_NORMAL)
cv2.imshow('dst',dst)
cv2.waitKey()
cv2.destroyAllWindows()

성공 !1
