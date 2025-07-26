#include <stdio.h>
#include <stdint.h>

int main() {
    FILE *in = fopen("level_1_breach.raw", "rb");
    FILE *out = fopen("level_1_breach.h", "w");
    fprintf(out, "const uint8_t audioData[] = {\n");
    int byte, count = 0;
    while ((byte = fgetc(in)) != EOF) {
        fprintf(out, "0x%02x", (uint8_t)byte);
        if (count++ % 16 == 15) fprintf(out, ",\n");
        else fprintf(out, ", ");
    }
    fprintf(out, "\n};");
    fclose(in);
    fclose(out);
    return 0;
}