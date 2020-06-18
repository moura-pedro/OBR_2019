import cv2
import numpy
 
cam = cv2.VideoCapture(0)
kernel = numpy.ones((5 ,5), numpy.uint8)
 
while (True):
    ret, frame = cam.read()
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
 #   rangeMax = numpy.array([150, 220, 80])     # B, G, R
 #   rangeMin = numpy.array([100, 70, 30])      # B, G, R
    rangeMax = numpy.array([90, 200, 150])     # H,S,V
    rangeMin = numpy.array([60, 80, 30])      # H,S,V
    imagem_mask = cv2.inRange(hsv, rangeMin, rangeMax)
    output = cv2.bitwise_and(frame,frame,mask = imagem_mask)
    # reduce the noise
    opening = cv2.morphologyEx(imagem_mask, cv2.MORPH_OPEN, kernel)
 
    ret = cv2.boundingRect(opening) #Returns the upper left (x, y), width (w), and height (h) coordinates
    print(ret)

    cv2.rectangle(frame,(ret[0],ret[1]),(int(ret[0]+ret[2]), int(ret[1] + ret[3])), (0, 0, 255), 3)     #Rectangle.
    cv2.circle(frame, (ret[0]+ret[2]/2, ret[1]+ret[3]/2), 5, (255, 0, 0), -1)       #Rectangle center

    cv2.imshow('IMAGE',frame)
    cv2.imshow('MASK',imagem_mask)
    cv2.imshow('MORFOLOGIC',opening)
    cv2.imshow('GREEN REGION', output)
 
    if(cv2.waitKey(1) == 27):
        break

cv2.waitKey(0)
cv2.destroyAllWindows()
