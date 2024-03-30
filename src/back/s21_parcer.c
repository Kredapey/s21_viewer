#include "s21_viewer.h"

/// @brief Главная функция, происходит два считывания содержимого в файле
/// @param file_name Название файла
/// @param res_data Основная структура
/// @param scale Коэффициент приближения-отдаления
/// @return 0 - ОК, 1 - Ошибка
int main_parser(char *file_name, data_struct *res_data, double scale) {
  int error = 0;
  error = first_read_file(file_name, &res_data->count_vertexes,
                          &res_data->count_facets);
  if (error == 0) {
    error = second_read_file(file_name, res_data);
    if (error == 1) {
      remove_data(res_data);
    } else {
      find_scale(scale, res_data);
      center_model(res_data);
    }
  }
  return error;
}

/// @brief Подсчет числа вершин и полигонов
/// @param file_name Название файла
/// @param count_vertexes Число вершин(Указатель), значение идет в структуру
/// @param count_facets Число полигонов(Указатель), значение идет в структуру
/// @return 0 - ОК, 1 - Ошибка
int first_read_file(char *file_name, unsigned int *count_vertexes,
                    unsigned int *count_facets) {
  FILE *fp = NULL;
  int error = 0;
  *count_vertexes = 0;
  *count_facets = 0;
  if ((fp = fopen(file_name, "r")) != NULL) {
    char str[1000] = "\0";
    while (fgets(str, 999, fp)) {
      if (str[0] == 'v' && str[1] == ' ') {
        *count_vertexes += 1;
      } else if (str[0] == 'f' && str[1] == ' ') {
        *count_facets += 1;
      }
    }
    fclose(fp);
  } else {
    printf("here\n");
    error = 1;
  }
  return error;
}

/// @brief Заполнение структуры (В том числе матрицы в ней) необходимыми
/// данными(Координаты вершин и точки соединения полигонов)
/// @param file_name Название файла
/// @param res_data Основная структура
/// @return 0 - ОК, 1 - Ошибка
int second_read_file(char *file_name, data_struct *res_data) {
  FILE *fp = NULL;
  int error = 0;
  int vert_count = 0, polygon_counter = 0;
  double numX = 0, numY = 0, numZ = 0;
  if ((fp = fopen(file_name, "r")) != NULL) {
    if ((res_data->coord_vert =
             calloc(res_data->count_vertexes * 3, sizeof(double))) != NULL) {
      if (error == 0) {
        if ((res_data->polygons = calloc(1, sizeof(int))) != NULL) {
          char str[1000000] = "\0";
          while (fgets(str, 1000000, fp)) {
            if (str[0] == 'v' && str[1] == ' ') {
              sscanf(str, "v %lf %lf %lf\n", &numX, &numY, &numZ);
              res_data->coord_vert[vert_count] = numX;
              vert_count += 1;
              res_data->coord_vert[vert_count] = numY;
              vert_count += 1;
              res_data->coord_vert[vert_count] = numZ;
              vert_count += 1;
            } else if (str[0] == 'f' && str[1] == ' ') {
              fill_faces(res_data, &polygon_counter, str);
            }
          }
          res_data->num_vert_in_pol = polygon_counter;
          change_min(res_data);
          transf_polygons(res_data);
          find_max_vert(res_data);
          fclose(fp);
        } else {
          error = 1;
        }
      }
    }
  } else {
    error = 1;
  }
  return error;
}

/// @brief Заполнение структуры данными о полигонах(Например: Было в файле - 1 2
/// 3 4, Стало в структуре - 1 2 2 3 3 4 4 1)
/// @param res_data Основная структура
/// @param res_count Счетчик элементов в массиве res_data->polygons[] в который
/// записываются данные о полигонах
/// @param str собственно строка из obj файла
void fill_faces(data_struct *res_data, int *res_count, char *str) {
  char *number = NULL;
  int count_number = 0, number_of_vert = 0, zero_flag = 0, temp = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    number = calloc(1000, sizeof(char));
    if (number != NULL) {
      zero_flag = 0;
      if (str[i] == ' ' &&
          ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '-')) {
        if (number_of_vert != 0) {
          number_of_vert += 1;
        } else {
          zero_flag = 1;
          number_of_vert += 1;
        }
        count_number = 0;
        i++;
        while (str[i] != ' ' && str[i] != '/' && str[i] != '\0') {
          number[count_number] = str[i];
          i++;
          count_number++;
        }
        i -= 1;
        res_data->polygons =
            realloc(res_data->polygons, (*res_count + 1) * sizeof(int));
        if (res_data->polygons != NULL) {
          res_data->polygons[*res_count] = atof(number);
          *res_count += 1;
        }
        if (zero_flag == 1) {
          temp = atof(number);
        } else {
          res_data->polygons =
              realloc(res_data->polygons, (*res_count + 1) * sizeof(int));
          if (res_data->polygons != NULL) {
            res_data->polygons[*res_count] = atof(number);
            *res_count += 1;
          }
        }
      }
      free(number);
    }
  }
  res_data->polygons =
      realloc(res_data->polygons, (*res_count + 1) * sizeof(int));
  if (res_data->polygons != NULL) {
    res_data->polygons[*res_count] = temp;
    *res_count += 1;
  }
}

