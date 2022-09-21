#include "unity.h"
#include "DHT.h"

/*
Se implemento un driver para los sensores DHT11 y DHT22:
    1. Test que comprueba que el puntero manejador es igual a la direccion de memoria del objeto.
    2. Test que prueba que se inicializo correctamente el driver.
    3. Test que prueba inicializar el driver con error en el GPIO.
    4. Test que comprueba que se guardo correctamente el nombre y getter funciona.
    5. Test que prueba el timeout del sensor (no respuesta del sensor).
    6. Test que prueba el valor de retorno de la humedad cuando hay un timeout.
    7. Test que prueba el valor de retorno de la temperatura cuando hay un timeout.
*/

void test_inicializar_sensor_comparar_retorno_puntero() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    TEST_ASSERT_EQUAL_PTR(&DHT, pDHT);
}

void test_inicializar_sensor() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    TEST_ASSERT_EQUAL(DHT_OK, DHT.init(pDHT, 1, DHT22, "Sensor Ambiental 1"));
}

void test_inicializar_sensor_gpio_errado() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    TEST_ASSERT_EQUAL(DHT_ERROR, pDHT->init(pDHT, -1, DHT22, "Sensor Ambiental 2"));
}

void test_imprimir_nombre_del_sensor() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    pDHT->init(pDHT, 10, DHT11, "Sensor Ambiental 1");
    TEST_ASSERT_EQUAL_STRING("Sensor Ambiental 1", pDHT->getName(pDHT)); 
}

void test_read_timeout() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    pDHT->init(pDHT, 1, DHT22, "Sensor Ambiental 3");
    TEST_ASSERT_EQUAL(DHT_TIMEOUT_ERROR, pDHT->read(pDHT)); 
}

void test_error_handler_timeout_humidity() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    pDHT->init(pDHT, 1, DHT22, "Sensor Ambiental 4");
    pDHT->read(pDHT);
    TEST_ASSERT_EQUAL(-99.9, DHT.getHumidity(pDHT)); 
}

void test_error_handler_timeout_temperature() {
    dht_t DHT, *pDHT = newDHT(&DHT);
    pDHT->init(pDHT, 1, DHT22, "Sensor Ambiental 5");
    pDHT->read(pDHT);
    TEST_ASSERT_EQUAL(-99.9, pDHT->getTemperature(pDHT)); 
}