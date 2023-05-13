/*
  Solution to Question 5 of AngelHack May 2023 Coding Challenge
  Answer = i love angelhack code challenge because it is fun and exciting and i dislike the word yab that appears in the phrase
*/

#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

/*
  Function to sort codebook according to length of encoding from fewer to most bits
*/
std::vector<std::pair<std::string, std::string>> sort_codebook(const std::unordered_map<std::string, std::string>& codebook)
{
  std::vector<std::pair<std::string, std::string>> sortedCodebook{codebook.begin(), codebook.end()};
  std::sort(
    sortedCodebook.begin(),
    sortedCodebook.end(),
    [](const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs)
    {
      return lhs.second < rhs.second;
    });

  return sortedCodebook;
}

/*
  Function to decode encoded string based on input codebook.
  In the event of ambiguity, function will always choose the symbol represented by fewer bits.
  If there are multiple symbols represented by the same code, output is undefined.
*/
std::string decode(const std::string& encoded, const std::unordered_map<std::string, std::string>& codebook)
{
  const auto& sortedCodebook = sort_codebook(codebook);
  std::string result;
  size_t pos = 0;
  auto encodedSize = encoded.size();

  while (pos < encodedSize)
  {
    auto validEncoding = false;
    for (const auto& code : sortedCodebook)
    {
      auto codeSize = code.second.size();
      if (encoded.substr(pos, codeSize) == code.second)
      {
        validEncoding = true;
        result += code.first;
        pos += codeSize;
        break;
      }
    }

    if (!validEncoding)
    {
      std::cout << "Failed to decode input. Encountered invalid code at position '" << pos << "'" << std::endl;
      return "";
    }
  }

  return result;
}

