// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_DEVICE_BLUETOOTH_LE_MOCK_REMOTE_SERVICE_H_
#define CHROMECAST_DEVICE_BLUETOOTH_LE_MOCK_REMOTE_SERVICE_H_

#include <vector>

#include "chromecast/device/bluetooth/le/remote_characteristic.h"
#include "chromecast/device/bluetooth/le/remote_device.h"
#include "chromecast/device/bluetooth/le/remote_service.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace chromecast {
namespace bluetooth {

class MockRemoteService : public RemoteService {
 public:
  MockRemoteService();

  MOCK_METHOD0(GetCharacteristics,
               std::vector<scoped_refptr<RemoteCharacteristic>>());
  MOCK_METHOD1(GetCharacteristicByUuid,
               scoped_refptr<RemoteCharacteristic>(
                   const bluetooth_v2_shlib::Uuid& uuid));
  MOCK_CONST_METHOD0(uuid, const bluetooth_v2_shlib::Uuid&());
  MOCK_CONST_METHOD0(handle, uint16_t());
  MOCK_CONST_METHOD0(primary, bool());

 private:
  ~MockRemoteService();
};

}  // namespace bluetooth
}  // namespace chromecast

#endif  // CHROMECAST_DEVICE_BLUETOOTH_LE_MOCK_REMOTE_SERVICE_H_
