#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
    std::string input;
    std::vector<std::string> stopWords = {"!", ",", ".", "?", "(", ")", "[", "]", "{", "}", "из", "от", "в", "на", "с", "по", "за", "к", "у", "о", "об", "но", "а", "и", "или", "если", "то", "не", "что", "как", "для", "это", "так", "же", "вот", "там", "тут", "где", "когда", "чтобы", "чтобы", "только", "уже", "еще", "ещё", "ну", "да", "нет", "ли", "бы", "б", "ведь", "во", "со", "до", "под", "над", "перед", "после", "между", "через", "при", "без", "про", "какой", "какая", "какое", "какие", "кто", "что", "чей", "чья", "чьё", "чьи", "который", "которая", "которое", "которые", "как", "так", "там", "тут", "здесь", "там", "туда", "сюда", "оттуда", "отсюда", "все", "всё", "всего", "всю", "всем", "всеми", "вся", "всей", "всюду", "никто", "ничто", "никакой", "нигде", "никогда", "нисколько", "нечего", "негде", "некуда", "некогда", "незачем"};
public:
    static void removeSpecialCharacters(std::string&);
    static void removeExtraSpaces(std::string&);
    static std::vector<std::string> tokenize(const std::string&);
    std::vector<std::string> removeStopWords(const std::vector<std::string>&);
    static std::string tokenizedToString(const std::vector<std::string>&);
};

#endif
