import cv2 as cv #Please install with PIP: pip install cv2
import numpy as np
import pyzbar.pyzbar as pyzbar #Please install with PIP: pip install pyzbar

cap = None
ret = None
frame = None
QRCode = None
i = None
item = None
key = None


print('START')
cap = cv.VideoCapture(0)
while True:
  ret , frame = cap.read()
  QRCode = pyzbar.decode(frame)
  for i in QRCode:
    print(item.data.decode())
  cv.imshow('Window',frame)
  key = cv.waitKey(100)
  if key == (ord('q')):
    break
cv.destroyAllWindows()
cap.release()
print('The End') 
