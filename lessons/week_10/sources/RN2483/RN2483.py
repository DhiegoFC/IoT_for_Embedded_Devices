import time
import serial

# Configurações do dispositivo com comandos mac e do ChirpStack
DEV_EUI = "0011223344556677"
APP_EUI = "0011223344556677"
APP_KEY = "00112233445566770011223344556677"
CHIRPSTACK_HOST = "192.168.1.2"
FREQ = "868200000"
CR = "4/5"
SF = "4"
BW = "125"
CHIRPSTACK_PORT = 1717

# Comando para enviar comandos mac para o dispositivo
def send_mac_command(ser, cmd):
    ser.write(cmd.encode() + b"\r\n")
    response = ser.readline().strip()
    return response.decode()

#Inicializa a conexão serial com o dispositivo com comandos mac
ser_mac = serial.Serial('COM6', 57600)
time.sleep(2)

send_mac_command(ser_mac, "sys reset")
time.sleep(2)

#Configuração do dispositivo com comandos radio
ok_counter_radio = 0
ok_counter_mac = 0

response_radio_cr = send_mac_command(ser_mac, "radio set cr " + CR)
response_radio_bw = send_mac_command(ser_mac, "radio set bw " + BW)
response_radio_freq = send_mac_command(ser_mac, "radio set freq " + FREQ)

if "ok" in response_radio_cr:
    ok_counter_radio += 1
else:
    print("Error in radio command (CR), Response:", response_radio_cr)

if "ok" in response_radio_bw:
    ok_counter_radio += 1
else:
    print("Error in radio command (BW), Response:", response_radio_bw)

if "ok" in response_radio_freq:
    ok_counter_radio += 1
else:
    print("Error in radio command (Freq), Response:", response_radio_freq)

if ok_counter_radio == 3:
    print("Radio commands OK")
else:
    print("Error in radio configurations. Aborting.")

#Aguarda 2 segundos antes de enviar os comandos mac
time.sleep(2)

#Configuração do dispositivo com comandos mac 
response_mac_deveui = send_mac_command(ser_mac, "mac set deveui " + DEV_EUI)
response_mac_appeui = send_mac_command(ser_mac, "mac set appeui " + APP_EUI)
response_mac_appkey = send_mac_command(ser_mac, "mac set appkey " + APP_KEY)
response_mac_dr = send_mac_command(ser_mac, "mac set dr " + SF)

if "ok" in response_mac_deveui:
    ok_counter_mac += 1
else:
    print("Error in mac command (DevAddr), Response:", response_mac_deveui)

if "ok" in response_mac_appeui:
    ok_counter_mac += 1
else:
    print("Error in mac command (AppEUI), Response:", response_mac_appeui)

if "ok" in response_mac_appkey:
    ok_counter_mac += 1
else:
    print("Error in mac command (AppKey), Response:", response_mac_appkey)

if "ok" in response_mac_dr:
    ok_counter_mac += 1
else:
    print("Error in mac command (DR), Response:", response_mac_dr)

if ok_counter_mac == 4:
    print("Mac commands OK")
else:
    print("Error in mac configurations. Aborting.")

#Join na rede LoRaWAN
joined = False
max_attempts = 10
join_count = 0

while not joined and join_count < max_attempts:
    join_count += 1
    print("Trying to join", join_count)
    response1 = send_mac_command(ser_mac, "mac join otaa")
    print(response1)

    if "ok" in response1:
        response2 = ser_mac.readline().strip().decode()
        print(response2)
        if "denied" in response2:
            print("Join denied. Retrying...")
            time.sleep(5)
        elif "joined" in response2 or "accepted" in response2:
            joined = True
            print("Join successful!")
            time.sleep(5)
        else:
            print("Unknown response after join2 command:", response2)
    else:
        print("Unknown response after join1 command:", response1)

if not joined:
    print("Unable to join after multiple attempts.")

#Tipo de mensagem
while True:
    message_type = input("Enter message type (confirmed/unconfirmed): ").lower()

    if message_type not in ["confirmed", "unconfirmed"]:
        print("Invalid message type. Please enter 'confirmed' or 'unconfirmed'.")
        continue  

    message_counter = 1
    confirm = True

    while True:
        #Envia uma mensagem para o ChirpStack
        print("Sending Uplink Message", message_counter)
        if confirm:
            response = send_mac_command(ser_mac, "mac tx cnf 1 1616")
            print("Sending confirmed message")
        else:
            response = send_mac_command(ser_mac, "mac tx uncnf 1 1616")
            print("Sending unconfirmed message")

        message_counter += 1

        if "mac_tx_ok" or "ok" or "accepted" in response:
            print("Message sent successfully!")
        else:
            print("Response:", response)

        time.sleep(30)
