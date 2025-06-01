#include "Utils.h"

namespace Snake
{
	void SelectionSort(std::map<std::string, int>& map)
	{
		for (int i = 0; i < map.size() - 1; ++i)
		{
			int min_idx = i;

			for (int j = i + 1; j < map.size(); ++j)
			{
				std::pair<const std::string, int>& min_idx_element = *std::next(map.begin(), min_idx);
				std::pair<const std::string, int>& jth_element = *std::next(map.begin(), j);

				if (jth_element.second > min_idx_element.second)
				{
					min_idx = j;
				}
			}

			std::pair<std::string, int> ith_element = *std::next(map.begin(), i);
			std::pair<std::string, int> min_idx_element = *std::next(map.begin(), min_idx);

			std::pair<const std::string, int> temp = _STD move(ith_element);
			ith_element = _STD move(min_idx_element);
			min_idx_element = _STD move(temp);
		}
	}
}