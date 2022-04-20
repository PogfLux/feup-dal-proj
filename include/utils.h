#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

class Exit{};

/**
 * @brief Clears the screen
 *
 */
void clearScreen();

/**
 * @brief Clears the standard input stream
 *
 */
void clearInput();

/**
 * @brief Waits for the user to press ENTER
 *
 * @param prompt the prompt to show, defaults to "Press ENTER to continue..."
 */
void waitForEnter(std::string prompt = "Press ENTER to continue...");

/**
 * @brief Splits a string by a character.
 *
 * @param str The string to be split.
 * @param i The character to use as the separator.
 * @return A vector with all the words in the string that were separated by the
 *         given character.
 */
std::vector<std::string> split(std::string str, char sep);

/**
 * @brief Normalizes a string.
 *
 * @details Replaces all tabs with spaces, removes duplicate spaces and trims
 *          spaces from the start and the end.
 *
 * @param input The string to normalize.
 */
void normalizeInput(std::string &input);