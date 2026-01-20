import smtplib

sender_email = "umair.arshad0156@gmail.com"
sender_password = "tvdecahftumuhtsu"

receiver_email = input("Enter recipient email: ")
subject = input("Enter subject: ")
body = input("Enter message body: ")

message = f"Subject: {subject}\n\n{body}"

try:
    with smtplib.SMTP("smtp.gmail.com", 587) as server:
        server.starttls()
        server.login(sender_email, sender_password)
        server.sendmail(sender_email, receiver_email, message)
        print("Email sent successfully!")
except Exception as e:
    print("Error:", e)