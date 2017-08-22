#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#include "shared.h"
#include "buttons.h"
#include "parser.h"
#include "ssd1306.h"
#include "keyboard.h"

#define READ_BUF_SIZE 256
#define DEFAULT_CMD_DELAY_MS 15
#define DEFAULT_CHAR_DELAY_MS 15

uint8_t col_lookup[7][3] = {  
   {18, 60, 103},
   {15, 57, 100},
   {12, 54, 97},
   {9, 51, 94},
   {6, 48, 91},
   {3, 45, 88},
   {0, 42, 85}
};

FRESULT sd_fresult;
FATFS sd_fs;
FIL sd_file;
DIR dir;
FILINFO fno;
uint8_t mount_result;
uint16_t cmd_delay, char_delay;

char* profile_fn;
uint8_t current_profile;
char temp_buf[LFN_SIZE];
char lfn_buf[LFN_SIZE];
char read_buffer[READ_BUF_SIZE];
char unnamed_keyname[] = "???";
char nonexistent_keyname[] = "-";

const char syntax_NAME[] = "NAME ";
const char syntax_REM[] = "REM ";
const char syntax_C_COMMENT[] = "// ";
const char syntax_DEFAULTDELAY[] = "DEFAULTDELAY ";
const char syntax_DEFAULTCHARDELAY[] = "DEFAULTCHARDELAY ";
const char syntax_DELAY[] = "DELAY ";
const char syntax_STRING[] = "STRING ";
const char syntax_ENTER[] = "ENTER";
const char syntax_[] = " ";

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
      profile_fn = fno.lfname[0] ? fno.lfname : fno.fname;
      if(strncmp(temp_buf, profile_fn, strlen(temp_buf)) == 0)
        return profile_fn;
    }
  }
  f_closedir(&dir);
  return NULL;
}

char* get_keyname(char* pf_fn, uint8_t keynum)
{
  if(pf_fn == NULL)
    return nonexistent_keyname;
  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "/%s/key%d.txt", pf_fn, keynum + 1);
  if(f_open(&sd_file, temp_buf, FA_READ) != 0)
  {
    f_close(&sd_file);
    return nonexistent_keyname;
  }
  memset(read_buffer, 0, READ_BUF_SIZE);
  f_gets(read_buffer, READ_BUF_SIZE, &sd_file);
  f_close(&sd_file);
  for (int i = 0; i < READ_BUF_SIZE; ++i)
    if(read_buffer[i] == '\r' || read_buffer[i] == '\n')
      read_buffer[i] = 0;
  if(strncmp(syntax_NAME, read_buffer, strlen(syntax_NAME)) == 0)
    return read_buffer + strlen(syntax_NAME);
  return unnamed_keyname;
}

void print_keyname(char* keyname, uint8_t keynum)
{
  if(strlen(keyname) > 7)
    keyname[7] = 0;
  uint8_t row = keynum / 3;
  uint8_t col = keynum - row * 3;
  uint8_t x_start = col_lookup[strlen(keyname) - 1][col];
  ssd1306_SetCursor(x_start, (row + 1) * 10 + 3);
  ssd1306_WriteString(keyname, Font_6x10,White);
}

void print_legend(uint8_t pf_num, char* pf_fn)
{
  ssd1306_Fill(Black);
  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "profile%d_", pf_num);
  char* pf_name = pf_fn + strlen(temp_buf);
  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "P%d: %s", pf_num, pf_name);
  if(strlen(temp_buf) > 21)
    temp_buf[21] = 0;
  uint8_t x_start = (21 - strlen(temp_buf)) * 3;
  ssd1306_SetCursor(x_start, 0);
  ssd1306_WriteString(temp_buf, Font_6x10,White);
  for (int i = 0; i < MAPPABLE_KEY_COUNT; ++i)
    print_keyname(get_keyname(pf_fn, i), i);
  ssd1306_UpdateScreen();
}

void change_profile(uint8_t dir)
{
  uint16_t count = 0;
  while(1)
  {
    count++;
    if(dir == NEXT_PROFILE)
      current_profile++;
    else
      current_profile--;
    char* ddddd = find_profile(current_profile);
    if(ddddd != NULL)
    {
      print_legend(current_profile, ddddd);
      return;
    }
    else if(count > 255)
    {
      ssd1306_Fill(Black);
      ssd1306_SetCursor(0, 0);
      ssd1306_WriteString("no valid profiles!",Font_6x10,White);
      ssd1306_UpdateScreen();
      return;
    }
  }
}

void parser_test(void)
{
  ;
}

char* goto_next_arg(char* buf)
{
  char* curr = buf;
  char* buf_end = curr + strlen(curr);
  if(curr >= buf_end)
    return NULL;
  while(curr < buf_end && *curr != ' ')
      curr++;
  while(curr < buf_end && *curr == ' ')
      curr++;
  if(curr >= buf_end)
    return NULL;
  return curr;
}

uint8_t parse_line(char* line)
{
  uint8_t result = PARSE_OK;
  cmd_delay = DEFAULT_CMD_DELAY_MS;
  char_delay = DEFAULT_CHAR_DELAY_MS;

  for (int i = 0; i < strlen(line); ++i)
    if(line[i] == '\r' || line[i] == '\n')
      line[i] = 0;
  printf(">> %s\n", line);

  if(strncmp(syntax_NAME, line, strlen(syntax_NAME)) == 0)
    ;
  else if(strncmp(syntax_REM, line, strlen(syntax_REM)) == 0)
    ;
  else if(strncmp(syntax_C_COMMENT, line, strlen(syntax_C_COMMENT)) == 0)
    ;
  else if(strncmp(syntax_STRING, line, strlen(syntax_STRING)) == 0)
    kb_print(line + strlen(syntax_STRING), char_delay);
  else if(strncmp(syntax_ENTER, line, strlen(syntax_ENTER)) == 0)
    {
      keyboard_press(KEY_RETURN);
      osDelay(char_delay);
      keyboard_release_all();
      osDelay(char_delay);
    }
  else if(goto_next_arg(line) == NULL || strlen(goto_next_arg(line)) <= 3)
    ;
  else
  {
    result = PARSE_ERROR;
  }
  if(result == PARSE_OK)
    osDelay(cmd_delay);
  return result;
}
  
void handle_keypress(uint8_t key_num)
{
  char* ddddd = find_profile(current_profile);
  if(ddddd == NULL)
    return;
  memset(temp_buf, 0, LFN_SIZE);
  sprintf(temp_buf, "/%s/key%d.txt", ddddd, key_num+1);
  if(f_open(&sd_file, temp_buf, FA_READ) != 0)
  {
    f_close(&sd_file);
    return;
  }
  printf("opened %s\n", temp_buf);
  while(f_gets(read_buffer, READ_BUF_SIZE, &sd_file) != NULL)
  {
    parse_line(read_buffer);
    memset(read_buffer, 0, READ_BUF_SIZE);
  }
  f_close(&sd_file);
  return;
}

