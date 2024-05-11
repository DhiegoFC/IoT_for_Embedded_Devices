import time
import serial

class RAK3172:
    def __init__(self, port):
        self.ser = serial.Serial(port, 115200, timeout=10)
        self.config = {
            "dev_eui": "1122334455667788",
            "app_eui": "1122334455667788",
            "app_key": "11223344556677881122334455667788",
            "band": "6", # 6=AU915 4=EU868
            "dr": "2",
            "dr_join": "2",
            "adr": "0"
        }
        self.initialize_device()

    def send_at_command(self, command):
        print(command)
        self.ser.write((command + '\r\n').encode())
        response = self.ser.readline().decode().strip()
        print(response)
        return response

    def initialize_device(self):
        self.ser.reset_input_buffer()
        response = self.send_at_command("AT")
        if "OK" not in response:
            raise Exception("Device not responding as expected to ATR command.")

    def configure_device(self):
        commands = [
            f"AT+BAND={self.config['band']}",
            f"AT+DEVEUI={self.config['dev_eui']}",
            f"AT+APPEUI={self.config['app_eui']}",
            f"AT+APPKEY={self.config['app_key']}",
            f"AT+ADR={self.config['adr']}",
            #"AT+NJM=1",
            #f"AT+DR={self.config['dr']}",
        ]
        for cmd in commands:
            if "OK" not in self.send_at_command(cmd):
                print(f"Configuration failed with command: {cmd}")
                return False
        return True

    def join_network(self):
        #self.ser.timeout = 6  # Define o timeout para 6 segundos apenas para o join
        cmd = f"AT+DR={self.config['dr_join']}" # Define Join Message Data Rate
        self.send_at_command(cmd)
        for attempt in range(10):
            response = self.send_at_command("AT+JOIN=1")
            if "OK" in response:
                join_response = self.ser.readline().decode().strip()
                print(join_response)
                if "JOINED" in join_response:
                    print("Join successful!")
                    return True
                else:
                    print(f"Join failed on attempt {attempt + 1}: {join_response}")
                    print("Wait 10 seconds...")
                    time.sleep(10)            
            else:
                print(f"Unexpected response on join attempt {attempt + 1}: {response}")
        return False

    def send_messages(self, message_type, num_messages, interval_seconds):
        confirm = '1' if message_type == 'C' else '0'
        self.send_at_command(f"AT+CFM={confirm}")
        for i in range(num_messages):
            cmd = f"AT+DR={self.config['dr']}" # Define Send Message Data Rate
            self.send_at_command(cmd)
            print(f"Sending message {i + 1}")
            self.send_at_command("AT+SEND=2:161616161616161616")
            if message_type == "C":   
                cnf_response = self.ser.readline().decode().strip()
                print(cnf_response)
            time.sleep(interval_seconds)

if __name__ == "__main__":
    # Verify RAK3172 USB Port
    lora_module = RAK3172('COM4')
    if lora_module.configure_device() and lora_module.join_network():
        message_type = input("Enter message type (C for confirmed, U for unconfirmed): ").upper()
        num_messages = int(input("Enter the number of messages to send: "))
        interval_seconds = int(input("Enter the interval between messages (in seconds): "))
        lora_module.send_messages(message_type, num_messages, interval_seconds)
    else:
        print("Failed to configure or join the network.")
