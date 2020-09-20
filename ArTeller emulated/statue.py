import paho.mqtt.client as mqtt
import random as rnd
import time

#ThingsBoard integration
ACCESS_TOKEN_1='lvULnyzvACSXReaJWr6V'   #this access token is used by discobolo to connect to ThingsBoard
ACCESS_TOKEN_2='BSIntglUNCJcSAEensUs'   #this access token is used by laocoonte to connect to ThingsBoard
broker="demo.thingsboard.io"            #default broker provided by ThingsBoard with its port
port=1883

#function definitions
def on_connect(client, userdata, flags, rc):        #connection feedback
    print("Connected with result code " + str(rc))

def on_publish(client,userdata,result):             #publish feedback
    print("data published to thingsboard \n")
    pass

def get_visitor():
    rand = rnd.uniform(0,100)
    if rand > 50:
        return 'bambino'
    else:
        return 'adulto'



#building json payload
def build_payload():
    vis = get_visitor()
    if vis == 'bambino':
        payload = '{"bambino":"bambino",'
    else:
        payload = '{"adulto":"adulto",'

    return (payload,vis)

#instantiating mqtt client for discobolo
discobolo = mqtt.Client()
discobolo.on_connect = on_connect
discobolo.on_publish = on_publish    
discobolo.username_pw_set(ACCESS_TOKEN_1)
print("discobolo created successfully")

#instantiating mqtt client for laocoonte
laocoonte = mqtt.Client()
laocoonte.on_connect = on_connect
laocoonte.on_publish = on_publish    
laocoonte.username_pw_set(ACCESS_TOKEN_2)
print("laocoonte created successfully")

#connection to thingsboards mqtt broker
discobolo.connect(broker,port,60)
laocoonte.connect(broker,port,60)

topic = "v1/devices/me/telemetry"       #in thingsboard every device has its own topic, which is telemetry

adulti_discobolo = 0
bambini_discobolo = 0
visitors_discobolo = 0
adulti_laocoonte = 0
bambini_laocoonte = 0
visitors_laocoonte = 0

initial_payload = '{"numero_adulti":"0","numero_bambini":"0","visitors":"0"}'
discobolo.publish(topic, initial_payload)
laocoonte.publish(topic, initial_payload)

while True:
    (payload,visitor) = build_payload()
    print(payload)
    if visitor == 'bambino':
        bambini_discobolo = bambini_discobolo + 1
        payload += '"triggered":"bambino",'
    else:
        adulti_discobolo = adulti_discobolo + 1
        payload += '"triggered":"adulto",'
    visitors_discobolo = visitors_discobolo + 1
    payload += '"numero_adulti":"' + str(adulti_discobolo) + '","numero_bambini":"'+ str(bambini_discobolo) + '","visitors":"' + str(visitors_discobolo) + '"}'
    discobolo.publish(topic, payload)    #publish random values to discobolo telemetries
    print("pubblicato discobolo")
    time.sleep(10)


    (payload,visitor) = build_payload()
    print(payload)
    if visitor == 'bambino':
        bambini_laocoonte = bambini_laocoonte + 1
        payload += '"triggered":"bambino",'
    else:
        adulti_laocoonte = adulti_laocoonte + 1
        payload += '"triggered":"adulto",'
    visitors_laocoonte = visitors_laocoonte + 1
    payload += '"numero_adulti":"' + str(adulti_laocoonte) + '","numero_bambini":"'+ str(bambini_laocoonte) + '","visitors":"' + str(visitors_laocoonte) + '"}'
    laocoonte.publish(topic, payload)    #publish random values to laocoonte telemetries
    print("pubblicato laocoonte")
    time.sleep(10)

discobolo.loop_forever()
laocoonte.loop_forever()