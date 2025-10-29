#ifndef UI_H
#define UI_H

#include "record.h"

void ui_print_separator(void);
void ui_print_blank_line(void);
int ui_prompt_main_menu(void);
int ui_prompt_secondary_menu(void);

void ui_add_single(const char *db_path);
void ui_add_bulk(const char *db_path);
void ui_list_all(const char *db_path);
void ui_search_and_act(const char *db_path);
void ui_print_marksheet(const StudentRecord *record);

#endif // UI_H
