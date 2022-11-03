package com.dxie03.shuttle.dao;

import com.dxie03.shuttle.pojo.MapInfo;
import org.apache.ibatis.annotations.*;
import com.dxie03.shuttle.pojo.ShuttleInfo;

@Mapper
public interface ShuttleInfoDao {
    @Insert("INSERT INTO shuttles (shuttleStat,latitude,longitude,shuttleID,passengerID,boardTime)" +
            "VALUES(1,0,0,1,#{suid},now())")
    Boolean Insert_Passenger(String suid);

    @Update("UPDATE shuttles SET latitude = #{latitude}, longitude = #{longitude} ")
    Boolean Update_latlong(int latitude,int longitude);

    @Select("SELECT * FROM shuttles WHERE shuttleID = #{shuttleID} ORDER BY boardTime ASC  LIMIT 1 ")
    ShuttleInfo Select_DropPeek(int shuttleID);

    @Select("SELECT * FROM map WHERE addr = #{stuAddr}")
    MapInfo Select_FindAddr(String stuAddr);

    @Delete("DELETE FROM shuttles WHERE passengerID = #{passengerID}")
    Boolean Delete_passenger(String passengerID);

    @Select("SELECT * FROM shuttles WHERE shuttleID = #{shuttleID}")
    ShuttleInfo Select_curLocation(int shuttleID);

}
