package com.dxie03.shuttle.service.impl;

import com.dxie03.shuttle.dao.ShuttleInfoDao;
import com.dxie03.shuttle.dao.StuInfoDao;
import com.dxie03.shuttle.pojo.MapInfo;
import com.dxie03.shuttle.pojo.ShuttleInfo;
import com.dxie03.shuttle.pojo.StuInfo;
import com.dxie03.shuttle.service.IShuttleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ShuttleServiceImpl implements IShuttleService {
    @Autowired
    private StuInfoDao stu = null;
    @Autowired
    private ShuttleInfoDao shuttle = null;


    @Override
    public StuInfo GetInfoBySuid(String suid){
        return stu.Verify_Suid(suid);
    }

    @Override
    public Boolean GetOn(String suid, String stuAddr){
        Boolean ret = stu.Update_Stu_on(suid,stuAddr);
        return ret;
    }

    @Override
    public Boolean DropOff(String suid){
        Boolean ret = stu.Update_Stu_off(suid);
        return ret;
    }

    @Override
    public Boolean InsertPassenger(String suid){
        return shuttle.Insert_Passenger(suid);
    }

    @Override
    public Boolean DeletePassenger(String passengerID){
        return shuttle.Delete_passenger(passengerID);
    }


    @Override
    public Boolean Move(int latitude,int longitude){
        return shuttle.Update_latlong(latitude,longitude);
    }

    @Override
    public ShuttleInfo GetDropPeek(int shuttleID){
        return shuttle.Select_DropPeek(shuttleID);
    }

    @Override
    public MapInfo GetLatLong(String stuAddr){
        return shuttle.Select_FindAddr(stuAddr);
    }

    @Override
    public ShuttleInfo GetCurLocation(int shuttleID){
        return shuttle.Select_curLocation(shuttleID);
    }

}
