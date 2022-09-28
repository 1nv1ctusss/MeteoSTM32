#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <inttypes.h>

#ifndef SIMULATOR
#include "esp.h"
#endif

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

#ifndef SIMULATOR
    virtual void addNewSensor(Sensor sens){}
    virtual void setClimateData(int temp, int co2, int hum){}
    virtual void setOutTemp(int temp, int hum, char* weather){}
//    virtual void setOutHum(int hum){}
    //virtual void setWeather(int cond){}
    virtual void setWLANstatus(){}
    virtual void setClockData(uint32_t timestamp){}
#endif

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
