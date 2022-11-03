package com.dxie03.shuttle.service;

import com.dxie03.shuttle.pojo.MapInfo;
import com.dxie03.shuttle.pojo.ShuttleInfo;
import com.dxie03.shuttle.pojo.StuInfo;

public interface IShuttleService {
    StuInfo GetInfoBySuid(String suid);

    Boolean GetOn(String suid, String stuAddr);

    Boolean DropOff(String suid);

    Boolean InsertPassenger(String suid);

    Boolean DeletePassenger(String passengerID);


    Boolean Move(int latitude,int longitude);

    ShuttleInfo GetDropPeek(int shuttleID);

    MapInfo GetLatLong(String stuAddr);

    ShuttleInfo GetCurLocation(int shuttleID);
}
