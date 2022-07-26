#include "unity.h"
#include "Leds.h"

/*
Driver de LEDs : Test
•Con la inicialización todos los LEDs quedan apagados.
•Prender un LED individual.
•Apagar un LED individual.
•Prender y apagar múltiples LED’s.
•Prender todos los LEDs de una vez.
•Apagar todos los LEDs de una vez.
•Consultar el estado de un LED que está encendido.
•Consultar el estado de un LED que está apagado.
•Revisar limites de los parametros.
•Revisar parámetros fuera de los limites.
*/

uint16_t  leds_virtuales;
bool      leds_estado;
gravedad_t gravedad_registrada;

void registrar_error(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...) {
     gravedad_registrada = gravedad;
}

void setUp(void) {
     gravedad_registrada = -1;
     LedsCreate(&leds_virtuales, registrar_error);  
}

// Con la inicialización todos los LEDs quedan apagados.
void test_todo_los_leds_inician_apagados(void) {
     uint16_t leds_virtuales = 0xFFFF;
     LedsCreate(&leds_virtuales, registrar_error);
     TEST_ASSERT_EQUAL(0x0, leds_virtuales);
}

// Prender un LED individual.
void test_prender_un_led_individual(void) {
     LedsSingleTurnOn(3);
     TEST_ASSERT_EQUAL(1<<2, leds_virtuales);
}

// Apagar un LED individual.
void test_apagar_un_led_individual(void) {
     LedsSingleTurnOn(3);
     LedsSingleTurnOff(3);
     TEST_ASSERT_EQUAL(0x0, leds_virtuales);
}

// Prender y apagar múltiples LED’s.
void test_prender_y_apagar_varios_leds(void) {
     LedsSingleTurnOn(3);
     LedsSingleTurnOn(7);
     LedsSingleTurnOff(7);
     TEST_ASSERT_EQUAL(1<<2, leds_virtuales);
}

// Prender todos los LEDs de una vez.
void test_prender_todos_los_leds(void) {
     LedsAllTurnOn();
     TEST_ASSERT_EQUAL(0xFFFF, leds_virtuales);
}

// Apagar todos los LEDs de una vez.
void test_apagar_todos_los_leds(void) {
     LedsAllTurnOn();
     LedsAllTurnOff();
     TEST_ASSERT_EQUAL(0x00, leds_virtuales);
}

// Consultar el estado de un LED que está encendido.
void test_consultar_estado_de_un_led_encendido(void) {
     LedsSingleTurnOn(5);
     leds_estado = LedsStateRead(5);
     TEST_ASSERT_EQUAL(true, leds_estado);
}

// Consultar el estado de un LED que está encendido.
void test_consultar_estado_de_un_led_apagado(void) {
     LedsSingleTurnOff(5);
     leds_estado = LedsStateRead(5);
     TEST_ASSERT_EQUAL(false, leds_estado);
}

// Revisar limites de los parametros - encender Led mas significativo
void test_encender_led_mas_significativo(void) {
     LedsSingleTurnOff(16);
     LedsSingleTurnOn(16);
     TEST_ASSERT_EQUAL(1<<15, leds_virtuales);
}

// Revisar limites de los parametros - encender Led menos significativo
void test_encender_led_menos_significativo(void) {
     LedsSingleTurnOff(1);
     LedsSingleTurnOn(1);
     TEST_ASSERT_EQUAL(1<<0, leds_virtuales);
}

// Revisar limites de los parametros - apagar Led mas significativo
void test_apagar_led_mas_significativo(void) {
     LedsSingleTurnOn(16);
     LedsSingleTurnOff(16);
     TEST_ASSERT_EQUAL(0<<15, leds_virtuales);
}

// Revisar limites de los parametros - apagar Led menos significativo
void test_apagar_led_menos_significativo(void) {
     LedsSingleTurnOn(1);
     LedsSingleTurnOff(1);
     TEST_ASSERT_EQUAL(0<<0, leds_virtuales);
}

// Prender un led invalido.
void test_prender_un_led_invalido(void) {
     LedsSingleTurnOn(17);
     TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
}

// Apagar un led invalido.
void test_apagar_un_led_invalido(void) {
     LedsSingleTurnOff(17);
     TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
}

//Consultar el estado de un led encendido invalido.
void test_consultar_estado_de_un_led_invalido_encendido(void) {
     LedsSingleTurnOn(5);
     leds_estado = LedsStateRead(17);
     TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
}

//Consultar el estado de un led apagado invalido.
void test_consultar_estado_de_un_led_invalido_apagado(void) {
     LedsSingleTurnOff(5);
     leds_estado = LedsStateRead(17);
     TEST_ASSERT_EQUAL(ALERTA, gravedad_registrada);
}