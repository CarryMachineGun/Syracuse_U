package com.dxie03.shuttle.pojo;

public class ShuttleInfo {

    private int shuttleID;
    private int shuttleStat;
    private int latitude;
    private int longitude;
    private String passengerID;


    //getter and setter-----------------------

    public int getShuttleID() {
        return shuttleID;
    }

    public void setShuttleID(int shuttleID) {
        this.shuttleID = shuttleID;
    }

    public int getShuttleStatus() {
        return shuttleStat;
    }

    public void setShuttleStatus(int shuttleStatus) {
        this.shuttleStat = shuttleStatus;
    }

    public int getLatitude() {
        return latitude;
    }

    public void setLatitude(int latitude) {
        this.latitude = latitude;
    }

    public int getLongitude() {
        return longitude;
    }

    public void setLongitude(int longitude) {
        this.longitude = longitude;
    }

    public String getPassengerID() {
        return passengerID;
    }

    public void setPassengerID(String passengerID) {
        this.passengerID = passengerID;
    }
}
