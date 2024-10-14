import cv2
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
import tkinter as tk
from tkinter import messagebox
import threading
import time

SMTP_SERVER = "smtp.gmail.com"
SMTP_PORT = 587
SENDER_EMAIL = "shubham0204.college@gmail.com"
SENDER_PASSWORD = "vyzs cmfq oldy wcqd"
RECEIVER_EMAIL = "equipintelligence@gmail.com"

def send_email(image):
    msg = MIMEMultipart()
    msg['From'] = SENDER_EMAIL
    msg['To'] = RECEIVER_EMAIL
    msg['Subject'] = "Someone at the door!"

    text = MIMEText("A face has been detected at your door. Please check the attached image.")
    msg.attach(text)

    image_data = cv2.imencode('.jpg', image)[1].tostring()
    image_mime = MIMEImage(image_data, name="visitor.jpg")
    msg.attach(image_mime)

    try:
        server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        server.starttls()
        server.login(SENDER_EMAIL, SENDER_PASSWORD)
        server.send_message(msg)
        server.quit()
        print("Email sent successfully")
    except Exception as e:
        print(f"Error sending email: {e}")

def show_alert():
    root = tk.Tk()
    root.withdraw()
    result = messagebox.askquestion("Door Alert", "Someone is at the door. Open?")
    if result == 'yes':
        print("Door opened")
    else:
        print("Door remains closed")

def main():
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
    cap = cv2.VideoCapture(0)

    face_detected = False
    last_detection_time = 0
    cooldown_period = 60  # seconds

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to grab frame")
            break

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)

        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
            current_time = time.time()
            if not face_detected and (current_time - last_detection_time) > cooldown_period:
                face_detected = True
                last_detection_time = current_time
                threading.Thread(target=send_email, args=(frame,)).start()
                threading.Thread(target=show_alert).start()

        cv2.imshow('Video', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()