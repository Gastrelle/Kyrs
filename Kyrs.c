#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <float.h>

void menu();
double f(double x);
int is_in_domain(double x);
double calculate_value_at_point(double x);
void tabl();
double find_min_on_interval(double start, double finish, double* min_x);
double find_max_on_interval(double start, double finish, double* max_x);
double find_x_for_y(double y, double accuracy);
double derivative_central(double x, double h);
double calculate_derivative_at_point(double x);

int main() {
    setlocale(LC_CTYPE, "RUS");
    printf("Программа для работы с функцией f(x)\n");

    int choice;
    do {
        menu();
        printf("Выберите функцию: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);

            double result = calculate_value_at_point(x);
            printf("f(%.2f) = %.6f\n", x, result);
            break;
        }

        case 2: {
            tabl();
            break;
        }

        case 3: {
            double start, finish;
            printf("Введите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &finish);

            if (start >= finish) {
                printf("Ошибка: начало интервала должно быть меньше конца\n");
                break;
            }

            double min_x, max_x;
            double min_val = find_min_on_interval(start, finish, &min_x);
            double max_val = find_max_on_interval(start, finish, &max_x);

            printf("\nМинимум: f(%.6f) = %.6f\n", min_x, min_val);
            printf("Максимум: f(%.6f) = %.6f\n", max_x, max_val);
            break;
        }

        case 4: {
            double y, accuracy;
            printf("Введите y: ");
            scanf("%lf", &y);
            printf("Введите точность: ");
            scanf("%lf", &accuracy);

            double found_x = find_x_for_y(y, accuracy);

            if (!found_x) {
                printf("Не удалось найти x такой, что f(x) = %.6f\n", y);
            }
            else {
                printf("Найдено: x = %.6f, f(x) = %.6f\n", found_x, f(found_x));
            }
            break;
        }

        case 5: {
            double x;
            printf("Введите x: ");
            scanf("%lf", &x);

            if (!is_in_domain(x)) {
                printf("Ошибка: значение x вне области определения функции\n");
                break;
            }
            double deriv = calculate_derivative_at_point(x);

            printf("\nРезультат (метод центральной разности):\n");
            printf("f'(%.6f) = %.9f\n", x, deriv);
            break;
        }

        case 0:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Неверный выбор, попробуйте снова.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}

double f(double x) {  
    if (x < 1) {
        if (x == 0) {
            return 0.5;
        }
        return (exp(x) - 1 - x) / (x * x);
    }
    else if (1 <= x && x < 5) {
        return (atan(x * x) / cbrt(1 + x));
    }
    else if (x >= 5) {
        return log(x * x + 1) * (2 * x * x * x - x + 4);
    }
    return 0;
}


int is_in_domain(double x) {
    return 1;
}

double calculate_value_at_point(double x) {
    return f(x);
}

void tabl() {
    double start, finish;

    printf("Введите начало интервала: ");
    scanf("%lf", &start);
    printf("Введите конец интервала: ");
    scanf("%lf", &finish);
    if (start >= finish) {
        printf("Ошибка: начало интервала должно быть меньше конца\n");
        return;
    }
    int points = finish - start + 1;
    printf("_____________________________\n");
    printf("|    X     |     F(X)       |\n");

    for (int i = 0; i < points; i++) {
        double x = start + i;
        printf("|%.6f  |    %.6f    |\n", x, f(x));
    }
    printf("_____________________________\n");
}


double find_min_on_interval(double start, double finish, double* min_x) {
    double min_val = DBL_MAX;
    *min_x = start;

    int points = finish - start + 1;
    for (int i = 0; i < points; i++) {
        double x = start + i;
        double y = f(x);
        if (y < min_val) {
            min_val = y;
            *min_x = x;
        }
    }

    return min_val;
}

double find_max_on_interval(double start, double finish, double* max_x) {
    double max_val = -DBL_MAX;
    *max_x = start;

    int points = finish - start + 1;
    for (int i = 0; i < points; i++) {
        double x = start + i;
        double y = f(x);
        if (y > max_val) {
            max_val = y;
            *max_x = x;
        }
    }
    return max_val;
}

double find_x_for_y(double y, double accuracy) {
    for (double x = 0; x <= 100.0; x++) { 
       if (fabs(f(x) - y) <= accuracy) {
            return x;  
       }
    }
    return 0;  
}

double derivative_central(double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double calculate_derivative_at_point(double x) {
    double h = 0.001;
    double deriv1 = derivative_central(x, h);

    return deriv1; 
}

void menu() {
    printf("\nМеню:\n");
    printf("1. Значение функции в точке\n");
    printf("2. Таблица значений\n");
    printf("3. Поиск минимума / максимума\n");
    printf("4. Поиск X по Y\n");
    printf("5. Производная в точке\n");
    printf("0. Выход\n");
}