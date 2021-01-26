import cv2

# rgb 이미지 불러오기
img = cv2.imread("opencv_test/cat.jpg")

# rgb 이미지 보기 cv2,imshow('이미지 경로', 이미지 파일) -> 이미지 보여주기

'''
v2.wait(0) - 키보드 동작에 따라 작동하는 함수
=> 키보드 바인딩 함수, 인수는 (밀리 초) 
=> 키보드 이벤트에 대해서 프로그램이 응답한다.
=> 인수로 0이 들어가면 키보드가 눌리기전까지 프로그램이 무기한 기다린다
'''

cv2.imshow("img", img)
cv2.waitKey(0)

# gray_scale 이미지 불러오기
gray_image = cv2.imread('opencv_test/cat.jpg', 0) # 인수를 0으로 전달하면 gray 이미지가 로드된다.

# gray 이미지 보기
cv2.imshow('gray_image', gray_image)
cv2.waitKey(0)
