from flask import Flask, render_template, Response
import cv2
import urllib
import numpy as np

app = Flask(__name__)

defaultCam = False

url="http://192.168.0.84/cam-hi.jpg"

if defaultCam:
    camera = cv2.VideoCapture(0)  # Change to your ESP32 cam URL if needed

def generate_frames():
    while True:
        if defaultCam:
            success, frame = camera.read()
            # print(frame)
            """
            Frame example
            [[ 14  17  15]
            [ 15  18  16]
            [ 16  19  17]
            ...
            [ 32  30  24]
            [ 32  30  24]
            [ 32  29  24]]]
            """
        else:
            img_resp=urllib.request.urlopen(url)
            imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
            frame=cv2.imdecode(imgnp,-1)
            success = True if frame is not None else False

            # print(frame)
        
            """
            Frame example
            [[23 19 14]
            [23 19 14]
            [23 19 14]
            ...
            [ 1  1  1]
            [ 1  1  1]
            [ 1  1  1]]]
            """
        # if not success:
        #     break
        # else:
        if success:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                    b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == "__main__":
    app.run(debug=True)


# Run server with
# 1. python .\video_stream.py