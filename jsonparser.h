/* Made by Palver. 08.11.2025.
 *
 * TODO:
 * - Probably should make and option to get values from JP_get_value() without unnecessary spaces and '\n'.
 *
 */

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Searches a string. If string is found returns the index, otherwise returns -1 */
int JP_find_str(char text[], char key[]) {
    bool is_str_found = false;
    int first_index;
    size_t i_text = 0;
    size_t i_str = 0;

    while (text[i_text] != '\0' && key[i_str] != '\0') {
        if (text[i_text] == key[i_str]) {
            if (i_str == 0) {
                first_index = i_text;
            }
            
            i_str++;
        } else {
            i_str = 0;
        }

        i_text++;

        if ((i_str + 1) == strlen(key)) {
            is_str_found = true;
        }
    }

    if (is_str_found) {
        return first_index;
    } else { return -1; }
}

char *JP_get_value(char text[], char key[]) {
    int index_key = JP_find_str(text, key);
    int val_index_start;
    int val_index_end;
    int value_size;
    char *value;

    if (index_key != -1) {
        int i = index_key;

        /* Search the start index*/
        while (text[i] != ':') {
            i++;
        }

        if (text[i] == ':') { /* exclude spaces */
            i++;
            while (text[i] == ' ') {
                i++;
            }
            val_index_start = i;
        } else { return NULL; }

        /* Search the end index */
        if (text[i] != '{' && text[i] != '[') {
            while (text[i] != ',' && text[i] != '\0') {
                i++;
            }

            if (text[i] == ',') {
                i--;

                /* exclude spaces before comma*/
                while (text[i] == ' ') {
                    i--;
                }

                val_index_end = i;
            } else { return NULL; }
        } else if (text[i] == '{') {
            i++;

            /* exclude garbage before the value */
            while (text[i] == ' ' || text[i] == '\n') {
                i++;
            }
            val_index_start = i;


            while (text[i] != '}') {
                i++;
            }
            if (text[i] != '}' && text[i] != '\0') { return NULL; }


            /* exclude grabge after the value */
            i--;
            while (text[i] == ' ') {
                i--;
            }


            val_index_end = i;
        } else if (text[i] == '[') {
            i++;

            /* exclude garbage before the value */
            while (text[i] == ' ' || text[i] == '\n') {
                i++;
            }
            val_index_start = i;

            
            while (text[i] != ']') {
                i++;
            }
            if (text[i] != ']' && text[i] != '\0') { return NULL; }


            /* exclude grabge after the value */
            i--;
            while (text[i] == ' ') {
                i--;
            }


            val_index_end = i;
        }

        /* Obtain the value */
        value_size = val_index_end - val_index_start+2; 
        value = (char*)malloc(value_size);
        if (value == NULL) { perror("Allocation failed"); exit(1); }

        strncpy(value, text+val_index_start, value_size-1);
        value[value_size-1] = '\0';   

        return value;
    }
}

#endif
