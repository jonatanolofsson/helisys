#ifndef SYS_COM_MAPLEMESSAGES_HPP_
#define SYS_COM_MAPLEMESSAGES_HPP_

#include <os/types.hpp>

namespace sys {
    using namespace os;
    template<int ID> struct MapleMessage;
    struct MapleMessages {
        static const int numberOfMessages = 4;

        enum Id {
            sensorMessage = 0,
            controlMessage = 1,
            cameraControlMessage = 2,
            ioctlMessage = 3
        };
        template<Id MID>
        struct Message { typedef typename MapleMessage<MID>::Type Type; };
    };

    struct SensorMessage {
        static const MapleMessages::Id ID = MapleMessages::sensorMessage;
        U16 imu[6];
        U16 pressure;
        U16 magnetometer[3];
        U16 wind[2];
        U16 distance[4];
        U16 rpm;
        U8 buttons;
    };

    struct ControlMessage {
        static const MapleMessages::Id ID = MapleMessages::controlMessage;
        U16 servo[3];
        U16 rpm;
    };

    struct CameraControlMessage {
        static const MapleMessages::Id ID = MapleMessages::cameraControlMessage;
        U16 horizontal;
        U16 vertical;
    };

    struct IoctlMessage {
        static const MapleMessages::Id ID = MapleMessages::ioctlMessage;
        U16 message;
        enum Bits {
            SEND_SENSOR_DATA = (1 << 0),
            RESPONSETEST = (1 << 1),
            STRESSTEST = (1 << 2)
        };
    };

    template<> struct MapleMessage<MapleMessages::sensorMessage> { typedef SensorMessage Type; };
    template<> struct MapleMessage<MapleMessages::controlMessage> { typedef ControlMessage Type; };
    template<> struct MapleMessage<MapleMessages::cameraControlMessage> { typedef CameraControlMessage Type; };
    template<> struct MapleMessage<MapleMessages::ioctlMessage> { typedef IoctlMessage Type; };
}
#endif