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

RF _rf;

const uint64_t PIPE = 0xE8E8F0F0E1LL;
int RF_RX = 9; // CE
int RF_TX = 10; // CSN

void setup() {
  
  Serial.begin(9600);
  _rf = RF(RF_RX, RF_TX, PIPE);
  _rf.enableReading();
  Serial.println("All set!");
}

void loop() {
  if (_rf.available()) {
    Serial.print(_rf.read());
  }
}
