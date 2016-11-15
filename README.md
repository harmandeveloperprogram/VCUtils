# VCUtils - Prerequisite open source libraries for voice clients
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
  
  
