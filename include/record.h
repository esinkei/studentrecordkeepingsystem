/**
 * Record management module for Student Record Keeping System.
 *
 * Encapsulates binary file operations for reading, writing, updating,
 * deleting and iterating over student records.
 */

#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include <stdbool.h>
#include <stddef.h>

#define STUDENT_NAME_MAX_LEN 50

typedef struct StudentRecord {
    char name[STUDENT_NAME_MAX_LEN];
    int roll;
    float math;
    float science;
    float english;
    float nepali;
    float social;
} StudentRecord;

typedef void (*record_iter_cb)(const StudentRecord *record, void *user_data);

// Append records
bool record_append_one(const char *path, const StudentRecord *record);
bool record_append_many(const char *path, const StudentRecord *records, size_t count);

// Read and iterate
bool record_iter_all(const char *path, record_iter_cb callback, void *user_data);
bool record_find_by_roll(const char *path, int roll, StudentRecord *out_record);

// Update and delete
bool record_update_by_roll(const char *path, int roll, const StudentRecord *updated_record);
bool record_delete_by_roll(const char *path, int roll);

// Helpers
float record_percentage(const StudentRecord *record);
const char *record_division(float percentage);

#endif // STUDENT_RECORD_H
