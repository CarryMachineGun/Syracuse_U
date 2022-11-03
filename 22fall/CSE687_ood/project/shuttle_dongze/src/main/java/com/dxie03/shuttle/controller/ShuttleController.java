package com.dxie03.shuttle.controller;

import com.dxie03.shuttle.pojo.ShuttleInfo;
import com.dxie03.shuttle.pojo.StuInfo;
import com.dxie03.shuttle.service.IShuttleService;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;


@RestController
@RequestMapping
public class ShuttleController {
    private IShuttleService service = null;

    public ShuttleController(IShuttleService value){
        service = value;
    }

    @GetMapping(value = "/requestPickup", produces = "application/json")
    public String RequestPickup(@RequestParam(value = "suid", required = false) String suid){

        //verify suid in the students table
        StuInfo stu_info = service.GetInfoBySuid(suid);

        if(stu_info == null){
            return "Not a SU student!";
        }
        return "Welcome, " + stu_info.getStuName() + " !";
    }

    @GetMapping(value = "/addPassenger", produces = "application/json")
    public String AddPassenger(@RequestParam(value = "suid",required = false)String suid,
                             @RequestParam(value = "stuAddr",required = false)String stuAddr){


        //verify given address and turn into (lat,long)
        if(service.GetLatLong(stuAddr)==null){
            return suid + " ,for your given address, service unavailable! ";
        }
        int stuLat = service.GetLatLong(stuAddr).getLatitude();
        int stuLong = service.GetLatLong(stuAddr).getLongitude();

        //check if try to add student that is already on the shuttle
        if(service.GetInfoBySuid(suid).getStatus()==1){
            return suid + " is already on the shuttle!";
        }

        //check if shuttle is not at the campus stop
        ShuttleInfo cur_shuttleInfo = service.GetDropPeek(1);
        if(cur_shuttleInfo!=null && (cur_shuttleInfo.getLatitude()!=0 ||cur_shuttleInfo.getLongitude()!=0)){
            return "Shuttle is on the way, please wait for getting on!";
        }

        //boarding
        Boolean ret1 = service.GetOn(suid,stuAddr);
        if(!ret1){
            return "Fail to add this passenger, update statement not work!";
        }
        Boolean ret2 = service.InsertPassenger(suid);
        if(!ret2){
            return "Fail to add this passenger, insert statement not work!";
        }

        //calculate ETA
        int curLat = service.GetDropPeek(1).getLatitude();
        int curLong = service.GetDropPeek(1).getLongitude();
        int eta = Math.abs(curLat-stuLat) + Math.abs(curLong-stuLong);

        return suid + " your deatination is " + stuAddr + ", ETA: "+ String.valueOf(eta);

    }

    @GetMapping(value = "/shuttleLocation", produces = "application/json")
    public String ShuttleLocation(@RequestParam(value = "latitude")int latitude,
                         @RequestParam(value = "longitude")int longitude){

        //drive to the given location
        Boolean ret = service.Move(latitude,longitude);
        if(!ret){return "Fail to move to the given (lat,long), update statement not work!";}

        //if this location is exactly the address of the first student to be dropped off
        String passengerID = service.GetDropPeek(1).getPassengerID();
        if(passengerID.equals("no_passenger")){//empty shuttle
            return "Shuttle is at ( "+ latitude + " , "+ longitude +" )";
        }
        String stuAddr = service.GetInfoBySuid(passengerID).getStuAddr();
        int stuLat = service.GetLatLong(stuAddr).getLatitude();
        int stuLong = service.GetLatLong(stuAddr).getLongitude();
        if(latitude==stuLat && longitude==stuLong){
            service.DropOff(passengerID);
            service.DeletePassenger(passengerID);
        }

        return "Shuttle is at ( "+ latitude + " , "+ longitude +" )";
    }



}
