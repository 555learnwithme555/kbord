  printf("pf_name %s\n", pf_name);
  printf("%s\n", temp_buf);
Program Size: Code=29790 RO-data=3646 RW-data=444 ZI-data=7396  
void print_keyname(char* keyname, uint8_t keynum)
{
  if(strlen(keyname) > 7)
    keyname[7] = 0;
  uint8_t row = keynum / 3;
  uint8_t col = keynum - row * 3;
  uint8_t x_start = col_lookup[strlen(keyname) - 1][col];
  printf("pk %d %d %d %d %s\n", keynum, col, row, x_start, keyname);
  ssd1306_SetCursor(x_start, row * 10);
  ssd1306_WriteString(keyname, Font_6x10,White);
}
void parser_test(void)
{
  char* ddddd = find_profile(3);
  print_legend(3, ddddd);
}

uint8_t find_keys(char* pf_fn, uint8_t keynum)
{
  if(pf_fn == NULL)
    return PARSE_ERROR;

  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "/%s/key%d.txt", pf_fn, keynum);
  if(f_open(&sd_file, temp_buf, FA_READ) != 0)
  {
    f_close(&sd_file);
    return PARSE_ERROR;
  }
  printf("%s\n", temp_buf);
  memset(read_buffer, 0, READ_BUF_SIZE);
  while(f_gets(read_buffer, READ_BUF_SIZE, &sd_file))
    printf(">>>>%s\n", read_buffer);
  f_close(&sd_file);
  return PARSE_OK;
}


void key_display_test(void)
{
  ssd1306_Fill(Black);
  ssd1306_SetCursor(COL_1_X, ROW_1_Y);
  ssd1306_WriteString("key001",Font_6x10,White);
  ssd1306_SetCursor(COL_2_X, ROW_1_Y);
  ssd1306_WriteString("key002",Font_6x10,White);
  ssd1306_SetCursor(COL_3_X, ROW_1_Y);
  ssd1306_WriteString("key003",Font_6x10,White);

  ssd1306_SetCursor(COL_1_X, ROW_2_Y);
  ssd1306_WriteString("key004",Font_6x10,White);
  ssd1306_SetCursor(COL_2_X, ROW_2_Y);
  ssd1306_WriteString("key005",Font_6x10,White);
  ssd1306_SetCursor(COL_3_X, ROW_2_Y);
  ssd1306_WriteString("key006",Font_6x10,White);

  ssd1306_SetCursor(COL_1_X, ROW_3_Y);
  ssd1306_WriteString("key007",Font_6x10,White);
  ssd1306_SetCursor(COL_2_X, ROW_3_Y);
  ssd1306_WriteString("key008",Font_6x10,White);
  ssd1306_SetCursor(COL_3_X, ROW_3_Y);
  ssd1306_WriteString("key009",Font_6x10,White);

  ssd1306_SetCursor(COL_1_X, ROW_4_Y);
  ssd1306_WriteString("key010",Font_6x10,White);
  ssd1306_SetCursor(COL_2_X, ROW_4_Y);
  ssd1306_WriteString("key011",Font_6x10,White);
  ssd1306_SetCursor(COL_3_X, ROW_4_Y);
  ssd1306_WriteString("key012",Font_6x10,White);

  ssd1306_SetCursor(COL_1_X, ROW_5_Y);
  ssd1306_WriteString("key013",Font_6x10,White);
  ssd1306_SetCursor(COL_2_X, ROW_5_Y);
  ssd1306_WriteString("key014",Font_6x10,White);
  ssd1306_SetCursor(COL_3_X, ROW_5_Y);
  ssd1306_WriteString("key015",Font_6x10,White);
  ssd1306_UpdateScreen();
}


 
    // printf("key %d not found\n", keynum);
  // printf("key %d has no name\n", keynum);
    // printf("%d: %s\n", i, keyname);

uint8_t get_keyname(char* pf_fn, uint8_t key_num)
{
  if(pf_fn == NULL)
    return PARSE_ERROR;
  for (int i = 0; i < MAPPABLE_KEY_COUNT; ++i)
  {
    memset(temp_buf, 0, LFN_SIZE);
    sprintf(temp_buf, "/%s/key%d.txt", pf_fn, i+1);
    if(f_open(&sd_file, temp_buf, FA_READ) != 0)
    {
      f_close(&sd_file);
      continue;
    }
    printf("%s\n", temp_buf);
    memset(read_buffer, 0, READ_BUF_SIZE);
    f_gets(read_buffer, READ_BUF_SIZE, &sd_file);
    printf(">>>>%s\n", read_buffer);
    f_close(&sd_file);
  }
  return PARSE_OK;
}

