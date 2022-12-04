#include "s21_decimal.h"

int8_t check_bit(const int positive_value, int8_t position) {
    return (positive_value & (1 << position)) ? 1 : 0;
}

void put_bit(int *positive_value, int8_t position) {
    *positive_value |= (1 << position);
}

void delete_bit(int *positive_value, int8_t position) {
    *positive_value &= ~(1 << position);
}

void set_bit(int *positive_value, int8_t position, int8_t bit) {
    if (bit) put_bit(positive_value, position);
    else delete_bit(positive_value, position);
}

int8_t get_exponent_rang(s21_decimal data) {
    int8_t exponent_rang = 0;
    int power = 1;

    for (int i = 16; i <= 23; ++i) {
        exponent_rang += check_bit(data.bits[3], i) * power;
        power *= 2;
    }

    return exponent_rang;
}

void set_exponent_rang(s21_decimal *data, uint8_t exponent_rang) {
    for (int i = 16; i <= 23; ++i) {
        set_bit(&(data->bits[3]), i, exponent_rang % 2);
        exponent_rang /= 2;
    }
}

int8_t get_sign_bit(s21_decimal value) {
    int8_t sign = check_bit(value.bits[3], 31);
    return sign;
}

void set_sign_bit(s21_decimal *data, uint8_t sign_bit) {
    set_bit(&(data->bits[3]), 31, sign_bit);
}


// ----------------------------------------------------------------------------------------

// There are some helpful functions that affect only natural number
// This functions dont work with 3-rd piece of decimal that include sign and exponent rang
// Their only task is to be part of the more complete functions

int add_bit_by_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int next_bite = 0;
    int error = 0;
    init(result); 

    for (int i = 0; i < AMOUNT_OF_PICES; ++i) {
        for (int j = 0; j < PIECE_AMOUNT_BITS; ++j) {
            int8_t k = check_bit(value_1.bits[i], j) + check_bit(value_2.bits[i], j) + next_bite;

            if (k % 2) put_bit(&(result->bits[i]), j);
            if (k >= 2) next_bite = 1;
            else next_bite = 0;
        }
    }

    if (next_bite) error = 1;
    return error;
}

// if value_1 < value_2 return 1
int sub_bit_by_bit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    init(result);

    for (int i = 0; i < AMOUNT_OF_PICES && !error; ++i) {
        for (int j = 0; j < PIECE_AMOUNT_BITS && !error; ++j) {
            if (check_bit(value_2.bits[i], j)) {
                if (!check_bit(value_1.bits[i], j)) {
                    put_bit(&(result->bits[i]), j);

                    int k = 1; 
                    int piece_number = i + (j + k) / PIECE_AMOUNT_BITS;
                    int bit_number = (j + k) % PIECE_AMOUNT_BITS;
                    while (!error && !check_bit(value_1.bits[piece_number], bit_number)) {
                        put_bit(&(value_1.bits[piece_number]), bit_number);

                        ++k;
                        piece_number = i + (j + k) / PIECE_AMOUNT_BITS;
                        bit_number = (j + k) % PIECE_AMOUNT_BITS;

                        if (i * PIECE_AMOUNT_BITS + j + k >= PIECE_AMOUNT_BITS * AMOUNT_OF_PICES) error = 1;
                    }

                    if (!error) delete_bit(&(value_1.bits[piece_number]), bit_number);
                }
            } else {
                set_bit(&(result->bits[i]), j, check_bit(value_1.bits[i], j));
            }
        }
    }

    return error;
}

int multiply_by_two(s21_decimal *data, int times) {
    int error = 0;

    for (int i = 0; i < times; ++i) {
        int looking_bits_piece = AMOUNT_OF_PICES - 1 - i / PIECE_AMOUNT_BITS;
        int looking_bit = PIECE_AMOUNT_BITS - 1 - i % PIECE_AMOUNT_BITS;

        if (check_bit(data->bits[looking_bits_piece], looking_bit))
            error = 1;
    }

    if (!error) {
        for (int t = 0; t < times; ++t) {
            for (int i = PIECE_AMOUNT_BITS * AMOUNT_OF_PICES - 1; i > 0; --i) {
                if (check_bit(data->bits[(i - 1) / PIECE_AMOUNT_BITS], (i - 1) % PIECE_AMOUNT_BITS))
                    put_bit(&(data->bits[i / PIECE_AMOUNT_BITS]), i % PIECE_AMOUNT_BITS);
                else
                    delete_bit(&(data->bits[i / PIECE_AMOUNT_BITS]), i % PIECE_AMOUNT_BITS);
                }
            delete_bit(&(data->bits[0]), 0);
        }
    }

    return error;
}

int8_t divide_by_two(s21_decimal *data) {
    int8_t remainder = check_bit(data->bits[0], 0);

    for (int i = 0; i < AMOUNT_OF_PICES; ++i) {
        for (int j = 0; j < PIECE_AMOUNT_BITS; ++j) {
            if (i != AMOUNT_OF_PICES || j != PIECE_AMOUNT_BITS)
                set_bit(&(data->bits[i]), j, check_bit(data->bits[i + (j + 1) / PIECE_AMOUNT_BITS], (j + 1) % PIECE_AMOUNT_BITS));
        }
    }

    return remainder;
}

