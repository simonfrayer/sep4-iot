#include <stdint.h>

struct MeasuredData {
	int16_t temperature;
	int16_t humidity;	
};

struct MeasuredData dataHandler_getData();
void dataHandler_setTemperature(int16_t sensorTemperature);
void dataHandler_setHumidity(int16_t sensorHumidity);