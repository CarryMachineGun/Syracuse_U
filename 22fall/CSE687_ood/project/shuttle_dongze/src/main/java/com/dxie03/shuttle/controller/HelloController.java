package com.dxie03.shuttle.controller;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {

    @RequestMapping
    public String helloWorld(){
        return "Hello666 from Spring Boot";
    }

    @RequestMapping("/goodbye")
    public String goodbye(){
        return "GoodBye666 from Spring Boot";
    }
}
