# Arduino Yun Muzzley Lock #

This repo contains the code for the Arduino Yun - Muzzley Lock project.

To take part of the Arduino Yun IoT capabilities, this project uses the new Arduino Ciao platform and the Muzzley Cloud to interact wih the "outside world"


# What is Arduino Ciao?

Ciao Connectors makes the Arduino boards able to communicate with the "outside world" very easily.

It only needs the Ciao Library running on the MCU (microcontroller) side to interact with your Arduino sketch code, and the Ciao Core running over the Linino OS to enable the communication with several modules called connectors.

More info about Arduino Ciao: [http://labs.arduino.org/ciao](http://labs.arduino.org/ciao)


# What is Muzzley?

Muzzley is an app for connected devices.

It ables the user to intearact with their connected devices using his smartphone or tablet, using wifi or 3G/LTE conectivity.

More info about Muzzley: [https://www.muzzley.com](https://www.muzzley.com)



# How do I get set up?

##Dependencies

* [Linino OS](http://www.linino.org) running on a Arduino / Linino compatible board. More info about the Linino OS installation on a Arduino Yun board can be found [here](http://labs.arduino.org/How+to+upgrade+the+Linino+distribution+for+Arduino+Yun)
* Install Arduino Ciao Core following the instructions [here](http://labs.arduino.org/Ciao+setup)
* Install the Arduino [Ciao Library](https://github.com/arduino-org/CiaoMCU) on the [Arduino IDE](https://www.arduino.cc/en/Main/Software) / [Arduino Studio](http://labs.arduino.org/tiki-index.php?page=Arduino+Studio)

##Install the Muzzley connector

1) Copy the Muzzley Connector folder to the Arduino Ciao **connectors** folder

2) Copy the Muzzley Connector configuration file to the Arduino Ciao **conf** folder

3) Install the following module dependencies on the Linino OS:

* distribute
* python-openssl
* pip
* requests


##Create your Muzzley App

1) Login on our [developers website](https://www.muzzley.com/developers) (or create a new account) and open the Apps page.

2) Now click on Create App and give your Muzzley App a name and a description like "Arduino Yun" and "Arduino Yun Muzzley example".

3) Select the Integration Type as "Cloud to Device" and add a name to the Provider field like "Arduino". It reffers to the manufacturers name that is integrating their products with us.

4) Complete the folowing fields "Profile Photo URL", "Channel Photo URL" and "Tile Photo URL" with some product images URLs. This images will appear on the Muzzley app then the user will add a new device, and on the respectve devices list.

5) The "Interface UUID" refers to the Muzzley interface that will be presented to the end user. You can update this field later, after reading our Interface documentation [here](http://clients.muzzley.com/documentation#interfaces), and implemeting you own interface. For now, please continue with the following steps to create your Muzzley App.

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


