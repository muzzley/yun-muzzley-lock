#include <Ciao.h>
#define DEBUG

int relay_pin = 13;
bool locked = true;
bool unlocking = false;
int timer = 0;
int max_time = 3000;

String lock_component = String("yunlock1");
String lock_property = String("status");

void setup() {
  pinMode(relay_pin, OUTPUT);
  Ciao.begin(250000);
  #ifdef DEBUG
    Serial.begin(57600);
    while(!Serial){}
    Serial.println("Started Ciao!");
  #endif
  digitalWrite(relay_pin, HIGH);
  delay(3000);
  digitalWrite(relay_pin, LOW);
}

void loop() {
  #ifdef DEBUG
    while(!Serial){}
  #endif

  CiaoData data;
  data = Ciao.read("muzzley");

  String command[5];
  String io;
  String component;
  String property;
  String value;
  String cid;
  String delimiter = String("|");

  if(!data.isEmpty()){
    String id = data.get(0);
    String message = data.get(1);
    String _cid = data.get(2);

    #ifdef DEBUG
      Serial.print("\n\n\nReceived a new message:");
      Serial.print("\nMessage Id: ");  // Ciao message ID
      Serial.print(id);
      Serial.print("\nMessage: ");     // Message (io/Component/Property/Value)
      Serial.print(message);
      Serial.print("\n_CID: ");        // Muzzley cid
      Serial.print(_cid);
      Serial.print("\n");
    #endif

    splitString(message, delimiter, command, 4);

    io = command[0];
    component = command[1];
    property = command[2];
    value = command[3];

    #ifdef DEBUG
      //Display the received message info
      Serial.print("\nIo:");
      Serial.print(command[0]);
      Serial.print("\nComponent:");
      Serial.print(command[1]);
      Serial.print("\nProperty:");
      Serial.print(command[2]);
      Serial.print("\nValue:");
      Serial.print(command[3]);
      Serial.print("\n");
    #endif

    String response_msg;

    if (io.equals("r")) {
      if (component == lock_component && property == lock_property) {
        
        if(locked){
          #ifdef DEBUG
            Serial.print("\nLock is locked!");
          #endif
          response_msg = lock_component + "|" + lock_property + "|" + "False";
        }else{
          #ifdef DEBUG
            Serial.print("\nLock is unlocked!");
          #endif
          response_msg = lock_component + "|" + lock_property + "|" + "True";
        }
        
        Ciao.writeResponse("muzzley", id, response_msg);
        #ifdef DEBUG
          Serial.print("\nResponse: " + response_msg);
        #endif
      }
    }

    if(io.equals("w")){
      if (component == lock_component && property == lock_property){
        if (value == "False") {
          timer=0;
          locked = true;
          unlocking = false;
          response_msg = lock_component + "|" + lock_property + "|" + "False";
          digitalWrite(relay_pin, LOW);
          #ifdef DEBUG
            Serial.print("\nLocked!");
          #endif
        } else if (value == "True" && unlocking == false){
          timer=0;
          locked = false;
          unlocking = true;
          response_msg = lock_component + "|" + lock_property + "|" + "True";
          digitalWrite(relay_pin, HIGH);
          #ifdef DEBUG
            Serial.print("\nUnlocked!");
          #endif
        }
        
        Ciao.write("muzzley", response_msg);

        #ifdef DEBUG
          Serial.print("\nUpdate Message sent: " + response_msg);
        #endif
      }
    }
  }

  // Prevent unlocking for a long time
  if (timer >= max_time) {
    timer=0;
    locked = true;
    unlocking = false;
    digitalWrite(relay_pin, LOW);
    String update_msg =  lock_component + "|" + lock_property + "|" + "False";
    Ciao.write("muzzley", update_msg);
   
  }

  delay(100);
  if (unlocking == true) {
    timer += 100;
  }
}
