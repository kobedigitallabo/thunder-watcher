The Thunder Watcher.
====
This device can sense the approach of lightning within several dozen kilometers, and make an alert to hide.
- Early warning indication of lightning storm activity within a 40km range.
- Provides distance estimation to the head of the storm.
- Detects both cloud-to-ground and intra-cloud (cloud-to-cloud) flashes.
- The intelligent algorithm provides for false disturber rejection.

# Description
The Thunder Watcher  is a programmable Wearable Device that detects the presence and approach of potentially hazardous lightning activity in the vicinity.  
It detects intra-cloud activity as well as cloud to ground ashes, often enabling risk to be evaluated for approaching storms.   
The AS3935 IC detects lightning activity as it approaches from up to 40 km away, which provides a much longer distance for lightning warning.  

# Demo
![ezgif.com-video-to-gif.gif (2.8 MB)](https://img.esa.io/uploads/production/attachments/3505/2017/04/27/10863/f30031aa-2af7-42f0-96c1-46a7f661c00a.gif)

# Requirement
* [ Arduino IDE 1.6.13](https://www.arduino.cc/en/main/OldSoftwareReleases)
* [FreqCounter Library](http://interface.khm.de/index.php/lab/interfaces-advanced/arduino-frequency-counter-library/)
* [ST7032 Library](https://github.com/tomozh/arduino_ST7032)

# Usage
1. Turn on the power switch.(Initialization is started.) 
1. You have to wait for a thunderstorm. 
1. When a thundercloud is detected, the LED will light up.
And the distance to the thundercloud is displayed on the LCD display. 
1. If thunderclouds are near, evacuate to a safe place.

# What do we need
* [an Arduino nano board](https://www.amazon.com/HiLetgo-ATmega328P-Controller-Development-Unsoldered/dp/B01DLIJQA2/ref=sr_1_2?s=industrial&ie=UTF8&qid=1493214301&sr=1-2&keywords=arduino+nano)

* [a Franklin Lightning Sensor (AS3935)](http://akizukidenshi.com/catalog/g/gK-08685/)

* [2x Round female pin header [5x1, 2.54mm]](https://www.amazon.com/Break-Away-Female-Headers-Machine/dp/B004G553U2/ref=sr_1_2?s=industrial&ie=UTF8&qid=1493214561&sr=1-2&keywords=Round+female+pin+header)
* 2x Male pin header [7x1, 2.54mm]
* [a  7x7 Perf Board  [2.54mm]](https://www.amazon.com/a14060500ux0490-Universal-Prototype-Solderable-Circuit/dp/B010XA3NZK/ref=sr_1_12?s=industrial&ie=UTF8&qid=1493214486&sr=1-12&keywords=universal+board)
*  a 6x4  Perf Board  [2.54mm]
* [a Tinned Copper Wire](https://www.amazon.com/dp/B000IJU260/ref=biss_dp_t_asn)
* [a Plastic Battery Holder for 2 x 3V CR2032 Coin Button Cell](https://www.amazon.com/Copapa-Plastic-Battery-Holder-CR2032/dp/B01N0L9JFU/ref=sr_1_fkmr2_1?ie=UTF8&qid=1493212948&sr=8-1-fkmr2&keywords=HiLetgo+CR2032+case)
* Watch Bands
* an LED
* [an LED Lens, Diffused Beam](http://cy.rsdelivers.com/product/asahi-rubber/a-48068l-kc/asahi-rubber-a-48068l-kc-led-lens-diffused-beam/5017104)
* [a 150 Ohm Resistor, 1/4 W](https://www.amazon.com/E-Projects-100EP514150R-150-Resistors-Pack/dp/B0185FGNI4/ref=sr_1_1?s=industrial&ie=UTF8&qid=1493213161&sr=1-1&keywords=150+Ohm+Resistors)
* [an Empty electronic lighter](https://www.amazon.com/Refillable-Cigarette-Lighter-Flashlight-Quantity/dp/B009Z2R1U6/ref=pd_bxgy_201_img_2?_encoding=UTF8&pd_rd_i=B009Z2R1U6&pd_rd_r=FFZ17SFNXYSHHH8J2C91&pd_rd_w=aNUmO&pd_rd_wg=rjKVa&psc=1&refRID=FFZ17SFNXYSHHH8J2C91)

![image.png (4.1 MB)](https://img.esa.io/uploads/production/attachments/3505/2017/05/02/10863/1bdc5e3a-7990-4fd5-8486-7ed1a0623e44.png)


##  Tools You Need
* Soldering iron
* Soldering iron stand
* Solder
* Lead Nippers
* Needle Nose Pliers
* Reverse Action Tweezers
* Utility Knife
* Stainless Steel Ruler
* Glue gun

![image.png (4.1 MB)](https://img.esa.io/uploads/production/attachments/3505/2017/05/01/10863/e3226e31-d4c3-49dc-abd2-eca56e0cdbb5.png)


# The circuit
<img width="500" alt="ThunderWatcher_circuit.png (495.1 kB)" src="https://img.esa.io/uploads/production/attachments/3505/2017/04/25/10863/da87048f-377e-47b5-bef6-a7888beddea0.png">

# Install
## Importing a FreqCounter Library
[Lab3 \- Laboratory for Experimental Computer Science](http://interface.khm.de/index.php/lab/interfaces-advanced/arduino-frequency-counter-library/)

In the Arduino IDE, navigate to Sketch > Include Library. At the top of the drop down list, select the option to "Add .ZIP Library''.
You will be prompted to select the library you would like to add.
Return to the Sketch > Import Library menu. You should now see the library at the bottom of the drop-down menu. It is ready to be used in your sketch. The zip file will have been expanded in the libraries folder in your Arduino sketches directory.

## Importing a ST7032 Library
[tomozh/arduino\_ST7032\- Arduino Liquid Crystal compatible library](https://github.com/tomozh/arduino_ST7032)

When you are on arduino_ST7032 project page, you press the 'Download ZIP' button which is located under the "Clone or Download" drop down.
This allows you to download the most recent version of the code as a zip archive.
![image.png (23.1 kB)](https://img.esa.io/uploads/production/attachments/3505/2017/04/27/10863/a65fd15c-09f3-4e49-b687-ce3d5450ec5a.png)

Down list, select the option to "Add .ZIP Library''.
You will be prompted to select the library you would like to add.
Return to the Sketch > Import Library menu. You should now see the library at the bottom of the drop-down menu. It is ready to be used in your sketch. The zip file will have been expanded in the libraries folder in your Arduino sketches directory.

# How to make
More info is recorded in the "howtomake.md" file.
[HowTo/arduino/How to make  Thunder Watcher.](/HowToMake-Desc.md)

# Contribution
1. Fork it ( http://github.com/ )
2. Create your feature branch (git checkout -b my-new-feature)
3. Commit your changes (git commit -am 'Add some feature')
4. Push to the branch (git push origin my-new-feature)
5. Create a new Pull Request



# Licence
[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)

# Author
[haru-kdl](https://github.com/haru-kdl)