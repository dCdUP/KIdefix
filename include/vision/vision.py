from ultralytics import YOLO

def detectState(path):
    model = YOLO("./module/traffic_signs.pt") #lädt das Modell
    print(path)
    source = fr"{path}" #Pfad des Bildes

    results = model(source) #gibt das Bild ins Modell zur Analyse

    for result in results:
        boxes = result.boxes #the bounding boxes

        #Loop through each detected object
        for box in boxes:
            class_id = box.cls #was erkannt wurde
            confidence = box.conf #der confidence score des erkannten Objekts
            x_min, y_min, x_max, y_max = box.xyxy[0] #die Koordinaten des erkannten Objekts

            print(f"Detected object with Class ID: {class_id} and Confidence: {confidence}")
            print(f"Bounding Box: [{x_min}, {y_min}, {x_max}, {y_max}]")

        result.show() #öffnet das Bild mit eingezeichneten Boxen und Ergebnissen
        #result.save(filename = "result.jpg") #speichert das Ergebnis als Bild

    if boxes.conf.item() >0.5 and (boxes.cls == 40 or boxes.cls == 24 or boxes.cls == 22 or boxes.cls == 38 or boxes.cls == 0 or boxes.cls == 34): #wenn der Konfidenzscore über 30% ist und das Stopschild (ID= 40.) erkannt wurde
        print("folgendes gefunden: ",result.boxes.cls.item())
        return int(result.boxes.cls.item())
    else:
        print("Nichts gefunden")

def movePosition(path):
    return (State,Xcoordinate)