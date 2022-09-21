#include "Leds.h"

#define MSB_LED             16
#define LSB_LED             1
#define LEDS_OFFSET         1
#define FIRST_BIT_ON        1
#define LEDS_ALL_OFF        0
#define LEDS_ALL_ON         0xFFFF
#define LED_TO_MASK(led)    (FIRST_BIT_ON << (led-LEDS_OFFSET))
#define LIMIT(led)          (led >= LSB_LED && led <= MSB_LED)

static uint16_t* puerto;
static registro_errores_t notificarError;

void LedsCreate(uint16_t * address, registro_errores_t errores) {
    puerto = address;
    LedsAllTurnOff();
    notificarError = errores;
}

void LedsSingleTurnOn(uint8_t led) {
    if(LIMIT(led)) {
        *puerto |= LED_TO_MASK(led);
    } else {
        notificarError(ALERTA, __FUNCTION__, __LINE__, "El numero de Led ingresado es invalido.");
    }   
}

void LedsSingleTurnOff(uint8_t led) {
    if(LIMIT(led)) {
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
    if(LIMIT(led)) {
        return ((*puerto) & LED_TO_MASK(led)) != 0;
    } else {
        notificarError(ALERTA, __FUNCTION__, __LINE__, "El numero de Led ingresado es invalido.");
    }
}