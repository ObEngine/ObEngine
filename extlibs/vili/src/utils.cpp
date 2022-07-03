#include <vili/utils.hpp>

#include <algorithm>
#include <cctype>
#ifdef __cpp_lib_to_chars
#include <charconv>
#endif

namespace vili::utils::string
{
    constexpr auto is_digit = static_cast<int (*)(int)>(std::isdigit);
    size_t count(const std::string& str, const std::string& occur)
    {
        int occurrences = 0;
        std::string::size_type start = 0;
        while ((start = str.find(occur, start)) != std::string::npos)
        {
            ++occurrences;
            start += occur.length();
        }
        return occurrences;
    }

    bool is_int(const std::string& str)
    {
        if (!str.empty())
        {
            if (str.substr(0, 1) == "-")
                return std::all_of(str.begin() + 1, str.end(), is_digit);
            return std::all_of(str.begin(), str.end(), is_digit);
        }
        return false;
    }

    bool is_float(const std::string& str)
    {
        std::string float_str = str;
        bool is_a_float = false;
        if (!float_str.empty())
        {
            if (float_str.substr(0, 1) == "-")
                float_str = float_str.substr(1);
            if (count(float_str, ".") == 1)
            {
                is_a_float = true;
                float_str.erase(float_str.find('.'));
            }
            return (
                std::all_of(float_str.begin(), float_str.end(), is_digit) && is_a_float);
        }
        return false;
    }

    std::string truncate_float(const std::string& str)
    {
        std::string result = str;
        while (
            result.size() > 2 && result.back() == '0' && result[result.size() - 2] != '.')
            result.pop_back();
        return result;
    }

    std::string quote(const std::string& str)
    {
        return "\"" + str + "\"";
    }

    double to_double(std::string_view input)
    {
#ifdef __cpp_lib_to_chars
        double data_out;
        std::from_chars(input.data(), input.data() + input.size(), data_out);
        return data_out;
#else
        return std::stod(input.data());
#endif
    }

    long long to_long(std::string_view input)
    {
#ifdef __cpp_lib_to_chars
        long long data_out;
        std::from_chars(input.data(), input.data() + input.size(), data_out);
        return data_out;
#else
        return std::stoll(input.data());
#endif
    }

    std::string replace(
        std::string subject, const std::string& search, const std::string& replace)
    {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return subject;
    }

    std::string indent(
        const std::string& input, unsigned int indent_level, bool pad_left)
    {
        return (pad_left ? std::string(indent_level, ' ') : "")
            + utils::string::replace(input, "\n", "\n" + std::string(indent_level, ' '));
    }

    std::size_t distance(std::string_view source, std::string_view target)
    {
        if (source.size() > target.size())
        {
            return distance(target, source);
        }

        const std::size_t min_size = source.size(), max_size = target.size();
        std::vector<std::size_t> lev_dist(min_size + 1);

        for (std::size_t i = 0; i <= min_size; ++i)
        {
            lev_dist[i] = i;
        }

        for (std::size_t j = 1; j <= max_size; ++j)
        {
            std::size_t previous_diagonal = lev_dist[0];
            ++lev_dist[0];

            for (std::size_t i = 1; i <= min_size; ++i)
            {
                const std::size_t previous_diagonal_save = lev_dist[i];
                if (source[i - 1] == target[j - 1])
                {
                    lev_dist[i] = previous_diagonal;
                }
                else
                {
                    lev_dist[i]
                        = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
                }
                previous_diagonal = previous_diagonal_save;
            }
        }

        return lev_dist[min_size];
    }

    std::vector<std::string> sort_by_distance(
        const std::string& source, const std::vector<std::string>& words, std::size_t limit)
    {
        std::vector<std::string> strings_sorted_by_distance = words;
        std::sort(strings_sorted_by_distance.begin(), strings_sorted_by_distance.end(),
            [source](const std::string& s1, const std::string& s2) {
                return utils::string::distance(s1, source) < utils::string::distance(s2, source);
            });
        if (limit && !strings_sorted_by_distance.empty())
        {
            return std::vector<std::string>(strings_sorted_by_distance.begin(),
                strings_sorted_by_distance.begin() + std::min(strings_sorted_by_distance.size() - 1, limit));
        }
        else
            return strings_sorted_by_distance;
    }
}