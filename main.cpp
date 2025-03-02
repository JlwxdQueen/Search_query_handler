#include "./tools/setup.h"
#include "include/Tokenizer.h"
#include "./include/relevanceProcessor.h"


#include <iostream>

int main() {

    setup();

    // Пример строки с лишними пробелами и стоп-словами
    std::string input = "  Это   пример   строки,  которая  содержит  лишние  пробелы и стоп-слова!  ";

    Tokenizer::removeSpecialCharacters(input);
    std::cout << "Строка после удаления специальных символов: \"" << input << "\"" << std::endl;

    // Удаляем лишние пробелы
    Tokenizer::removeExtraSpaces(input);
    std::cout << "Строка после удаления лишних пробелов: \"" << input << "\"" << std::endl;

    // Токенизируем строку
    std::vector<std::string> tokens = Tokenizer::tokenize(input);
    std::cout << "Токены: ";
    for (const auto& token : tokens) {
        std::cout << "\"" << token << "\" ";
    }
    std::cout << std::endl;

    // Удаляем стоп-слова
    Tokenizer tokenizer;
    std::vector<std::string> filteredTokens = tokenizer.removeStopWords(tokens);
    std::cout << "Токены после удаления стоп-слов: ";
    for (const auto& token : filteredTokens) {
        std::cout << "\"" << token << "\" ";
    }
    std::cout << std::endl;

    // Преобразуем токены обратно в строку
    const std::string result = Tokenizer::tokenizedToString(filteredTokens);
    std::cout << "Строка после обработки: \"" << result << "\"" << std::endl;

    // Искомая информация
    const std::string seekedInfo = "machine learning";

    // Создаем объект RelevanceProcessor
    RelevanceProcessor processor(seekedInfo);

    // Список документов для сравнения
    std::vector<std::string> documents = {
        "machine learning is a subset of artificial intelligence",
        "artificial intelligence and machine learning are closely related",
        "deep learning is a subset of machine learning",
        "machine learning algorithms are used in various applications",
        "artificial intelligence is the future of technology"
    };

    // Вычисляем релевантность для каждого документа
    processor.calculate_relevance(documents);

    // Выводим результаты релевантности
    for (const auto& doc : documents) {
        const float relevance = processor.get_relevance(doc);
        std::cout << "Document: \"" << doc << "\" has relevance: " << relevance << std::endl;
    }

    return 0;
}