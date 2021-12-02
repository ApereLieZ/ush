#include "../inc/libmx.h"

char **mx_strsplit(char const *s, char c) {
	if (s == NULL) {
		return NULL;
	}
	int count = mx_count_words(s, c);
	char **words = malloc(sizeof(char*) * (count + 1));
	int begin = 0;
	for (int i = 0; i < count; i++) {
		while (s[begin] == c) {
			begin++;
		}
		int begin_word = begin;
		int word_len = 0;
		while (s[begin_word] != c) {
			word_len++;
			begin_word++;
		}
		words[i] = mx_strnew(word_len);
		mx_strncpy(words[i], s + begin, word_len);
		begin += word_len;
	}
	words[count] = NULL;
	return words;
}

