CW:
A: 0 B:1
A: 0 B:0
A: 1 B:0
A: 1 B:1

falling edge on A, if B is low CW, otherwise ccw
delay 20ms

HAL_Delay(500);
    printf("CARD_PRESENT: %d\n", HAL_GPIO_ReadPin(CARD_PRESENT_GPIO_Port, CARD_PRESENT_Pin));  
uint8_t aaa = HAL_GPIO_ReadPin(E2A_GPIO_Port, E2A_Pin);
    uint8_t bbb = HAL_GPIO_ReadPin(E2B_GPIO_Port, E2B_Pin);

    printf("A: %d   B:%d\n", HAL_GPIO_ReadPin(E2A_GPIO_Port, E2A_Pin), HAL_GPIO_ReadPin(E2B_GPIO_Port, E2B_Pin));
    HAL_Delay(30);

printf("A: %d B:%d\n", aaa, bbb);

typedef struct
{
  int32_t last_recv;
  int32_t curr_index;
  int32_t buf_size;
  uint8_t* buf;
} button_status;
  ssd1306_Init();
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0,20);
  ssd1306_WriteString("Profile 1",Font_11x18,White);
  ssd1306_UpdateScreen();
  HAL_Delay(1000);
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0,0);
  ssd1306_WriteString("The quick brown fox",Font_7x10,White);
  ssd1306_SetCursor(0,10);
  ssd1306_WriteString("jumps over the lazy",Font_7x10,White);
  ssd1306_SetCursor(0,21);
  ssd1306_WriteString("doge much better",Font_7x10,White);
  ssd1306_SetCursor(0,32);
  ssd1306_WriteString("1234 1234 1234 1234 5678",Font_7x10,White);
  ssd1306_UpdateScreen();
  led_test();

void neopixel_show(uint8_t* red, uint8_t* green, uint8_t* blue)
{
  for (int i = 0; i < NEOPIXEL_COUNT; ++i)
  {
    uint32_t head = 24 * i;
    for (int i = 0; i < 8; ++i)
    {
      if (red[i] )
      {
        /* code */
      }
      ws_spi_buf[head + i] = ;
    }
  }
}