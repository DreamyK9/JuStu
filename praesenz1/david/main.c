/**
 * Programm zur Ermittlung der Buchstabenhäufigkeiten eines Textes.
 *
 * Entwickelt im Rahmen der Aufgabenstellung der zweiten Präsenz des Juniorstudiums "Imperative Programmierung"
 * (1. Semester) an der Uni Rostock von David Breyer, Florian Zinck und Anton Vogelsang.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define char_index(x) (x - 97)
#define index_char(x) (x + 97)
#define ALPHABET_LENGTH 26
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

#define GERMAN  "enisratdhulcgmob"
#define SPANISH "eaosrnidlctumpbg"
#define ENGLISH "etaoinsrhldcumfp"
#define ITALIAN "eaionlrtscdupmvg"
#define print_language(i) switch (i) { case 0:  printf("German");  break; \
                                       case 1:  printf("Spanish"); break; \
                                       case 2:  printf("Italian"); break; \
                                       case 3:  printf("English"); break; \
                                       default: printf("N/A");     break; }

/**
 * Liest den Inhalt einer Datei in einen char-Buffer
 *
 * Funktionsweise:
 *  Es wird versucht, die Datei zu öffnen.
 *  Wenn ein Fehler dabei auftritt, wird ein nullpointer zurückgegeben.
 *  Die Länge der Datei wird mit fseek() und fread() bestimmt und ein Buffer dieser Größe wird alloziert.
 *  Der Inhalt der Datei wird in den Buffer kopiert und die Datei geschlossen.
 *
 * @param file_name Pfad der Datei
 * @return Pointer zum ersten char im Buffer
 */
char* read_file_contents(const char* file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == 0) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    char* buffer = malloc(length + 1);
    fseek(file, 0, SEEK_SET);
    fread(buffer, length, 1, file);
    fclose(file);
    buffer[length] = 0;

    return buffer;
}

typedef struct {
    unsigned long* char_counts;
    unsigned long char_count;
} analyze_result_t;

/**
 * Zählt die Buchstaben in einem string und gibt diese als Array mit einer Länge von 26 zusammen mit der Gesamtzahl
 * an Buchstaben zurück.
 *
 * Funktionsweise:
 *  Es wird ein unsigned long array mit der Länge von 26 allokiert und die Werte werden mit 0 initialisiert.
 *  Es wird über jeden Buchstaben des String iteriert. Wenn es sich um einen Buchstaben handelt, wird der Wert
 *  im Array an der Position des Buchstabens im Alphabet inkrementiert.
 *
 * @param content Der Inhalt der Datei als string
 * @param out analyse_result_t zum Zurückgeben der Werte
 */
void calculate_char_count(char* content, analyze_result_t* out) {
    out->char_counts = calloc(ALPHABET_LENGTH, sizeof(unsigned long));
    out->char_count = 0;

    int c;
    for (int i = 0; content[i]; i++) {
        c = tolower((unsigned char) content[i]);
        out->char_count++;
        if (isalpha(c)) {
            out->char_counts[char_index(tolower(c))]++;
        }
    }
}

/**
 * Berechnet die relative Häufigkeit von jedem Buchstaben und speichert sie in einem float-Array.
 *
 * Funktionsweise:
 *  Alloziert ein Array von 26 floats.
 *  Iteriert über die Buchstaben und speichert deren Häufigkeit in Prozent ein dem float-Array.
 *
 * @param analysis Das Ergebnis der Buchstabenzählung (calculate_char_count)
 * @return Das float-Array mit den relativen Häufigkeiten in Prozent
 */
float* calculate_char_freq(analyze_result_t* analysis) {
    float* percentages = malloc(ALPHABET_LENGTH * sizeof(float));
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        percentages[i] = (((float)analysis->char_counts[i]) / ((float)analysis->char_count)) * 100;
    }
    return percentages;
}

