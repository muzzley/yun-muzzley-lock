# Arduino YÚN Muzzley Lock #

For one or other reason, all of us have wished to remotely open our door to someone we trust and there was no way to do it. Or committed the most common mistake of leaving the keyring behind when closing our door…

![YUN_Board](./images/YUN-Board.png)

If you wish to hack your electric door lock and be able to unlock it through your smartphone, this is the time to embrace a very simple project where you will only need a solid-state relay to act on the lock, an Arduino YÚN to provide the WiFi connection, some simple wiring and Muzzley app!

Muzzley is a cloud based app that gathers all of your connected devices and puts them to work together in an intuitive way.
The app allows connected devices of different brands to communicate with and respond to each other. This not only brings more value to the majority of consumers who are still figuring out the value of the smart home, but also to the brands we integrate with.

![YUN_Muzzley_Context](./images/YUN-Muzzley-Context.png)

Some of the brands that work with us: Philips Hue Lamp, Nest Learning Thermostat®, Nest Protect: Smoke + Carbon Monoxide™, Rachio Smart Sprinkler and Koubachi Wi-Fi Plant Sensor.

Alongside this, we're working on a machine learning algorithm that will make these devices more intuitive and customized than ever. Because we believe that people have better things to do than to automate their devices, our goal is to create an ecosystem that adapts to the user's patterns and behaviors.

Muzzley is available in iOS, Android and Windows Phone.
More info about Muzzley: https://www.muzzley.com

f: /muzzleypower

t: @muzzleypower


# What is Arduino Ciao?


Arduino Ciao is a easy-to-use and powerful technology that enables Arduino sketches to communicate intuitively with the "outside World". It aims to simplify interaction between microcontroller and Linino OS  allowing a variety of connections with most common protocols, third-party services and social networks.

Ciao has been designed and developed to be modular and easily configurable. Its goal is to support several connectors capable of interacting with system resources (filesystem, console, memory) and to communicate with the most common and useful protocols (XMPP, HTTP, WebSocket, COAP, etc..) and applications (Jabber, WeChat, Twitter, Facebook, etc.).

It only needs the Ciao Library running on the MCU (microcontroller) side to interact with your Arduino sketch code, and the Ciao Core running over the Linino OS to enable the communication with several modules called connectors.

More info about Arduino Ciao: [http://labs.arduino.org/ciao](http://labs.arduino.org/ciao)


# How to wire the lock to the Arduino?

The image below shows the wiring needed to connect the lock to the Arduino board:

![YUN_Lock_Proj](./images/YUN-Lock-Proj.png)


# How do I get set up?

##Dependencies

* [Linino OS](http://www.linino.org) running on a Arduino / Linino compatible board. More info about the Linino OS installation on a Arduino YÚN board can be found [here](http://labs.arduino.org/How+to+upgrade+the+Linino+distribution+for+Arduino+Yun)
* Install Arduino Ciao Core following the instructions [here](http://labs.arduino.org/Ciao+setup)
* Install the Arduino [Ciao Library](https://github.com/arduino-org/CiaoMCU) on the [Arduino IDE](https://www.arduino.cc/en/Main/Software) / [Arduino Studio](http://labs.arduino.org/tiki-index.php?page=Arduino+Studio)
* Install the following python module dependencies on the Linino OS:
 * distribute
 * python-openssl
 * paho-mqtt
 * urllib3
 * requests

##Install the Muzzley connector

1) Download the project from the following [url](https://github.com/muzzley/arduino-ciao-muzzley-connector) and follow the included set up instructions.


##Create your Muzzley App

1) Login on our [developers website](https://www.muzzley.com/developers) (or create a new account) and open the Apps page.

2) Now click on Create App and give your Muzzley App a name and a description like "Arduino Yun" and "Arduino YÚN Muzzley example".

3) Select the Integration Type as "Cloud to Device" and add a name to the Provider field like "Arduino". It reffers to the manufacturers name that is integrating their products with us.

4) Complete the folowing fields "Profile Photo URL", "Channel Photo URL" and "Tile Photo URL" with some product images URLs. This images will appear on the Muzzley app then the user will add a new device, and on the respectve devices list.

5) The "Interface UUID" refers to the Muzzley interface that will be presented to the end user. You can update this field later, after reading our Interface documentation [here](http://clients.muzzley.com/documentation#interfaces), and implementing you own interface. For now, the html, css and javascript code used for this example is provided in the widget folder, and can be used to create your first Muzzley widget.

6) Select the "Device discovery" as "UPNP". This is the method used by the Arduino Ciao Muzzley connector to authenticate the device in your local network. 

7) Finally add some e-mail addresses to the "Email Access List", including yours. This is the list of authortized users to add your Arduino devices using your Arduino Muzzley App.

8) Click on "save changes" to store your configuration.

9) Now you will have to create a "profile spec" to specify some characterictics of your product. Please read our documentation on the following [link](http://clients.muzzley.com/documentation#selfcare).


##Update your connector configuration file


1) Update the Muzzley connector configuration file muzzley.json.conf in the **/etc/muzzley/** folder with the details about your own Muzzley App.

* **app_uuid** - Muzzley App unique identifier.

* **app_token** - Muzzley App authentincation token.

* **profile_id** - Muzzley profile specification unique identifier.

* **serial_number** - It can be any uuid string referring one instace of your device.
                      For exampe if your have 2 boards running your Muzzley App, they must be identified with different uuid's.

* **friendly_name** - It will be the custom name of your device.
                      It may be changed as as you will at any time, and it will be presented to the user on the Muzzley App as the primary device name.

* **components** -  One array with the Arduino componets acordingly with what as specicfied on our website. Id must contain the id, label and type for each one of them.


##Upload the Arduino Sketch

1) Connect the Arduino USB port to the computer, if not already connected, and open the Arduino IDE.

2) Open the doorlock.ino skecth, compile it, select the correst serial port and finally upload it to the Arduino board.

3) Check the video [here](https://www.youtube.com/watch?v=r1HL9QZI-as), and Enjoy! :)


