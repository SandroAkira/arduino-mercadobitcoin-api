#include <MercadoBitcoinApi.h>

/*******************************************************************
 *  An example of getting ticker info from mercadobitcoin.com.br   *
 *                                                                 *
 *  Based on Brian Lough's CoinMarketCap library example           *
 *******************************************************************/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- Install From Library Manager -------
#include <ArduinoJson.h>


//------- Replace the following! ------
char ssid[] = "SSID";       // your network SSID (name)
char password[] = "PASSWORD";  // your network key


WiFiClientSecure client;
MercadoBitcoinApi api(client);

// CoinMarketCap's limit is "no more than 10 per minute"
// Make sure to factor in if you are requesting more than one coin.
unsigned long api_mtbs = 60000; //mean time between api requests
unsigned long api_due_time = 0;

void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void printTickerData(String ticker) {
  Serial.println("---------------------------------");
  Serial.println("Getting ticker data for " + ticker);
  Serial.println("---------------------------------");


  MBTickerResponse response = api.GetTickerInfo(ticker);
  if (response.error == "") {
    Serial.print("High: ");
    Serial.println(response.high);
    Serial.print("Low : ");
    Serial.println(response.low);
    Serial.print("Last: ");
    Serial.println(response.last);
    Serial.print("Vol : ");
    Serial.println(response.vol);
    Serial.print("Buy : ");
    Serial.println(response.buy);
    Serial.print("Sell: ");
    Serial.println(response.sell);
    Serial.print("Data: ");
    Serial.println(response.date);

  } else {
    Serial.print("Error getting data: ");
    Serial.println(response.error);
  }
  Serial.println("---------------------------------");
}

void loop() {
  unsigned long timeNow = millis();
  if ((timeNow > api_due_time))  {
    printTickerData("BTC");
    printTickerData("LTC");
    printTickerData("BCH");
    api_due_time = timeNow + api_mtbs;
  }
}
