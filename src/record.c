#include "record.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

static FILE *open_file(const char *path, const char *mode) {
    return fopen(path, mode);
}

bool record_append_one(const char *path, const StudentRecord *record) {
    FILE *fp = open_file(path, "ab");
    if (!fp) {
        return false;
    }
    size_t written = fwrite(record, sizeof(StudentRecord), 1, fp);
    fclose(fp);
    return written == 1;
}

bool record_append_many(const char *path, const StudentRecord *records, size_t count) {
    FILE *fp = open_file(path, "ab");
    if (!fp) {
        return false;
    }
    size_t total_written = 0;
    for (size_t i = 0; i < count; ++i) {
        total_written += fwrite(&records[i], sizeof(StudentRecord), 1, fp);
    }
    fclose(fp);
    return total_written == count;
}

bool record_iter_all(const char *path, record_iter_cb callback, void *user_data) {
    FILE *fp = open_file(path, "rb");
    if (!fp) {
        return false;
    }
    StudentRecord rec;
    while (fread(&rec, sizeof(StudentRecord), 1, fp) == 1) {
        callback(&rec, user_data);
    }
    fclose(fp);
    return true;
}

bool record_find_by_roll(const char *path, int roll, StudentRecord *out_record) {
    FILE *fp = open_file(path, "rb");
    if (!fp) {
        return false;
    }
    StudentRecord rec;
    bool found = false;
    while (fread(&rec, sizeof(StudentRecord), 1, fp) == 1) {
        if (rec.roll == roll) {
            if (out_record) {
                *out_record = rec;
            }
            found = true;
            break;
        }
    }
    fclose(fp);
    return found;
}

bool record_update_by_roll(const char *path, int roll, const StudentRecord *updated_record) {
    FILE *fp = open_file(path, "rb+");
    if (!fp) {
        return false;
    }
    StudentRecord rec;
    bool updated = false;
    while (fread(&rec, sizeof(StudentRecord), 1, fp) == 1) {
        if (rec.roll == roll) {
            if (fseek(fp, -(long)sizeof(StudentRecord), SEEK_CUR) != 0) {
                break;
            }
            size_t written = fwrite(updated_record, sizeof(StudentRecord), 1, fp);
            updated = (written == 1);
            break;
        }
    }
    fclose(fp);
    return updated;
}

bool record_delete_by_roll(const char *path, int roll) {
    char tmp_path[512];
    snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", path);

    FILE *src = open_file(path, "rb");
    if (!src) {
        return false;
    }
    FILE *dst = open_file(tmp_path, "wb");
    if (!dst) {
        fclose(src);
        return false;
    }

    StudentRecord rec;
    bool deleted = false;
    while (fread(&rec, sizeof(StudentRecord), 1, src) == 1) {
        if (rec.roll == roll) {
            deleted = true;
            continue; // skip the record to delete
        }
        fwrite(&rec, sizeof(StudentRecord), 1, dst);
    }

    fclose(src);
    fclose(dst);

    if (deleted) {
        if (remove(path) != 0) {
            // cleanup best-effort
            remove(tmp_path);
            return false;
        }
        if (rename(tmp_path, path) != 0) {
            return false;
        }
        return true;
    } else {
        // nothing deleted; keep original and remove temp
        remove(tmp_path);
        return false;
    }
}

float record_percentage(const StudentRecord *record) {
    if (!record) return 0.0f;
    float total = record->math + record->science + record->english + record->nepali + record->social;
    return total / 5.0f;
}

const char *record_division(float percentage) {
    if (percentage >= 80.0f && percentage <= 100.0f) return "Distinction";
    if (percentage >= 70.0f) return "First";
    if (percentage >= 60.0f) return "Second";
    if (percentage >= 50.0f) return "Third";
    return "No Division";
}
