#include "main.h"
#include "cmsis_os.h"

#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "Meteo.pb.h"


void StartClimateTask(void *argument);
void StartSerialTask(void *argument);
void LoadAssetsFromSd(uint32_t* assets_location_in_sdram);
void TFT_FillScreen(uint32_t color);
uint32_t Storage_CheckBitmapFile(const char* BmpName, uint32_t *FileLen);
uint32_t Storage_OpenReadFile(uint8_t *Address, const char* BmpName);
void BSP_LCD_DrawBitmap(uint32_t Xpos, uint32_t Ypos, uint8_t *pbmp);
