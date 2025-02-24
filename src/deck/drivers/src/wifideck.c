#define DEBUG_MODULE "WIFIDECK"

#include "deck.h"
#include "param.h"

#include "cpx_internal_router.h"
#include "cpx_external_router.h"
#include "cpx_uart_transport.h"
#include "cpx.h"

static bool isInit = false;

void wifiInit(DeckInfo *info)
{
  if (isInit)
    return;

  // Pull reset for ESP32
  pinMode(DECK_GPIO_IO1, OUTPUT);
  digitalWrite(DECK_GPIO_IO1, LOW);

  cpxUARTTransportInit();
  cpxInternalRouterInit();
  cpxExternalRouterInit();
  cpxInit();

  // Release reset for ESP32
  digitalWrite(DECK_GPIO_IO1, HIGH);
  pinMode(DECK_GPIO_IO1, INPUT_PULLUP);

  isInit = true;
}

bool wifiTest()
{
  return true;
}

const DeckDriver wifi_driver = {
  .vid = 0,
  .pid = 0,
  .name = "wifiDeck",

  .usedPeriph = DECK_USING_UART2,

  .init = wifiInit,
  .test = wifiTest,
};

DECK_DRIVER(wifi_driver);

/** @addtogroup deck
*/
PARAM_GROUP_START(deck)

/**
 * @brief Nonzero if CRTP over UART has been forced
 */
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, wifiDeck, &isInit)

PARAM_GROUP_STOP(deck)