void change_min(data_struct *res_data) {
  for (unsigned int i = 0; i <= res_data->num_vert_in_pol; i++) {
    if (res_data->polygons[i] < 0) {
      res_data->polygons[i] = res_data->count_vertexes + res_data->polygons[i];
    }
  }
}

/// @brief Удаление полигона
/// @param res_data Основная структура
void remove_polygons(data_struct *res_data) {
  if (res_data->polygons != NULL) {
    free(res_data->polygons);
  }
}

/// @brief Перемещение объекта по оси x, y или z
/// @param res_data Основная структура
/// @param a На сколько нужно переместить
/// @param xyz По какой оси передвигать (x - 0, y - 1, z - 2)
void transition(data_struct *res_data, double a, int xyz) {
  if (xyz == 0) {
    for (int i = 0; i < (int)res_data->count_vertexes * 3; i += 3)
      res_data->coord_vert[i] += a;
  } else if (xyz == 1) {
    for (int i = 1; i < (int)res_data->count_vertexes * 3; i += 3)
      res_data->coord_vert[i] += a;
  } else if (xyz == 2) {
    for (int i = 2; i < (int)res_data->count_vertexes * 3; i += 3)
      res_data->coord_vert[i] += a;
  }
}

/// @brief Вращение по оси x
/// @param res_data Основная структура
/// @param angle Угол вращения
void rotation_by_x(data_struct *res_data, double angle) {
  double rad = degree_to_rad(angle);
  for (int i = 0; i < (int)res_data->count_vertexes * 3; i += 3) {
    double temp_y = res_data->coord_vert[i + 1];
    double temp_z = res_data->coord_vert[i + 2];
    res_data->coord_vert[i + 1] = cos(rad) * temp_y + sin(rad) * temp_z;
    res_data->coord_vert[i + 2] = sin(rad) * (-temp_y) + cos(rad) * temp_z;
  }
}

/// @brief Вращение по оси у
/// @param res_data Основная структура
/// @param angle Угол вращения
void rotation_by_y(data_struct *res_data, double angle) {
  double rad = degree_to_rad(angle);
  for (int i = 1; i < (int)res_data->count_vertexes * 3; i += 3) {
    double temp_x = res_data->coord_vert[i - 1];
    double temp_z = res_data->coord_vert[i + 1];
    res_data->coord_vert[i - 1] = cos(rad) * temp_x + sin(rad) * temp_z;
    res_data->coord_vert[i + 1] = sin(rad) * (-temp_x) + cos(rad) * temp_z;
  }
}

/// @brief Вращение по оси z
/// @param res_data Основная структура
/// @param angle Угол вращения
void rotation_by_z(data_struct *res_data, double angle) {
  double rad = degree_to_rad(angle);
  for (int i = 2; i < (int)res_data->count_vertexes * 3; i += 3) {
    double temp_x = res_data->coord_vert[i - 2];
    double temp_y = res_data->coord_vert[i - 1];
    res_data->coord_vert[i - 2] = cos(rad) * temp_x - sin(rad) * temp_y;
    res_data->coord_vert[i - 1] = sin(rad) * temp_x + cos(rad) * temp_y;
  }
}

/// @brief Превращение градусов в радианы
/// @param angle Угол для превращения
/// @return Возращает радианы
double degree_to_rad(double angle) { return PI * angle / 180; }

/// @brief Удаление структуры
/// @param data Основная структура
void remove_data(data_struct *data) {
  if (data->coord_vert != NULL) {
    free(data->coord_vert);
  }
  remove_polygons(data);
}

