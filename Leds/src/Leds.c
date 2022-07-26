#include "Leds.h"

#define MSB_LED             16
#define LSB_LED             1
#define LEDS_OFFSET         1
#define FIRST_BIT_ON        1
#define LEDS_ALL_OFF        0
#define LEDS_ALL_ON         0xFFFF
#define LED_TO_MASK(led)    (FIRST_BIT_ON << (led-LEDS_OFFSET))

static uint16_t* puerto;
static registro_errores_t notificarError;

void LedsCreate(uint16_t * address, registro_errores_t errores) {
    puerto = address;
    *puerto = LEDS_ALL_OFF;
    notificarError = errores;
}

void LedsSingleTurnOn(uint8_t led) {
    if(led >= LSB_LED && led <= MSB_LED) {
        *puerto |= LED_TO_MASK(led);
    } else {
        notificarError(ALERTA, __FUNCTION__, __LINE__, "El numero de Led ingresado es invalido.");
    }   
}

void LedsSingleTurnOff(uint8_t led) {
    if(led >= LSB_LED && led <= MSB_LED) {
        *puerto &= ~(LED_TO_MASK(led));
    } else {
        notificarError(ALERTA, __FUNCTION__, __LINE__, "El numero de Led ingresado es invalido.");
    }
}

void LedsAllTurnOn(void) {
    *puerto = LEDS_ALL_ON;
 }

void LedsAllTurnOff(void) {
    *puerto = LEDS_ALL_OFF;
}

bool LedsStateRead(uint8_t led) {
    if(led >= LSB_LED && led <= MSB_LED) {
        uint16_t aux = 0;
        aux |= LED_TO_MASK(led);
        if((*puerto & aux) == aux)
            return true;
        else
            return false;
    } else {
        notificarError(ALERTA, __FUNCTION__, __LINE__, "El numero de Led ingresado es invalido.");
    }
}