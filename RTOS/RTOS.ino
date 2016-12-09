#include "Arduino_FreeRTOS.h"
#include "Arduino.h"
#include "task.h"

//Variáveis da Biblioteca FreeRTOS
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskResume 1
#define INCLUDE_vTaskPriorityGet 1
#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_vTaskDelay 1

//Buttons
#define ButtonBlink  11
#define ButtonProg  6
#define ButtonBeep  9
#define ButtonReset 12

//OUTPUTS
#define LED_Azul 5
#define LED_Verde 4
#define LED_Amarelo 3
#define LED_Vermelho 2
#define Buzina 7
#define LED_Branco 10

void TaskBlink( void *pvParameters );
void TaskProg(void *pvParameters);
void TaskBeep(void *pvParameters);
void TaskButton(void *pvParameters);

TaskHandle_t HandleBlink;
TaskHandle_t HandleProg;
TaskHandle_t HandleBeep;
TaskHandle_t HandleButton;


void setup() {

  //xTaskCreate(TaskName, StringTaksName, StackSize, AddressVariable, Priority, pxCreateTask);
  xTaskCreate(TaskBlink, (const portCHAR *)"Blink", 128, NULL, 1, &HandleBlink);
  xTaskCreate(TaskProg, (const portCHAR *)"Prog", 128, NULL, 1, &HandleProg);
  xTaskCreate(TaskBeep, (const portCHAR *)"Beep", 128, NULL, 1, &HandleBeep);
  xTaskCreate(TaskButton, (const portCHAR *)"Button", 128, NULL, 1, &HandleButton);



}

void loop() {
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  //Método RUN
{
  (void) pvParameters;

  //Inicializa a porta LED1 como saída.
  pinMode(10, OUTPUT);
  pinMode(ButtonBlink, INPUT);

  //Tempo Real em milisegundos, não em ciclos.
  int tickTime = 1000 / portTICK_PERIOD_MS;
  int i;

  for (;;) {

    digitalWrite(10, HIGH);
    vTaskDelay( tickTime );
    digitalWrite(10, LOW);
    vTaskDelay( tickTime );

      if (digitalRead(ButtonBlink) == HIGH) {
        vTaskSuspend(HandleProg);
        vTaskSuspend(HandleBeep);
      }
    }



  }




/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskProg(void *pvParameters)  //Método RUN
{
  (void) pvParameters;

  pinMode(ButtonProg, INPUT);

  for (;;) {

    digitalWrite(LED_Azul, HIGH);
    delay(200);
    digitalWrite(LED_Verde, HIGH);
    delay(200);
    digitalWrite(LED_Amarelo, HIGH);
    delay(200);
    digitalWrite(LED_Vermelho, HIGH);
    delay(200);
    digitalWrite(LED_Vermelho, LOW);
    delay(200);
    digitalWrite(LED_Amarelo, LOW);
    delay(200);
    digitalWrite(LED_Verde, LOW);
    delay(200);
    digitalWrite(LED_Azul, LOW);
    delay(200);

    if (digitalRead(ButtonProg) == HIGH) {
      vTaskSuspend(HandleBlink);
      vTaskSuspend(HandleBeep);
    }

  }
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBeep(void *pvParameters) //Método RUN
{
  (void) pvParameters;

  pinMode(8, OUTPUT);

  pinMode(ButtonBeep, INPUT);

  for (;;) {

    //Ambulância
    tone(8, 1440);
    delay(200);
    tone(8, 1880);
    delay(200);

    if (digitalRead(ButtonBeep) == HIGH) {
      vTaskSuspend(HandleBlink);
      vTaskSuspend(HandleProg);
    }

  }

}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskButton(void *pvParameters) //Método RUN
{
  (void) pvParameters;

  pinMode(ButtonReset, INPUT);
  int BButton = digitalRead(ButtonReset);

  for (;;) {

    if (digitalRead(ButtonReset) == HIGH) {
      vTaskResume(HandleBlink);
      vTaskResume(HandleProg);
      vTaskResume(HandleBeep);
    }

  }

}