void parser_test(void)
{
  char* ddddd = find_profile(1);
  // for (int i = 0; i < MAPPABLE_KEY_COUNT; ++i)
  //   find_keys(ddddd, i);
  print_legend(ddddd);
}
  
  


uint8_t print_legend(char* pf_fn)
{
  if(pf_fn == NULL)
    return PARSE_ERROR;
  for (int i = 1; i <= MAPPABLE_KEY_COUNT; ++i)
  {
    memset(temp_buf, 0, LFN_SIZE);
    sprintf(temp_buf, "/%s/key%d.txt", pf_fn, i);
    printf("%s\n", temp_buf);
    if(f_open(&sd_file, temp_buf, FA_READ) != 0)
    {
      f_close(&sd_file);
      continue;
    }
    memset(read_buffer, 0, READ_BUF_SIZE);
    f_gets(read_buffer, READ_BUF_SIZE, &sd_file);
    printf(">>>>%s\n", read_buffer);
    f_close(&sd_file);
  }
  return PARSE_OK;
}
void parser_test(void)
{
  char* ddddd = find_profile(1);
  find_keys(ddddd, 1);
  find_keys(ddddd, 2);
  find_keys(ddddd, 3);
  find_keys(ddddd, 4);
  find_keys(ddddd, 5);
  for (int i = 0; i < MAPPABLE_KEY_COUNT; ++i)
    find_keys(ddddd, i);
}

char ffffff[] = "/profile1_twitch/key1.txt";

void find_keys(char* pf_fn)
{
  uint32_t now = HAL_GetTick();
  for (int i = 1; i <= MAPPABLE_KEY_COUNT; ++i)
  {
    memset(temp_buf, 0, LFN_SIZE);
    sprintf(temp_buf, "/%s/key%d.txt", pf_fn, i);
    if(f_open(&sd_file, temp_buf, FA_READ) != 0)
      continue;
    printf("%s\n", temp_buf);
    memset(read_buffer, 0, READ_BUF_SIZE);
    while(f_gets(read_buffer, READ_BUF_SIZE, &sd_file))
      printf(">>>>%s\n", read_buffer);
  }
  printf("took %dms\n", HAL_GetTick() - now);
}
char ffffff[] = "/profile1_twitch/key1.txt";

find_keys(find_profile(1));
void find_keys(char* pf_fn)
{
  if(pf_fn == NULL)
    return;
  uint32_t now = HAL_GetTick();
  for (int i = 1; i <= MAPPABLE_KEY_COUNT; ++i)
  {
    memset(temp_buf, 0, LFN_SIZE);
    sprintf(temp_buf, "/%s/key%d.txt", pf_fn, i);
    if(f_open(&sd_file, temp_buf, FA_READ) != 0)
      continue;
    printf("%s\n", temp_buf);
    memset(read_buffer, 0, READ_BUF_SIZE);
    f_gets(read_buffer, READ_BUF_SIZE, &sd_file);
    printf(">>>>%s\n", read_buffer);
  }
  printf("took %dms\n", HAL_GetTick() - now);
}

void find_keys(char* pf_fn, uint8_t key_num)
{
  if(pf_fn == NULL)
    return;
  if(f_open(&sd_file, ffffff, FA_READ) != 0)
      return;
  while(f_gets(read_buffer, READ_BUF_SIZE, &sd_file))
    printf(">>>>%s\n", read_buffer);
}

void parser_test(void)
{
  
  // for (int i = 0; i < 8; ++i)
  // {
  //   char* result = find_profile(i);
  //   if(result == NULL)
  //     continue;
  //   printf("%s\n", result);
  //   find_keys(result);
  // }

  if(f_open(&sd_file, ffffff, FA_READ) != 0)
      return;
  while(f_gets(read_buffer, READ_BUF_SIZE, &sd_file))
    printf(">>>>%s\n", read_buffer);
}
  
  



