#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <float.h>


double f(double x);
int is_in_domain(double x);
double calculate_value_at_point(double x);

int tabl(double start, double finish, double step);

double find_min_on_interval(double start, double finish, double step, double* min_x);
double find_max_on_interval(double start, double finish, double step, double* max_x);

int find_all_x_for_y(double y, double start, double finish, double step, double results[], int max_results);

double derivative_central(double point, double step);
double calculate_derivative_at_point(double point, double step);

int main() {
    setlocale(LC_CTYPE, "RUS");
    printf("Программа для работы с функцией f(x)\n");

    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Значение функции в точке\n");
        printf("2. Таблица значений\n");
        printf("3. Поиск минимума и максимума\n");
        printf("4. Поиск всех X по Y\n");
        printf("5. Производная в точке\n");
        printf("6. Запись таблицы в файл\n");
        printf("0. Выход\n");
        printf("Выберите функцию: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);

            if (!is_in_domain(x)) {
                printf("Ошибка: x вне области определения\n");
                break;
            }
            printf("f(%.6f) = %.6f\n", x, calculate_value_at_point(x));
            break;
        }

        case 2: {
            double start, finish, step;
            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &finish);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            tabl(start, finish, step);
            break;
        }

        case 3: {
            double start, finish, step;
            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &finish);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            double min_x, max_x;
            double min_val = find_min_on_interval(start, finish, step, &min_x);
            double max_val = find_max_on_interval(start, finish, step, &max_x);

            printf("\nМинимум: f(%.6f) = %.6f\n", min_x, min_val);
            printf("Максимум: f(%.6f) = %.6f\n", max_x, max_val);
            break;
        }

        case 4: {
            double y, start, finish, step;
            printf("Введите y: ");
            scanf("%lf", &y);
            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &finish);
            printf("Введите шаг: ");
            scanf("%lf", &step);

            double results[1000];
            int count = find_all_x_for_y(y, start, finish, step, results, 1000);

            if (count == 0) {
                printf("Решений не найдено.\n");
            }
            else {
                printf("Найдено решений: %d\n", count);
                for (int i = 0; i < count && i < 1000; i++) {
                    printf("x = %.6f, f(x) = %.6f\n", results[i], f(results[i]));
                }
            }
            break;
        }

        case 5: {
            double point, step;
            printf("Введите точку x: ");
            scanf("%lf", &point);

            printf("Введите шаг: ");
            scanf("%lf", &step);

            if (!is_in_domain(point)) {
                printf("Ошибка: точка x вне области определения\n");
                break;
            }

            printf("f'(%.6f) = %.9f\n", point, calculate_derivative_at_point(point, step));
            break;
        }
        case 6: {
            double start, finish, step;
            char filename[256];

            printf("Введите началo интервала: ");
            if (scanf("%lf", &start) != 1) { printf("Ошибка ввода.\n"); break; }

            printf("Введите конец интервала: ");
            if (scanf("%lf", &finish) != 1) { printf("Ошибка ввода.\n"); break; }

            printf("Введите шаг: ");
            if (scanf("%lf", &step) != 1) { printf("Ошибка ввода.\n"); break; }

            printf("Введите имя файла для сохранения (например, output.txt): ");
            if (scanf("%255s", filename) != 1) { printf("Ошибка ввода имени файла.\n"); break; }

            int result = write_table_to_file(start, finish, step, filename);
            switch (result) {
            case 0:
                printf("Таблица успешно записана в файл '%s'.\n", filename);
                break;
            case -1:
                printf("Ошибка: недопустимые параметры интервала или шага.\n");
                break;
            case -2:
                printf("Ошибка: не удалось создать файл '%s'.\n", filename);
                break;
            default:
                printf("Неизвестная ошибка.\n");
            }
            break;
        }
        case 0:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Неверный выбор.\n");
        }

    } while (choice != 0);

    return 0;
}

double f(double x) {
    if (x < 1) {
        if (x == 0) return 0.5;
        return (exp(x) - 1 - x) / (x * x);
    }
    else if (1 <= x && x < 5) {
        return atan(x * x) / cbrt(1 + x);
    }
    else if (x >= 5) {
        return log(x * x + 1) * (2 * x * x * x - x + 4);
    }
}

int is_in_domain(double x) {
    return 1;
}

double calculate_value_at_point(double x) {
    return f(x);
}

int tabl(double start, double finish, double step) {
    if (start >= finish || step <= 0) {
        printf("Ошибка: неверные параметры\n");
        return -1;
    }

    printf("_____________________________\n");
    printf("|    X     |     F(X)       |\n");

    for (double x = start; x <= finish; x += step) {
        printf("|%.6f | %.6f |\n", x, f(x));
    }

    printf("_____________________________\n");
    return 0; 
}

double find_min_on_interval(double start, double finish, double step, double* min_x) {
    double min_val = DBL_MAX;

    for (double x = start; x <= finish; x += step) {
        double y = f(x);
        if (y < min_val) {
            min_val = y;
            *min_x = x;
        }
    }
    return min_val;
}

double find_max_on_interval(double start, double finish, double step, double* max_x) {
    double max_val = -DBL_MAX;

    for (double x = start; x <= finish; x += step) {
        double y = f(x);
        if (y > max_val) {
            max_val = y;
            *max_x = x;
        }
    }
    return max_val;
}

int find_all_x_for_y(double y, double start, double finish, double step, double results[], int max_results) {
    int count = 0;

    for (double x = start; x <= finish; x += step) {
        double diff = fabs(f(x) - y);

        if (diff <= step * 2) {
            if (count < max_results) {
                results[count] = x;
            }
            count++;
        }
    }
    return count;
}

double derivative_central(double point, double h) {
    return (f(point + h) - f(point - h)) / (2 * h);
}

double calculate_derivative_at_point(double point, double step) {
    return derivative_central(point, step);
}

int write_table_to_file(double start, double finish, double step, const char* filename) {
    if (start >= finish || step <= 0) {
        return -1; 
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        return -2; 
    }

    fprintf(file, "_____________________________\n");
    fprintf(file, "|    X     |     F(X)       |\n");

    for (double x = start; x <= finish; x += step) {
        fprintf(file, "|%.6f | %.6f |\n", x, f(x));
    }

    fprintf(file, "_____________________________\n");
    fclose(file);
    return 0; 
}