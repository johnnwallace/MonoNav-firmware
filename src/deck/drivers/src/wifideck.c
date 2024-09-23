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

  // Reset ESP32, camera

  // Initialize cpx
  cpxUARTTransportInit();
  cpxInternalRouterInit(); // do we need this?
  cpxExternalRouterInit();
  cpxInit();

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


  .usedGpio = DECK_USING_IO_1,

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
PARAM_ADD_CORE(PARAM_UINT8 | PARAM_RONLY, cpxOverUART2, &isInit)

PARAM_GROUP_STOP(deck)