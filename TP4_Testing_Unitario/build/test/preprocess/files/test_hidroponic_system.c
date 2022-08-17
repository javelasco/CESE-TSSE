#include "src/DHT.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
void test_inicializar_sensor_comparar_retorno_puntero() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    UnityAssertEqualNumber((UNITY_INT64)((&DHT)), (UNITY_INT64)((pDHT)), (((void*)0)), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_HEX64);

}



void test_inicializar_sensor() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    UnityAssertEqualNumber((UNITY_INT)((DHT_OK)), (UNITY_INT)((DHT.init(pDHT, 1, DHT22, "Sensor Ambiental 1"))), (((void*)0)), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_INT);

}



void test_inicializar_sensor_gpio_errado() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    UnityAssertEqualNumber((UNITY_INT)((DHT_ERROR)), (UNITY_INT)((pDHT->init(pDHT, -1, DHT22, "Sensor Ambiental 2"))), (((void*)0)), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

}



void test_imprimir_nombre_del_sensor() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    pDHT->init(pDHT, 10, DHT11, "Sensor Ambiental 1");

    UnityAssertEqualString((const char*)(("Sensor Ambiental 1")), (const char*)((pDHT->getName(pDHT))), (((void*)0)), (UNITY_UINT)(33));

}



void test_read_timeout() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    pDHT->init(pDHT, 1, DHT22, "Sensor Ambiental 3");

    UnityAssertEqualNumber((UNITY_INT)((DHT_TIMEOUT_ERROR)), (UNITY_INT)((pDHT->read(pDHT))), (((void*)0)), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}



void test_error_handler_timeout_humidity() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    pDHT->init(pDHT, 1, DHT22, "Sensor Ambiental 4");

    pDHT->read(pDHT);

    UnityAssertEqualNumber((UNITY_INT)((-99.9)), (UNITY_INT)((DHT.getHumidity(pDHT))), (((void*)0)), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);

}



void test_error_handler_timeout_temperature() {

    dht_t DHT, *pDHT = newDHT(&DHT);

    pDHT->init(pDHT, 1, DHT22, "Sensor Ambiental 5");

    pDHT->read(pDHT);

    UnityAssertEqualNumber((UNITY_INT)((-99.9)), (UNITY_INT)((pDHT->getTemperature(pDHT))), (((void*)0)), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT);

}
