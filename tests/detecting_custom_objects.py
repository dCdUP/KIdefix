import tensorflow.keras
from PIL import Image, ImageOps
import numpy as np
import cv2 as cv #Please install with PIP: pip install cv2

TM_DATA = None
model = None
cap = None
ret = None
frame = None
PredictionVariable = None
key = None


print('Start')
# Disable scientific notation for clarity
np.set_printoptions(suppress=True)

# Load the model
model = tensorflow.keras.models.load_model('keras_model.h5')

# Create the array of the right shape to feed into the keras model
# The 'length' or number of images you can put into the array is
# determined by the first position in the shape tuple, in this case 1.
TM_DATA = np.ndarray(shape=(1, 224, 224, 3), dtype=np.float32)
cap = cv.VideoCapture(0)
while True:
  ret , frame = cap.read()
  cv.imshow('Window',frame)
  frame = cv.resize(frame, (224, 224))
  image_array = np.asarray(frame)
  # Normalize the image
  normalized_image_array = (image_array.astype(np.float32) / 127.0) - 1
  # Load the image into the array
  TM_DATA[0] = normalized_image_array
  PredictionVariable = model.predict(TM_DATA)
  print('Prediction:')
  print(PredictionVariable)
  key = cv.waitKey(2000)
  if key == (ord('q')):
    break
cv.destroyAllWindows()
cap.release()
print('The End')
