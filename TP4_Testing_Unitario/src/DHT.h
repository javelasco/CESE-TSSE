#ifndef DHT_INC_DHT_H_
#define DHT_INC_DHT_H_

#include <stdio.h>
#include <stdint.h>

#define OUTPUT_MODE             0
#define INPUT_MODE              1
#define LOW                     0
#define HIGH                    1

typedef enum model_t {
    DHT11,
    DHT22
} model_t;

typedef enum {
    DHT_OK,
    DHT_ERROR,
    DHT_TIMEOUT_ERROR,
    DHT_CHECKSUM_ERROR
} dht_status;

typedef const struct _dht   dht_t;
struct _dht {
    char*       _name;
    model_t     _type;
    uint16_t    _dht_pin;
    uint32_t    _start_sig_us;
    float       _temperature;
    float       _humidity;

    dht_status  (*init)(void* pvS, int16_t gpio, model_t type, char* name);
    dht_status  (*read)(void* pvS);
    float       (*getHumidity)(void*pvS);
    float       (*getTemperature)(void*pvS);
    char*		(*getName)(void* pvS);
};

dht_t* newDHT(struct _dht*);

#endif /* DHT_INC_DHT_H_ */