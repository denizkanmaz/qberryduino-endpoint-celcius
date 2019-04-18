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

//  Description: Please refer to "TEHUMessageFactory.h".

#include "Arduino.h"
#include "TEHUMessageFactory.h"

// Creates a ready to send "Current State" message for Temperature and
// Humidity using given parameters.
String TEHUMessageFactory::create(char devId[],
                                  char connectionId[],
                                  String tehuData[]) {

  t =   keyval(MESSAGE_TYPE_KEY, CURR)
        + keyval(DEV_ID_KEY, devId)
        + keyval(CONNECTION_ID_KEY, connectionId);

  lineI = TEHU_START_INDEX;
  for (i = 0; i < TEHU_LINES_LENGTH; i++) {
    t += keyval(lineI, tehuData[i]);
    lineI++;
  }
  return message(t);
}