// ----------------------------------------------------------------------------------------

// Function increases order of magnitude for a number in decimal(10) notation
// Return number of possible increase without overflow or 0
int increase_order_of_magnitude(s21_decimal *data, int times) {
    int error = 0, rang = 0;
    s21_decimal result;
    s21_copy_decimal(*data, &result);

    int i;
    for (i = 0; i < times && !error; ++i) {
        s21_decimal buffer_1, buffer_2;
        s21_copy_decimal(result, &buffer_1);
        s21_copy_decimal(result, &buffer_2);

        error += multiply_by_two(&buffer_1, 3);
        multiply_by_two(&buffer_2, 1);

        error += add_bit_by_bit(buffer_1, buffer_2, &result);
    }

    if (!error) {
        s21_copy_decimal(result, data);
        set_exponent_rang(data, get_exponent_rang(*data) + times);
    } else {
        error = i - 1;
    }
    
    return error;
}

int find_main_bit(s21_decimal data) {
    int i, j;
    int stop = 0;

    for (int i = AMOUNT_OF_PICES; i >= 0 && !stop; --i) {
        for (int j = PIECE_AMOUNT_BITS; j >= 0 && !stop; --j) {
            if (check_bit(data.bits[i], j)) stop = 1;
        }
    }

    int main_bit = i * AMOUNT_OF_PICES + j;
    if (!stop) main_bit = -1;
    return main_bit;
}

// Return the remainder of the division
// DONT WORK
int8_t decrease_order_of_magnitude(s21_decimal *data) {
    s21_decimal divider, result;
    s21_decimal_from_int(10, &divider);

    int main_bit = find_main_bit(*data); // ___NEED___ check if main_bit == -1 or main_bit < 3
    int main_bit_diff = main_bit - 3;
    multiply_by_two(&divider, main_bit_diff);

    for (int i = main_bit / PIECE_AMOUNT_BITS; i >= 0 && main_bit_diff; --i) {
        for (int j = main_bit % PIECE_AMOUNT_BITS; j >= 0 && main_bit_diff; --j) {
            s21_decimal difference;
            int error = sub_bit_by_bit(*data, divider, &difference);

            if (!error) {
                s21_copy_decimal(difference, data);
                put_bit(&(result.bits[0]), j);
            }
            multiply_by_two(&result, 1);
            divide_by_two(&divider);

            --main_bit_diff;
        }
    }

    s21_copy_decimal(result, data);
    return 0; // ___CHANGE___ return remainder of division (data)
}

int init(s21_decimal *data) {
    // data->bits = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) data->bits[i] = 0;
}

int s21_decimal_from_int(int src, s21_decimal *dst) {
    init(dst);
    if (src < 0) {
        if (src != -2147483648) src *= -1;
        set_sign_bit(dst, 1);
    }
    dst->bits[0] = src;
}

void s21_print_decimal(s21_decimal data) {
    /*
     for (int i = 127; i >= 0; --i) {
        printf("%d", check_bit(data.bits[i / 32], i % 32));
     }
     */
     for (int i = AMOUNT_OF_PICES; i >= 0; --i) {
        for (int j = PIECE_AMOUNT_BITS - 1; j >= 0; --j) {
            if (i == 3 && (j == 15 || j == 23)) printf(" - ");
            printf("%d", check_bit(data.bits[i], j));
        }
        printf("\n");
     }
}

void s21_copy_decimal(s21_decimal src, s21_decimal *dst) {
    for (int i = 0; i < 4; ++i) dst->bits[i] = src.bits[i];
}

// -------------------- ARITHMETIC OPERATIONS --------------------

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    // s21_decimal buffer_1;
    // s21_decimal buffer_2;

    int8_t exp_diff = get_exponent_rang(value_1) - get_exponent_rang(value_2);
    s21_decimal *ptr = &value_2;
    if (exp_diff < 0) {
        ptr = &value_1;
        exp_diff *= -1;
    }

    int error = increase_order_of_magnitude(&value_2, exp_diff);
    if (error) {
           
    }

}

// -------------------- ANOTHER FUNCTIONS --------------------

int s21_negate(s21_decimal value, s21_decimal *result) {
    s21_copy_decimal(value, result);

    if (get_sign_bit(value)) set_sign_bit(result, 0);
    else set_sign_bit(result, 1);
}



int main() {
    s21_decimal number_1, number_2, result;
    s21_decimal_from_int(123, &number_1);
    s21_decimal_from_int(124, &number_2);

    decrease_order_of_magnitude(&number_1);
    s21_print_decimal(number_1);
/*
    int error = sub_bit_by_bit(number_1, number_2, &result);
    printf("ERROR - %d\n", error);
    s21_print_decimal(number_1);
    printf("\n");
    s21_print_decimal(number_2);
    printf("\n");
    s21_print_decimal(result);
    printf("\n");

    // increase_order_of_magnitude(&number, 5);
    // s21_print_decimal(number);
*/
    return 0;
}
