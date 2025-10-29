#include "ui.h"

#include <stdio.h>

#define DB_PATH "rex.txt" // Keep original filename for backward compatibility

int main(void) {
    while (1) {
        ui_print_separator();
        ui_print_blank_line();
        int choice = ui_prompt_main_menu();
        switch (choice) {
            case 1:
                ui_add_single(DB_PATH);
                break;
            case 2:
                ui_add_bulk(DB_PATH);
                break;
            case 3:
                ui_list_all(DB_PATH);
                break;
            case 4:
                ui_search_and_act(DB_PATH);
                break;
            case 5:
                return 0;
            default:
                ui_print_separator();
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}
