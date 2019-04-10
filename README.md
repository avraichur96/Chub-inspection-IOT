# Chub-inspection-IOT
An IOT solution for  pneumatic machine that inspects the weights of Chubs (adhesive sachets)
The working video can be found [here](https://drive.google.com/open?id=0B2yX3u2D42m-Q0xZWGhTcS1mZVRZMHB3eHkzZDlpNjRLdlg0)

## Task

Industrial adhesive sachets(called chubs) flowing in a water canal are to be inspected for their weights. The following operations are to be performed:

1) Pick the chub from the water conveyor
2) Weigh the chub using a load cell 
3) Allow the chub back into the flow
4) Update the weight on a local site (using _ESP8266_ as a **WIFI HOTSPOT**)

We used a belt conveyor instead of water to test our pneumatics model.

## features 

1) Overall pneumatic operation with suction cup 
2) delay and drop height of chub, parameters adjustable 
3) The machine acts as a **WIFI HOTSPOT**   

## Pneumatics cycle 

The best option to pick the chub off flowing water is to use a suction cup. We used suction cup along with pneumatic cylinders for actuation. Infrared sensors were used to detect the entry of single Chub. The following cycle takes place:

1) The Infrared sensor detectsthe arrival of chub  
2) Vertical cylinder moves down and suction starts (delay parameter)
3) The chub is taken above along with the vertical cylinder 
4) The horizontal cylinder comes into position on which a Load Cell is mounted 
5) The suction is released and Chub drops onto platform (drop height parameter)
6) The Load cell measures weight and the horizontal cylinder moves back to its initial position 
7) A constrainer (M.S. flat rod) pushes the chub back onto conveyor

The working video can be found [here](https://drive.google.com/open?id=0B2yX3u2D42m-Q0xZWGhTcS1mZVRZMHB3eHkzZDlpNjRLdlg0) for clarity.

## Communication between the ESP and arduino 

Serial communication is the main protocol used for communication. There are still, the following caveats:

1) The arduino cannot be interrupted for weights when the pneumatic cycle is in progress.
2) The ESP module should not be queried for drop height and delay parameter, when the ESP is serving web pages. 

Thus, 'approach' and 'listenn' pins are introduced (basically Rx and Tx pins of Serial communication) 
Arduino can request for delay, drop by its approach(Tx) pin and wait for response from ESP through the listenn(Rx) pin. The reverse applies to ESP. The connection are shown below for clarity- 
                    
                  *Arduino (Rx or listenn)  ----------- > ESP (Tx or approach)*
                  *Arduino (Tx or approach) ----------- > ESP (Rx or listenn)*
                  
                  
                  
                  
