#include "MercadoBitcoinApi.h"

MercadoBitcoinApi::MercadoBitcoinApi(Client &client)	{
  this->client = &client;
}

String MercadoBitcoinApi::SendGetToMercadoBitcoin(String command) {
  String body="";
  body.reserve(700);
  bool finishedHeaders = false;
  bool currentLineIsBlank = true;
	long now;
	bool avail;

	if (client->connect(MercadoBitcoin_HOST, Port)) {
		// Serial.println(".... connected to server");
		String a="";
		char c;
		int ch_count=0;
		client->println("GET " + command + " HTTP/1.1");
    client->println("Host: " MercadoBitcoin_HOST);
		client->println(F("User-Agent: arduino/1.0.0"));
		client->println();
		now=millis();
		avail=false;
		while (millis()-now<1500) {
			while (client->available()) {
				char c = client->read();
				//Serial.write(c);

        if(!finishedHeaders){
          if (currentLineIsBlank && c == '\n') {
            finishedHeaders = true;
          }
        } else {
          body=body+c;
          ch_count++;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }

				avail=true;
			}
			if (avail) {
        body="["+body+"]";
				// Serial.println("Body:");
				// Serial.println(body);
				// Serial.println("END");
				break;
			}
		}
	}

  return body;
}

MBTickerResponse MercadoBitcoinApi::GetTickerInfo(String coinId) {
  // https://api.MercadoBitcoin.com/api/BTC/ticker/
  coinId.toUpperCase();
  String command="/api/" + coinId + "/ticker/";

  // Serial.println(command);
  String response = SendGetToMercadoBitcoin(command);
  MBTickerResponse responseObject = MBTickerResponse();
  DynamicJsonBuffer jsonBuffer;
	JsonArray& root = jsonBuffer.parseArray(response);
  if (root.success()) {
    responseObject.high = root[0]["ticker"]["high"].as<double>();
    responseObject.low = root[0]["ticker"]["low"].as<double>();
    responseObject.last = root[0]["ticker"]["last"].as<double>();
    responseObject.vol = root[0]["ticker"]["vol"].as<double>();
    responseObject.buy = root[0]["ticker"]["buy"].as<double>();
    responseObject.sell = root[0]["ticker"]["sell"].as<double>();
    responseObject.date = root[0]["ticker"]["date"].as<double>();
  } else {
    JsonObject& rootObject = jsonBuffer.parseObject(response);
    if (rootObject.containsKey("error")) {
       responseObject.error = rootObject["error"].as<String>();
    } else {
      responseObject.error = "Failed to parse JSON";
    }

    return responseObject;
  }
}