int main()
{
 static const std::unordered_map<std::string, std::string> codebook =
 {
    { "a", "00" },
    { "b", "01" },
    { "c", "10" },
    { "d", "1100" },
    { "e", "1101" },
    { "f", "1110" },
    { "g", "111100" },
    { "h", "111101" },
    { "i", "111110" },
    { "j", "1111110000" },
    { "k", "1111110001" },
    { "l", "1111110010" },
    { "m", "1111110011" },
    { "n", "1111110100" },
    { "o", "1111110101" },
    { "p", "1111110110" },
    { "q", "1111110111" },
    { "r", "1111111000" },
    { "s", "1111111001" },
    { "t", "1111111010" },
    { "u", "1111111011" },
    { "v", "1111111100" },
    { "w", "1111111101" },
    { "x", "1111111110" },
    { "y", "1111111111" },
    { "z", "11111111110000" },
    { " ", "11111111110001" }
  };

  const std::string encoded = "11111011111111110001111111001011111101011111111100110111111111110001001111110100111100110111111100101111010010111111000111111111110001101111110101110011011111111111000110111101001111110010111111001011011111110100111100110111111111110001011101100011111110111111111001110111111111110001111110111111101011111111110001111110111111100111111111110001111011111110111111110100111111111100010011111101001100111111111100011101111111111010111110111111101011111011111101001111001111111111000100111111010011001111111111000111111011111111110001110011111011111110011111110010111110111111000111011111111111000111111110101111011101111111111100011111111101111111010111111110001100111111111100011111111111000111111111110001111111101011110100111111101011111111110001001111110110111111011011010011111110001111111001111111111100011111101111110100111111111100011111111010111101110111111111110001111111011011110111111110000011111110011101";
  auto decoded = decode(encoded, codebook);

  /*
    From given codebook, there is ambiguity with "yaa" and "z", as well as "yab" and " ".

    In order to disambiguate the decoded string, we will need to make the following assumptions:
      1. Output should be a proper sentence. i.e. All words should be separated by a single spacing
      2. In the event of ambiguity, word will be chosen to be actual word from the dictionary where possible
        - e.g. 0111111110111111111111000111111100101101 can either be "buyable" or "bu le", but "buyable" will be chosen here as it is an actual word
        - Dictionary used in code below is retrieved from https://svnweb.freebsd.org/base/head/share/dict/web2)

    Steps to disambiguate decoded string:
      1. Replace all occurrences of "yaa" with "z" and "yab" with " "
      2. Check if actual words that contained "yaa" or "yab" was replaced, and revert them
        - e.g. Revert "enjo le" to "enjoyable"

    Note: It is possible to perform disambiguation in function but it will make solution much more complex.
          Hence, for this challenge disambiguation will be done separately, outside the function.
  */

  // Words containing "yaa" and "yab" from word list retrieved from https://svnweb.freebsd.org/base/head/share/dict/web2
  static const std::unordered_map<std::string, std::string> wordsToRevert =
  {
    { "assa le", "assayable" },
    { "bull le", "bullyable" },
    { "bu le", "buyable" },
    { "clerg le", "clergyable" },
    { "conve le", "conveyable" },
    { "cr le", "cryable" },
    { "da haga", "dayabhaga" },
    { "deca le", "decayable" },
    { "defra le", "defrayable" },
    { "dela le", "delayable" },
    { "destro le", "destroyable" },
    { "disma le", "dismayable" },
    { "displa le", "displayable" },
    { "emplo ility", "employability" },
    { "emplo le", "employable" },
    { "enjo le", "enjoyable" },
    { "enjo leness", "enjoyableness" },
    { "enjo ly", "enjoyably" },
    { "fl le", "flyable" },
    { "gua a", "guayaba" },
    { "gua i", "guayabi" },
    { "gua o", "guayabo" },
    { "impa le", "impayable" },
    { "nonclerg le", "nonclergyable" },
    { "nonrepa le", "nonrepayable" },
    { "obe le", "obeyable" },
    { "pa ility", "payability" },
    { "pa le", "payable" },
    { "pa leness", "payableness" },
    { "pa ly", "payably" },
    { "pla ility", "playability" },
    { "pla le", "playable" },
    { "portra le", "portrayable" },
    { "prepa le", "prepayable" },
    { "purve le", "purveyable" },
    { "quarr le", "quarryable" },
    { "repa le", "repayable" },
    { "sa ility", "sayability" },
    { "sa le", "sayable" },
    { "sa leness", "sayableness" },
    { "sla le", "slayable" },
    { "sta le", "stayable" },
    { "surve le", "surveyable" },
    { "swa le", "swayable" },
    { "unalla le", "unallayable" },
    { "unalla ly", "unallayably" },
    { "unbu le", "unbuyable" },
    { "unbu leness", "unbuyableness" },
    { "unclerg le", "unclergyable" },
    { "unclo le", "uncloyable" },
    { "unconve le", "unconveyable" },
    { "undeca le", "undecayable" },
    { "undeca leness", "undecayableness" },
    { "undela le", "undelayable" },
    { "undestro le", "undestroyable" },
    { "undisma le", "undismayable" },
    { "undispla le", "undisplayable" },
    { "undr le", "undryable" },
    { "unemplo ility", "unemployability" },
    { "unemplo le", "unemployable" },
    { "unemplo leness", "unemployableness" },
    { "unemplo ly", "unemployably" },
    { "unenjo le", "unenjoyable" },
    { "ungainsa le", "ungainsayable" },
    { "ungainsa ly", "ungainsayably" },
    { "unla le", "unlayable" },
    { "unpa le", "unpayable" },
    { "unpa leness", "unpayableness" },
    { "unpa ly", "unpayably" },
    { "unpla le", "unplayable" },
    { "unportra le", "unportrayable" },
    { "unpra le", "unprayable" },
    { "unsa ility", "unsayability" },
    { "unsa le", "unsayable" },
    { "unsla le", "unslayable" },
    { "unsta le", "unstayable" },
    { "unsurve le", "unsurveyable" },
    { "unswa le", "unswayable" },
    { "  a", " yaba" },     // Word has additional space as "a" is a proper word
    { "  ber", " yabber" }, // Word has additional space as "ber" is a proper word
    { " bi", "yabbi" },
    { " ble", "yabble" },
    { "  by", " yabby" },   // Word has additional space as "by" is a proper word
    { "  u", " yabu" },     // Word has additional space as "u" is a proper word
    { "   ", " yab " }      // "   " violates assumption 1, so we will replace it with " yab " even though "yab" is not a proper word
  };

  decoded = std::regex_replace(decoded, std::regex("yaa"), "z");
  decoded = std::regex_replace(decoded, std::regex("yab"), " ");

  for (const auto& wordToRevert : wordsToRevert)
    decoded = std::regex_replace(decoded, std::regex(wordToRevert.first), wordToRevert.second);

  // Sentence starting with space violates assumption 1, so we will replace space with "yab"
  if (!decoded.empty() && decoded[0] == ' ')
    decoded = "yab" + decoded.substr(1);

  std::cout << decoded << std::endl;
}