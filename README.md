### huge thanks to the amazing [rp2040 skeleton project](https://github.com/daveythacher/RP2040_SKELETON). it helped immensly setting up this project. i probably couldn't have done it without

# &lt;still need good name :)&gt;
#### A lighting focused midi controller

---
### Why?
I started this project as i wanted phisical controls to go with the [mydmx3](https://www.adj.com/mydmx-3) dmx controller software.  
Mydmx3 practicly only support midi as data in/out next to dmx out. So a midi controller it is.  
There are more than enough midi controllers on the market but almost all of them are audio focused in the controls. I couldn't really vind any that i would like for controlling lighting. So i decided to design and build my own.

### Requirements
I set a couple of requirements that i definetly wanted in my controler. As following:  
#### Controls:

- **motorized faders**. Mostly for dimming controls, enough in the playback section and 1 as Master.  
  I chose motorized so they could sync with the controlling software if the value changes and for for example if you were to switch banks to a new set of controls. (mydmx doesn't support that but i wanted to design my controller to work with almost anything.)

  
- **Buttons**. for playbacks/executors en general control, a whole lot.  
  Of Course. what would a controller be without a lot of buttons. I also want them to have black with transparent text keycaps and rgb leds below to show the status of the button.

- **Encoders**. Mostly speed control but could also be dimmer, at least 1 per "channel"/collumn and a couple spare.
  I wanted some encoders to be able to change the speed of scene/cue playbacks. But also for for example a dimmer channel dat isn't changed often but often enough to have phisical controls for.

- **Small Displays/Scribble Strips**. channel/collumn names, one per channel/collumn.  
  To show what cue/scene was mapped to that channel/collumn. If i implement bank switching inside the controller (as mydmx doesn't support like anything. only the most basic midi triggering) i want to see what cue i have mapped on that fader/buttons.
  And maybe also to show the fader/encoder value when changing. For if you want it to a specific value and the visual position isn't enough.

- **Keypad**. just one, numbers 0-9 + some modifiers.  
  Should speak for itself. just general number inputs and modifiers.

- **"Master" Display**. (relatively) big display, just one.  
   A around 3a4" touch display for configuration of the controller and general info. Main controls for anything happening inside the controller.

- **Leds**. A lot. most RGB some just Amber.  
  I want all the buttons to have a seperate controllable RGB led to show the buttons status. and about 16 mono Amber leds around the encoders to show their value.

#### Conectivity:

- **usb midi**. one usb-B port.
  To connect to a pc running for example mydmx.

- **hardware midi**. 2 or 3 din-5 ports.
  To connect to other midi gear or any controller that has hardware midi ports on it. Should have the same data as the usb midi port

- **External Switch Ports**. 2a3 x 1/4" jack.
  To connect external footswitches or pedals. should support normal on/off footswitches and maybe one or 2 can have analog value support.

- **Desk Light**. xlr-4?.
  A xlr connector that support a lot of desk lights. preferably xlr-4 so it isn't confused with audio or dmx signals. Sadly there isn't a standard for desk ligths as far as i can find.

- **Powercon Socket**. Blue one. maybe also power out.  
  Of cource. It needs some power to run. prefereably powercon (true1??) but a C14 socket would also work.  
  with the motor faders and a lot of leds the usb supplied power wont be enough.

#### And here are some features i want to support but arent required for the mvp: 

- **USB Hub**. Probably USB-A sockets.  
  To connect more devices downstream from the controller

- **RTP MIDI**. Wifi/Ethernet  
  Using a ESP32 or similar to handle the network stack and enable the controller to communicate either wireless or via a ethernet cable.  
  Adding to the already available midi connection options of USB-MIDI and hardware-MIDI

- **Web Server**.  
  Maybe a configuration webserver as the display will be quite small. would also run on the ESP32 that handels the network.  
  it connects to the main rp2040 using uart.