void parser_test(void)
{
  for (int i = 0; i < 16; ++i)
  {
    char* result = find_profile(i);
    if(result == NULL)
      printf("profile %d not found\n", i);
    else
      printf("%s\n", result);
  }
}
  
void parser_test(void)
{
  if (f_opendir(&dir, "/") != FR_OK)
    return;
  char* result
  uint32_t now = HAL_GetTick();
  for (int i = 0; i < 255; ++i)
    find_profile(i);
  f_closedir(&dir);
  printf("took %dms\n", HAL_GetTick() - now);
}
  void parser_test(void)
{
  if (f_opendir(&dir, "/") != FR_OK)
    return;
  for (int i = 0; i < 255; ++i)
  {
    char* result = find_profile(i);
  }
  f_closedir(&dir);
}
void parser_test(void)
{
  uint32_t now = HAL_GetTick();
  for (int i = 0; i < 32; ++i)
    find_profile(i);
  printf("took %dms\n", HAL_GetTick() - now);
}
  
char* find_profile(uint8_t pid)
{
  fno.lfname = lfn_buf; 
  fno.lfsize = LFN_SIZE - 1;

  if (f_opendir(&dir, "/") != FR_OK)
    return NULL;

  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "profile%d_", pid);
  while(1)
  {
    memset(lfn_buf, 0, LFN_SIZE);
    if (f_readdir(&dir, &fno) != FR_OK || fno.fname[0] == 0)
      break;
    if (fno.fattrib & AM_DIR)
    {
      filename = fno.lfname[0] ? fno.lfname : fno.fname;
      if(strncmp(temp_buf, filename, strlen(temp_buf)) == 0)
      {
        printf("%s\n", filename);
        return filename;
      }
    }
  }
  f_closedir(&dir);
  return NULL;
}
  
uint8_t find_profile(uint8_t pid)
{
  fno.lfname = lfn_buf; 
  fno.lfsize = LFN_SIZE - 1;

  sd_fresult = f_opendir(&dir, "/");
  if (sd_fresult != FR_OK)
    return sd_fresult;

  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "profile%d_", pid);
  while(1)
  {
    memset(lfn_buf, 0, LFN_SIZE);
    sd_fresult = f_readdir(&dir, &fno);
    if (sd_fresult != FR_OK || fno.fname[0] == 0)
      break;
    if (fno.fattrib & AM_DIR)
    {
      filename = fno.lfname[0] ? fno.lfname : fno.fname;
      printf("%s\n", filename);
      if(strncmp(temp_buf, filename, strlen(temp_buf)) == 0)
        printf("found\n");
    }
  }
  f_closedir(&dir);
  return sd_fresult;
}


void parser_test(void)
{
  DIR dj;
  FILINFO fno;
  sd_fresult = f_findfirst(&dj, &fno, "", "profile1_*");
  if(sd_fresult == 0 && fno.fname[0])
    printf("%s\n", fno.fname);
}
char filename[] = "/profile1/key1.txt";

WCHAR ff_convert (WCHAR wch, UINT dir) 
{ 
    if (wch < 0x80)
      return wch;
    return 0; 
}

WCHAR ff_wtoupper (WCHAR wch) 
{ 
    if (wch >= 0x80)
      return 0; 

  if (wch >= 'a' && wch <= 'z')
    wch &= ~0x20; 
  return wch; 
}

void parser_test(void)
{
  if(f_stat(filename, NULL) != 0)
    return;
  if(f_open(&sd_file, filename, FA_READ) != 0)
    return;

  while(f_gets(read_buffer, READ_BUF_SIZE, &sd_file))
  {
    printf(">>>>%s\n", read_buffer);
  }

  f_close(&sd_file);
}





mount_result = f_mount(&sd_fs, "", 1);
  if(mount_result != 0)
    spi_set_speed_neopixel();

void parser_test(void)
{
  if(mount_result != 0)
    return;
  printf("looking for profile1 folder...\n");
  sd_fresult = f_stat("profile1", NULL);
  if(sd_fresult != 0)
    return;
  printf("entering profile1 folder...\n");
  f_chdir("/dir1");
  printf("sd_fresult: %d\n", sd_fresult);
}


printf("\nmounting SD card...\n");
  int32_t mount_result = f_mount(&sd_fs, "", 1);
  printf("result: %d\n", mount_result);

