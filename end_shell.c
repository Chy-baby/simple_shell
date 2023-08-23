#include "main.h"

/**
 * Exit - function that exits the shell
 * @runtime_data: data relevant (status and args)
 * Return: 0 on success
 */

int Exit(data *runtime_data)
{
        unsigned int i;
        int digit;
        int str_len;
        int number;

        if (runtime_data->args[1] != NULL)
        {
                i = strToint(runtime_data->args[1]);
                digit = isDigit(runtime_data->args[1]);
                str_len = strLen(runtime_data->args[1]);
                number = i > (unsigned int) INT_MAX;

                if (!digit || str_len > 10 || number)
                {
                        getError(runtime_data, 2);
                        runtime_data->status = 2;
                        return (1);
                }

                runtime_data->status = (i % 256);
        }
        return (0);
}
