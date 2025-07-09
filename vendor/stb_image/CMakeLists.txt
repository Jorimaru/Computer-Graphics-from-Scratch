project(stb_image)

add_library(stb_image
  src/stb_image.c
  src/stb_image_write.c)

target_include_directories(stb_image PUBLIC
  include)
