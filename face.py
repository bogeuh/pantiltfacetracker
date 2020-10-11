#import all the required modules

import numpy as np
import serial
import time
import sys
import cv2

#sys.path.append('/usr/local/lib/python2.7/site-packages')

#Setup Communication path for arduino (In place of 'COM5' (windows) or ''/dev/tty.usbmodemxxx' (mac) put the port to which your arduino is connected)
arduino = serial.Serial('/dev/ttyACM0',9600)
arduino.flushInput()
previousxx = 0
previousyy = 0
time.sleep(0.5)
print("Connected to Arduino...")

#importing the Haarcascade for face detection
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
#body_cascade = cv2.CascadeClassifier('haarcascade_upperbody.xml')

#To capture the video stream from webcam.
cap = cv2.VideoCapture(0)
print("Getting camera image...")
#Read the captured image, convert it to Gray image and find faces
while 1:
# ret returns true or false if an image was detected or not
#so while true:
    #reduce the captures to 10 per second or less
    #time.sleep(0.1)
    ret, img = cap.read()
    cv2.namedWindow('img', cv2.WINDOW_NORMAL)
    ###############
    #my camera size is 848,480
    #somehow more like 1000 wide
    ##################
    #cv2.resizeWindow('img', 500,500)
    #image = cv2.line(image, start_point, end_point, color, thickness) 
    #0,0 is top left corner 
    
    ##create two horizontal lines with circle in the middle
    cv2.line(img,(50,240),(414,240),(0,255,0),3)
    cv2.line(img,(434,240),(798,240),(0,255,0),3)

    cv2.circle(img, (424,240), 3, (255,0,0), -1)

    #vertical lines
    cv2.line(img,(424,20),(424,230),(0,0,255),3)
    cv2.line(img,(424,250),(424,460),(0,0,255),3)

##################
##detect faces
##################
    gray  = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    #body = body_cascade.detectMultiScale(
    #faces = face_cascade.detectMultiScale(gray, 1.4, 5)
    face = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.5,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv2.CASCADE_SCALE_IMAGE
    )

    #detect the face and make a rectangle around it.
    for (x,y,w,h) in face:
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),5)
        #roi_gray  = gray[y:y+h, x:x+w]
        #roi_color = img[y:y+h, x:x+w]

        #arr = {y:y+h, x:x+w}
        # print (arr)

        # print ('X :' +str(x))
        # print ('Y :'+str(y))
        # print ('x+w :' +str(x+w))
        # print ('y+h :' +str(y+h))

        # Center of roi (Rectangle)
        xx = int(x+(x+w)/2)
        yy = int(y+(y+h)/2)
        # print (xx)
        # print (yy)
        center = (xx,yy)
        if ((previousxx + 30) < xx or xx < (previousxx - 30)):
            previousxx = xx
            # sending data to arduino
            #print("Center of Rectangle is :", center)
            #data = "X{0:d}Y{1:d}Z".format(xx, yy)
            data = "X"+str(xx)+"Y"+str(yy)
            #print ("output = '" +data+ "'")
        
        #########
        ## sending data crashes the detector?
        ## reduce baudrate?
        ####################

            arduino.write(data)


        # same , send only if difference is big enough    
        if ((previousyy + 15) < yy or yy < (previousyy - 15)):
            previousyy = yy
            # sending data to arduino
            #print("Center of Rectangle is :", center)
            #data = "X{0:d}Y{1:d}Z".format(xx, yy)
            data = "X"+str(xx)+"Y"+str(yy)
            #print ("output = '" +data+ "'")
        
            #########
            ## sending data crashes the detector?
            ## reduce baudrate?
            ####################

            arduino.write(data)
        


    #Display the stream.
    cv2.imshow('img',img)

    #Hit 'Esc' to terminate execution
    k = cv2.waitKey(30) & 0xff
    if k == 27:
       break