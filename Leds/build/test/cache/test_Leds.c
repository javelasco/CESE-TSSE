#include "src/Leds.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
uint16_t leds_virtuales;



_Bool 

         leds_estado;

gravedad_t gravedad_registrada;



void registrar_error(gravedad_t gravedad, const char * funcion, int linea, const char * mensaje, ...) {

     gravedad_registrada = gravedad;

}



void setUp(void) {

     gravedad_registrada = -1;

     LedsCreate(&leds_virtuales, registrar_error);

}





void test_todo_los_leds_inician_apagados(void) {

     uint16_t leds_virtuales = 0xFFFF;

     LedsCreate(&leds_virtuales, registrar_error);

     UnityAssertEqualNumber((UNITY_INT)((0x0)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

}





void test_prender_un_led_individual(void) {

     LedsSingleTurnOn(3);

     UnityAssertEqualNumber((UNITY_INT)((1<<2)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);

}





void test_apagar_un_led_individual(void) {

     LedsSingleTurnOn(3);

     LedsSingleTurnOff(3);

     UnityAssertEqualNumber((UNITY_INT)((0x0)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_INT);

}





void test_prender_y_apagar_varios_leds(void) {

     LedsSingleTurnOn(3);

     LedsSingleTurnOn(7);

     LedsSingleTurnOff(7);

     UnityAssertEqualNumber((UNITY_INT)((1<<2)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

}





void test_prender_todos_los_leds(void) {

     LedsAllTurnOn();

     UnityAssertEqualNumber((UNITY_INT)((0xFFFF)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

}





void test_apagar_todos_los_leds(void) {

     LedsAllTurnOn();

     LedsAllTurnOff();

     UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_INT);

}





void test_consultar_estado_de_un_led_encendido(void) {

     LedsSingleTurnOn(5);

     leds_estado = LedsStateRead(5);

     UnityAssertEqualNumber((UNITY_INT)((

    1

    )), (UNITY_INT)((leds_estado)), (

    ((void *)0)

    ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);

}





void test_consultar_estado_de_un_led_apagado(void) {

     LedsSingleTurnOff(5);

     leds_estado = LedsStateRead(5);

     UnityAssertEqualNumber((UNITY_INT)((

    0

    )), (UNITY_INT)((leds_estado)), (

    ((void *)0)

    ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_INT);

}





void test_encender_led_mas_significativo(void) {

     LedsSingleTurnOff(16);

     LedsSingleTurnOn(16);

     UnityAssertEqualNumber((UNITY_INT)((1<<15)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);

}





void test_encender_led_menos_significativo(void) {

     LedsSingleTurnOff(1);

     LedsSingleTurnOn(1);

     UnityAssertEqualNumber((UNITY_INT)((1<<0)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(97), UNITY_DISPLAY_STYLE_INT);

}





void test_apagar_led_mas_significativo(void) {

     LedsSingleTurnOn(16);

     LedsSingleTurnOff(16);

     UnityAssertEqualNumber((UNITY_INT)((0<<15)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_INT);

}





void test_apagar_led_menos_significativo(void) {

     LedsSingleTurnOn(1);

     LedsSingleTurnOff(1);

     UnityAssertEqualNumber((UNITY_INT)((0<<0)), (UNITY_INT)((leds_virtuales)), (

    ((void *)0)

    ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_INT);

}





void test_prender_un_led_invalido(void) {

     LedsSingleTurnOn(17);

     UnityAssertEqualNumber((UNITY_INT)((ALERTA)), (UNITY_INT)((gravedad_registrada)), (

    ((void *)0)

    ), (UNITY_UINT)(117), UNITY_DISPLAY_STYLE_INT);

}





void test_apagar_un_led_invalido(void) {

     LedsSingleTurnOff(17);

     UnityAssertEqualNumber((UNITY_INT)((ALERTA)), (UNITY_INT)((gravedad_registrada)), (

    ((void *)0)

    ), (UNITY_UINT)(123), UNITY_DISPLAY_STYLE_INT);

}





void test_consultar_estado_de_un_led_invalido_encendido(void) {

     LedsSingleTurnOn(5);

     leds_estado = LedsStateRead(17);

     UnityAssertEqualNumber((UNITY_INT)((ALERTA)), (UNITY_INT)((gravedad_registrada)), (

    ((void *)0)

    ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT);

}





void test_consultar_estado_de_un_led_invalido_apagado(void) {

     LedsSingleTurnOff(5);

     leds_estado = LedsStateRead(17);

     UnityAssertEqualNumber((UNITY_INT)((ALERTA)), (UNITY_INT)((gravedad_registrada)), (

    ((void *)0)

    ), (UNITY_UINT)(137), UNITY_DISPLAY_STYLE_INT);

}
