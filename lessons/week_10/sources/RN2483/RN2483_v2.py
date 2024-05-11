
import time
import serial

class RN2483:
    def __init__(self, port):
        self.ser = serial.Serial(port, 57600, timeout=10)
        self.config = {
            'dev_eui': '0011223344556677',
            'app_eui': '0011223344556677',
            'app_key': '00112233445566770011223344556677',
            'freq': '868200000',
            'cr': '4/5',
            'sf': '4',
            'bw': '125'
        }
        time.sleep(2)  # Wait for serial connection to establish

    def send_at_command(self, command):
        self.ser.write((command + "\r\n").encode())
        return self.ser.readline().strip().decode()

    def configure_device(self):
        self.send_at_command("sys reset")
        time.sleep(2)
        if "ok" in self.send_at_command(f"radio set cr {self.config['cr']}") and            "ok" in self.send_at_command(f"radio set bw {self.config['bw']}") and            "ok" in self.send_at_command(f"radio set freq {self.config['freq']}"):
            return True
        return False

    def join_network(self):
        self.send_at_command(f"mac set deveui {self.config['dev_eui']}")
        self.send_at_command(f"mac set appeui {self.config['app_eui']}")
        self.send_at_command(f"mac set appkey {self.config['app_key']}")
        self.send_at_command(f"mac set dr {self.config['sf']}")
        for attempt in range(10):
            response = self.send_at_command("mac join otaa")
            if "ok" in response:
                time.sleep(10)  # Wait for join process
                if "accepted" in self.ser.readline().decode().strip():
                    print("Join successful!")
                    return True
                else:
                    print(f"Join failed on attempt {attempt + 1}")
            else:
                print(f"Unexpected response on join attempt {attempt + 1}: {response}")
        return False

    def send_messages(self, message_type, num_messages, interval_seconds):
        for i in range(num_messages):
            self.send_at_command(f"mac tx {message_type.lower()} 1 48656C6C6F")
            response = self.ser.readline().decode().strip()
            print(f"Message {i + 1} status: {response}")
            time.sleep(interval_seconds)

if __name__ == "__main__":
    lora_device = RN2483('COM6')
    if lora_device.configure_device() and lora_device.join_network():
        message_type = input("Enter message type (C for confirmed, U for unconfirmed): ").upper()
        num_messages = int(input("Enter the number of messages to send: "))
        interval_seconds = int(input("Enter the interval between messages (in seconds): "))
        lora_device.send_messages(message_type, num_messages, interval_seconds)
    else:
        print("Failed to configure or join the network.")
