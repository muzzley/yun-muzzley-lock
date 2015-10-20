#include <Ciao.h>
#define DEBUG

int relay_pin = 13;
bool locked = true;
bool unlocking = false;
int timer = 0;
int max_time = 3000;

void setup() {
  pinMode(13, OUTPUT);
  Ciao.begin(115000);
  #ifdef DEBUG
    Serial.begin(57600);
    while(!Serial){}
    Serial.println("Started Ciao!");
  #endif
  digitalWrite(13, LOW);
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
      Serial.print("\nReceived a new message:");
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
      if (component == "yunlock1" && property == "locked") {
        response_msg = component + "|" + property + "|" + locked;
        #ifdef DEBUG
          Serial.print("\nLock is locked: " + locked);
        #endif

        Ciao.writeResponse("muzzley", id, response_msg);
        #ifdef DEBUG
          Serial.print("\nResponse: " + response_msg);
        #endif
      }
    }

    if(io.equals("w")){
      if (component == "yunlock1" && property == "locked"){
        if (value == "False") {
          locked = false;
          unlocking = false;
          digitalWrite(relay_pin, LOW);
        } else if (value == "True" && unlocking == false){
          locked = true;
          unlocking = true;
          digitalWrite(relay_pin, HIGH);
        }

        response_msg = component + "|" + property + "|" + locked;
        Ciao.writeResponse("muzzley", response_msg);

        #ifdef DEBUG
          Serial.print("\nUpdate Message sent: " + response_msg);
        #endif
      }
    }
  }

  // Prevent unlocking for a long time
  if (timer >= max_time) {
    unlocking = false;
    digitalWrite(relay_pin, LOW);
    locked = false;
    String update_msg =  "yunlock1|locked|true";
    Ciao.writeResponse("muzzley", update_msg);
  }

  delay(100);
  if (unlocking == true) {
    timer += 100;
  }
}
