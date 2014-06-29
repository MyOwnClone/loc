#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace loc {

class StringUtils
{
  public:
    // Naive and slow (who cares...)
    template <typename T>
    static T lexicalCast(const std::string &str, bool *wasValid = nullptr)
    {
      T result;
      std::stringstream ss;

      ss << str;
      ss >> result;

      if (wasValid)
        *wasValid = !ss.fail();

      return result;
    }

    static std::string toLower(const std::string &str)
    {
      std::string result = str;
      std::transform(result.begin(), result.end(), result.begin(), tolower);
      return result;
    }

    static std::string toUpper(const std::string &str)
    {
      std::string result = str;
      std::transform(result.begin(), result.end(), result.begin(), toupper);
      return result;
    }

    static std::string replace(const std::string &str, char find, char replace, int startIndex = 0, bool ignoreCase = false)
    {
      if (startIndex >= (int)str.size()) return str;
      if (startIndex < 0) startIndex = 0;

      if (ignoreCase == false)
      {
        std::string result = str;

        for (size_t i = (size_t)startIndex; i < result.size(); ++i)
          if (result[i] == find)
            result[i] = replace;

        return result;
      }

      std::string result = str;
      find = tolower(find);

      for (size_t i = (size_t)startIndex; i < result.size(); ++i)
        if (tolower(result[i]) == find)
          result[i] = replace;

      return result;
    }

    static std::string replace(const std::string &str, const std::string &find, const std::string &replace, int startIndex = 0, bool ignoreCase = false)
    {
      if (startIndex >= (int)str.size()) return str;
      if (startIndex < 0) startIndex = 0;

      if (ignoreCase == false)
      {
        std::string result = str;

        for (size_t i = (size_t)startIndex; (i = result.find(find, i)) != std::string::npos; i += replace.length())
          result.replace(i, find.length(), replace);

        return result;
      }

      // Very lazy lowercase replace
      std::string result = str;
      std::string lowResult = toLower(str);
      std::string lowFind = toLower(find);

      for (size_t i = (size_t)startIndex; (i = lowResult.find(lowFind, i)) != std::string::npos; i += replace.length())
      {
        result.replace(i, lowFind.length(), replace);
        lowResult.replace(i, lowFind.length(), replace);
      }

      return result;
    }

    static int find(const std::string &str, char c, int startIndex = 0, bool ignoreCase = false)
    {
      if (startIndex >= (int)str.size()) return -1;
      if (startIndex < 0) startIndex = 0;
      
      if (ignoreCase == false)
      {
        std::size_t result = str.find(c, startIndex);

        if (result != std::string::npos)
          return (int)result;
      }
      else
      {
        c = tolower(c);

        for (size_t i = (size_t)startIndex; i < str.size(); ++i)
          if (tolower(str[i]) == c)
            return (int)i;
      }

      return -1;
    }

    static int find(const std::string &str, const std::string &findStr, int startIndex = 0, bool ignoreCase = false)
    {
      if (startIndex >= (int)str.size()) return -1;
      if (startIndex < 0) startIndex = 0;

      if (ignoreCase == false)
      {
        std::string::size_type result = str.find(findStr, startIndex);

        if (result != std::string::npos)
          return (int)result;
      }
      else
      {
        // Very lazy lowercase find
        std::string lower = toLower(str);
        std::size_t result = lower.find(toLower(findStr), startIndex);

        if (result != std::string::npos)
          return (int)result;
      }

      return -1;
    }

    static std::string trim(const std::string &str)
    {
      size_t trimLeft = 0;
      size_t len = str.length();
      size_t trimRight = len - 1;

      while (trimLeft < len && isspace(str[trimLeft]))
        ++trimLeft;

      while (trimRight < len && isspace(str[trimRight]))
        --trimRight;

      if (trimRight >= len || trimLeft >= len || trimRight < trimLeft)
        return std::string("");

      return str.substr(trimLeft, trimRight - trimLeft + 1);
    }

    static bool startsWith(const std::string &str, const std::string &findStr, bool ignoreCase = false)
    {
      return find(str, findStr, 0, ignoreCase) == 0;      
    }

    static std::string between(const std::string &str, const std::string &start, const std::string &end, int startIndex = 0, bool ignoreCase = false)
    {
      int si = start.empty() ? startIndex : find(str, start, startIndex, ignoreCase);
      if (si < 0)
        return std::string("");

      si += (int)start.length();

      int ei = end.empty() ? (int)str.length() : find(str, end, si, ignoreCase);
      if (ei < 0 || ei <= si)
        return std::string("");

      return str.substr(si, ei - si);
    }

    static int split(const std::string &str, std::vector<std::string> &result, const std::string &separator, bool ignoreEmpty = true, bool autoTrim = false)
    {
      if (str.empty())
        return 0;

      int sepLen = (int)separator.length() - 1;

      if (sepLen < 0)
        return 0;

      int count = 0;
      int cursor = -1;

      do
      {
        int nextCursor = find(str, separator, cursor + 1);
        if (nextCursor == -1)
          break;

        if (!ignoreEmpty || (ignoreEmpty && nextCursor - cursor > 1))
        {
          if (autoTrim)
          {
            if (ignoreEmpty)
            {
              std::string trimmed = trim(str.substr(cursor + 1, nextCursor - cursor - 1));
              if (!trimmed.empty())
                result.push_back(trimmed);
              else
                --count;
            }
            else
              result.push_back(trim(str.substr(cursor + 1, nextCursor - cursor - 1)));
          }
          else
            result.push_back(str.substr(cursor + 1, nextCursor - cursor - 1));
        }

        ++count;
        cursor = nextCursor + sepLen;

      } while (true);

      if (!ignoreEmpty || (ignoreEmpty && (int)str.length() - cursor > 1))
      {
        if (autoTrim)
        {
          if (ignoreEmpty)
          {
            std::string trimmed = trim(str.substr(cursor + 1, (int)str.length() - cursor - 1));
            if (!trimmed.empty())
              result.push_back(trimmed);
            else
              --count;
          }
          else
            result.push_back(trim(str.substr(cursor + 1, (int)str.length() - cursor - 1)));
        }
        else
          result.push_back(str.substr(cursor + 1, (int)str.length() - cursor - 1));
      }

      ++count;
      return count;
    }
};

}
