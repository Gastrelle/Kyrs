#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <float.h>

double f(double x) {  //функция 
	if (x < 1) {
        if (x == 0) {
            // Предел при x = 0: (e^x - 1 - x)/x^2 -> 1/2
            return 0.5;
        }
        return (exp(x) - 1 - x) / (x * x);
    }
    else if (1<= x < 5) {
        return (atan(x * x) / cbrt(1+x));
    }
    else if (x>=5) {
        return log(x * x + 1) * (2 * x * x * x - x + 4);
    }
}

// Проверка области определения
int is_in_domain(double x) {
    return 1;
}

void calculate_value(d) {
    double x;
    printf("Введите x: ");
    scanf("%lf", &x);
    if (!is_in_domain) {
        printf("Ошибка: значение x вне области определения фцнкции.\n");
        return;
    }
    double result = f(x);
    printf("f(%.2f) = %.6f\n", x, result);
}

void tabl() {
    double start, finish;

    printf("Введите начало интервала: ");
    scanf("%lf", &start);
    printf("Введите конец интервала: ");
    scanf("%lf", &finish);
    if (start>= finish) {
        printf("Ошибка: начало интервала должно быть меньше конца\n");
        return;
    }
    int points = finish-start+1;
    printf("_________________________\n");
    printf("|    X     |     F(X)   |\n");

    for (int i = 0; i < points; i++) {
        double x = start + i;
        printf("|%.6f  |    %.6f|\n", x, f(x));
    }
    printf("_________________________\n");
}

void find_extremums() {
    double start, finish;
    printf("Введите начало интервала: ");
    scanf("%lf", &start);
    printf("Введите конец интервала: ");
    scanf("%lf", &finish);
    if (start >= finish) {
        printf("Ошибка: начало интервала должно быть меньше конца\n");
        return;
    }
    double min_val = DBL_MAX;
    double max_val = -DBL_MAX;
    double min_x = start, max_x = finish;
    int points = finish - start + 1;
    for (int i = 0; i < points; i++) {
        double x = start + i;
        double y = f(x);
        if (y < min_val) {
            min_val = y;
            min_x = x;
        }
        if (y > max_val) {
            max_val = y;
            max_x = x;
        }
    }
    printf("\nМинимум: f(%.6f) = %.6f\n", min_x, min_val);
    printf("Максимум: f(%.6f) = %.6f\n", max_x, max_val);
}

void find_x_by_y() {
    double y, accuracy;
    printf("Введите y: ");
    scanf("%lf", &y);
    
    printf("Введите точность: ");
    scanf("%lf", &accuracy);
    int flag = 0;
    for (double x = 0; x <= 100.0; x++) { //4.000000  0.882105 для проверки
        if (fabs(f(x) - y) < accuracy) {  
            printf("Найдено: x = %.6f, f(x) = %.6f\n", x, f(x));
            flag = 1;
        }
    }
    if (!flag) {
        printf("Не удалось найти x такой, что f(x) = %.6f\n", y);
    }
}

void calculate_derivative() {

    printf("Здесь будет поиск производной");

}
void menu() {
    printf("Меню:\n");
    printf("1. Значение функции в точке\n");
    printf("2. Таблица значений\n");
    printf("3. Поиск минимума / максимума\n");
    printf("4. Поиск X по Y\n");
    printf("5. Производная в точке\n");
    printf("0. Выход\n");
}

int main() {
	setlocale(LC_CTYPE, "RUS");
    printf("Программа для работы с функцией f(x)\n");
    menu();
    printf("Выберите функцию: ");
    int choice;
    scanf("%d", &choice);
	
    switch (choice) {
    case 1:
        calculate_value();
        break;
    case 2:
        tabl();
        break;
    case 3:
        find_extremums();
        break;
    case 4:
        find_x_by_y();
        break;
    case 5:
        calculate_derivative();
        break;
    case 0:
        printf("Выход из программы.\n");
        break;
    default:
        printf("Неверный выбор! Попробуйте снова.\n");
        break;
    }

}