void keyboard_release(uint8_t k)
{
  if(k > 127)
    return;
  uint8_t usage_id = _asciimap[k];
  if(usage_id & 0x80)
    kb_buf[1] &= ~(0x02);
  usage_id = usage_id & 0x7f;

  for (int i = 2; i < KB_BUF_SIZE; ++i)
    if(kb_buf[i] == usage_id)
      kb_buf[i] = 0;

  // print_kb_buf();
  USBD_HID_SendReport(&hUsbDeviceFS, kb_buf, KB_BUF_SIZE);
}


printf("usage_id: 0x%x\n", usage_id);
  keyboard_press('a');
  HAL_Delay(50);
  keyboard_press('H');
  HAL_Delay(50);
  keyboard_release('a');
  HAL_Delay(50);
  keyboard_release('H');
  hello UPPERCASE
  // release_all();hello worldhello world
void keyboard_release(uint8_t k)
{
  if(k == 0)
    return;

  if(k & 0x80)
  {
    kb_buf[1] &= ~(0x02);
    k &= 0x7f;
  }
  for (int i = 2; i < 5; ++i)
    if(kb_buf[i] == k)
      kb_buf[i] = 0;
  USBD_HID_SendReport(&hUsbDeviceFS, kb_buf, 5);
}
hello UPPERCASE


    keyboard_update();

    if(is_fresh_pressed(&button_status[KEY_ROT2A_CW]))
    {
      printf("rot2 cw\n");
      service_fresh_press(&button_status[KEY_ROT2A_CW]);
    }

    if(is_fresh_pressed(&button_status[KEY_ROT2B_CCW]))
    {
      printf("rot2 ccw\n");
      service_fresh_press(&button_status[KEY_ROT2B_CCW]);
    }

    if(is_fresh_pressed(&button_status[KEY_0]))
    {
      printf("key0\n");
      service_fresh_press(&button_status[KEY_0]);
    }

    HAL_Delay(30);

button_status[KEY_0].button_state = 1 - HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin);
  if(button_status[KEY_0].prev_state == BUTTON_RELEASED && button_status[KEY_0].button_state == BUTTON_PRESSED)
    fresh_pressed(&button_status[KEY_0]);
  else if(button_status[KEY_0].prev_state == BUTTON_PRESSED && button_status[KEY_0].button_state == BUTTON_RELEASED)
    button_status[KEY_0].service_status = BUTTON_SERVICE_UNSERVICED;

<<<<<<< HEAD
if(button_event[KEY_ROT2A_CW])
    {
      printf("rot2 cw\n");
      button_event[KEY_ROT2A_CW] = 0;
    }

    if(button_event[KEY_ROT2B_CCW])
    {
      printf("rot2 ccw\n");
      button_event[KEY_ROT2B_CCW] = 0;
    }


=======
interrupt A on both edges, on high save timestamp, on low if idled long enough trigger event
save timestamp on both edge, trigger event if last ts was mre than  20ms ago
>>>>>>> 9b77f36630b4bb392fecc9a195f6ead5bb813dc4

CW:
A: 0 B:1
A: 0 B:0
A: 1 B:0
A: 1 B:1
kkkkkkkk
falling edge on A, if B is low CW, otherwise ccw
delay 20ms

HAL_Delay(500);
    printf("CARD_PRESENT: %d\n", HAL_GPIO_ReadPin(CARD_PRESENT_GPIO_Port, CARD_PRESENT_Pin));  
uint8_t aaa = HAL_GPIO_ReadPin(E2A_GPIO_Port, E2A_Pin);
    uint8_t bbb = HAL_GPIO_ReadPin(E2B_GPIO_Port, E2B_Pin);

    printf("A: %d   B:%d\n", HAL_GPIO_ReadPin(E2A_GPIO_Port, E2A_Pin), HAL_GPIO_ReadPin(E2B_GPIO_Port, E2B_Pin));
    HAL_Delay(30);
hhhhhhhhhhhhhhhhhhh
printf("A: %d B:%d\n", aaa, bbb);

  last_activity = HAL_GetTick();
  if(HAL_GPIO_ReadPin(E2B_GPIO_Port, E2B_Pin) == GPIO_PIN_SET)
    printf("ccw\n");
  else
    printf("cw\n");

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