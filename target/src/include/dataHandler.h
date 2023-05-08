#include <stdint.h>

struct MeasuredData {
	int16_t temperature;
	int16_t humidity;	
	int16_t co2;
};

struct Limits {
	int16_t minLimit;
	int16_t maxLimit;
}

struct MeasuredData dataHandler_getData();
struct Limits dataHandler_getLimits();
void dataHandler_setTemperature(int16_t sensorTemperature);
void dataHandler_setHumidity(int16_t sensorHumidity);
void dataHandler_setCO2(int16_t sensorCO2);
void dataHandler_setLimits(int16_t minLimit, int16_t maxLimit);