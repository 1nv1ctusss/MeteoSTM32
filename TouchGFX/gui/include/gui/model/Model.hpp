#ifndef MODEL_HPP
#define MODEL_HPP

#ifndef SIMULATOR
#include "Meteo.pb.h"
#include <stdlib.h>
#endif

class ModelListener;

#ifndef SIMULATOR
	typedef struct {
		Sensor *array;
		size_t used;
		size_t size;
	} Array;
#endif

class Model
{

public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void HAScreenActive()
    {
         isHAScreenActive = true;
    }

    void tick();
protected:
    ModelListener* modelListener;
    bool isHAScreenActive = false;

};

#ifndef SIMULATOR

	Sensor getSensors(uint8_t n);

    void initArray(Array *a, size_t initialSize);

    void insertArray(Array *a, Sensor element);
#endif

#endif // MODEL_HPP