/// @brief Функция ищет dmax - максимальную разницу между min и max среди всех
/// осей
/// @param data Основная структура
/// @return Возвращает dmax
double find_dmax(data_struct *data) {
  double dmax = 0.0;
  find_max_min(data);
  double raz_x = data->max_x - data->min_x, raz_y = data->max_y - data->min_y,
         raz_z = data->max_z - data->min_z;
  if (raz_x >= raz_y && raz_x >= raz_z) {
    dmax = raz_x;
  } else if (raz_y >= raz_x && raz_y >= raz_z) {
    dmax = raz_y;
  } else if (raz_z >= raz_x && raz_z >= raz_y) {
    dmax = raz_z;
  }
  return dmax;
}

/// @brief Функция для адекватной отрисовки(Чтобы модель помещалась в экран)
/// @param val Коэффициент
/// @param res_data Основная структура
void find_scale(double val, data_struct *res_data) {
  double scale = 0.0;
  double dmax = find_dmax(res_data);
  scale = (2 * val) / dmax;
  for (int i = 0; i < (int)res_data->count_vertexes * 3; i++) {
    for (int j = 0; j < 3; j++) {
      res_data->coord_vert[i] *= scale;
      if (j != 2) {
        i++;
      }
    }
  }
}

/// @brief Трансформирует числа вершин  в полигонах в необходимый вид(Например:
/// Было - 1 2 2 3 3 4 4 1, стало - 0 1 1 2 2 3 3 0)
/// @param res_data Основная структура
void transf_polygons(data_struct *res_data) {
  for (int i = 0; i < (int)res_data->num_vert_in_pol; i++) {
    res_data->polygons[i] -= 1;
  }
}

/// @brief Отцентровка модели
/// @param res_data Основная структура
void center_model(data_struct *res_data) {
  double center_x = 0.0, center_y = 0.0, center_z = 0.0;
  find_max_min(res_data);
  center_x = res_data->min_x + (res_data->max_x - res_data->min_x) / 2;
  center_y = res_data->min_y + (res_data->max_y - res_data->min_y) / 2;
  center_z = res_data->min_z + (res_data->max_z - res_data->min_z) / 2;
  for (int i = 0; i < (int)res_data->count_vertexes * 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j == 0) {
        res_data->coord_vert[i] -= center_x;
      } else if (j == 1) {
        res_data->coord_vert[i] -= center_y;
      } else if (j == 2) {
        res_data->coord_vert[i] -= center_z;
      }
      if (j != 2) {
        i++;
      }
    }
  }
}

/// @brief Находит max и min значения в каждой оси
/// @param data Основная структура
void find_max_min(data_struct *data) {
  int start_count = 0;
  for (int i = 0; i < (int)data->count_vertexes * 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (start_count == 0) {
        data->min_x = data->coord_vert[0];
        data->max_x = data->coord_vert[0];
        data->min_y = data->coord_vert[1];
        data->max_y = data->coord_vert[1];
        data->min_z = data->coord_vert[2];
        data->max_z = data->coord_vert[2];
        start_count++;
      }
      if (j == 0) {
        if (data->coord_vert[i] > data->max_x) {
          data->max_x = data->coord_vert[i];
        } else if (data->coord_vert[i] < data->min_x) {
          data->min_x = data->coord_vert[i];
        }
      } else if (j == 1) {
        if (data->coord_vert[i] > data->max_y) {
          data->max_y = data->coord_vert[i];
        } else if (data->coord_vert[i] < data->min_y) {
          data->min_y = data->coord_vert[i];
        }
      } else if (j == 2) {
        if (data->coord_vert[i] > data->max_z) {
          data->max_z = data->coord_vert[i];
        } else if (data->coord_vert[i] < data->min_z) {
          data->min_z = data->coord_vert[i];
        }
      }
      if (j != 2) {
        i++;
      }
    }
  }
}

/// @brief Функция приближения отдаления
/// @param res_data Основная структура
/// @param coef Коэффициент приближения отдаления
void scale_data(data_struct *res_data, double coef) {
  if (coef != 0) {
    for (int i = 0; i < (int)res_data->count_vertexes * 3; i++) {
      res_data->coord_vert[i] *= coef;
    }
  }
}

void find_max_vert(data_struct *res_data) {
  double min = res_data->coord_vert[0];
  double max = res_data->coord_vert[0];
  for (unsigned int i = 0; i < res_data->count_vertexes * 3; i++) {
    if (res_data->coord_vert[i] > max) {
      max = res_data->coord_vert[i];
    } else if (res_data->coord_vert[i] < min) {
      min = res_data->coord_vert[i];
    }
  }
  res_data->max_vert = fabs(min) > max ? fabs(min) : max;
  res_data->max_vert *= 1.2;
}
