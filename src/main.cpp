#include <LinxESP32.h>

LinxESP32* LinxDevice;

void setup()
{
  LinxDevice = new LinxESP32();

  // PWM & Servo Setup
  uint8_t pwmList[] = {};    // Max16Ch {0, 26, ...}
  uint16_t pwmFrequency = 12000;  // LED:12000, Servo:50
  for (int i = 0; i < sizeof(pwmList); i++) {
    ledcSetup(i, pwmFrequency, 8);
    pinMode(pwmList[i], OUTPUT);
    ledcAttachPin(pwmList[i], i);
  }

  // I2C Begin ch0:Wire, ch1:Wire1
  //Wire.begin(0, 26);
  //Wire1.begin(32, 33);

  // The LINX Listener Is Pre Instantiated.
  // Set SSID (Network Name), Security Type, Passphrase/Key, And Call Start With Desired Device IP and Port
  // If not set, it will connect with the last connection information
  LinxWifiConnection.SetSsid("Zerojet");
  LinxWifiConnection.SetSecurity(WPA2_PASSPHRASE);  //NONE, WPA2_PASSPHRASE, WPA2_KEY, WEP40, WEO104
  LinxWifiConnection.SetPassphrase("jetboatsareawesome"); 

  // Wi-Fi
  // LinxWifiConnection.Start(LinxDevice, 44300);

  // The LINXT Listener Is Pre Instantiated, Call Start And Pass A Pointer To The LINX Device And The UART Channel To Listen On
  // ch0:Serial
  // ch1:Serial1
  // ch2:Serial2
  // ch3:SerialBT
  LinxSerialConnection.Start(LinxDevice, 3);
}

void loop()
{
  // LinxWifiConnection.CheckForCommands();
  LinxSerialConnection.CheckForCommands();

}
