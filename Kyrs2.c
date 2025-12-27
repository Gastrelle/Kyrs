#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <float.h>

double f(double x);
int print_table(double start, double finish, double step, FILE* out);
double find_min(double start, double finish, double step, double* x_min);
double find_max(double start, double finish, double step, double* x_max);
int find_x_for_y(double y, double start, double finish, double step, double res[], int max);
double derivative(double x, double h);
int save_table_to_file(double start, double finish, double step, const char* fname);


int main() {
    setlocale(LC_CTYPE, "RUS");
    printf("Программа для работы с функцией f(x)\n");

    int choice;
    do {
        printf("\nМеню:\n"
            "1. Значение функции в точке\n"
            "2. Таблица значений\n"
            "3. Минимум и максимум\n"
            "4. Поиск X по Y\n"
            "5. Производная в точке\n"
            "6. Сохранить таблицу в файл\n"
            "0. Выход\n"
            "Выберите функцию: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            choice = -1;
        }

        switch (choice) {
        case 1: {
            double x;
            printf("Ввеите x: ");
            scanf("%lf", &x);
            printf("f(%.6f) = %.6f\n", x, f(x));
            break;
        }

        case 2: {
            double a, b, h;
            printf("Введите начало, конец, шаг: ");  //здесь и далее вводится через пробел
            scanf("%lf %lf %lf", &a, &b, &h);
            print_table(a, b, h, stdout);
            break;
        }

        case 3: { 
            double a, b, h, x_min, x_max;
            printf("Введите начало, конец, шаг: ");
            scanf("%lf %lf %lf", &a, &b, &h);

            double min_val = find_min(a, b, h, &x_min);
            double max_val = find_max(a, b, h, &x_max);

            printf("Минимум: f(%.6f) = %.6f\n", x_min, min_val);
            printf("Максимум: f(%.6f) = %.6f\n", x_max, max_val);
            break;
        }
        /*так как функция возрастает от минус бесконечности до плюс бесконечности,
         локальных экстремумов у неё нет. поэтому экстремумы на заданном отрезке достигаются только на его концах*/


        case 4: {
            double y, a, b, h, res[1000];
            printf("Введите y, начало, конец, шаг: ");
            scanf("%lf %lf %lf %lf", &y, &a, &b, &h);

            int n = find_x_for_y(y, a, b, h, res, 1000);

            if (n == 0) {
                printf("Решений не найдено.\n");
            }
            else {
                printf("Найдено %d решений:\n", n);
                for (int i = 0; i < n; i++)
                    printf("x = %.6f -> f(x) = %.6f\n", res[i], f(res[i]));
            }
            break;
        }

        case 5: {
            double x, h;
            printf("Введите x, шаг: ");
            scanf("%lf %lf", &x, &h);
            printf("f'(%.6f) = %.9f\n", x, derivative(x, h));
            break;
        }

        case 6: {
            double a, b, h;
            char name[256];
            printf("Введите начало, конец, шаг: "); 
            scanf("%lf %lf %lf", &a, &b, &h);

            printf("Введите имя файла: ");
            scanf("%255s", name);
            int r = save_table_to_file(a, b, h, name);
            if (r == 0) printf("Таблица сохранена в '%s'.\n", name);
            else if (r == -1) printf("Ошибка параметров.\n");
            else printf("Не удалось создать файл.\n");
            break;
        }

        case 0:
            printf("Выход.\n");
            break;

        default:
            printf("Неверный выбор, попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}


double f(double x) {
    if (x < 1) {
        if (x == 0.0) return 0.5;
        return (exp(x) - 1.0 - x) / (x * x);
    }
    else if (x < 5.0) {
        return atan(x * x) / cbrt(1.0 + x);
    }
    else {
        return log(x * x + 1.0) * (2.0 * x * x * x - x + 4.0);
    }
}

int print_table(double start, double finish, double step, FILE* out) {
    if (start >= finish || step <= 0) return -1;

    fprintf(out, "_____________________________\n");
    fprintf(out, "|    X     |     F(X)       |\n");
    for (double x = start; x <= finish; x += step) {
        fprintf(out, "|%9.6f | %13.6f |\n", x, f(x));
    }
    fprintf(out, "_____________________________\n");
    return 0;
}

double find_min(double start, double finish, double step, double* x_min) {
    double min_val = DBL_MAX;
    for (double x = start; x <= finish; x += step) {
        double y = f(x);
        if (y < min_val) {
            min_val = y;
            *x_min = x;
        }
    }
    return min_val;
}

double find_max(double start, double finish, double step, double* x_max) {
    double max_val = -DBL_MAX;
    for (double x = start; x <= finish; x += step) {
        double y = f(x);
        if (y > max_val) {
            max_val = y;
            *x_max = x;
        }
    }
    return max_val;
}

int find_x_for_y(double y, double start, double finish, double step, double res[], int max) {
    int cnt = 0;
    for (double x = start; x <= finish; x += step) {
        if (fabs(f(x) - y) <= 2.0 * step && cnt < max) {
            res[cnt++] = x;
        }
    }
    return cnt;
}

double derivative(double x, double h) {
    return (f(x + h) - f(x - h)) / (2.0 * h);
}


int save_table_to_file(double start, double finish, double step, const char* fname) {
    FILE* f = fopen(fname, "w");
    if (!f) return -2;
    int r = print_table(start, finish, step, f);
    fclose(f);
    return r == 0 ? 0 : -1;
}