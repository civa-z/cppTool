#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <memory.h>

#include "xlibwrapper.h"

class HandControler{
public:
    HandControler():max_buf_size(6), flag(true), xlibWrapper(){};
    void onhandmove(double* jiontsPosition){
        double x = 0,y = 0,z = 0;
        for (int i = 11; i <= 12 ;++i){
            x += jiontsPosition[3 * i];
            y += jiontsPosition[3 * i + 1];
            z += jiontsPosition[3 * i + 2];
        }

        x = x / 2;
        y = y / 2;
        z = z / 2;
        int xx = pushandget(x_buff, int(x));
        int yy = pushandget(y_buff, int(y));
        int zz = pushandget(z_buff, int(z));

        xx = 300 + xx;
        yy = 150 - yy;
        xx = xx * zz / 800;
        yy = yy * zz / 800;

        if (flag == true)
            xlibWrapper.setCursorPos(xx*4, yy*4);
        flag = !flag;
    }
    
    int pushandget(std::list<int>& buff, int value){
        if (buff.size() == max_buf_size)
            buff.pop_front();
        buff.push_back(value);
        int sum = std::accumulate(buff.begin(), buff.end(), 0);
        //std::cout<<"sum:"<<sum<<" buff.size() "<< buff.size()<<std::endl;
        return sum / int(buff.size());        
    }

    void leftButtonPress(){
        xlibWrapper.buttonPress(Button1);
    }

    void leftButtonRelease(){
        xlibWrapper.buttonRelease(Button1);
    }

    void scrollUpPress(){
        std::cout<<"scrollUpPress"<<std::endl;
        xlibWrapper.buttonPress(Button4, 0x10);
        usleep(100000);
        xlibWrapper.buttonRelease(Button4, 0x810);
    }
    void scrollUpRelease(){
        std::cout<<"scrollUpRelease"<<std::endl;
        xlibWrapper.buttonPress(Button5, 0x10);
        usleep(100000);
        xlibWrapper.buttonRelease(Button5, 0x1010);
    }

private:
    std::list<int> x_buff;
    std::list<int> y_buff;
    std::list<int> z_buff;
    const unsigned int max_buf_size;
    bool flag;
    XlibWrapper xlibWrapper;
};
