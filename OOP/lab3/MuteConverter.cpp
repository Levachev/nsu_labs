#include "MuteConverter.h"

void MuteConverter::convert(std::array<int16_t, BUFFER_OF_DATA_SIZE> &buffer_of_current_data, std::array<int16_t, BUFFER_OF_DATA_SIZE> &buffer_of_secondary_data)
{
	for(int i=0;i<BUFFER_OF_DATA_SIZE;i++)
	{
		buffer_of_current_data[i]=0;
	}
	return;
}