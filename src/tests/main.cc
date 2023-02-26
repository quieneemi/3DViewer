#include <gtest/gtest.h>

#include "mesh_loader.h"

s21::Mesh mesh;
s21::MeshLoader mesh_loader;

const QString path = "../../object-files/";

TEST(mesh_loader, error_type) {
  QPair<uint, uint> mesh_info = mesh_loader.Load(&mesh, "abc.png");
  ASSERT_EQ(mesh_info.first, 0);
  ASSERT_EQ(mesh_info.second, 0);
}

TEST(mesh_loader, cow) {
  QPair<uint, uint> mesh_info = mesh_loader.Load(&mesh, path + "cow.obj");
  ASSERT_EQ(mesh_info.first, 4583);
  ASSERT_EQ(mesh_info.second, 5804);
}

TEST(mesh_loader, sword) {
  QPair<uint, uint> mesh_info = mesh_loader.Load(&mesh, path + "sword.obj");
  ASSERT_EQ(mesh_info.first, 1329);
  ASSERT_EQ(mesh_info.second, 1298);
}

TEST(mesh_loader, dodecahedron) {
  QPair<uint, uint> mesh_info =
      mesh_loader.Load(&mesh, path + "dodecahedron.obj");
  ASSERT_EQ(mesh_info.first, 20);
  ASSERT_EQ(mesh_info.second, 36);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
