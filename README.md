# Prerequisite open source libraries for voice clients
Voice Client utilities

## Setting environment for Raspberry Pi3 
### Create root account password and allow login

    // create password
    sudo passwd root
  
    // allow login with root
    sudo vi /etc/ssh/sshd_config
  
    // Change the configuration as following
    PermitRootLogin yes
    StrictModes no
  
    // reboot
    reboot
  
### Add Wifi connectivity

    // edit wpa_supplicant.conf
    sudo vi /etc/wpa_supplicant/wpa_supplicant.conf
  
    // add wifi ssid and password
    network={
        ssid="xxx"
        psk="xxx"
    }
  
    // reboot and check if the wlan0 is visible
    ifconfig
  
## Install USB Sound Card

### Add device info to alsa-base.conf

    vi /etc/modprobe.d/alsa-base.conf

    // Add the following to alsa-base.conf
    options snd-usb-audio index=0
    options snd_bcm2835 index=1
    options snd slots=snd-usb-audio,snd_bcm2835

    // Now, reboot the Raspberry Pi
    reboot 

    // After rebooting, check if the USB sound card is attached
    aplay -l
    
    **** List of PLAYBACK Hardware Devices ****
    card 0: S2 [Sound Blaster Play! 2], device 0: USB Audio [USB Audio]
    Subdevices: 1/1
    Subdevice #0: subdevice #0
    card 1: ALSA [bcm2835 ALSA], device 0: bcm2835 ALSA [bcm2835 ALSA]
    Subdevices: 8/8
    Subdevice #0: subdevice #0
    Subdevice #1: subdevice #1
    Subdevice #2: subdevice #2
    Subdevice #3: subdevice #3
    Subdevice #4: subdevice #4
    Subdevice #5: subdevice #5
    Subdevice #6: subdevice #6
    Subdevice #7: subdevice #7
    card 1: ALSA [bcm2835 ALSA], device 1: bcm2835 ALSA [bcm2835 IEC958/HDMI]
    Subdevices: 1/1
    Subdevice #0: subdevice #0

    // Try to record your voice and play it.
    // Recoding
    rec -t wav  -r 16000 -b 16 -c 1 temp.wav

    // play
    play temp.wav

### Reference

https://computers.tutsplus.com/articles/using-a-usb-audio-device-with-a-raspberry-pi--mac-55876


## Install the utility tools

### 1. Update apt-get list first

    sudo apt-get update
    sudo apt-get upgrade

### 2. Install tools: git, openssl, curl, sox

    sudo apt-get install git-core
    sudo apt-get install openssl
    sudo apt-get install curl
    sudo apt-get install sox

### 3. Install libraries: libssl, libcurl, libvlc, libasound, rapidjson
    
    // libssl
    sudo apt-get install libssl-dev

    // libcurl
    sudo apt-get install libcurl4-openssl-dev

    // libvlc
    sudo apt-get install libvlc-dev

    // libasound
    sudo apt-get install libasound-dev

    // rapidjson
    git clone https://github.com/miloyip/rapidjson.git
    cd rapidjson/include
    cp -r rapidjson /usr/local/bin

### 4. Install Wiring Pi

    http://wiringpi.com/download-and-install/

    // First, go to any temporary folder for installing 3rd party libs.
    cd temp
    git clone git://git.drogon.net/wiringPi
    cd wiringPi
    ./build

    // Testing
    gpio -v
    gpio readall
