import serial
import time

serial_port = "/dev/tty.usbmodem101"
baud_rate = 9600
file_name = "data.csv"

def save_card() -> None:
    ser = serial.Serial(serial_port, baud_rate)

    with open(file_name, "wb") as output_file:
        print(f"Saving data to {file_name}")
        while True:
            if ser.in_waiting > 0:
                data = ser.read(ser.in_waiting)
                print(data.decode('utf-8'), end="")

                filtered_data = data.replace(b"~", b"")
                output_file.write(filtered_data)

                if b"~" in data:
                    ser.close()
                    break

    print("\nFile saved successfully")

if __name__ == "__main__":
    save_card()