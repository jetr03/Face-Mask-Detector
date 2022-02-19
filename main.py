import numpy as np
import cv2
import datetime
import keras
import keras.backend as k
from keras.layers import Conv2D,MaxPooling2D,SpatialDropout2D,Flatten,Dropout,Dense
from tensorflow.keras.optimizers import Adam
from keras.preprocessing import image
from keras.models import Sequential,load_model
model=Sequential()
model.add(Conv2D(32,(3,3),activation='relu',input_shape=(150,150,3))) 
#Input images have dimensions 150 x 150 pixels having three color channels RGB
model.add(MaxPooling2D())
model.add(Conv2D(32,(3,3),activation='relu')) #relu: y=max(x, 0)
model.add(MaxPooling2D())
model.add(Conv2D(32,(3,3),activation='relu'))
model.add(MaxPooling2D())
# We created three layers of CNN 
model.add(Flatten())
# Flatten converts data into linear array which then serves as input for the next layer
model.add(Dense(100,activation='relu'))
#Dense implements the operation: output = activation(dot(input, kernel) + bias) 
model.add(Dense(1,activation='sigmoid')) 
# sigmoid = 1/(1+e^-x)
model.compile(optimizer='adam',loss='binary_crossentropy',metrics=['accuracy']) 
# adam is the best available optimizer
from keras.preprocessing.image import ImageDataGenerator
training_function = ImageDataGenerator(
        rescale=1./255,
        horizontal_flip=True,
        zoom_range=0.2,
        shear_range=0.2,
        )       
testing_function = ImageDataGenerator(rescale=1./255)
training_set = training_function.flow_from_directory(
        'train',
        target_size=(150,150),
        batch_size=20 ,
        class_mode='binary')
# We are feeding data to the model in packets to 20 each       
testing_set = testing_function.flow_from_directory(
        'test',
        target_size=(150,150),
        batch_size=20,
        class_mode='binary')
        # class is kept binary as the program will decide between mask and no mask
model_saved=model.fit_generator(
        training_set,
        epochs=20,
        validation_data=testing_set,
        )
model.save('maskdetection.h5',model_saved)
training_model=load_model('maskdetection.h5')
sample_image=image.load_img(r'insert_directory',
                          target_size=(150,150,3))
# In place of insert_directory,paste the location of the folder including the file 1-with-mask.jpg. 
# For_example C:\Users\v\Downloads\FaceMaskDetector-master\test\with_mask\1-with-mask.jpg
sample_image
sample_image=image.img_to_array(sample_image)
sample_image=np.expand_dims(sample_image,axis=0)
training_model.predict(sample_image)[0][0]
training_model=load_model('maskdetection.h5')
web_camera=cv2.VideoCapture(0)
face_cascade=cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
# multistage concatenation of several classifiers
while web_camera.isOpened():
    _,Image=web_camera.read()
    face=face_cascade.detectMultiScale(Image,scaleFactor=1.1,minNeighbors=4)
    for(x,y,w,h) in face:
        face_image = Image[y:y+h, x:x+w]
        cv2.imwrite('temp.jpg',face_image)
        sample_image=image.load_img('temp.jpg',target_size=(150,150,3))
        sample_image=image.img_to_array(sample_image)
        sample_image=np.expand_dims(sample_image,axis=0)
        pred=training_model.predict(sample_image)[0][0]
        if pred==1:
            cv2.rectangle(Image,(x,y),(x+w,y+h),(0,0,255),3)
            cv2.putText(Image,'STOP!! NO MASK',((x+w)//2,y+h+20),cv2.FONT_HERSHEY_DUPLEX,1,(0,0,255),3)
        else:
            cv2.rectangle(Image,(x,y),(x+w,y+h),(0,255,0),3)
            cv2.putText(Image,'MASK FOUND',((x+w)//2,y+h+20),cv2.FONT_HERSHEY_DUPLEX,1,(0,255,0),3)
        datet=str(datetime.datetime.now())
        cv2.putText(Image,datet,(410,460),cv2.FONT_HERSHEY_DUPLEX,0.5,(255,255,255),1)
    cv2.imshow('img',Image)
    if cv2.waitKey(1)==ord('q'):
        break
web_camera.release()
cv2.destroyAllWindows()
