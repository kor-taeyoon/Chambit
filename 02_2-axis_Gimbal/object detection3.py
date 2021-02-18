//주소 : https://bskyvision.com/678

import cv2

import cvlib as cv
from cvlib.object_detection import draw_bbox

image_path = 'test1.JPG' # 여기에는 테스트할 이미지의 경로 및 이름을 넣어주시면 됩니다. 
im = cv2.imread(image_path) # 이미지 읽기


# object detection (물체 검출)
bbox, label, conf = cv.detect_common_objects(im)

print(bbox, label, conf)

im = draw_bbox(im, bbox, label, conf) 


cv2.imwrite('result.jpg', im) # 이미지 쓰기
