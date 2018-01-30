# arduino-mercadobitcoin-api
A wrapper around the [MercadoBitcoin](https://www.mercadobitcoin.com.br/) API for Arduino (supports ESP8266).

The MercadoBitcoin API can be used to look information on crypto currency coins, included Bitcoin, Litecoin and Bitcoin Cash.

## Usage

The simplest way to see how it works is the check out [the example that comes with the library](https://github.com/SandroAkira/arduino-mercadobitcoin-api/blob/master/examples/ESP8266/GetTickerInfo/GetTickerInfo.ino).

### GetTickerInfo:
A wrapper around the single ticker endpoint

Code is as follows:
```
MBTickerResponse response = api.GetTickerInfo(ticker);
```

Ticker unfortunately is not the symbol for some reason. Go to [MercadoBitcoin](https://www.mercadobitcoin.com.br/api-doc/) and select the coin you would like to check, the ticker name makes up the last part of the URL. e.g: https://MercadoBitcoin.net/api/BTC/ticker/ , "BTC" is the cryptocurrency value.

Check out the currency on [MercadoBitcoin](https://www.mercadobitcoin.com.br/api-doc/) to get available values.

The return object has the following values:
```
struct MBTickerResponse{
  float high;
  float low;
  float last;
  float vol;
  float buy;
  float sell;
  float date;

  String error;
};
```
### GetTickerInfo:
