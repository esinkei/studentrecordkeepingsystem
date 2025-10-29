#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---- Internal input helpers (local to this file) ----
static int ui_prompt_int(const char *prompt) {
    char buf[64];
    for (;;) {
        printf("%s", prompt);
        fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin)) {
            clearerr(stdin);
            continue;
        }
        size_t n = strlen(buf);
        if (n > 0 && buf[n - 1] == '\n') buf[n - 1] = '\0';
        char *end = NULL;
        long v = strtol(buf, &end, 10);
        if (end && end != buf && *end == '\0') return (int)v;
        printf("Please enter a valid integer.\n");
    }
}

static float ui_prompt_float(const char *prompt) {
    char buf[64];
    for (;;) {
        printf("%s", prompt);
        fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin)) {
            clearerr(stdin);
            continue;
        }
        size_t n = strlen(buf);
        if (n > 0 && buf[n - 1] == '\n') buf[n - 1] = '\0';
        char *end = NULL;
        float v = strtof(buf, &end);
        if (end && end != buf && *end == '\0') return v;
        printf("Please enter a valid number.\n");
    }
}

static void ui_prompt_string(const char *prompt, char *out, size_t out_size) {
    for (;;) {
        printf("%s", prompt);
        fflush(stdout);
        if (!fgets(out, out_size, stdin)) {
            clearerr(stdin);
            continue;
        }
        size_t n = strlen(out);
        if (n > 0 && out[n - 1] == '\n') out[n - 1] = '\0';
        if (out[0] == '\0') {
            printf("Input cannot be empty.\n");
            continue;
        }
        return;
    }
}

// ---- Public UI helpers ----
void ui_print_separator(void) {
    printf("***************************************************************************\n");
}

void ui_print_blank_line(void) {
    printf("\n");
}

int ui_prompt_main_menu(void) {
    printf("1. Add a record\n2. Add Bulk Records\n3. List Students\n4. Search Student\n5. Quit\n");
    int choice = ui_prompt_int("What's your choice? : ");
    return choice;
}

int ui_prompt_secondary_menu(void) {
    ui_print_separator();
    printf("1. Edit Record\n");
    printf("2. Delete Record\n");
    printf("3. View Marksheet\n");
    printf("4. Quit\n");
    return ui_prompt_int("What is your choice?: ");
}

static void ui_fill_record(StudentRecord *rec) {
    ui_prompt_string("Enter name: ", rec->name, sizeof(rec->name));
    rec->roll = ui_prompt_int("Enter roll: ");
    rec->math = ui_prompt_float("Enter marks obtained in Maths: ");
    rec->science = ui_prompt_float("Enter marks obtained in Science: ");
    rec->english = ui_prompt_float("Enter marks obtained in English: ");
    rec->nepali = ui_prompt_float("Enter marks obtained in Nepali: ");
    rec->social = ui_prompt_float("Enter marks obtained in Social: ");
}

void ui_add_single(const char *db_path) {
    StudentRecord rec;
    ui_fill_record(&rec);
    if (record_append_one(db_path, &rec)) {
        printf("Record saved successfully!\n");
    } else {
        fprintf(stderr, "Failed to save the record.\n");
    }
}

void ui_add_bulk(const char *db_path) {
    int count = ui_prompt_int("How many students?: ");
    if (count <= 0) return;
    for (int i = 0; i < count; ++i) {
        printf("Enter information for student %d :\n", i + 1);
        StudentRecord rec;
        ui_fill_record(&rec);
        if (!record_append_one(db_path, &rec)) {
            fprintf(stderr, "Failed to save record %d.\n", i + 1);
        }
    }
    printf("All records (attempted) written.\n");
}

static void print_summary_cb(const StudentRecord *rec, void *user_data) {
    (void)user_data;
    printf("%d\t\t\t\t%s\n", rec->roll, rec->name);
}

void ui_list_all(const char *db_path) {
    FILE *fp = fopen(db_path, "rb");
    if (!fp) {
        fprintf(stderr, "No records found or failed to open file.\n");
        return;
    }
    fclose(fp);

    ui_print_separator();
    printf("Roll\t\t\t\tName\t\t\n");
    if (!record_iter_all(db_path, print_summary_cb, NULL)) {
        fprintf(stderr, "Failed to read records.\n");
    }
}

void ui_print_marksheet(const StudentRecord *s) {
    float pcent = record_percentage(s);
    const char *div = record_division(pcent);

    printf("***************************************************************************\n");
    printf("|\tRoll\t: %-50d      |\n", s->roll);
    printf("|\tName\t: %-50s      |\n", s->name);
    printf("***************************************************************************\n");
    printf("|\tS.N.\t| Subjects                       |\tMarks\t\t  |\n");
    printf("***************************************************************************\n");
    printf("|\t1\t| Mathematics                    |  \t%-5.2f\t\t  |\n", s->math);
    printf("|\t2\t| English                        |  \t%-5.2f\t\t  |\n", s->english);
    printf("|\t3\t| Nepali                         |  \t%-5.2f\t\t  |\n", s->nepali);
    printf("|\t4\t| Science                        |  \t%-5.2f\t\t  |\n", s->science);
    printf("|\t5\t| Social                         |  \t%-5.2f\t\t  |\n", s->social);
    printf("***************************************************************************\n");
    printf("|\t \t| Percentage                     |  \t%-5.2f%%\t\t  |\n", pcent);
    printf("|\t \t| Division                       |  \t%-15s\t  |\n", div);
    printf("***************************************************************************\n");
    printf("END OF RESULT!\n");
}

void ui_search_and_act(const char *db_path) {
    int k = ui_prompt_int("Enter the roll no: ");
    StudentRecord rec;
    if (!record_find_by_roll(db_path, k, &rec)) {
        printf("Record not found!\n");
        return;
    }

    printf("Record Found\n");
    printf("Record name: %s\n", rec.name);

    int choice = ui_prompt_secondary_menu();
    switch (choice) {
        case 1: {
            // modify
            StudentRecord updated = rec;
            // Allow changing name and marks
            ui_prompt_string("Enter name: ", updated.name, sizeof(updated.name));
            updated.math = ui_prompt_float("Enter marks obtained in Maths: ");
            updated.science = ui_prompt_float("Enter marks obtained in Science: ");
            updated.english = ui_prompt_float("Enter marks obtained in English: ");
            updated.nepali = ui_prompt_float("Enter marks obtained in Nepali: ");
            updated.social = ui_prompt_float("Enter marks obtained in Social: ");
            if (record_update_by_roll(db_path, k, &updated)) {
                printf("Record successfully updated!\n");
            } else {
                printf("Failed to update record.\n");
            }
            break;
        }
        case 2: {
            // delete
            if (record_delete_by_roll(db_path, k)) {
                printf("Record deleted successfully!\n");
            } else {
                printf("Failed to delete record.\n");
            }
            break;
        }
        case 3: {
            // view marksheet
            ui_print_marksheet(&rec);
            break;
        }
        default:
            break;
    }
}
