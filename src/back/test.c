#include <check.h>

#include "s21_viewer.h"

START_TEST(test_parcer_1) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(data.count_facets, 6);
  ck_assert_uint_eq(data.count_vertexes, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_parcer_2) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq(data.coord_vert[0], 1.0);
  ck_assert_double_eq(data.coord_vert[1], 1.0);
  ck_assert_double_eq(data.coord_vert[2], -1.0);
  ck_assert_double_eq(data.coord_vert[21], -1.0);
  ck_assert_double_eq(data.coord_vert[22], -1.0);
  ck_assert_double_eq(data.coord_vert[23], 1.0);
  remove_data(&data);
}
END_TEST

START_TEST(test_parcer_3) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(data.count_facets, 6);
  ck_assert_uint_eq(data.count_vertexes, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_parcer_4) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube1.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(data.coord_vert[0], 0.952381, 1e-07);
  ck_assert_double_eq(data.coord_vert[1], 1.0);
  ck_assert_double_eq_tol(data.coord_vert[2], -0.952381, 1e-07);
  ck_assert_double_eq_tol(data.coord_vert[21], -0.952381, 1e-07);
  ck_assert_double_eq(data.coord_vert[22], -1.0);
  ck_assert_double_eq_tol(data.coord_vert[23], 0.952381, 1e-07);
  remove_data(&data);
}
END_TEST

START_TEST(test_parcer_5) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube2.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(data.coord_vert[0], 0.952381, 1e-07);
  ck_assert_double_eq_tol(data.coord_vert[1], 0.952381, 1e-07);
  ck_assert_double_eq(data.coord_vert[2], -1.0);
  ck_assert_double_eq_tol(data.coord_vert[21], -0.952381, 1e-07);
  ck_assert_double_eq_tol(data.coord_vert[22], -0.952381, 1e-07);
  ck_assert_double_eq(data.coord_vert[23], 1.0);
  remove_data(&data);
}
END_TEST

START_TEST(test_parcer_no_file) {
  data_struct data = {0};
  char *name_file = "no_file.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 1);
  remove_data(&data);
}
END_TEST

START_TEST(test_scale) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  scale_data(&data, 2);
  ck_assert_double_eq(data.coord_vert[0], 2.0);
  ck_assert_double_eq(data.coord_vert[1], 2.0);
  ck_assert_double_eq(data.coord_vert[2], -2.0);
  ck_assert_double_eq(data.coord_vert[21], -2.0);
  ck_assert_double_eq(data.coord_vert[22], -2.0);
  ck_assert_double_eq(data.coord_vert[23], 2.0);
  remove_data(&data);
}
END_TEST

START_TEST(test_transition_x) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  transition(&data, 2.5, 0);
  ck_assert_double_eq(data.coord_vert[0], 3.5);
  ck_assert_double_eq(data.coord_vert[21], 1.5);
  remove_data(&data);
}
END_TEST

START_TEST(test_transition_y) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  transition(&data, 2.5, 1);
  ck_assert_double_eq(data.coord_vert[1], 3.5);
  ck_assert_double_eq(data.coord_vert[22], 1.5);
  remove_data(&data);
}
END_TEST

START_TEST(test_transition_z) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  transition(&data, 2.5, 2);
  ck_assert_double_eq(data.coord_vert[2], 1.5);
  ck_assert_double_eq(data.coord_vert[23], 3.5);
  remove_data(&data);
}
END_TEST

START_TEST(test_rotation_x) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  rotation_by_x(&data, 15);
  ck_assert_double_eq_tol(data.coord_vert[1], 0.707107, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[2], -1.224745, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[22], -0.707107, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[23], 1.224745, 1e-06);
  remove_data(&data);
}
END_TEST

START_TEST(test_rotation_y) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  rotation_by_y(&data, 15);
  ck_assert_double_eq_tol(data.coord_vert[0], 0.707107, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[2], -1.224745, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[21], -0.707107, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[23], 1.224745, 1e-06);
  remove_data(&data);
}
END_TEST

START_TEST(test_rotation_z) {
  data_struct data = {0};
  char *name_file = "./back/obj/cube.obj";
  int result = main_parser(name_file, &data, 1);
  ck_assert_int_eq(result, 0);
  rotation_by_z(&data, 15);
  ck_assert_double_eq_tol(data.coord_vert[0], 0.707107, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[1], 1.224745, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[21], -0.707107, 1e-06);
  ck_assert_double_eq_tol(data.coord_vert[22], -1.224745, 1e-06);
  remove_data(&data);
}
END_TEST

int main() {
  Suite *s1 = suite_create("3DViewer: ");

  TCase *tc1_1 = tcase_create("3DViewer: ");
  SRunner *sr = srunner_create(s1);
  int result = 0;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_parcer_1);
  tcase_add_test(tc1_1, test_parcer_2);
  tcase_add_test(tc1_1, test_parcer_3);
  tcase_add_test(tc1_1, test_parcer_4);
  tcase_add_test(tc1_1, test_parcer_5);
  tcase_add_test(tc1_1, test_parcer_no_file);
  tcase_add_test(tc1_1, test_scale);
  tcase_add_test(tc1_1, test_transition_x);
  tcase_add_test(tc1_1, test_transition_y);
  tcase_add_test(tc1_1, test_transition_z);
  tcase_add_test(tc1_1, test_rotation_x);
  tcase_add_test(tc1_1, test_rotation_y);
  tcase_add_test(tc1_1, test_rotation_z);

  srunner_run_all(sr, CK_VERBOSE);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
