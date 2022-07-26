/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_todo_los_leds_inician_apagados(void);
extern void test_prender_un_led_individual(void);
extern void test_apagar_un_led_individual(void);
extern void test_prender_y_apagar_varios_leds(void);
extern void test_prender_todos_los_leds(void);
extern void test_apagar_todos_los_leds(void);
extern void test_consultar_estado_de_un_led_encendido(void);
extern void test_consultar_estado_de_un_led_apagado(void);
extern void test_encender_led_mas_significativo(void);
extern void test_encender_led_menos_significativo(void);
extern void test_apagar_led_mas_significativo(void);
extern void test_apagar_led_menos_significativo(void);
extern void test_prender_un_led_invalido(void);
extern void test_apagar_un_led_invalido(void);
extern void test_consultar_estado_de_un_led_invalido_encendido(void);
extern void test_consultar_estado_de_un_led_invalido_apagado(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
}

/*=======Teardown (stub)=====*/
void tearDown(void) {}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_Leds.c");
  run_test(test_todo_los_leds_inician_apagados, "test_todo_los_leds_inician_apagados", 32);
  run_test(test_prender_un_led_individual, "test_prender_un_led_individual", 39);
  run_test(test_apagar_un_led_individual, "test_apagar_un_led_individual", 45);
  run_test(test_prender_y_apagar_varios_leds, "test_prender_y_apagar_varios_leds", 52);
  run_test(test_prender_todos_los_leds, "test_prender_todos_los_leds", 60);
  run_test(test_apagar_todos_los_leds, "test_apagar_todos_los_leds", 66);
  run_test(test_consultar_estado_de_un_led_encendido, "test_consultar_estado_de_un_led_encendido", 73);
  run_test(test_consultar_estado_de_un_led_apagado, "test_consultar_estado_de_un_led_apagado", 80);
  run_test(test_encender_led_mas_significativo, "test_encender_led_mas_significativo", 87);
  run_test(test_encender_led_menos_significativo, "test_encender_led_menos_significativo", 94);
  run_test(test_apagar_led_mas_significativo, "test_apagar_led_mas_significativo", 101);
  run_test(test_apagar_led_menos_significativo, "test_apagar_led_menos_significativo", 108);
  run_test(test_prender_un_led_invalido, "test_prender_un_led_invalido", 115);
  run_test(test_apagar_un_led_invalido, "test_apagar_un_led_invalido", 121);
  run_test(test_consultar_estado_de_un_led_invalido_encendido, "test_consultar_estado_de_un_led_invalido_encendido", 127);
  run_test(test_consultar_estado_de_un_led_invalido_apagado, "test_consultar_estado_de_un_led_invalido_apagado", 134);

  return UnityEnd();
}