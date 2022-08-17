#include "DHT.h"
#include "DHT_generic_port.c"

#define DHT11_START_SIG_US      20000
#define DHT22_START_SIG_US      3000
#define DHT_MAX_DATA_BYTES      5


static dht_status dht_init(void* pvS, int16_t gpio, model_t type, char* name);
static dht_status dht_read(void* pvS);
static float dht_getHumidity(void* pvS);
static float dht_getTemperature(void* pvS);
static char* dht_getName(void* pvS);
static int32_t get_signal_level(void* pvS, uint32_t timeout, uint8_t state);
static dht_status error_handler(void* pvS, dht_status response);

/* Constructor */
dht_t* newDHT(struct _dht* _pDHT) {
    /* Method mapping */
   _pDHT->init              = dht_init;
   _pDHT->read              = dht_read;
   _pDHT->getHumidity       = dht_getHumidity;
   _pDHT->getTemperature    = dht_getTemperature;
   _pDHT->getName           = dht_getName;   
   return _pDHT;
}

static dht_status dht_init(void* pvS, int16_t gpio, model_t type, char* name) {
    struct _dht* pDHT = (struct _dht*)pvS;
    pDHT->_name = name;
    
    if(0 > gpio)
        return DHT_ERROR;
    
    pDHT->_dht_pin = gpio;
    pDHT->_type = type;
    switch (type) {
        case DHT11:
            pDHT->_start_sig_us = DHT11_START_SIG_US;
            break;

        case DHT22:
            pDHT->_start_sig_us = DHT22_START_SIG_US;
            break;

        default:
            return DHT_ERROR;
    }
    return DHT_OK;
}

static dht_status dht_read(void* pvS) {
    struct _dht* pDHT = (struct _dht*)pvS;
    int32_t uSec = 0;
    uint8_t dhtData[DHT_MAX_DATA_BYTES], byteIdx = 0, bitIdx = 7;

    /* Reset values */
    for(uint8_t i = 0; i < DHT_MAX_DATA_BYTES; i++)
        dhtData[i] = 0;

    /* Send start signal to DHT sensor */
    hal_set_gpio_mode(pDHT->_dht_pin, OUTPUT_MODE);

    /* --------- pull down for 3/20 ms for a smooth and nice wake up */
    hal_set_gpio_level(pDHT->_dht_pin, LOW);
    hal_delay_us(pDHT->_start_sig_us);

    /* --------- pull up for 25 ms for a gentile asking for data */
    hal_set_gpio_level(pDHT->_dht_pin, HIGH);
    hal_delay_us(25);

    /* --------- change to input mode */
    hal_set_gpio_mode(pDHT->_dht_pin, INPUT_MODE);

    /* DHT will keep the line low for 80 us and then high for 80 us */
    uSec = get_signal_level(pvS, 80, LOW);
    if(0 > uSec) return error_handler(pvS, DHT_TIMEOUT_ERROR);

    /* --------- 80 us up */
    uSec = get_signal_level(pvS, 80, HIGH);
    if(0 > uSec) return error_handler(pvS, DHT_TIMEOUT_ERROR);

    /* No errors, read the 40 data bits */
    for( uint8_t i = 0; i < 40; i++ ) {
		/* --------- starts new data transmission with > 50 us low signal */
		uSec = get_signal_level(pvS, 56, LOW);
		if(0 > uSec) return error_handler(pvS, DHT_TIMEOUT_ERROR);

		/* --------- check to see if after >70us rx data is a 0 or a 1 */
		uSec = get_signal_level(pvS, 75, HIGH);
		if(0 > uSec) return error_handler(pvS, DHT_TIMEOUT_ERROR);

        /*
           --------- add the current read to the output data
           --------- since all dhtData array where set to 0 at the start, 
           --------- only look for "1" (> 28 us)
        */
		if (uSec > 40)
		    dhtData[byteIdx] |= (1 << bitIdx);
	
		/* --------- index to next byte */
		if (bitIdx == 0) {
            bitIdx = 7;
            ++byteIdx;
        } else {
            bitIdx--;
        } 
	}

    /* Get humidity from Data[0] and Data[1] */
    switch(pDHT->_type) {
        case DHT11:
            pDHT->_humidity     = dhtData[0];
            pDHT->_temperature  = dhtData[2];
            break;
        
        case DHT22:
            pDHT->_humidity     =   dhtData[0];
            pDHT->_humidity     *=  0x100;					// >> 8
            pDHT->_humidity     +=  dhtData[1];
            pDHT->_humidity     /=  10;						// get the decimal

            /* --------- get temp from Data[2] and Data[3] */
            
            pDHT->_temperature  =   dhtData[2] & 0x7F;	
            pDHT->_temperature  *=  0x100;				    // >> 8
            pDHT->_temperature  +=  dhtData[3];
            pDHT->_temperature  /=  10;

            if(dhtData[2] & 0x80) 			                // negative temp
                pDHT->_temperature *= -1;
            break;
    }

    /* Verify if checksum is ok */
	/* --------- checksum is the sum of Data 8 bits masked out 0xFF */
	if (dhtData[4] == ((dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3]) & 0xFF)) 
		return error_handler(pvS, DHT_OK);
	else 
		return error_handler(pvS, DHT_CHECKSUM_ERROR);
}

static float dht_getHumidity(void* pvS) {
    struct _dht* pDHT = (struct _dht*)pvS;
    return pDHT->_humidity;
}

static float dht_getTemperature(void* pvS) {
    struct _dht* pDHT = (struct _dht*)pvS;
    return pDHT->_temperature;
}

static char* dht_getName(void* pvS) {
    struct _dht* pDHT = (struct _dht*)pvS;
    return pDHT->_name;
}

static int32_t get_signal_level(void* pvS, uint32_t timeout, uint8_t state) {
    struct _dht* pDHT = (struct _dht*)pvS;
    uint32_t _uSec = 0;
    while(hal_get_gpio_level(pDHT->_dht_pin) == state) {
        if(_uSec > timeout) return -1;
        _uSec++;
        hal_delay_us(1);
    }
    return _uSec;
}

static dht_status error_handler(void* pvS, dht_status response) {
    struct _dht* pDHT = (struct _dht*)pvS;
    switch(response) {
        case DHT_TIMEOUT_ERROR :
            pDHT->_temperature  = -99.99;
            pDHT->_humidity     = -99.99;
            break;

        case DHT_CHECKSUM_ERROR:
            pDHT->_temperature  = -127.0;
            pDHT->_humidity     = -127.0;
            break;

        case DHT_OK:
            break;
    }
    return response;
}