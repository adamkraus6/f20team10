/** **************************************************************************
 * @file
 * 
 * @brief Main file
 ****************************************************************************/
 /** **************************************************************************
  * @mainpage Program 2 - Word Frequency
  *
  * @section course_section Course Information
  *
  * @authors Adam Kraus, Lochlan Munro
  *
  * @par Professor:
  *         Roger L. Schrader
  *
  * @par Course:
  *         CSC215 - M002 - Programming Techniques
  *
  * @par Location:
  *         Classroom Building - 203
  *
  * @date Due November 6, 2020
  *
  * @section program_section Program Information
  *
  * @details
  * This program takes in a text file with words and outputs information based 
  * on the frequency of the words in the text file.
  * 
  * This program is started at the command line with 3 necessary arguments, 
  * and 1 optional argument. The 3 necessary arguments include the file that 
  * has all the words, and 2 files that hold a list of the words based on 
  * their first letter and then a list of the words based on the optional 
  * argument. The optional argument is used to determine whether to output
  * words based on frequency, length, or both.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
    c:\> prog3.exe inputfile outputWords outputStats -[option]
             inputfile   - filename containing our words/story
             outputWords - filename to output words in increasing order
             outputStats - filename to output stats for words based on option
             [option]    - option to change output of stats, "f" for frequency, "l" for length, can use multiple options in any order (ex: -fl)
    @endverbatim
  *
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  *****************************************************************************/

#include "prog2.h"
#include "wordFreq.h"

  /** ***************************************************************************
   * @author Adam Kraus, Lochlan Munro
   *
   * @par Description:
   * Main function
   *
   * @param[in] argc - number of command line arguments supplied.
   * @param[in] argv - 2D char array of command line arguments.
   *
   * @returns exit code
   *
   *****************************************************************************/
int main(int argc, char** argv)
{
    string option, inputFile, outputWords, outputStats, word;
    ifstream fin;
    ofstream fout1, fout2;
    wordFreq words;

    // check command line arguments
    if (argc < 4 || argc > 5)
    {
        cout << "Usage: prog2.exe inputFile outputWords outputStats [option]" << endl;
        exit(0);
    }

    if (argc == 5)
    {
        option = argv[4];
    }
    else {
        option = "-f";
    }

    // check option
    if (option != "-f" && option != "-l"
        && option != "-fl" && option != "-lf")
    {
        cout << "Invalid option: " << option << endl;
        exit(0);
    }

    inputFile = argv[1];
    outputWords = argv[2];
    outputStats = argv[3];
    
    // open/check input file
    fin.open(inputFile, ios::in);
    if (!fin.is_open())
    {
        cout << "Unable to open file: " << inputFile << endl;
        exit(0);
    }

    // open/check output words file
    fout1.open(outputWords, ios::out);
    if (!fout1.is_open())
    {
        cout << "Unable to open file: " << outputWords << endl;
        exit(0);
    }

    // open/check output stats file
    fout2.open(outputStats, ios::out);
    if (!fout2.is_open())
    {
        cout << "Unable to open file: " << outputStats << endl;
        exit(0);
    }

    while (fin >> word)
    {
        trimPunct(word);
        wordToLower(word);

        if (word.empty()) continue;
        //cout << word << endl;

        if (words.findbyWord(word))
        {
            if (!words.increment(word))
            {
                cout << "Unable to increment word: " << word << endl;
                exit(0);
            }
        }
        else {
            if (!words.insert(word))
            {
                cout << "Unable to insert word: " << word << endl;
                exit(0);
            }
        }
    }

    words.printbyLetter(fout1);

    if (option == "-f")
    {
        words.printbyFrequency(fout2);
    }
    else if (option == "-l")
    {
        words.printbyLength(fout2);
    }
    else if (option == "-fl")
    {
        words.printbyFrequency(fout2);
        words.printbyLength(fout2);
    }
    else if (option == "-lf")
    {
        words.printbyLength(fout2);
        words.printbyFrequency(fout2);
    }

    // clear list, free memory
    words.clear();
    fin.close();
    fout1.close();
    fout2.close();
}