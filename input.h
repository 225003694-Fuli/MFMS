#ifndef INPUT_H
#define INPUT_H

int readInt(const char *prompt, int min, int max);

float readFloat(const char *prompt, float min);

void readString(const char *prompt, char *dest, int size);

#endif
