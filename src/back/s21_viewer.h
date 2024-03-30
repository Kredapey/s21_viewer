#ifndef S21_VIEWER_H
#define S21_VIEWER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  unsigned int count_vertexes;  // количество вершин
  unsigned int count_facets;    // количество полигонов
  double *coord_vert;
  int *polygons;
  unsigned int num_vert_in_pol;
  double min_x, max_x, min_y, max_y, min_z, max_z;
  double max_vert;
} data_struct;

#define PI 3.141592

enum res_matrix { OK = 0, MATRIX_ERROR = 1, CALC_ERROR = 2, MEM_ERROR = 3 };

int main_parser(char *file_name, data_struct *res_data, double scale);
int first_read_file(char *file_name, unsigned int *count_vertexes,
                    unsigned int *count_facets);
int second_read_file(char *file_name, data_struct *res_data);
void coord_matrix(data_struct *res_data, char *str, int vert);
int counter_faces(char *str);
void fill_faces(data_struct *res_data, int *res_count, char *str);
void remove_polygons(data_struct *res_data);
void transition(data_struct *res_data, double a, int xyz);
void rotation_by_x(data_struct *res_data, double angle);
void rotation_by_y(data_struct *res_data, double angle);
void rotation_by_z(data_struct *res_data, double angle);
double degree_to_rad(double angle);
void scale_data(data_struct *res_data, double coef);
void remove_data(data_struct *data);
double find_dmax(data_struct *data);
void find_scale(double val, data_struct *res_data);
void transf_polygons(data_struct *res_data);
void find_max_min(data_struct *data);
void center_model(data_struct *res_data);
int check_dyn_memory(data_struct *res_data, int *res_count, double temp);
void change_min(data_struct *res_data);
void find_max_vert(data_struct *res_data);

#endif  // S21_VIEWER_H