/**
 * Sortiert das Ergebnis von `calculate_char_freq` nach Häufigkeiten und gibt die
 * 16 Häufigsten Buchstaben geordnet als string zurück.
 *
 * @param p float-Array mit relativen Häufigkeiten in Prozent
 * @return string aus den 16 Häufigsten Buchstaben
 */
char* sort_letters_by_frequency(float* p) {
    float* percentages = malloc(ALPHABET_LENGTH * sizeof(float));
    memcpy(percentages, p, ALPHABET_LENGTH);
    char* out = malloc(16 * sizeof(char) + 1);
    out[16] = 0;

    for (int i = 0; i < 16; i++) {
        float max = 0;
        char m = 0;

        for (char j = 0; j < ALPHABET_LENGTH; j++) {
            if (max < percentages[j]) {
                max = percentages[j];
                m = j;
            }
        }
        percentages[m] = 0;
        out[i] = index_char(m);
    }

    free(percentages);

    return out;
}

/**
 * Implementation des Levenshtein-Algorithmus, der zum erkennen der Sprache benutzt wird.
 *
 * Code aus: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
 */
int levenshtein(const char* s1, const char* s2, unsigned int s1len, unsigned int s2len) {
    unsigned int x, y, lastdiag, olddiag;
    unsigned int column[17];
    for (y = 1; y <= s1len; y++) {
        column[y] = y;
    }
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y-1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return column[s1len];
}

#define comp(l, i) if ((l) < prev) { prev = l; max = i; }

typedef struct {
    double probability;
    int result; // Index der ermittelten Sprache { SPANISH, GERMAN, ITALIAN, ENGLISH }
} language_result_t;

/**
 * Ermittelt die Sprache des Textes mithilfe der Levenshtein-Distanz
 * von strings der häufigsten Buchstaben der Sprachen Deutsch, Spanisch, Englisch und Italienisch und
 * des `chars` Parameters.
 *
 * @param chars Häufigste Buchstaben eines Textes als String, Rückgabe von `sort_letters_by_frequency`
 * @param out Pointer zu einem language_result_t-Struct, in dem das Ergebnis gespeichert wird.
 */
void guess_language(char* chars, language_result_t* out) {
    int prev = INT_MAX;
    int max = 0;
    int esp = levenshtein(chars, SPANISH, 16, 16);
    int ger = levenshtein(chars, GERMAN, 16, 16);
    int it =  levenshtein(chars, ITALIAN, 16, 16);
    int en =  levenshtein(chars, ENGLISH, 16, 16);

    comp(ger, 0)
    comp(esp, 1)
    comp(it,  2)
    comp(en,  3)

    int sum = ger + esp + it + en;

    out->probability = (sum - prev) * (100.0 / sum);
    out->result = max;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file path> [OPTIONAL ARGUMENTS]\nArguments:\n  -o: Print the text to stdout before analysing\n", argv[0]);
        return 1;
    }

    unsigned char print_contents = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            print_contents = 1;
        }
    }

    char* data = read_file_contents(argv[1]);

    if (data == 0) {
        printf("%s: Error: File couldn't be opened", argv[0]);
        return 1;
    }

    if (print_contents) {
        printf("%s\n", data);
    }

    analyze_result_t analyze_result;
    calculate_char_count(data, &analyze_result);

    float* percentages = calculate_char_freq(&analyze_result);

    char* freqs = sort_letters_by_frequency(percentages);
    language_result_t language_result;
    guess_language(freqs, &language_result);

    float percentage_sum = 0;

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        percentage_sum += percentages[i];

        if (percentages[i] == 0.0) continue;

        printf("%05.2f%% %c\n", percentages[i], toupper(index_char(i)));
    }

    printf("%05.2f%% Other\n", 100.0 - percentage_sum);

    printf("\nThe text is probably (%.2f%%) ", language_result.probability);
    print_language(language_result.result);
    printf("!\n");

    free(freqs);
    free(percentages);
    free(analyze_result.char_counts);
    free(data);

    return 0;
}
