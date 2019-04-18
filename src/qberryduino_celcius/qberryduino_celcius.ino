//  Copyright (c) 2019-present, Deniz Kanmaz. All rights reserved.
//  This source code is licensed under the GNU GENERAL PUBLIC
//  LICENCE V3. Use of this source code is governed by a license
//  that can be found in the LICENSE file.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  LICENSE file for more details.

//  You should have received a copy of the LICENSE file along with
//  this program. If not, see <http://www.gnu.org/licenses/>.

//	Description: "qberryduino_celcuis.ino" is a wireless RF temperature
//	and humidity sensor solution. It sends message to gateway
//  (for instance, qberryduino-gateway-one) through the RF.

#include "RF.h"
#include <DHT.h>
#define DHT11_PIN 5
//#define DHTTYPE DHT11
#define DHTTYPE DHT22
#include "TEHUMessageFactory.h"

DHT dht(DHT11_PIN, DHTTYPE);

RF _rf;


TEHUMessageFactory _tehuMF = TEHUMessageFactory();

char devId [] = "123456789";
const uint64_t PIPE = 0xE8E8F0F0E1LL;
int RF_RX = 9; // CE
int RF_TX = 10; // CSN

class DHTValues {
  public:
    float temp;
    float hum;
};


void setup() {

  Serial.begin(9600);
  Serial.println("I am celcius!");
  dht.begin();

  _rf = RF(RF_RX, RF_TX, PIPE);
  _rf.enableWriting();

}



DHTValues getDHTValues() {

  float hum = dht.readHumidity();
  float temp = (float) dht.readTemperature();
  Serial.println(hum);
  Serial.println(temp);

  DHTValues vals = DHTValues();
  vals.temp =   temp;
  vals.hum = hum;
  return vals;
}

char  connId [] = "RF";

void loop() {

  DHTValues vals = getDHTValues();
  delay(5000);
  String td[2] = {String(vals.temp), String(vals.hum)};
  String test = _tehuMF.create(devId
                               , connId
                               , td);
  Serial.println(test);
  _rf.write(test);
}
